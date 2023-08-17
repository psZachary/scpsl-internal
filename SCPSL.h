#pragma once
#include <WinUser.h>

namespace Keybinding {
	Input::KeyCode getPressedKeybind() {
		static bool b;
		
		for (int i = 0; i < 509; i++) {
			if (i == 0)
				continue;

			auto kb = (Input::KeyCode)i;

			if (Input::GetKeyInt(i))
				return kb;
		}

		return Input::KeyCode::None;
	}

	void Update() {
		if (cvar::Keybinding::active) {
			auto kb = getPressedKeybind();

			if (kb != Input::KeyCode::None)
			{
				cvar::Keybinding::stored = kb;
				cvar::Keybinding::active = false;
				cvar::Keybinding::finished = true;
			}
		}
	}
}

//>>>>>>> Stashed changes
namespace hooks {

	namespace Firearm {
		tMethod oEquipUpdate = 0;

		void EquipUpdate(uintptr_t _this) {
			oEquipUpdate(_this);

			auto status  = InventorySystem_Items_Firearms::Firearm::field__status(_this);
			Local::curAmmo = (status).Ammo;
		}
	}

	namespace ServerTime {
		int localTime;

		tMethod oUpdate = 0;

		void Update(uintptr_t _this) {
			oUpdate(_this);

			localTime = SCPSL::ServerTime::field_timeFromStartup(_this);
		}
	}

	namespace Scp106PlayerScript {
		tMethod oUpdate = 0;

		float remainingCooldown;

		bool AllowDistance() {

			auto pos = Local::getPos();

			float num = GetDistance(pos, aimbotTarget.position);
			float num2 = abs(pos.Y - aimbotTarget.position.Y);
			if ((num >= 3.1f && num2 < 1.02f) || (num >= 3.4f && num2 < 1.95f) || (num >= 3.7f && num2 < 2.2f) || (num >= 3.9f && num2 < 3.f) || num >= 4.2f)
				return false;

			return true;
		}

		void Update(uintptr_t _this) {
			oUpdate(_this);

			remainingCooldown = SCPSL::Scp106PlayerScript::field__remainingCooldown(_this);

			if (Mirror::NetworkBehaviour::get_isLocalPlayer(_this) && cvar::aimbot::active && remainingCooldown <= 0 && Local::role == RoleType::Scp106) {

				if (aimbotTarget.object != NULL && AllowDistance()) {
					SCPSL::Scp106PlayerScript::CmdMovePlayer(_this, aimbotTarget.object, ServerTime::localTime);
				}
			}
		}
	}

	namespace CharacterClassManager {

		tMethod oUpdate = 0;

		void Update(uintptr_t component) {

			int team = SCPSL::CharacterClassManager::field_CurClass(component);

			auto player = UnityEngine::Component::get_gameObject(component);

			auto transform = UnityEngine::Component::get_transform(component);

			vec3 position = UnityEngine::Transform::get_position(transform);

			auto hub = SCPSL::CharacterClassManager::field__hub(component);

			auto fpc = SCPSL::CharacterClassManager::field__fpc(component);

			auto nickSync = SCPSL::ReferenceHub::field_nicknameSync(hub);

			auto name = SCPSL::NicknameSync::field__myNickSync(nickSync);

			auto role = SCPSL::CharacterClassManager::get_CurRole(component);

			auto roleName = SCPSL::Role::field_fullName(role);

			auto pms = SCPSL::ReferenceHub::field_playerMovementSync(hub);

			auto serverSidePos = SCPSL::PlayerMovementSync::field__realModelPosition(pms);

			auto netId = Mirror::NetworkBehaviour::get_netId(component);

			auto interactionCoordinator = SCPSL::ReferenceHub::field_interCoordinator(component);

			auto inventoru = SCPSL::ReferenceHub::field_inventory(component);

			auto curItem = InventorySystem::Inventory::get_NetworkCurItem(inventoru);

			bool isLocalPlayer = Mirror::NetworkBehaviour::get_isLocalPlayer(component);

			if (isLocalPlayer) {
				if (Local::role == 2)
					Local::position = Local::cameraPosition;
				else
					Local::position = position;
				
				Local::address = player;
				Local::transform = transform;
				Local::hub = hub;
				Local::interactCoordinator = interactionCoordinator;

				Local::role = team;

				if (pms)
					Local::serverPosition = serverSidePos;
			}

			bool visible = false;

			//Linecast01(vec3,vec3,int)
			if(Local::role != 2)
				visible = !UnityEngine::Physics::Linecast01(Local::cameraPosition, vec3(position.X, position.Y + RoleHelper::GetAimbotOffset(cvar::aimbot::hitbox, team), position.Z), aimbotMask);

			static auto ent = Player();

			ent.Reset();

			ent.object = player;
			ent.pms = pms;
			ent.ccm = component;
			ent.position = position;
			ent.team = team;
			ent.role = roleName;
			ent.name = name;
			ent.visible = visible;
			ent.isLocalPlayer = isLocalPlayer;
			ent.netId = netId;
			ent.referenceHub = hub;
			ent.itemId = curItem.TypeId;
			
			bool found = false;

			for (int i = 0; i < entityList.size(); i++)
			{
				if (entityList[i].ccm != component)
					continue;

				entityList[i] = ent;
				found = true;
				break;
			}

			if (!found)
				entityList.push_back(ent);

			ent.Reset();

			oUpdate(component);
		}
	}

