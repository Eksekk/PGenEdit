#include "pch.h"
#include "main.h"
#include <globals.h>
#include "Generator.h"
#include <cstdlib>
#include "LowLevel.h"
#include "MainWindow.h"
#include "Application.h"
#include "GameData.h"
#include <string>
#include "Utility.h"
#include "PlayerData.h"
#include "PlayerPanel.h"
#include "ClassWindow.h"
#include "GameData.h"
#include "Tests.h"
#include <fstream>

extern bool inMM;

std::vector<void*> getPlayerPointersMm8()
{
    int count;
    void* ptrs[5];
    _asm
    {
        push ebx
        push esi
        push edi
        mov edi, 0xB7CA60 // address of count
        mov edi, dword ptr [edi]
        mov count, edi
        mov ebx, 0xB7CA4C // players roster txt indexes, or FFFFFFFF if player not in party
        xor esi, esi
        get:
            mov ecx, dword ptr [ebx]
            add ebx, 4
            test ecx, ecx
            js skipField
                push ecx
                mov ecx, 0xB20E90
                call absolute 0x4026F4 // getPlayerPtr()
                mov dword ptr [ptrs + esi * 4], eax
                inc esi
            skipField:
            dec edi
            jne get
        exit:
        pop ebx
        pop esi
        pop edi
    }
    return std::vector<void*>(ptrs, ptrs + count);
}

// ----------------------------------------------------------------------------
// application startup
// ----------------------------------------------------------------------------

namespace
{
    HINSTANCE hInstance;
    // Critical section that guards everything related to wxWidgets "main" thread
    // startup or shutdown.
    wxCriticalSection gs_wxStartupCS;
    // Handle of wx "main" thread if running, NULL otherwise
    HANDLE gs_wxMainThread = NULL;

    //  wx application startup code -- runs from its own thread
    unsigned wxSTDCALL MyAppLauncher(void* event)
    {
        // Note: The thread that called run_wx_gui_from_dll() holds gs_wxStartupCS
        //       at this point and won't release it until we signal it.

        // We need to pass correct HINSTANCE to wxEntry() and the right value is
        // HINSTANCE of this DLL, not of the main .exe, use this MSW-specific wx
        // function to get it. Notice that under Windows XP and later the name is
        // not needed/used as we retrieve the DLL handle from an address inside it
        // but you do need to use the correct name for this code to work with older
        // systems as well.
        /*const HINSTANCE
            hInstance = wxDynamicLibrary::MSWGetModuleHandle("PartyGenerator",
                &gs_wxMainThread);
        if (!hInstance)
        {
            MessageBoxA(nullptr, "failed to get DLL's handle", nullptr, MB_OK | MB_ICONERROR | MB_APPLMODAL);
            return 0; // failed to get DLL's handle
        }*/
                

        // wxIMPLEMENT_WXWIN_MAIN does this as the first thing
        wxDISABLE_DEBUG_SUPPORT();

        // We do this before wxEntry() explicitly, even though wxEntry() would
        // do it too, so that we know when wx is initialized and can signal
        // run_wx_gui_from_dll() about it *before* starting the event loop.
        //wxInitializer wxinit;
        //if (!wxinit.IsOk())
        if (!wxInitialize())
        {
            MessageBoxA(nullptr, "failed to init wx", nullptr, MB_OK | MB_ICONERROR | MB_APPLMODAL);
            return 0; // failed to init wx
        }
                
        // Signal run_wx_gui_from_dll() that it can continue
        HANDLE hEvent = *(static_cast<HANDLE*>(event));
        if (!SetEvent(hEvent))
        {
            MessageBoxA(nullptr, "failed setting up the mutex", nullptr, MB_OK | MB_ICONERROR | MB_APPLMODAL);
            return 0; // failed setting up the mutex
        }

        // Run the app:
        wxEntry(hInstance);
        return 1;
    }

} // anonymous namespace

