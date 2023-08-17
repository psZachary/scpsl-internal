#pragma once
//#define _CONSOLA

namespace hooks {
	namespace hkMirror {
		namespace NetworkClient {
#if _DEVELOPER
			typedef void(__fastcall* tSend)(uintptr_t, uintptr_t, uintptr_t, uintptr_t, uintptr_t);

			tSend oRequestMessage = 0;
			tSend oDisarmMessage = 0;
			tSend oShotMessage = 0;
			tSend oCoinMessage = 0;
			tSend oBlinkMessage = 0;
			tSend oSnapMessage = 0;
			tSend oCmdMessage = 0;

			void hkDisarmMessage(uintptr_t rcx, uintptr_t rdx, uintptr_t r8, uintptr_t r9, uintptr_t stack) {
				uintptr_t myStack = stack;

				if (aimbotTarget.object != NULL)
					myStack = aimbotTarget.referenceHub;

#ifdef _CONSOLA
				printf(xorstr_("RCX (PTR): %p\n"), rcx);
				printf(xorstr_("RDX (PTR): %p\n"), rdx);
				printf(xorstr_("R8 (PTR): %p\n"), r8);
				printf(xorstr_("R9 (PTR): %p\n"), r9);
				printf(xorstr_("STACK (PTR): %p\n"), stack);
				printf(xorstr_("--------------------------\n"));
				printf(xorstr_("RCX (INT): %i\n"), (int)rcx);
				printf(xorstr_("RDX (INT): %i\n"), (int)rdx);
				printf(xorstr_("R8 (INT): %i\n"), (int)r8);
				printf(xorstr_("R9 (INT): %i\n"), (int)r9);
				printf(xorstr_("STACK (INT): %i\n"), (int)stack);
#endif

				oDisarmMessage(rcx, rdx, r8, r9, stack);
			}

			void hkCmdMessage(uintptr_t rcx, uintptr_t rdx, uintptr_t r8, uintptr_t r9, uintptr_t stack) {
#ifdef _CONSOLA
				printf(xorstr_("RCX (PTR): %p\n"), rcx);
				printf(xorstr_("RDX (PTR): %p\n"), rdx);
				printf(xorstr_("R8 (PTR): %p\n"), r8);
				printf(xorstr_("R9 (PTR): %p\n"), r9);
				printf(xorstr_("STACK (PTR): %p\n"), stack);
				printf(xorstr_("--------------------------\n"));
				printf(xorstr_("RCX (INT): %i\n"), (int)rcx);
				printf(xorstr_("RDX (INT): %i\n"), (int)rdx);
				printf(xorstr_("R8 (INT): %i\n"), (int)r8);
				printf(xorstr_("R9 (INT): %i\n"), (int)r9);
				printf(xorstr_("STACK (INT): %i\n"), (int)stack);

				if (Local::hub != NULL) {
					auto netId = Mirror::NetworkBehaviour::get_netId(Local::interactCoordinator);

					printf(xorstr_("NET ID: %i\n"), (int)netId);
				}
				
#endif

				oCmdMessage(rcx, rdx, r8, r9, stack);
			}

			void hkBlinkMessage(uintptr_t rcx, uintptr_t rdx, uintptr_t r8, uintptr_t r9, uintptr_t stack) {
				oBlinkMessage(rcx, rdx, r8, r9, stack);
			}

			void hkRequestMessage(uintptr_t rcx, uintptr_t rdx, uintptr_t r8, uintptr_t r9, uintptr_t stack) {
				auto myRcx = rcx;

				//Force Server-Side Scope
				// 0x30000 = Stop Aiming Down Sight
				// 0x20000 = Start Aiming Down Sight
				if (myRcx >= 0x30000 && myRcx < 0x40000) {
					myRcx -= 0x10000;
				}

				oRequestMessage(myRcx, rdx, r8, r9, stack);
			}

			void hkShotMessage(uintptr_t rcx, uintptr_t rdx, uintptr_t r8, uintptr_t r9, uintptr_t stack) {
				oShotMessage(rcx, rdx, r8, r9, stack);

				if(cvar::aimbot::doubleTap)
					oShotMessage(rcx, rdx, r8, r9, stack);
			}

			void hkCoinMessage(uintptr_t rcx, uintptr_t rdx, uintptr_t r8, uintptr_t r9, uintptr_t stack) {
				for (int i = 0; i < cvar::callAmount; i++) {
					oCoinMessage(rcx, rdx, r8, r9, stack);
				}
			}

			void hkSnapMessage(uintptr_t rcx, uintptr_t rdx, uintptr_t r8, uintptr_t r9, uintptr_t stack) {
				#ifdef _CONSOLA
				printf(xorstr_("RCX (PTR): %p\n"), rcx);
				printf(xorstr_("RDX (PTR): %p\n"), rdx);
				printf(xorstr_("R8 (PTR): %p\n"), r8);
				printf(xorstr_("R9 (PTR): %p\n"), r9);
				printf(xorstr_("STACK (PTR): %p\n"), stack);
				printf(xorstr_("--------------------------\n"));
				printf(xorstr_("RCX (INT): %i\n"), (int)rcx);
				printf(xorstr_("RDX (INT): %i\n"), (int)rdx);
				printf(xorstr_("R8 (INT): %i\n"), (int)r8);
				printf(xorstr_("R9 (INT): %i\n"), (int)r9);
				printf(xorstr_("STACK (INT): %i\n"), (int)stack);
				#endif

				oSnapMessage(rcx,rdx,r8,r9,stack);
			}
#endif
		}

		namespace NetworkBehaviour {
			typedef void(__fastcall* tSendCommandInternal)(uintptr_t, uintptr_t, Il2CppString*, uintptr_t, int, bool);

			tSendCommandInternal oSendCommandInternal = 0;

			bool fixingNetId = false;

			void hkSendCommandInternal(uintptr_t _this, uintptr_t type, Il2CppString* cmdName, uintptr_t writer, int channelId, bool requiresAuthority) {
				fixingNetId = true;
				oSendCommandInternal(_this, type, cmdName, writer, channelId, false);
				fixingNetId = false;
			}
		}
	}
}