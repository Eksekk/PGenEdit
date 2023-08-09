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
            
        ;// TODO: also zero recovery?
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
}
// hooks[RECOVERY_MULTIPLIER] = Hook
// ({
// 	HookElementBuilder().address(0x48E962)
// ) };