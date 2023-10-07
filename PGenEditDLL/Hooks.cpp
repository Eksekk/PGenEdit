#include "pch.h"
#include "main.h"
#include "Hooks.h"
#include "LowLevel.h"
#include "Utility.h"
#include "HookParams.h"

static void recoveryMultiplier_7(HookData* d)
{

}

// USING REFERENCE actually adds a layer of indirection you need to handle (dereference alias to get proper value)
int partyOffset = offsetof(mm7::GameParty, playersArray);
int playerSize = sizeof(mm7::Player);
int recoveryOffset = offsetof(mm7::Player, recoveryDelay);
auto& rec = HookParams::noRecoveryEnabled;
static __declspec(naked) void noRecovery_7()
{
    _asm
    {
        ; player index
        push ecx
        sub ecx, partyOffset
        mov eax, ecx
        mov ecx, playerSize
        push edx
        cdq
        idiv ecx
        pop edx
        mov ecx, [rec];// ecx = address of first byte
        mov al, byte ptr[ecx + eax]
        test al, al
        pop ecx
        je standard
        
        mov eax, dword ptr [recoveryOffset]
        and word ptr [ecx + eax], 0
        xor eax, eax
        inc eax; success
        ret 4

        standard:
        mov edx, dword ptr[esp + 4]
        test edx, edx
        mov eax, 0x48E968;// return to old code
        jmp eax
    }
}

// recovery multiplier

// also game versions the hook applies to

// IMPORTANT: adding hooks in main file scope doesn't work
void setupHooks() {
    hooks.emplace(HK_NO_RECOVERY, Hook(
        HookElementBuilder().address(mmv(0, 0x48E962, 0)).target(mmv(0U, (uint32_t)noRecovery_7, 0U)).type(HOOK_ELEM_TYPE_JUMP).description("No recovery for player").build()
    ));
    hooks.at(HK_NO_RECOVERY).enable();

    // ATTEMPT AT CATCHING WINDOW MESSAGES

    auto getFileNameFromPath = [](const std::string& str) -> std::string
    {
        int lastSlashPos = -1;
        int i = 0;
        for (char c : str)
        {
            if (c == '/' || c == '\\')
            {
                lastSlashPos = i;
            }
            ++i;
        }
        if (lastSlashPos == -1)
        {
            return "";
        }
        std::string result = str.substr(lastSlashPos + 1);
        while (!result.empty() && (result.back() == '/' || result.back() == '\\'))
        {
            result.pop_back();
        }
        return stringToLower(result);
    };

    typedef LRESULT(APIENTRY* WxWndProc)(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    auto module = GetModuleHandleA("wxmsw321ud_core_vc_custom.dll");
    assert(module);
    WxWndProc wxWndProc = reinterpret_cast<WxWndProc>(GetProcAddress(module, "wxWndProc"));
    auto func = [=](HookData* d) -> int
    {
        MSG* msg = (MSG*)dword(d->esp);
        HWND handle = msg->hwnd;
        char buffer[600];
        GetWindowModuleFileNameA(handle, buffer, 600);
        std::string name = getFileNameFromPath(buffer);
        if (name == "pgenedit.dll" && msg->message != WM_TIMER)
        {
            wxWndProc(handle, msg->message, msg->wParam, msg->lParam);
            // one stack arg
            // return directly to base code (skip overwritten call)
            d->push(dword(d->esp - 4));
            return HOOK_RETURN_AUTOHOOK_NO_PUSH;
            //wxWndProc();
        }
        if (unloadCleanupStarted)
        {
            MessageBoxA(nullptr, "Unload cleanup started", nullptr, 0);
            // window message autohook entered, ctrl + F3 message dispatched, hooks are removed, code memory is freed, returns to user32, which tries to return to hook proc
            d->push(dword(d->esp - 4));
            return HOOK_RETURN_AUTOHOOK_NO_PUSH;
        }
        return HOOK_RETURN_SUCCESS;
    };
    hooks.emplace(3, Hook
        ({
            HookElementBuilder().address(mmv(0, 0x462AFC, 0)).type(HOOK_ELEM_TYPE_AUTOHOOK_BEFORE).func(func).build(),
            HookElementBuilder().address(mmv(0, 0x463309, 0)).type(HOOK_ELEM_TYPE_AUTOHOOK_BEFORE).func(func).build(),
            HookElementBuilder().address(mmv(0, 0x4975C3, 0)).type(HOOK_ELEM_TYPE_AUTOHOOK_BEFORE).func(func).build(),
            HookElementBuilder().address(mmv(0, 0x497CC1, 0)).type(HOOK_ELEM_TYPE_AUTOHOOK_BEFORE).func(func).build(),
            HookElementBuilder().address(mmv(0, 0x4BE762, 0)).type(HOOK_ELEM_TYPE_AUTOHOOK_BEFORE).func(func).build(),
            HookElementBuilder().address(mmv(0, 0x4BE838, 0)).type(HOOK_ELEM_TYPE_AUTOHOOK_BEFORE).func(func).build(),
            HookElementBuilder().address(mmv(0, 0x4BFCA5, 0)).type(HOOK_ELEM_TYPE_AUTOHOOK_BEFORE).func(func).build(),
            HookElementBuilder().address(mmv(0, 0x4BFCFC, 0)).type(HOOK_ELEM_TYPE_AUTOHOOK_BEFORE).func(func).build(),
        }));
    // doesn't solve any problems I intended to solve (tooltips and creation time); keeping it, because it may prove useful later
    // hooks.at(3).enable(); // FIXME! crashes on dll unload
}
// hooks[RECOVERY_MULTIPLIER] = Hook
// ({
// 	HookElementBuilder().address(0x48E962)
// ) };