	namespace SpectatorCamera {
		tMethod oAwake = 0;

		uintptr_t singletonCam = 0;

		void Awake(uintptr_t _this)
		{
			oAwake(_this);

			singletonCam = SCPSL::SpectatorCamera::field_cam(_this);
		}
	}

	namespace AspectRatioSync {
		typedef void(__fastcall* tCmdSetAspectRatio)(uintptr_t, float);

		tCmdSetAspectRatio oCmdSetAspectRatio = 0;

		void hkCmdSetAspectRatio(uintptr_t c, float r) {
			return oCmdSetAspectRatio(c, 1);
		}
	}

	namespace SpectatorManager {
		tMethod oUpdate = 0;

		bool AllowAntiDesync() {
			return Local::serverPosition != vector3zero;
		}

		void TeleportToServerPos() {
			UnityEngine::Transform::set_position(Local::transform, Local::serverPosition);
		}

		bool syncback()
		{
			return Input::GetKeyInt(Input::KeyCode::Home) || Input::GetKeyInt(Input::KeyCode::Keypad1);
		}

		void Update(uintptr_t component) {

			if (Mirror::NetworkBehaviour::get_isLocalPlayer(component)) {

				if (Local::role == 2 && hooks::SpectatorCamera::singletonCam != NULL)
					Local::camera = hooks::SpectatorCamera::singletonCam;
				else
					Local::camera = SCPSL::SpectatorManager::field_mainCam(component);
				

				if (Local::camera) {
					UnityEngine::Camera::set_farClipPlane(Local::camera, 120);

					Local::viewMatrix = api::get_viewmatrix(Local::camera);
					Local::cameraPosition = api::get_camera_position(Local::camera);

					Local::cameraTransform = UnityEngine::Component::get_transform(Local::camera);

					hooks::hkUnityEngine::Camera::oSetFOV(Local::camera, cvar::cameraFov);
				}

				if (syncback() || (cvar::player::antiDesync && AllowAntiDesync() && GetDistance(Local::position, Local::serverPosition) >= 2 && UnityEngine::Physics::Linecast01(Local::serverPosition, Local::position, aimbotMask)))
				{
					TeleportToServerPos();
				}
			}

			oUpdate(component);
		}
	}
#if _DEVELOPER
	namespace FootstepSync {
		void Misc__Deaf939()
		{
			if (!cvar::player::deaf939_enable)
				return;

			if (cvar::player::deaf939)
				return;

			cvar::player::deaf939 = true;

			auto at = SCPSL::FootstepSync::pCmdScp939Noise();
			at += 0xB8;
			int relativeoffset = *(int*)(at + 0x3);
			at = *(uintptr_t*)(at + relativeoffset + 0x7);
			auto str = (Il2CppString*)(at);
			if (str)
			{
				str->data[0] = L'\0';
				str->length = 0;
			}

			at = SCPSL::FootstepSync::pRpcPlayLandingFootstep();
			at += 0xB3;
			relativeoffset = *(int*)(at + 0x3);
			at = *(uintptr_t*)(at + relativeoffset + 0x7);
			str = (Il2CppString*)(at);
			if (str)
			{
				str->data[0] = L'\0';
				str->length = 0;
			}
		}
	}
#endif

	namespace TeslaGate {
		typedef void(__fastcall* tElectrocutePlayer)(uintptr_t, uintptr_t);

		tMethod oUpdate = 0;
		tElectrocutePlayer oElectrocutePlayer = 0;

		void Update(uintptr_t component) {

			if (Input::GetKeyInt(Input::KeyCode::L) && cvar::player::teslaKill) {
				oElectrocutePlayer(component, Local::address);
			}
		}

		void hkElectrocutePlayer(uintptr_t component, uintptr_t player) {

			if (!cvar::player::antiTesla)
				return oElectrocutePlayer(component, Local::address);
		}
	}

	namespace PlayableScpsController {
		tMethod oUpdate = 0;
		float attackDist = 2.4f * 1.25f;
		float remainingCooldown;

		void Update(uintptr_t component) {

			if (Mirror::NetworkBehaviour::get_isLocalPlayer(component) && cvar::aimbot::active && remainingCooldown <= 0 && Local::role == RoleType::Scp049) {

				if (aimbotTarget.object != NULL) {
					if (GetDistance(Local::getPos(), aimbotTarget.position) <= attackDist) {
						SCPSL::PlayableScpsController::CmdTransmit_ByteAndGameObject(component,0,aimbotTarget.object);
					}
				}
			}

			oUpdate(component);
		}
	}

	namespace FirstPersonController {
		typedef vec3(__fastcall* tForward)(uintptr_t);
		typedef vec3(__fastcall* tGetEulerAngles)(uintptr_t);
		typedef void(__fastcall* tLookRotation)(uintptr_t, uintptr_t, uintptr_t, float, float);

		tMethod oUpdate = 0;

		tForward oForward = 0;
		tForward oRight = 0;

		tGetEulerAngles oGetEulerAngles = 0;

		tLookRotation oLookRotation = 0;

		float walkSpeed, runSpeed, jumpSpeed;

		bool fixingMovement = false;

