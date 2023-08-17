#pragma once

namespace hooks {
	namespace hkUnityEngine {
		namespace PostProcessVolume {
			tMethod oUpdate = 0;

			void Update(uintptr_t component) {
				if (component == NULL)
					return;

				if(Local::role == Scp93953 || Local::role == Scp93989 || Local::role == Spectator)
					UnityEngine::Behaviour::set_enabled(component, true);
				else
					UnityEngine::Behaviour::set_enabled(component, false);
			}
		}

		namespace Camera {
			typedef void(__fastcall* tSetFOV)(uintptr_t, float);

			tSetFOV oSetFOV = 0;

			void set_Fov(uintptr_t camera, float value) {
				if (camera == NULL)
					return;

				oSetFOV(camera, cvar::cameraFov);
			}
		}

		namespace Physics {

			struct Ray {
				UVector3 origin;
				UVector3 direction;
			};

			typedef bool(__fastcall* tRaycast)(UVector3, UVector3, uintptr_t*, float, int);
			typedef bool(__fastcall* tRaycast01)(UVector3, UVector3, uintptr_t*, float, int, int);
			typedef bool(__fastcall* tRaycast02)(Ray, uintptr_t*, float, int);
			typedef bool(__fastcall* tRaycast03)(Ray, uintptr_t*, float, int, int);
			typedef uintptr_t(__fastcall* tRaycastAll)(UVector3, UVector3, float, int);

			tRaycast oRaycast = 0;
			tRaycast01 oRaycast01 = 0;
			tRaycast02 oRaycast02 = 0;
			tRaycast03 oRaycast03 = 0;
			tRaycastAll oRaycastAll = 0;

			bool hkRaycast(UVector3 origin, UVector3 direction, uintptr_t* hitInfo, float maxDistance, int layerMask) {
				return oRaycast(origin, direction, hitInfo, 7000, layerMask);
			}

			bool hkRaycast01(UVector3 origin, UVector3 direction, uintptr_t* hitInfo, float maxDistance, int layerMask, int query) {
				return oRaycast01(origin, direction, hitInfo, 7000, layerMask, query);
			}

			bool hkRaycast02(Ray ray, uintptr_t* hitInfo, float maxDistance, int layerMask) {
				return oRaycast02(ray, hitInfo, 7000, layerMask);
			}

			bool hkRaycast03(Ray ray, uintptr_t* hitInfo, float maxDistance, int layerMask, int query) {
				return oRaycast03(ray, hitInfo, 7000, layerMask, query);
			}

			uintptr_t hkRaycastAll(UVector3 origin, UVector3 direction, float maxDistance, int layerMask) {
				return oRaycastAll(origin, direction, 7000, layerMask);
			}
		}
	}
}