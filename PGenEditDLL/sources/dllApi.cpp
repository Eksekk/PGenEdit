#include "pch.h"
#include "main.h"
#include "Generator.h"
#include "LowLevel.h"
#include "MainWindow.h"
#include "GuiApplication.h"
#include "GameData.h"
#include "Utility.h"
#include "PlayerData.h"
#include "PlayerPanel.h"
#include "ClassWindow.h"
#include "Tests.h"
#include "Enum_const.h"
#include "PlayerStructAccessor.h"
#include "globals.h"
#include "EditorMainWindow.h"
#include "ControlPanel.h"
#include "LuaFunctions.h"
#include "PartyStructAccessor.h"
#include "GameStructAccessor.h"
#include <ItemStructAccessor.h>
#include <LodStructAccessor.h>
#include <MapStructAccessor.h>
#include "LuaWrapper.h"
#include <Hook.h>

extern bool inMM;
extern void setMaxSkillLevel();
extern void setupHooks();

std::vector<void*> getPlayerPointersMm8()
{
    int count;
    void* ptrs[5];
    // assembly just for fun, could be done in c++ with dword() macro
    _asm
    {
        push ebx
        push esi
        push edi
        mov edi, 0xB7CA60 // address of count
        mov edi, dword ptr [edi]
        // mov count, edi
        mov ebx, 0xB7CA4C // players roster txt indexes, or FFFFFFFF if player not in party
        xor esi, esi
        get:
            mov ecx, dword ptr [ebx]
            add ebx, 4
            test ecx, ecx
            js skipField
                push ecx
                mov ecx, 0xB20E90
                mov eax, 0x4026F4 // getPlayerPtr()
                call eax
                mov dword ptr [ptrs + esi * 4], eax
                inc esi
            skipField:
            dec edi
        jne get
        mov count, esi
        pop edi
        pop esi
        pop ebx
    }
    return std::vector<void*>(ptrs, ptrs + count);
}

void updatePartySizeAndPlayerPtrs()
{
    std::vector<void*> ptrs = getPlayerPointersMm8();
    CURRENT_PARTY_SIZE = ptrs.size();
    assert((int)ptrs.size() <= MAX_PLAYERS);
    size_t i;
    for (i = 0; i < std::min(ptrs.size(), (size_t)MAX_PLAYERS); ++i)
    {
        playersInParty.at(i) = ptrs[i];
    }
    for (; i < (size_t)MAX_PLAYERS; ++i)
    {
        playersInParty.at(i) = 0;
    }
}

HMODULE fasmDll;