		void FixCamera(std::vector<quat> rots) {
			if (!rots.size())
				return;
			SCPSL::MouseLook::set_field__cameraTargetRot(Local::mouseLook, rots[1]);
			SCPSL::MouseLook::set_field__characterTargetRot(Local::mouseLook, rots[0]);
			SCPSL::MouseLook::LookRotation(Local::mouseLook, Local::transform, Local::cameraTransform, 0, 0);
		}

		std::vector<quat> AimbotCode(bool customPos = false, UVector3 posi = UVector3()) {
			static std::vector<quat> tmp;

			tmp.clear();

			if (Local::mouseLook != NULL && Local::camera != NULL && aimbotTarget.object != NULL) {
				float offset = RoleHelper::GetAimbotOffset(cvar::aimbot::hitbox, aimbotTarget.team);

				auto transform = UnityEngine::Component::get_transform(aimbotTarget.ccm);

				vec3 pos = UnityEngine::Transform::get_position(transform);

				if (GetDistance(Local::position, pos) < 300) {

					tmp.push_back(SCPSL::MouseLook::field__characterTargetRot(Local::mouseLook));
					tmp.push_back(SCPSL::MouseLook::field__cameraTargetRot(Local::mouseLook));

					pos.Y += offset;

					if (customPos)
						pos = posi;

					vec3 angle = pos - Local::cameraPosition;

					quat lookAngle = UnityEngine::Quaternion::LookRotation01(angle);

					UnityEngine::Transform::set_rotation(CustomNetManagerTransform, lookAngle); //bad way to do it, change later

					vec3 eulerAngles = UnityEngine::Transform::get_eulerAngles(CustomNetManagerTransform);

					quat cameraRot = UnityEngine::Quaternion::Euler(eulerAngles.X, 0, 0);
					quat characterRot = UnityEngine::Quaternion::Euler(0, eulerAngles.Y, 0);

					SCPSL::MouseLook::set_field__cameraTargetRot(Local::mouseLook, cameraRot);
					SCPSL::MouseLook::set_field__characterTargetRot(Local::mouseLook, characterRot);
					SCPSL::MouseLook::LookRotation(Local::mouseLook, Local::transform, Local::cameraTransform, 0, 0);
				}
			}
			return tmp;
		}

#if _DEVELOPER

		void DoSpinbotCode() {
			if (Local::transform == NULL || !cvar::player::spinbot || fixingMovement)
				return;

			//173 nearby
			if (aimbotTarget.object != NULL && aimbotTarget.team == 0)
			{
				vec3 angle = UnityEngine::Transform::get_position(UnityEngine::Component::get_transform(aimbotTarget.ccm)) - Local::cameraPosition;

				quat lookAngle = UnityEngine::Quaternion::LookRotation01(angle);

				UnityEngine::Transform::set_rotation(CustomNetManagerTransform, lookAngle); //bad way to do it, change later

				vec3 eulerAngles = UnityEngine::Transform::get_eulerAngles(CustomNetManagerTransform);

				quat characterRot = UnityEngine::Quaternion::Euler(0, eulerAngles.Y, 0);

				UnityEngine::Transform::set_localRotation(Local::transform, characterRot);
			}
			else {
				UnityEngine::Transform::set_localRotation(Local::transform, UnityEngine::Quaternion::Euler(0, cvar::player::spinbotEuler, 0));
			}
		}

		vec3 hkForward(uintptr_t transform) {

			if (!transform)
				return vector3zero;

			if (transform == Local::transform && cvar::player::spinbot && Local::cameraTransform)
			{
				auto eulerAngles = UnityEngine::Transform::get_eulerAngles(Local::cameraTransform);

				UnityEngine::Transform::set_eulerAngles(CustomNetManagerTransform, vec3(0, eulerAngles.Y, 0));

				return oForward(CustomNetManagerTransform);
			}

			return oForward(transform);
		}

		vec3 hkRight(uintptr_t transform) {

			if (!transform)
				return vector3zero;

			if (transform == Local::transform && cvar::player::spinbot && Local::cameraTransform)
			{
				auto eulerAngles = UnityEngine::Transform::get_eulerAngles(Local::cameraTransform);

				UnityEngine::Transform::set_eulerAngles(CustomNetManagerTransform, vec3(0, eulerAngles.Y, 0));

				return oRight(CustomNetManagerTransform);
			}

			return oRight(transform);
		}

		void MouseLook(uintptr_t _this) {

			if (!Local::cameraTransform)
				return;

			auto quat1 = SCPSL::MouseLook::field__characterTargetRot(_this);
			auto quat2 = SCPSL::MouseLook::field__cameraTargetRot(_this);

			UnityEngine::Transform::set_rotation(CustomNetManagerTransform, quat1);

			vec3 euler1 = UnityEngine::Transform::get_eulerAngles(CustomNetManagerTransform);

			UnityEngine::Transform::set_rotation(CustomNetManagerTransform, quat2);

			vec3 euler2 = UnityEngine::Transform::get_eulerAngles(CustomNetManagerTransform);

			auto euler = vec3(euler2.X, euler1.Y, 0);

			auto quat = MathUtil::ToEuler(euler);

			UnityEngine::Transform::set_rotation(Local::cameraTransform, quat);
		}

