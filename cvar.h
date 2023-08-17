#pragma once

typedef struct {
	double r;       // a fraction between 0 and 1
	double g;       // a fraction between 0 and 1
	double b;       // a fraction between 0 and 1
} rgb;

namespace cvar {

	bool bobuck;

	namespace visuals {
		bool playerEsp, locationEsp, playerList, itemEsp, chams, chams_oldv, drawFovCircle, aimbot_target;
		float itemRenderDistance = 10;
		float itemUpdateCooldown = 55;
		float locationRenderDistance = 500;
		int entityListUpdateCooldown = 1000;
		int eluc = 0;
		float rainbow_color_h = 0;
		float rainbow_speed = 1;
		bool ambience_enabled;
		bool aimbot_target_rainbow;
		rgb rainbow_color = rgb();
		float aimbot_target_color[3] = { 1.0f, 1.0f, 1.0f };
		float doorYpos = -65535.f;
	}
	bool minecraftStep = true;
	float radius = -65535.f;
	float step = -65535.f;

	namespace aimbot {
		bool active, friendlyFire, targetTutorial, tutorialAsSerpentsHand, noRecoil, silent, prioritizeHumans;

#if _DEVELOPER
		bool scpFriendlyFire;
		bool doubleTap;
#endif

		int hitbox;
		int fov = 120;

		float customFirerate_c;

		bool fullAuto;
		bool customFirerate;
	}

	float btnSize = 30;

	namespace player {
		bool antiTesla, deaf939, deaf939_enable, noclip, teslaKill, antiDesync, scpcbDoorInteractive;

		bool spinbot, jitterMode;
		//-- DON'T SHOW ON MENU
		// Range 0,360
		float spinbotEuler;
		//---------------------
		float spinbotSpeed;

		bool holdToSprint = true;
	}

#if _DEVELOPER
	namespace sniper {
		bool active;

		bool snipeWeapons;
		bool snipeGrenades;
		bool snipeMedicals;
		bool snipeKeycards;
		bool snipeScps;
		bool snipeArmours;
		bool snipeAmmo;
		bool snipeOther;
	}

	namespace speedhack {
		bool active;
		float multiplier;
		float jumpMultiplier;
	}
#endif
	namespace menu {
		bool show = true;

		int id = 0;
	}

	namespace etc {
		bool hearAll;
		float ambientColor[3] = { 0.4f, 0.4f, 0.4f };
		bool ambientRainbow = false;
		bool experimentalServerCrashHandcuff;

#if _DEVELOPER
		bool memeMenu = true;
#endif
	}

	namespace Keybinding {
		bool active;
		int activeId;
		bool finished;
		bool is_b_down;
		Input::KeyCode stored;
	}

	namespace Keybinds {
		Input::KeyCode noclip = Input::KeyCode::F;
		Input::KeyCode toggleMenu = Input::KeyCode::Insert;
		Input::KeyCode spinbot = Input::KeyCode::None;
		Input::KeyCode speedhack = Input::KeyCode::K;
		Input::KeyCode friendlyfire = Input::KeyCode::None;
		Input::KeyCode visuals = Input::KeyCode::None;
		Input::KeyCode aimbot = Input::KeyCode::None;
		Input::KeyCode doubleTap = Input::KeyCode::None;
	}

	int callAmount = 50;

	float cameraFov = 70;

	void DefaultSettings() {
		visuals::playerList = true;
		visuals::playerEsp = true;
		visuals::locationEsp = true;
		player::antiDesync = true;
		player::antiTesla = true;
		player::deaf939_enable = true;
		player::teslaKill = false;
		aimbot::active = true;
		aimbot::fov = 500;
		aimbot::friendlyFire = false;
		aimbot::hitbox = 2;
		aimbot::noRecoil = true;
		aimbot::targetTutorial = true;
		aimbot::tutorialAsSerpentsHand = true;
#if _DEVELOPER
		speedhack::active = true;
		speedhack::multiplier = 1.3f;
		speedhack::jumpMultiplier = 0;
#endif
		etc::hearAll = true;
		callAmount = 1;
		aimbot::customFirerate = false;
		aimbot::customFirerate_c = 0;
		aimbot::fullAuto = true;
		aimbot::silent = true;
		aimbot::prioritizeHumans = true;
		visuals::aimbot_target_rainbow = true;
		visuals::itemEsp = true;

	}
}