extern "C"
{
    void run_wx_gui_from_dll(/*const char* title*/)
    {
        // In order to prevent conflicts with hosting app's event loop, we
        // launch wx app from the DLL in its own thread.
        //
        // We can't even use wxInitializer: it initializes wxModules and one of
        // the modules it handles is wxThread's private module that remembers
        // ID of the main thread. But we need to fool wxWidgets into thinking that
        // the thread we are about to create now is the main thread, not the one
        // from which this function is called.
        //
        // Note that we cannot use wxThread here, because the wx library wasn't
        // initialized yet. wxCriticalSection is safe to use, though.

        wxCriticalSectionLocker lock(gs_wxStartupCS);

        if (!gs_wxMainThread)
        {
            HANDLE hEvent = CreateEvent
            (
                NULL,  // default security attributes
                FALSE, // auto-reset
                FALSE, // initially non-signaled
                NULL   // anonymous
            );
            if (!hEvent)
            {
                MessageBoxA(nullptr, "Failed creating event", nullptr, MB_OK | MB_ICONERROR | MB_APPLMODAL);
                return; // error
            }
            

            // NB: If your compiler doesn't have _beginthreadex(), use CreateThread()
            gs_wxMainThread = (HANDLE)_beginthreadex
            (
                NULL,           // default security
                0,              // default stack size
                &MyAppLauncher,
                &hEvent,        // arguments
                0,              // create running
                NULL
            );

            if (!gs_wxMainThread)
            {
                CloseHandle(hEvent);
                MessageBoxA(nullptr, "Failed creating the thread", nullptr, MB_OK | MB_ICONERROR | MB_APPLMODAL);
                return; // error
            }

            // Wait until MyAppLauncher signals us that wx was initialized. This
            // is because we use wxMessageQueue<> and wxString later and so must
            // be sure that they are in working state.
            WaitForSingleObject(hEvent, INFINITE);
            CloseHandle(hEvent);
        }

        // Send a message to wx thread to show a new frame:
        //wxThreadEvent* event =
        //    new wxThreadEvent(wxEVT_THREAD, CMD_SHOW_WINDOW);
        //event->SetString(title);
        //event->SetInt(true);
        //wxQueueEvent(wxApp::GetInstance(), event);
    }

    void wx_dll_cleanup()
    {
        wxCriticalSectionLocker lock(gs_wxStartupCS);

        if (!gs_wxMainThread)
            return;

        // If wx main thread is running, we need to stop it. To accomplish this,
        // send a message telling it to terminate the app.
        wxThreadEvent* event =
            new wxThreadEvent(wxEVT_THREAD, CMD_TERMINATE);
        wxQueueEvent(wxApp::GetInstance(), event);

        // We must then wait for the thread to actually terminate.
        WaitForSingleObject(gs_wxMainThread, INFINITE);
        CloseHandle(gs_wxMainThread);
        gs_wxMainThread = NULL;
        wxUninitialize();
    }

    Application* app = nullptr;
    DLL_EXPORT BOOL __stdcall APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
    {
        switch (fdwReason)
        {
        case DLL_PROCESS_ATTACH:
            {
                // code from MMExtension
                const int addr = 0x41EDE1;
                if (GetModuleHandleA("mm6.exe") || GetModuleHandleA("mm7.exe") || GetModuleHandleA("mm8.exe")) // are we injected into mm[678].exe?
                {
                    switch (byte(addr))  // just a random address
                    {
                    case 0xEC:
                        MMVER = 6;
                        MAX_PLAYERS = 4;
                        break;
                    case 0x45:
                        MMVER = 7;
                        MAX_PLAYERS = 4;
                        break;
                    case 0x53:
                        MMVER = 8;
                        MAX_PLAYERS = 5;
                        break;
                    default:
                        MessageBoxA(0, "This is not a supported Might and Magic game", "MMExtension Error", MB_ICONERROR);
                        ExitProcess(0);
                    }
                    inMM = true;
                }
                else // for testing
                {
                    MMVER = 7;
                    MAX_PLAYERS = 4;
                }

                if (MMVER == 7 && GetModuleHandleA("elemental.dll"))
                {
                    IS_ELEMENTAL_MOD = true;
                }
                // TODO: test for Merge (run lua script?)
                generator = new Generator();
                break;
            }

        case DLL_PROCESS_DETACH:
            // detach from process
            //wxUninitialize();
            //MSGBOX("x");
            delete generator;
            //app->OnExit();
            // OnExit isn't called by CleanUp so must be called explicitly.
            //app->OnExit();
            //app->CleanUp();
            //MessageBoxA(nullptr, "Library unloaded successfully.", "Unloaded!", 0);
            break;
        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
        }
        return TRUE; // successful
    }

    /*
        IMPORTANT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        don't directly call wxWidgets methods here, always queue events to be processed by
        main application class. Otherwise, Bad Things(TM) might occur

        ------------------------------------------------------------------------------------

        PROBLEM WITH THREADING
        problem statement: we are clicking button (and calling generate function) from our dll's thread,
        which may cause race condition with base game or even mmextension (modifying player data)
        possible solutions:
        1) suspend all other threads, generate and resume them - easy, but inelegant and may not work correctly - 
           what if other thread was about to write into one of player struct's fields?
        2) call SetThreadContext() (and get the context in dllmain), generate and set old context - almost exactly like 1)
        3) expose a flag that user clicked generate button, hook game event loop and check it, and if it's set call generation
           function in main thread (also causing dll thread to wait for completion etc.) - possible slight performance penalty
           and low-level problems, also might have to have access to wxWidgets data (ideally not, but stuff like this happens) and it could cause problems
        4) force user to use hotkey combination to generate instead of button (can call generate function directly) - like 3), but simpler and much worse UX
        5) same as above, but write hook only when user wants to generate and restore standard code afterwards - no performance penalty,
           but more complex, otherwise same as 3)
        6) call PauseGame, generate and call ResumeGame (and add logic for checking if it wasn't already paused etc.) -
           should deal with base game, but mmextension (and for example elemental mod) might still theoretically interfere
        7) do away with wxWidgets thread and somehow integrate it into game main thread's event loop - I think it's best solution,
           but don't know yet how to do that - MAKING PROGRESS
           
           DONE?
    */

    DLL_EXPORT void __stdcall init()
    {
        //run_wx_gui_from_dll();
        // wxWidgets init
        HINSTANCE hinstExe = GetModuleHandleA(nullptr); // HMODULE is convertible to HINSTANCE
        //wxEntry(hinstExe); // STARTS EVENT LOOP AND RUNS IT, OTHER CODE CAN'T EXECUTE
        if (!wxEntryStart(hinstExe))
        {
            MessageBoxA(nullptr, "Party generator couldn't load", nullptr, 0);

            // flush logs (saw it in some wxwidgets source file)
            //delete wxLog::SetActiveTarget(NULL);
        }
        app = &wxGetApp();
        assert(dynamic_cast<Application*>(app));
        app->CallOnInit();
        std::vector<wxString> errors;
        if (MMVER == 6)
        {
            errors = Tests::run<mm6::Player, mm6::Game>();
        }
        else if (MMVER == 7)
        {
            errors = Tests::run<mm7::Player, mm7::Game>();
        }
        else if (MMVER == 8)
        {
            errors = Tests::run<mm8::Player, mm8::Game>();
        }
        if (errors.size() > 0)
        {
            wxString str = concatWxStrings(errors);
            wxLogError(str);
            std::fstream file("pgen_errors.txt", std::ios::out | std::ios::in | std::ios::trunc);
            file << str;
            file.close();
        }
        //MSGBOX((std::string("app: ") + std::to_string((int)app)).c_str());
        //MSGBOX((std::string("window: ") + std::to_string((int)app->mainWindow)).c_str());
    }

    DLL_EXPORT void __stdcall runEventLoopOnce()
    {
        //assert(dynamic_cast<wxLogGui*>(wxLog::GetActiveTarget()));
        wxLog::FlushActive();
        app->ProcessPendingEvents();
        //wxGetApp().mainWindow->playerPanels.size()
        //wxLogFatalError("app pointer: %X, mainWindow pointer: %X, playerPanels pointer: %X", (unsigned int)app, (unsigned int)app->mainWindow, (unsigned int)&app->mainWindow->playerPanels);
    }

    DLL_EXPORT void __stdcall displayMainWindow(bool visible)
    {
        if (!GameData::allDataReceived)
        {
            std::vector<wxString> errors;
            if (GameData::classes.empty()) // TODO change check, as data will be partially filled from game structures
            {
                errors.push_back("Game class info wasn't received from lua yet!");
            }
            if (GameData::skills.empty())
            {
                errors.push_back("Game skill info wasn't received from lua yet!");
            }
            // TODO: check all data to be received from lua
            wxMessageBox(concatWxStrings(errors, "\n"), "Error", wxOK | wxICON_ERROR);
            return;
        }
        wxGetApp().mainWindow->Show(visible);
    }

    DLL_EXPORT void __stdcall unloadCleanup()
    {
        //delete generator;
        //wx_dll_cleanup();
        wxLog::FlushActive();
        wxEntryCleanup();
    }

    DLL_EXPORT void __stdcall setLuaState(void* ptr)
    {
        // allow setting lua formula on some fields (like resistance points amount or level)
        // environment from mmextension with our table containing current generation/player state
        // (serialize to json from c++ and deserialize in lua into table)

        // horrible hack, but should work:
        /*
        for k, v in pairs(debug.getregistry()) do
            if type(k) == "userdata" and getU(v, "HookData") then
                M.dll.setLuaState(
                    mem.u4[
                        tonumber(
                            tostring(k):match("x([%dA-Fa-f]+)")
                            , 16
                        )
                    ]
                )
                break
            end
        end
        */
        Lua = (lua_State*)ptr;
    }

    DLL_EXPORT void __stdcall setClassData(const char* jsonStr)
    {
        GameData::processClassDataJson(jsonStr);
    }

    DLL_EXPORT void __stdcall setSkillData(const char* jsonStr)
    {
        GameData::processSkillDataJson(jsonStr);
    }

    DLL_EXPORT bool __stdcall setCallbacks(const char* jsonStr)
    {
        Json json = Json::parse(jsonStr);
        isTwoHanded = (isTwoHanded_ptr)(unsigned int)json["isTwoHanded"];
        isEquippableInOffhand = (isEquippableInOffhand_ptr)(unsigned int)json["isEquippableInOffhand"];
        return true;
    }

    DLL_EXPORT void __stdcall setPlayerPointers(void** ptrs)
    {
        if (!generator->players)
        {
            generator->players = new void* [MAX_PLAYERS];
        }
        // TODO: mm8 compatibility (player pointers and player names and even player count can change at runtime!)
        for (int i = 0; i < MAX_PLAYERS; ++i)
        {
            generator->players[i] = ptrs[i];
        }
    }
}