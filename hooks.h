#pragma once
#include <structs.h>
#include <SCPSL/UnityEngine/Physics.h>
#include <SCPSL/UnityEngine/Component.h>
#include <SCPSL/UnityEngine/Transform.h>
#include <SCPSL/UnityEngine/LayerMask.h>
#include <SCPSL/UnityEngine/CharacterController.h>
#include <SCPSL/UnityEngine/RenderSettings.h>
#include <SCPSL/UnityEngine/AudioSource.h>
#include <SCPSL/UnityEngine/Object.h>
#include <SCPSL/UnityEngine/Camera.h>
#include <SCPSL/UnityEngine/Quaternion.h>
#include <SCPSL/UnityEngine_Networking/UnityWebRequest.h>
#include <SCPSL/UnityEngine/Behaviour.h>
#include <SCPSL/UnityEngine/Time.h>
#include <SCPSL/UnityEngine/AnimationCurve.h>
#include <SCPSL/UnityEngine/CanvasRenderer.h>
#include <SCPSL/UnityEngine_Rendering_PostProcessing/PostProcessVolume.h>
#include <SCPSL/UnityEngine/Screen.h>
#include <SCPSL/UnityEngine/GameObject.h>
#include <SCPSL/UnityEngine/Vector3.h>
#include <SCPSL/UnityEngine/Input.h>
#include <SCPSL/UnityEngine/Material.h>
#include <SCPSL/UnityEngine/Renderer.h>
#include <SCPSL/UnityEngine/Shader.h>
#include <SCPSL/UnityEngine/MeshRenderer.h>
#include <SCPSL/UnityEngine/SkinnedMeshRenderer.h>
#include <SCPSL/UnityEngine/Random.h>
#include <SCPSL/UnityEngine/Texture2D.h>
#include "./kiero/minhook/include/MinHook.h"
#include <api.h>
#include <map>
#include <memory.h>
#include <SCPSL/Mirror/NetworkBehaviour.h>
#include <SCPSL/ReferenceHub.h>
#include <SCPSL/PlayerMovementSync.h>
#include <SCPSL/CharacterClassManager.h>
#include <SCPSL/FootstepSync.h>
#include <SCPSL/NicknameSync.h>
#include <SCPSL/FirstPersonController.h>
#include <SCPSL/MouseLook.h>
#include <SCPSL/GameCore/Console.h>
#include <SCPSL/AnimationController.h>
#include <Input.h>
#include <SCPSL/SpectatorManager.h>
#include <SCPSL/SpectatorCamera.h>
#include <SCPSL/Role.h>
#include <SCPSL/Radio.h>
#include <SCPSL/Scp049_2PlayerScript.h>
#include <RoleHelper.h>
#include <cvar.h>
#include <SCPSL/Assets__Scripts_Dissonance/DissonanceUserSetup.h>
#include <SCPSL/Assets__Scripts_Dissonance/DissonanceEnumUtils.h>
#include <SCPSL/Dissonance_Audio_Playback/VoicePlayback.h>
#include <SCPSL/CameraShaking/RecoilShake.h>
#include <SCPSL/NewMainMenu.h>
#include <SCPSL/PlayableScpsController.h>
#include <SCPSL/CustomNetworkManager.h>
#include <SCPSL/System/Object.h>
#include <SCPSL/CursorManager.h>
#include <SCPSL/InventorySystem_Items_ThrowableProjectiles/ThrownProjectile.h>
#include <SCPSL/InventorySystem_Items_Firearms_Modules/StandardHitregBase.h>
#include <SCPSL/InventorySystem_Items_Firearms_Modules/AutomaticAction.h>
#include <SCPSL/InventorySystem_Items/ItemBase.h>
#include <SCPSL/PlayerStatsSystem/PlayerStats.h>
#include <SCPSL/PlayerStatsSystem/SyncedStatBase.h>
#include <SCPSL/InventorySystem_Items_Pickups/PickupSyncInfo.h>
#include <SCPSL/InventorySystem_Items_Pickups/ItemPickupBase.h>
#include <SCPSL/TeslaGate.h>
#include <Mirror.h>
#include <SCPSL/Scp914/Scp914Controller.h>
#include <SCPSL/InventorySystem/Inventory.h>
#include <SCPSL/Intercom.h>	
#include <SCPSL/Hitmarker.h>	
#include <SCPSL/StaringIsRude.h>	
#include <SCPSL/InventorySystem_Items_Firearms/Firearm.h>	
#include <SCPSL/PlayableScps_ScriptableObjects/Scp173Data.h>
#include <SCPSL/PlayableScps_ScriptableObjects/ScpScriptableObjects.h>
#include <SCPSL/InventorySystem_Items/ViewmodelCamera.h>
#include <SCPSL/Interactables_Interobjects_DoorUtils/DoorVariant.h>
#include <SCPSL/Interactables_Interobjects_DoorUtils/RegularDoorButton.h>
#include <SCPSL/Interactables_Interobjects/BasicDoor.h>
#include <SCPSL/Interactables/InteractableCollider.h>
#include <SCPSL/Interactables/InteractionCoordinator.h>
#include <SCPSL/ServerTime.h>
#include <SCPSL/Ragdoll.h>
#include <SCPSL/InventorySystem_Searching/SearchCoordinator.h>
#include <defines.h>
#include <comdef.h>
#include <SCPSL/Steamworks/ISteamUser.h>
#include <SCPSL/AspectRatioSync.h>
#include <SCPSL/Steamworks/ISteamFriends.h>
#include <SCPSL/SteamManager.h>
#include <SCPSL/RemoteAdmin/QueryProcessor.h>
#include <SCPSL/MapGeneration/RoomIdentifier.h>
#include <SCPSL/PlayableScps/Scp049.h>
#include <SCPSL/Scp106PlayerScript.h>
#include <SCPSL/PlayableScps/Scp096.h>
#include <SCPSL/PlayableScps/Scp939.h>
#include <SCPSL/PlayableScps/Scp173.h>
#include <SCPSL/PlayableScps_Abilities/Scp096Attack.h>
#include <SCPSL/PlayableScps_Abilities/Scp173Snap.h>
#include <MathUtil.h>
#include <ItemHelper.h>
#include <AimbotHelper.h>
#include "GameObject.h"
#include "UnityEngine.h"
#include "LayerMaskUtil.h"
#include "SCPSL.h"
#include "SpecialHooks.h"
#include "bobuck.h"
namespace Hooks {