		void hkLookRotation(uintptr_t _this, uintptr_t character, uintptr_t camera, float plusH, float plusV) {

			if (!cvar::player::spinbot)
				return oLookRotation(_this, character, camera, plusH, plusV);

			oLookRotation(_this, camera, camera, plusH, plusV);

			MouseLook(_this);
		}

#endif

		float origRadius = -65535.f;
		float origStep = -65535.f;

		void Update(uintptr_t component) {

			if (!Mirror::NetworkBehaviour::get_isLocalPlayer(component))
				return oUpdate(component);

			auto cc = SCPSL::FirstPersonController::field__characterController(component);

			if (origRadius == -65535.f || origStep == -65535.f)
			{
				origRadius = UnityEngine::CharacterController::get_radius(cc);
				origStep = 0.3f;

				cvar::step = origStep;
			}

			UnityEngine::CharacterController::set_stepOffset(cc, cvar::minecraftStep ? cvar::step : origStep);

#pragma region CheatCode

#if _DEVELOPER
			if (cvar::player::deaf939_enable)
				FootstepSync::Misc__Deaf939();
#endif
			if (!cachedMask)
			{
				int result = 0;

				int num = UnityEngine::LayerMask::NameToLayer(IlString(xorstr_(L"Default")));
				bool flag = num != -1;
				if (flag) {
					result |= 1 << num;
				}

				num = UnityEngine::LayerMask::NameToLayer(IlString(xorstr_(L"CCTV")));
				flag = num != -1;
				if (flag) {
					result |= 1 << num;
				}

				num = UnityEngine::LayerMask::NameToLayer(IlString(xorstr_(L"Door")));
				flag = num != -1;
				if (flag) {
					result |= 1 << num;
				}

				num = UnityEngine::LayerMask::NameToLayer(IlString(xorstr_(L"Locker")));
				flag = num != -1;
				if (flag) {
					result |= 1 << num;
				}

				aimbotMask = result;
				cachedMask = true;
			}

			Local::mouseLook = SCPSL::FirstPersonController::field__mouseLook(component);

			if (Input::GetKeyInt(323) && !cvar::aimbot::silent) {
				AimbotCode();
			}

			//bunny hop
			SCPSL::FirstPersonController::set_field_wantsToJump(component, Input::GetKeyInt(32));
			SCPSL::FirstPersonController::set_field_NoclipEnabled(component, Input::GetKeyInt(cvar::Keybinds::noclip));

#if _DEVELOPER
			if (cvar::player::spinbot)
			{
				if (!cvar::player::jitterMode)
				{
					float tmp = cvar::player::spinbotEuler + (cvar::player::spinbotSpeed * UnityEngine::Time::get_deltaTime());

					if (tmp > 360)
						tmp -= 360;

					if (tmp < 0 || tmp > 5000)
						tmp = 0;

					cvar::player::spinbotEuler = tmp;
				}
				else {
					cvar::player::spinbotEuler = UnityEngine::Random::Range(0,360);
				}
			}

			static bool speedhackKey = false;
			if (Input::GetKeyInt(cvar::Keybinds::speedhack)) {
				if (!speedhackKey) {
					cvar::speedhack::active = !cvar::speedhack::active;
					speedhackKey = true;
				}
			}
			else {
				speedhackKey = false;
			}

			float multiplier = 1;
			float jMultiplier = 0;

			if (cvar::speedhack::active) {
				multiplier = cvar::speedhack::multiplier;
				jMultiplier = cvar::speedhack::jumpMultiplier;
			}

			oldRole = curRole;
			curRole = SCPSL::FirstPersonController::field_curRole(component);

			if (curRole) {
				if (curRole != oldRole)
				{
					walkSpeed = SCPSL::Role::field_walkSpeed(curRole);
					runSpeed = SCPSL::Role::field_runSpeed(curRole);
					jumpSpeed = SCPSL::Role::field_jumpSpeed(curRole);
				}

				SCPSL::Role::set_field_walkSpeed(curRole, walkSpeed * multiplier);
				SCPSL::Role::set_field_runSpeed(curRole, runSpeed * multiplier);
				SCPSL::Role::set_field_jumpSpeed(curRole, jumpSpeed + jMultiplier);
			}
#endif

#pragma endregion
			
			if (!cvar::player::spinbot)
				return oUpdate(component);

			oUpdate(component);

#if _DEVELOPER
			DoSpinbotCode();

			MouseLook(Local::mouseLook);
#endif
		}
	}

	namespace StandardHitregBase {
		typedef bool(__fastcall* tClientCalculateHit)(uintptr_t, ShotMessage* msg);

		tClientCalculateHit oCalculateHit = 0;