extern "C"
{
	DLL_EXPORT void __stdcall setPlayerPointers(void** ptrs, int count);

    GuiApplication* app = nullptr;
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
                        MAX_MASTERY = Mastery::MASTERY_MASTER;
                        setFieldSizes_6();
						makeEnums();
                        break;
                    case 0x45:
                        MMVER = 7;
                        MAX_PLAYERS = 4;
						setFieldSizes_7();
                        makeEnums();
                        break;
                    case 0x53:
                        MMVER = 8;
                        MAX_PLAYERS = 5;
                        setFieldSizes_8();
                        makeEnums();
                        break;
                    default:
                        MessageBoxA(0, "This is not a supported Might and Magic game", "MMExtension Error", MB_ICONERROR);
                        ExitProcess(0);
                    }
                    inMM = true;
                }

                if (MMVER == 7 && GetModuleHandleA("elemental.dll"))
                {
                    IS_ELEMENTAL_MOD = true;
                }
                setMaxSkillLevel();

                // TODO: test for Merge (run lua script?)
                break;
            }

        case DLL_PROCESS_DETACH:
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
    
    static bool dontFreeFasmDll = false;
    DLL_EXPORT void __stdcall init()
    {
        uint32_t playerSize, playerStart, playerCount;

        // system info for hook code allocations
        GetNativeSystemInfo(&systemInfo);

        // load fasm dll and its main assemble function
        if (fasmDll = GetModuleHandleA("fasm.dll"))
        {
            dontFreeFasmDll = true;
        }
        else if (std::filesystem::exists(".\\fasm.dll"))
        {
            fasmDll = LoadLibraryA(".\\fasm.dll");
        }
        else if (std::filesystem::exists(".\\ExeMods\\MMExtension\\fasm.dll"))
        {
            fasmDll = LoadLibraryA(".\\ExeMods\\MMExtension\\fasm.dll");
        }
        else
        {
            wxLogFatalError("FASM dll not found");
        }
        fasm_Assemble = (Fasm_Assemble)GetProcAddress(fasmDll, "fasm_Assemble");

        if (MMVER == 6)
        {
            PlayerStructAccessor_6::_initMaps();
            playerAccessor = new PlayerStructAccessor_6;
            partyAccessor = new PartyStructAccessor_6;
            gameAccessor = new GameStructAccessor_6;
            itemAccessor = new ItemStructAccessor_6;
            lodAccessor = new LodStructAccessor_6;
            mapAccessor = new MapStructAccessor_6;
            playerSize = sizeof(mm6::Player);
            playerStart = offsetof(mm6::GameParty, playersArray);
            playerCount = 4;
            void* ptrs[]{ (void*)0x908F34, (void*)0x90A550, (void*)0x90BB6C, (void*)0x90D188 };
            setPlayerPointers(ptrs, playerCount);
        }
        else if (MMVER == 7)
        {
            PlayerStructAccessor_7::_initMaps();
            playerAccessor = new PlayerStructAccessor_7;
            partyAccessor = new PartyStructAccessor_7;
            gameAccessor = new GameStructAccessor_7;
            itemAccessor = new ItemStructAccessor_7;
            lodAccessor = new LodStructAccessor_7;
            mapAccessor = new MapStructAccessor_7;
            playerSize = sizeof(mm7::Player);
            playerStart = offsetof(mm7::GameParty, playersArray);
            playerCount = 4;
            void* ptrs[]{ (void*)0xACD804, (void*)0xACF340, (void*)0xAD0E7C, (void*)0xAD29B8 };
            setPlayerPointers(ptrs, playerCount);
            //HookElement2* el = new HookElementAsmhookBefore(0x444441, "aaa\nstc");
            //el->enable();
        }
        else if (MMVER == 8)
        {
			PlayerStructAccessor_8::_initMaps();
			playerAccessor = new PlayerStructAccessor_8;
            partyAccessor = new PartyStructAccessor_8;
            gameAccessor = new GameStructAccessor_8;
            itemAccessor = new ItemStructAccessor_8;
            lodAccessor = new LodStructAccessor_8;
            mapAccessor = new MapStructAccessor_8;
            playerSize = sizeof(mm8::Player);
            playerStart = offsetof(mm8::GameParty, playersArray);
            playerCount = 50;
		}
        for (size_t i = 0; i < playerCount; ++i)
        {
            playersFullArray[i] = (void*)(playerStart + playerSize * i);
        }
		generator = new Generator();

        setupHooks();

        //run_wx_gui_from_dll();
        // wxWidgets init
        HINSTANCE hinstExe = GetModuleHandleA(nullptr); // HMODULE is convertible to HINSTANCE
        //wxEntry(hinstExe); // STARTS EVENT LOOP AND RUNS IT, OTHER CODE CAN'T EXECUTE
        if (!wxEntryStart(hinstExe))
        {
            MessageBoxA(nullptr, "Party generator couldn't load", nullptr, 0);
            return;
            // flush logs (saw it in some wxwidgets source file)
            //delete wxLog::SetActiveTarget(NULL);
        }
		app = &wxGetApp();
		app->CallOnInit(); // create gui

        // need to create after wxwidgets is initialized
		mainUpdateTimer = new wxTimer;
        mainUpdateTimer->Bind(wxEVT_TIMER, runUpdateTimerCallbacks);
		addUpdateTimerCallback(GameData::updateIsInGameAndPartySize);
		mainUpdateTimer->Start(350, wxTIMER_CONTINUOUS);
        
        //MSGBOX((std::string("app: ") + std::to_string((int)app)).c_str());
        //MSGBOX((std::string("window: ") + std::to_string((int)app->mainWindow)).c_str());
    }

    DLL_EXPORT int __stdcall setHook(int id, bool on)
    {
        try
        {
            hooks.at(id).enable(on);
            return true;
        }
        catch (const std::exception& e)
        {
            wxLogError("Received exception: %s", e.what());
            return false;
        }
    }

    DLL_EXPORT void __stdcall runEventLoopOnce()
    {
        //assert(dynamic_cast<wxLogGui*>(wxLog::GetActiveTarget()));
        wxLog::FlushActive();
        //app->ProcessPendingEvents();
        //wxGetApp().mainWindow->playerPanels.size()
        //wxLogFatalError("app pointer: %X, mainWindow pointer: %X, playerPanels pointer: %X", (unsigned int)app, (unsigned int)app->mainWindow, (unsigned int)&app->mainWindow->playerPanels);
    }

    bool checkBeforeShowingWindows()
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
			if (GameData::primaryStats.empty())
			{
				errors.push_back("Statistics info wasn't received from lua yet!");
            }
            if (GameData::items.empty())
            {
                errors.push_back("Items info wasn't received from lua yet!");
            }
			// TODO: check all data to be received from lua
			wxMessageBox(concatWxStrings(errors, "\n"), "Error", wxOK | wxICON_ERROR);
			return false;
		}
        return true;
    }

    DLL_EXPORT void __stdcall displayMainWindow(bool visible)
    {
        if (checkBeforeShowingWindows())
        {
            wxGetApp().mainWindow->Show(visible);
        }
    }

	DLL_EXPORT void __stdcall displayEditorMainWindow(bool visible)
	{
		if (checkBeforeShowingWindows())
		{
			wxGetApp().editorMainWindow->showModalCustom();
		}
	}
    
	DLL_EXPORT void __stdcall displayControlPanel(bool visible)
	{
        wxGetApp().controlPanel->Show(visible);
	}

    DLL_EXPORT void __stdcall unloadCleanup()
    {
        unloadCleanupStarted = true;
        if (!dontFreeFasmDll)
        {
            FreeLibrary(fasmDll);
        }
		delete mainUpdateTimer;
		delete generator;
		delete playerAccessor;
        delete partyAccessor;
        delete gameAccessor;
        delete itemAccessor;
        delete lodAccessor;
        delete mapAccessor;
        removeHooks();
        wxLog::FlushActive();
        wxEntryCleanup();
        codeMemoryFullFree();
        luaDeInit();
    }

    DLL_EXPORT void __stdcall setLuaState(void* ptr)
    {
        // allow setting lua formula on some fields (like resistance points amount or level)
        // environment from mmextension with our table containing current generation/player state
        // (serialize to json from c++ and deserialize in lua into table)
        
        bool init = Lua == nullptr; // only once
        Lua = (lua_State*)ptr;
        luaWrapper.setLuaState(Lua);
        if (init)
        {
            luaInit();
        }
    }

    DLL_EXPORT void __stdcall setClassData(const char* jsonStr)
    {
        GameData::processClassDataJson(jsonStr);
    }

    DLL_EXPORT void __stdcall setSkillData(const char* jsonStr)
    {
        GameData::processSkillDataJson(jsonStr);
	}

	DLL_EXPORT void __stdcall setMiscData(const char* jsonStr)
	{
		GameData::processMiscDataJson(jsonStr);
    }

    DLL_EXPORT void __stdcall setItemData(const char* jsonStr)
    {
        GameData::processItemDataJson(jsonStr);
    }

    DLL_EXPORT bool __stdcall setCallbacks(const char* jsonStr)
    {
        Json json = Json::parse(jsonStr);
        isTwoHanded = (isTwoHanded_ptr)(unsigned int)json["isTwoHanded"];
        isEquippableInOffhand = (isEquippableInOffhand_ptr)(unsigned int)json["isEquippableInOffhand"];
        return true;
    }

    DLL_EXPORT void __stdcall setPlayerPointers(void** ptrs, int count)
    {
        wxASSERT_MSG(count <= MAX_PLAYERS, wxString::Format("Invalid player count (%d, max is %d)", count, MAX_PLAYERS));
        for (int i = 0; i < count; ++i)
        {
            playersInParty[i] = ptrs[i];
        }
    }

    DLL_EXPORT bool __stdcall runLuaScriptFromDLL(const char* str)
    {
        return runScript(str);
    }

    DLL_EXPORT int __stdcall runTests()
    {
        try
        {
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
				wxString str = concatWxStrings(errors, "\n\n");
				std::fstream file("pgen_errors.txt", std::ios::out | std::ios::trunc);
				file << str;
				file.close();
                if (!Asserter::logAutomatically)
                {
                    wxLogError("%d tests failed. Error messages:\n\n%s", errors.size(), str);
                    wxLog::FlushActive();
                }
                return 0;
            }
        }
        catch (const std::exception& ex)
        {
            wxLogError(ex.what());
            wxLog::FlushActive();
            return 0;
        }
        return 1;
    }
}