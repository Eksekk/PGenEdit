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

extern bool inMM;
extern void setMaxSkillLevel();

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
	if (!players)
	{
		players = new void* [MAX_PLAYERS];
	}
    assert(ptrs.size() <= MAX_PLAYERS);
    for (size_t i = 0; i < ptrs.size(); ++i)
    {
        players[i] = ptrs[i];
    }
}

extern "C"
{
	DLL_EXPORT void __stdcall setPlayerPointers(void** ptrs);

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
    
    DLL_EXPORT void __stdcall init()
    {
        if (MMVER == 6)
        {
            PlayerStructAccessor_6::_initMaps();
            // new scope so compiler doesn't complain
            {
                void* ptrs[]{ (void*)0x908F34, (void*)0x90A550, (void*)0x90BB6C, (void*)0x90D188 };
                setPlayerPointers(ptrs);
            }
            playerAccessor = new PlayerStructAccessor_6;
            partyAccessor = new PartyStructAccessor_6;
            gameAccessor = new GameStructAccessor_6;
        }
        else if (MMVER == 7)
        {
            PlayerStructAccessor_7::_initMaps();
            {
                void* ptrs[]{ (void*)0xACD804, (void*)0xACF340, (void*)0xAD0E7C, (void*)0xAD29B8 };
                setPlayerPointers(ptrs);
            }
            playerAccessor = new PlayerStructAccessor_7;
            partyAccessor = new PartyStructAccessor_7;
            gameAccessor = new GameStructAccessor_7;
        }
        else if (MMVER == 8)
        {
			PlayerStructAccessor_8::_initMaps();
			playerAccessor = new PlayerStructAccessor_8;
            partyAccessor = new PartyStructAccessor_8;
            gameAccessor = new GameStructAccessor_8;
		}
		generator = new Generator();
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
			wxGetApp().editorMainWindow->Show(visible);
		}
	}
    
	DLL_EXPORT void __stdcall displayControlPanel(bool visible)
	{
        wxGetApp().controlPanel->Show(visible);
	}

    DLL_EXPORT void __stdcall unloadCleanup()
    {
		delete mainUpdateTimer;
		delete generator;
		delete playerAccessor;
        delete partyAccessor;
        delete gameAccessor;
		if (players)
		{
			delete[] players; // deletes only stored player pointer array, not actual player structs
		}
        removeHooks();
        wxLog::FlushActive();
        wxEntryCleanup();
    }

    DLL_EXPORT void __stdcall setLuaState(void* ptr)
    {
        // allow setting lua formula on some fields (like resistance points amount or level)
        // environment from mmextension with our table containing current generation/player state
        // (serialize to json from c++ and deserialize in lua into table)
        
        bool init = Lua == nullptr; // only once
        Lua = (lua_State*)ptr;
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

    DLL_EXPORT bool __stdcall setCallbacks(const char* jsonStr)
    {
        Json json = Json::parse(jsonStr);
        isTwoHanded = (isTwoHanded_ptr)(unsigned int)json["isTwoHanded"];
        isEquippableInOffhand = (isEquippableInOffhand_ptr)(unsigned int)json["isEquippableInOffhand"];
        return true;
    }

    DLL_EXPORT void __stdcall setPlayerPointers(void** ptrs)
    {
        if (!players)
        {
            players = new void* [MAX_PLAYERS];
        }
        for (int i = 0; i < MAX_PLAYERS; ++i)
        {
            players[i] = ptrs[i];
        }
    }

    DLL_EXPORT bool __stdcall runLuaScriptFromDLL(const char* str)
    {
        return runScript(str);
    }

    DLL_EXPORT void __stdcall runTests()
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
				wxLogError("%d tests failed. Error messages:\n\n%s", errors.size(), str);
				wxLog::FlushActive();
            }
        }
        catch (const std::exception& ex)
        {
            wxLogError(ex.what());
            wxLog::FlushActive();
        }
    }
}