		bool hkClientCalculateHit(uintptr_t instance, ShotMessage* msg) {
			if(!cvar::aimbot::active || aimbotTarget.object == NULL || Local::mouseLook == NULL || Local::cameraTransform == NULL)
				return oCalculateHit(instance, msg);

			auto myCameraPos = UnityEngine::Transform::get_position(Local::cameraTransform);

#if _DEVELOPER
			if (!cvar::aimbot::silent) {

				FirstPersonController::fixingMovement = true;

				FirstPersonController::AimbotCode();

				auto quat1 = SCPSL::MouseLook::field__characterTargetRot(Local::mouseLook);
				auto quat2 = SCPSL::MouseLook::field__cameraTargetRot(Local::mouseLook);

				bool result = oCalculateHit(instance, msg);

				UnityEngine::Transform::set_rotation(CustomNetManagerTransform, quat1);

				vec3 euler1 = UnityEngine::Transform::get_eulerAngles(CustomNetManagerTransform);

				UnityEngine::Transform::set_rotation(CustomNetManagerTransform, quat2);

				vec3 euler2 = UnityEngine::Transform::get_eulerAngles(CustomNetManagerTransform);

				auto eulerAngles = vec3(euler2.X,euler1.Y,0);

				msg->ShooterCameraRotation = eulerAngles.X;
				msg->ShooterCharacterRotation = eulerAngles.Y;
				msg->ShooterPosition = myCameraPos;
				FirstPersonController::fixingMovement = false;
				return result;		
			}


			FirstPersonController::fixingMovement = false;

			oCalculateHit(instance, msg);

			auto serverSidePos = aimbotTarget.position;
			auto myPos = Local::position;

			float offset = RoleHelper::GetAimbotOffset(cvar::aimbot::hitbox, aimbotTarget.team);

			serverSidePos.Y += offset;

			vec3 angle = serverSidePos - Local::cameraPosition;

			serverSidePos.Y -= offset;
			
			vec3 angleTarget = myPos - serverSidePos;

			quat lookAngle = UnityEngine::Quaternion::LookRotation01(angle);
			quat lookAngleTarget = UnityEngine::Quaternion::LookRotation01(angleTarget);

			UnityEngine::Transform::set_rotation(CustomNetManagerTransform, lookAngle);

			vec3 eulerAngles = UnityEngine::Transform::get_eulerAngles(CustomNetManagerTransform);

			UnityEngine::Transform::set_rotation(CustomNetManagerTransform, lookAngleTarget);

			vec3 eulerAnglesTarget = UnityEngine::Transform::get_eulerAngles(CustomNetManagerTransform);

			auto euler = UnityEngine::Quaternion::Euler(0,eulerAnglesTarget.Y,0);

			msg->TargetNetId = aimbotTarget.netId;
			msg->ShooterCameraRotation = eulerAngles.X;
			msg->ShooterCharacterRotation = eulerAngles.Y;
			msg->ShooterPosition = myCameraPos;
			msg->TargetPosition = serverSidePos;
			msg->TargetRotation = euler;
			
			return true;
#else
			auto rotations = FirstPersonController::AimbotCode();
			bool result = oCalculateHit(instance, msg);
			if (cvar::aimbot::silent)
				FirstPersonController::FixCamera(rotations);
			return result;
#endif
		}
	}

#if _DEVELOPER

	namespace Scp173 {
		tMethod snapRun = 0;

		void Run(uintptr_t _this) {

			if(aimbotTarget.object == NULL)
				return snapRun(_this);

			auto targetPos = UnityEngine::Transform::get_position(UnityEngine::Component::get_transform(aimbotTarget.pms));
			auto myPos = UnityEngine::Transform::get_position(Local::transform);
			auto serverPos = Local::getPos();

			if (GetDistance(serverPos, targetPos) > 3)
			{
				return snapRun(_this);
			}

			UnityEngine::Transform::set_position(Local::transform, vec3(targetPos.X, targetPos.Y + RoleHelper::GetAimbotOffset(2, RoleType::ClassD)+ 0.1f, targetPos.Z));
			auto rotations = FirstPersonController::AimbotCode(true, UVector3(myPos.X, myPos.Y - 1000, myPos.Z));
			snapRun(_this);
			FirstPersonController::FixCamera(rotations);
			UnityEngine::Transform::set_position(Local::transform, myPos);
		}
	}

	namespace Scp096 {
		tMethod attackRun = 0;

		UVector3 GetBestPosition(bool* isDoor) {
			if (aimbotTarget.object == NULL)
			{
				*isDoor = true;
				return scpDoor.position;
			}

			auto targetPos = UnityEngine::Transform::get_position(UnityEngine::Component::get_transform(aimbotTarget.pms));

			*isDoor = false;
			return targetPos;
		}

		void Run(uintptr_t _this) {

			if ((aimbotTarget.object == NULL && scpDoor.object == NULL))
				return attackRun(_this);

			bool isDoor = false;
			auto myPos = UnityEngine::Transform::get_position(Local::transform);
			UnityEngine::Transform::set_position(Local::transform, GetBestPosition(&isDoor));
			auto rotations = FirstPersonController::AimbotCode();
			attackRun(_this);
			FirstPersonController::FixCamera(rotations);
			UnityEngine::Transform::set_position(Local::transform, myPos);
		}
	}

#endif

	namespace Crosshair {
		tMethod oUpdate = 0;

		void hkUpdate(uintptr_t _this) {
			auto go = UnityEngine::Component::get_gameObject(_this);

			UnityEngine::GameObject::SetActive(go, false);
		}
	}

	namespace RecoilShake {
		typedef void(__fastcall* RecoilShakeCtor_p)(uintptr_t, RecoilSettings, uintptr_t, uintptr_t);
		RecoilShakeCtor_p RecoilShakeCtor_i = 0;
		void __fastcall RecoilShakeCtor_h(uintptr_t r, RecoilSettings rs, uintptr_t f, uintptr_t m)
		{
			if (!r)
				return;

			RecoilSettings a = rs;
			if (cvar::aimbot::noRecoil) {
				a.SideKick = 0;
				a.UpKick = 0;
				a.ZAxis = 0;
			}

			return RecoilShakeCtor_i(r, a, f, m);
		}
	}
#if _DEVELOPER
	namespace CursorManager {