	void TryHook(uintptr_t address, LPVOID detour, LPVOID* original) {
		if (MH_CreateHook(reinterpret_cast<LPVOID>(address), detour, original) == MH_STATUS::MH_OK) {
			MH_EnableHook(reinterpret_cast<LPVOID>(address));
		}
	}

	void Initialize() {
		auto base = api::GetModuleBase();
	
		TryHook(SCPSL::CharacterClassManager::pUpdate(),&hooks::CharacterClassManager::Update, reinterpret_cast<LPVOID*>(&hooks::CharacterClassManager::oUpdate));
		TryHook(SCPSL::SpectatorManager::pUpdate(), &hooks::SpectatorManager::Update, reinterpret_cast<LPVOID*>(&hooks::SpectatorManager::oUpdate));
		TryHook(CameraShaking::RecoilShake::p_ctor(), &hooks::RecoilShake::RecoilShakeCtor_h, reinterpret_cast<LPVOID*>(&hooks::RecoilShake::RecoilShakeCtor_i));
		TryHook(SCPSL::TeslaGate::pElectrocutePlayer(), &hooks::TeslaGate::hkElectrocutePlayer, reinterpret_cast<LPVOID*>(&hooks::TeslaGate::oElectrocutePlayer));
		TryHook(SCPSL::TeslaGate::pUpdate(), &hooks::TeslaGate::Update, reinterpret_cast<LPVOID*>(&hooks::TeslaGate::oUpdate));
		TryHook(SCPSL::NewMainMenu::pUpdate(), &hooks::NewMainMenu::Update, reinterpret_cast<LPVOID*>(&hooks::NewMainMenu::oUpdate));
		TryHook(SCPSL::FirstPersonController::pUpdate(), &hooks::FirstPersonController::Update, reinterpret_cast<LPVOID*>(&hooks::FirstPersonController::oUpdate));
		TryHook(SCPSL::CustomNetworkManager::pUpdate(), &hooks::CustomNetworkManager::Update, reinterpret_cast<LPVOID*>(&hooks::CustomNetworkManager::oUpdate));
		TryHook(SCPSL::Radio::pUpdate(), &hooks::Radio::Update, reinterpret_cast<LPVOID*>(&hooks::Radio::oUpdate));
		TryHook(SCPSL::PlayableScpsController::pUpdate(), &hooks::PlayableScpsController::Update, reinterpret_cast<LPVOID*>(&hooks::PlayableScpsController::oUpdate));
		TryHook(InventorySystem_Items_Firearms_Modules::AutomaticAction::p_ctor(), &hooks::AutomaticAction::hkCtor, reinterpret_cast<LPVOID*>(&hooks::AutomaticAction::oCtor));
		TryHook(SCPSL::Hitmarker::pUpdate(), &hooks::Hitmarker::Update, reinterpret_cast<LPVOID*>(&hooks::Hitmarker::oUpdate));
		TryHook(SCPSL::Hitmarker::pPlayHitmarker(), &hooks::Hitmarker::PlayHitmarker, reinterpret_cast<LPVOID*>(&hooks::Hitmarker::oPlayHitmarker));
		TryHook(SCPSL::Hitmarker::pHitmarkerMsgReceived(), &hooks::Hitmarker::HitmarkerMessageReceived, reinterpret_cast<LPVOID*>(&hooks::Hitmarker::oHitmarkerReceived));
		TryHook(SCPSL::StaringIsRude::pUpdate(), &hooks::StaringIsRude::Update, reinterpret_cast<LPVOID*>(&hooks::StaringIsRude::oUpdate));
		TryHook(PlayableScps_ScriptableObjects::ScpScriptableObjects::pAwake(), &hooks::ScpScriptableObjects::Awake, reinterpret_cast<LPVOID*>(&hooks::ScpScriptableObjects::oAwake));
		TryHook(UnityEngine_Rendering_PostProcessing::PostProcessVolume::pUpdate(), &hooks::hkUnityEngine::PostProcessVolume::Update, reinterpret_cast<LPVOID*>(&hooks::hkUnityEngine::PostProcessVolume::oUpdate));
		TryHook(InventorySystem_Items_Firearms_Modules::StandardHitregBase::pClientCalculateHit(), &hooks::StandardHitregBase::hkClientCalculateHit, reinterpret_cast<LPVOID*>(&hooks::StandardHitregBase::oCalculateHit));
		TryHook(InventorySystem_Items_Pickups::ItemPickupBase::pFixedUpdate(), &hooks::ItemPickupBase::Update, reinterpret_cast<LPVOID*>(&hooks::ItemPickupBase::oUpdate));
		TryHook(SCPSL::SpectatorCamera::pAwake(), &hooks::SpectatorCamera::Awake , reinterpret_cast<LPVOID*>(&hooks::SpectatorCamera::oAwake));
		TryHook(UnityEngine::Camera::pSet_fieldOfView(), &hooks::hkUnityEngine::Camera::set_Fov, reinterpret_cast<LPVOID*>(&hooks::hkUnityEngine::Camera::oSetFOV));
		TryHook(MapGeneration::RoomIdentifier::pAwake(), &hooks::RoomIdentifier::Awake, reinterpret_cast<LPVOID*>(&hooks::RoomIdentifier::oAwake));
		

#if _DEVELOPER

		TryHook(base + offset::nc_msgRequest, &hooks::hkMirror::NetworkClient::hkRequestMessage, reinterpret_cast<LPVOID*>(&hooks::hkMirror::NetworkClient::oRequestMessage));
//
		//TryHook(UnityEngine::Physics::pRaycastAll01(), &hooks::hkUnityEngine::Physics::hkRaycastAll, reinterpret_cast<LPVOID*>(&hooks::hkUnityEngine::Physics::oRaycast01));
		TryHook(base + offset::nc_msgCoin, &hooks::hkMirror::NetworkClient::hkCoinMessage, reinterpret_cast<LPVOID*>(&hooks::hkMirror::NetworkClient::oCoinMessage));
		//TryHook(base + offset::nc_snap, &hooks::hkMirror::NetworkClient::hkSnapMessage, reinterpret_cast<LPVOID*>(&hooks::hkMirror::NetworkClient::oSnapMessage));
		TryHook(base + offset::nc_msgShot, &hooks::hkMirror::NetworkClient::hkShotMessage, reinterpret_cast<LPVOID*>(&hooks::hkMirror::NetworkClient::oShotMessage));
		//TryHook(base + offset::nc_cmd, &hooks::hkMirror::NetworkClient::hkCmdMessage, reinterpret_cast<LPVOID*>(&hooks::hkMirror::NetworkClient::oCmdMessage));
		//TryHook(base + offset::nc_msgDisasrm, &hooks::hkMirror::NetworkClient::hkDisarmMessage, reinterpret_cast<LPVOID*>(&hooks::hkMirror::NetworkClient::oDisarmMessage));
		//TryHook(base + offset::nc_blink, &hooks::hkMirror::NetworkClient::hkBlinkMessage, reinterpret_cast<LPVOID*>(&hooks::hkMirror::NetworkClient::oBlinkMessage));
		TryHook(SCPSL::CursorManager::pIsMovementLocked(), &hooks::CursorManager::IsMovementLocked, reinterpret_cast<LPVOID*>(&hooks::CursorManager::oIsMovementLocked));
		TryHook(SCPSL::AspectRatioSync::pCmdSetAspectRatio(), &hooks::AspectRatioSync::hkCmdSetAspectRatio, reinterpret_cast<LPVOID*>(&hooks::AspectRatioSync::oCmdSetAspectRatio));
		//TryHook(SCPSL::Ragdoll::pUpdate(), &hooks::Ragdoll::Update, reinterpret_cast<LPVOID*>(&hooks::Ragdoll::oUpdate));
		TryHook(UnityEngine::Transform::pGet_forward(), &hooks::FirstPersonController::hkForward, reinterpret_cast<LPVOID*>(&hooks::FirstPersonController::oForward));
		TryHook(UnityEngine::Transform::pGet_right(), &hooks::FirstPersonController::hkRight, reinterpret_cast<LPVOID*>(&hooks::FirstPersonController::oRight));
		//TryHook(UnityEngine_Networking::UnityWebRequest::p_ctor(), &hooks::hkMirror::a::hkReq, reinterpret_cast<LPVOID*>(&hooks::hkMirror::a::oRequest));
		//TryHook(UnityEngine_Networking::UnityWebRequest::p_ctor984(), &hooks::hkMirror::a::hkReq01, reinterpret_cast<LPVOID*>(&hooks::hkMirror::a::oRequest01));

		TryHook(PlayableScps_Abilities::Scp096Attack::pRun(), &hooks::Scp096::Run, reinterpret_cast<LPVOID*>(&hooks::Scp096::attackRun));
		TryHook(PlayableScps_Abilities::Scp173Snap::pRun(), &hooks::Scp173::Run, reinterpret_cast<LPVOID*>(&hooks::Scp173::snapRun));
		TryHook(SCPSL::MouseLook::pLookRotation(), &hooks::FirstPersonController::hkLookRotation, reinterpret_cast<LPVOID*>(&hooks::FirstPersonController::oLookRotation));
		TryHook(UnityEngine::Material::pGet_mainTexture(), &hkGetTexture, reinterpret_cast<LPVOID*>(&oGetTexture));
#endif
		TryHook(InventorySystem_Items_Firearms::Firearm::pEquipUpdate(), &hooks::Firearm::EquipUpdate, reinterpret_cast<LPVOID*>(&hooks::Firearm::oEquipUpdate));
		TryHook(SCPSL::Scp106PlayerScript::pUpdate(), &hooks::Scp106PlayerScript::Update, reinterpret_cast<LPVOID*>(&hooks::Scp106PlayerScript::oUpdate));
		TryHook(SCPSL::ServerTime::pUpdate(), &hooks::ServerTime::Update, reinterpret_cast<LPVOID*>(&hooks::ServerTime::oUpdate));
		TryHook(Interactables_Interobjects::BasicDoor::pCustomUpdate(), &hooks::BasicDoor::Update, reinterpret_cast<LPVOID*>(&hooks::BasicDoor::oUpdate));
		TryHook(Interactables::InteractionCoordinator::pUpdate(), &hooks::InteractableCoordinator::Update, reinterpret_cast<LPVOID*>(&hooks::InteractableCoordinator::oUpdate));
#if _DEVELOPER
#pragma region Speedhack
		
		TryHook(PlayableScps::Scp049::pGet_MaxSpeed(), &scp_speedhack::hk049, reinterpret_cast<LPVOID*>(&scp_speedhack::o049));
		TryHook(PlayableScps::Scp096::pGet_MaxSpeed(), &scp_speedhack::hk096, reinterpret_cast<LPVOID*>(&scp_speedhack::o096));
		TryHook(PlayableScps::Scp939::pGet_MaxSpeed(), &scp_speedhack::hk939, reinterpret_cast<LPVOID*>(&scp_speedhack::o939));
		TryHook(PlayableScps::Scp173::pGet_MaxSpeed(), &scp_speedhack::hk173, reinterpret_cast<LPVOID*>(&scp_speedhack::o173));
	
#pragma endregion
#endif
	}
}