		typedef int(__fastcall* tIsMovementLocked)();
		tIsMovementLocked oIsMovementLocked = 0;

		int IsMovementLocked() {
			return 0;
		}
	}
#endif

	namespace CustomNetworkManager {

		typedef void(__fastcall* tUpdate)(uintptr_t);
		tUpdate oUpdate = 0;

		void Update(uintptr_t component) {

			if(!CustomNetManagerTransform)
				CustomNetManagerTransform = UnityEngine::Component::get_transform(component);

			static bool menuKeyPress = false;

			if (Input::GetKeyInt(cvar::Keybinds::toggleMenu)) {
				if (!menuKeyPress) {
					cvar::menu::show = !cvar::menu::show;
					menuKeyPress = true;
				}
			}
			else {
				menuKeyPress = false;
			}

			static bool spinbotK = false;
			static bool ffK = false;
			static bool aimbotK = false;
			static bool dtK = false;

			if (Input::GetKeyDown(cvar::Keybinds::friendlyfire, &ffK))
				cvar::aimbot::friendlyFire = !cvar::aimbot::friendlyFire;

			if (Input::GetKeyDown(cvar::Keybinds::spinbot, &spinbotK))
				cvar::player::spinbot = !cvar::player::spinbot;

			if (Input::GetKeyDown(cvar::Keybinds::aimbot, &aimbotK))
				cvar::aimbot::active = !cvar::aimbot::active;

#if _DEVELOPER
			if (Input::GetKeyDown(cvar::Keybinds::doubleTap, &dtK))
				cvar::aimbot::doubleTap = !cvar::aimbot::doubleTap;
#endif

			UnityEngine::RenderSettings::set_fog(false);
			if (cvar::visuals::ambience_enabled) {
				UnityColor color = UnityColor(cvar::etc::ambientColor[0], cvar::etc::ambientColor[1], cvar::etc::ambientColor[2], true);
				if (cvar::etc::ambientRainbow) {
					color.r = cvar::visuals::rainbow_color.r;
					color.g = cvar::visuals::rainbow_color.g;
					color.b = cvar::visuals::rainbow_color.b;
				}
				
				UnityEngine::RenderSettings::set_ambientLight(color);
			}
			else
			{
				UnityColor color = UnityColor(0.4f, 0.4f, 0.4f, true);
				UnityEngine::RenderSettings::set_ambientLight(color);
			}


			Keybinding::Update();

			oUpdate(component);
		}
	}

	namespace Radio {
		typedef void(__fastcall* tUpdate)(uintptr_t);

		tUpdate oUpdate = 0;

		int getTeamId(int role) {
			switch (role) {
			case RoleType::ChaosConscript:
			case RoleType::ChaosMarauder:
			case RoleType::ChaosRepressor:
			case RoleType::ChaosRifleman:
				return 2;
			case RoleType::ClassD:
				return 4;
			case RoleType::FacilityGuard:
			case RoleType::NtfCaptain:
			case RoleType::NtfPrivate:
			case RoleType::NtfSergeant:
			case RoleType::NtfSpecialist:
				return 1;
			case RoleType::Scientist:
				return 3;
			case RoleType::Scp049:
			case RoleType::Scp0492:
			case RoleType::Scp079:
			case RoleType::Scp096:
			case RoleType::Scp106:
			case RoleType::Scp173:
			case RoleType::Scp93953:
			case RoleType::Scp93989:
				return 0;
			case RoleType::Tutorial:
				return 6;
			}

			return 5;
		}

		void Update(uintptr_t component) {

			oUpdate(component);

			auto dissonanceUserSetup = SCPSL::Radio::field__dissonanceSetup(component);
			auto hub = SCPSL::Radio::field__hub(component);
			auto ccm = SCPSL::ReferenceHub::field_characterClassManager(hub);
			auto role = SCPSL::CharacterClassManager::field_CurClass(ccm);

			if (Mirror::NetworkBehaviour::get_isLocalPlayer(component) && dissonanceUserSetup) {
				if (cvar::etc::hearAll && !Input::GetKeyInt(Input::KeyCode::Q)) {
					Assets__Scripts_Dissonance::DissonanceUserSetup::UpdateForTeam(dissonanceUserSetup, 5);
				}
				else {
					Assets__Scripts_Dissonance::DissonanceUserSetup::UpdateForTeam(dissonanceUserSetup, getTeamId(Local::role));
				}
			}

			int team = getTeamId(role);

			if (cvar::etc::hearAll) {
				team = 5;
			}

			if (!Mirror::NetworkBehaviour::get_isLocalPlayer(component)) {
				Assets__Scripts_Dissonance::DissonanceUserSetup::set_SpectatorChat(dissonanceUserSetup, team == 5);
			}

			if (cvar::etc::hearAll) {
				auto source = SCPSL::Radio::field_playerSource(component);

				uintptr_t source2 = 0;

				auto unityPlayback = SCPSL::Radio::field_unityPlayback(component);

				if (unityPlayback)
					source2 = Dissonance_Audio_Playback::VoicePlayback::field_AudioSourcek__BackingField(unityPlayback);

				if (source) {
					UnityEngine::AudioSource::set_volume(source, 1);
					UnityEngine::AudioSource::set_spatialBlend(source, 0);
				}
				if (source2) {
					UnityEngine::AudioSource::set_volume(source2, 1);
					UnityEngine::AudioSource::set_spatialBlend(source2, 0);
				}
			}
		}
	}

	namespace NewMainMenu {

		tMethod oUpdate = 0;

		void Update(uintptr_t component) {

			oUpdate(component);

			if (SpectatorCamera::singletonCam != NULL) {
				EspReset();
				Local::Reset();

				cvar::player::deaf939 = false;
				cachedMask = false;
				FirstPersonController::fixingMovement = false;
				SpectatorCamera::singletonCam = NULL;
				scpDoor.object = NULL;
			}
		}
	}

	namespace AutomaticAction {
		typedef void(__fastcall* tCtor)(uintptr_t, uintptr_t, bool, float, float, uint8_t, uint8_t, float, RecoilSettings, uintptr_t, bool, uintptr_t);
		tCtor oCtor = 0;

		void __fastcall hkCtor(uintptr_t _this, uintptr_t selfRef, bool semiAuto, float boltTravelTime, float cooldownBetweenShots, uint8_t	dryFireClip, uint8_t triggerClip, float gunshotPitchRandomization, RecoilSettings recoilSettings, uintptr_t recoilPattern, bool hasBoltLock, uintptr_t m) {

			bool a = semiAuto;
			float b = cooldownBetweenShots;

			if (cvar::aimbot::fullAuto)
				a = false;

			if (cvar::aimbot::customFirerate)
				b = cvar::aimbot::customFirerate_c;

			return oCtor(_this, selfRef, a, boltTravelTime, b, dryFireClip, triggerClip, gunshotPitchRandomization, recoilSettings, recoilPattern, hasBoltLock, m);
		}
	}

	namespace StaringIsRude {
		uintptr_t singleton = NULL;
		uintptr_t clip = NULL;

		tMethod oUpdate = 0;

		void PlayShotSound()
		{
			if (singleton == NULL || clip == NULL)
				return;

			auto source = SCPSL::StaringIsRude::field_SCP173ShotSource(singleton);

			UnityEngine::AudioSource::PlayOneShot(source,clip);
		}

		void Update(uintptr_t component)
		{
			if (Mirror::NetworkBehaviour::get_isLocalPlayer(component))
			{
				singleton = component;

				//Update location esp positions lol
				for (int i = 0; i < locationList.size(); i++)
				{
					locationList[i].position = UnityEngine::Transform::get_position(UnityEngine::GameObject::get_transform(locationList[i].object));
				}
			}

			oUpdate(component);
		}
	}

	namespace ScpScriptableObjects {
		tMethod oAwake = 0;

		void Awake(uintptr_t _this) {

			oAwake(_this);

			auto s173 = PlayableScps_ScriptableObjects::ScpScriptableObjects::field_Scp173Data(_this);

			auto clips = PlayableScps_ScriptableObjects::Scp173Data::field_GotShotClips(s173);

			StaringIsRude::clip = Array::Get(clips,0);
		}
	}

	namespace Hitmarker {

		typedef void(__fastcall* tPlayHitmarker)(float);
		typedef void(__fastcall* tHitmarkerReceived)(HitmarkerMessage);
		tPlayHitmarker oPlayHitmarker = 0;
		tHitmarkerReceived oHitmarkerReceived = 0;
		tMethod oUpdate = 0;

		uintptr_t singleton = 0;

		float t = 0;
		float targetSize = 0;

		void PlayHitmarker(float size)
		{
			t = 1.f;
			targetSize = size;
			StaringIsRude::PlayShotSound();
		}

		void HitmarkerMessageReceived(HitmarkerMessage msg) {
			PlayHitmarker(1.2f);
		}

		void Update(uintptr_t component)
		{
			singleton = component;

			auto animationCurve = SCPSL::Hitmarker::field__opacityOverTime(component);

			if (!animationCurve)
				return;

			auto targetImage = SCPSL::Hitmarker::field__targetImage(component);

			if (!targetImage)
				return;

			if (t > 0)
			{
				auto transform = UnityEngine::Component::get_transform(targetImage);

				t -= UnityEngine::Time::get_deltaTime();

				UnityEngine::CanvasRenderer::SetAlpha(targetImage, 1);

				auto evaluate = UnityEngine::AnimationCurve::Evaluate(animationCurve, 1 - t) * targetSize;

				UnityEngine::Transform::set_localScale(transform, vec3(evaluate, evaluate, evaluate));
			}
			else {
				UnityEngine::CanvasRenderer::SetAlpha(targetImage, 0);
			}
		}
	}

	namespace ItemPickupBase {

		tMethod oUpdate = 0;
		float delta = 0;
		bool updated = false;

		void Update(uintptr_t component)
		{
			if (!cvar::visuals::itemEsp)
			{
				itemList.clear();
				return oUpdate(component);
			}

			auto pos = UnityEngine::Transform::get_position(UnityEngine::Component::get_transform(component));

			if(GetDistance(Local::position, pos) > cvar::visuals::itemRenderDistance)
				return oUpdate(component);

			auto info = InventorySystem_Items_Pickups::ItemPickupBase::get_NetworkInfo(component);

			static Pickup ent = Pickup();

			ent.Reset();

			ent.object = component;
			ent.position = pos;
			ent.itemId = info.ItemId;

			bool itemWasFound = false;

			for (int i = 0; i < itemList.size(); i++)
			{
				if (itemList[i].object != component)
					continue;

				itemWasFound = true;

				itemList[i] = ent;
				break;
			}

			delta += UnityEngine::Time::get_deltaTime();

			if (delta >= cvar::visuals::itemUpdateCooldown)
			{
				delta = 0;
				itemWasFound = false;
				itemList.clear();
			}
			else {
				if (itemWasFound)
				{
					ent.Reset();
					return oUpdate(component);
				}
			}

			if(!itemWasFound)
				itemList.push_back(ent);

			ent.Reset();

			oUpdate(component);
		}
	}

	namespace RoomIdentifier {
		tMethod oAwake = 0;

		void Awake(uintptr_t _this) {


			oAwake(_this);

			auto room = (RoomName)MapGeneration::RoomIdentifier::field_Name(_this);

			if (!RoomHelper::isValidEspRoom(room))
				return;

			static Location tmp;
			tmp.Reset();
			tmp.object = UnityEngine::Component::get_gameObject(_this);
			tmp.position = UnityEngine::Transform::get_position(UnityEngine::Component::get_transform(_this));
			tmp.name = room;

			locationList.push_back(tmp);
		}
	}

	namespace BasicDoor {
		tMethod oUpdate = 0;

		void Update(uintptr_t _this) {

			oUpdate(_this);

			auto transform = UnityEngine::Component::get_transform(_this);
			auto pos = UnityEngine::Transform::get_position(transform);

			auto _array = Interactables_Interobjects::BasicDoor::field__buttons(_this);
			if (!_array)
				return;

			int len = Array::Length(_array);

			float bestBtnDistance = 500;

			uintptr_t bestBtn = NULL;
			uintptr_t bestBtnTransform = NULL;

			for (int i = 0; i < len; i++) {
				auto btn = Array::Get(_array, 0);
				if (!btn)
					continue;

				auto btnTransform = UnityEngine::Component::get_transform(btn);

				float dist = GetDistance(Local::getPos(), UnityEngine::Transform::get_position(btnTransform));

				if (dist < bestBtnDistance)
				{
					bestBtnDistance = dist;
					bestBtn = btn;
					bestBtnTransform = btnTransform;
				}
			}

			if( bestBtn == NULL || bestBtnTransform == NULL )
				return;

			static vec3 myPos;
			myPos = Local::serverPosition;

			if (myPos == vector3zero)
				myPos = Local::position;

			static Door ent;

			ent.Reset();

			ent.object = _this;
			ent.transform = transform;
			ent.position = pos;
			ent.interactable = bestBtn;
			ent.interactableTransform = bestBtnTransform;
			ent.interactablePosition = UnityEngine::Transform::get_position(bestBtnTransform);

			float dist = GetDistance(myPos, ent.interactablePosition);

			bool flag = scpDoor.object != NULL && dist < scpDoor.distance();

			if (dist > 4.69f || !cvar::player::scpcbDoorInteractive)
			{
				ent.Reset();
				return;
			}

			if (!flag && scpDoor.object != NULL)
				return;

			scpDoor = ent;
			ent.Reset();
		}
	}

	namespace InteractableCoordinator {

		tMethod oUpdate = 0;

		void Update(uintptr_t _this) {
			oUpdate(_this);

			if (!Mirror::NetworkBehaviour::get_isLocalPlayer(_this))
				return;

			if (Input::GetKeyInt(Input::KeyCode::E) && (scpDoor.object != NULL && scpDoor.interactable != NULL) && scpDoor.distance() < 4.69f) {
				auto netIdentity = Mirror::NetworkBehaviour::get_netIdentity(scpDoor.object);
				auto colId = Interactables::InteractableCollider::field_ColliderId(scpDoor.interactable);
				Interactables::InteractionCoordinator::CmdServerInteract(_this, netIdentity, colId);
			}
		}
	}
}

#ifdef _DEVELOPER
namespace scp_speedhack {
	typedef float(__fastcall* tGetMaxSpeed)(uintptr_t);

	tGetMaxSpeed o049 = 0;
	tGetMaxSpeed o096 = 0;
	tGetMaxSpeed o939 = 0;
	tGetMaxSpeed o173 = 0;

	tMethod scp049upd = 0;

	float getSpeed(float base) {
		if (!cvar::speedhack::active)
			return base;

		return base * cvar::speedhack::multiplier;
	}

	void hk049_Update(uintptr_t _this) {
		scp049upd(_this);

		hooks::PlayableScpsController::remainingCooldown = PlayableScps::Scp049::field_RemainingKillCooldown(_this);
	}

	float hk049(uintptr_t _this) {
		return getSpeed(o049(_this));
	}

	float hk096(uintptr_t _this) {
		return getSpeed(o096(_this));
	}

	float hk939(uintptr_t _this) {
		return getSpeed(o939(_this));
	}

	float hk173(uintptr_t _this) {
		return getSpeed(o173(_this));
	}
}
#endif