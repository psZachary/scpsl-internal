#pragma once
#include "imgui/imgui.h"

namespace RoleHelper {
	ImColor GetTeamColor(int team) {

		auto role = (RoleType)team;

		switch (role)
		{
		case None:
			return ImColor(255, 255, 255);
			// xorstr_("white");
			break;
		case Scp173:
			return ImColor(255, 0, 0);
			// xorstr_("red");
			break;
		case ClassD:
			return ImColor(184, 73, 0);
			// xorstr_("orange");
			break;
		case Spectator:
			return ImColor(255, 255, 255);
			// xorstr_("white");
			break;
		case Scp106:
			return ImColor(255, 0, 0);
			// xorstr_("red");
			break;
		case NtfSpecialist:
		case NtfSergeant:
			return ImColor(0, 119, 255);
			break;
		case Scp049:
			return ImColor(255, 0, 0);
			// xorstr_("red");
			break;
		case Scientist:
			return ImColor(199, 199, 0);
			// xorstr_("yellow");
			break;
		case Scp079:
			return ImColor(255, 0, 0);
			break;
		case ChaosConscript:
		case ChaosMarauder:
		case ChaosRepressor:
		case ChaosRifleman:
			return ImColor(0, 163, 0);
			// xorstr_("green");
			break;
		case Scp096:
			return ImColor(255, 0, 0);
			// xorstr_("red");
			break;
		case Scp0492:
			return ImColor(255, 0, 0);
			// xorstr_("red");
			break;
		case NtfCaptain:
			return ImColor(0, 0, 255);
			// xorstr_("blue");
			break;
		case NtfPrivate:
			return ImColor(0, 217, 255);
			break;
		case Tutorial:
			return ImColor(0, 255, 0);
			// xorstr_("lime");
			break;
		case FacilityGuard:
			return ImColor(0, 219, 164);
			// xorstr_("lightblue");
			break;
		case Scp93953:
			return ImColor(255, 0, 0);
			// xorstr_("red");
			break;
		case Scp93989:
			return ImColor(255, 0, 0);
			// xorstr_("red");
			break;
		default:
			return ImColor(255, 255, 255);
			break;
		}

		return ImColor(255, 255, 255);
	}

	bool IsSCP(int team) {
		auto role = (RoleType)team;

		switch (role)
		{
		case Scp173:
		case Scp106:
		case Scp049:
		case Scp079:
		case Scp096:
		case Scp0492:
		case Scp93953:
		case Scp93989:
			return true;
		default:
			return false;
		}
	}

	bool IsAlive(int team, bool includeSpectator = false) {
		auto role = (RoleType)team;

		switch (role)
		{
		case Spectator:
			return includeSpectator;
		case Scp173:
		case ClassD:
		case Scp106:
		case NtfSpecialist:
		case Scp049:
		case Scientist:
		case Scp079:
		case ChaosConscript:
		case Scp096:
		case Scp0492:
		case NtfSergeant:
		case NtfCaptain:
		case NtfPrivate:
		case Tutorial:
		case FacilityGuard:
		case Scp93953:
		case Scp93989:
		case ChaosRifleman:
		case ChaosRepressor:
		case ChaosMarauder:
			return true;
		default:
			return false;
		}
	}

	bool IsHuman(int team) {
		auto role = (RoleType)team;

		switch (role)
		{
		case ClassD:
		case NtfSpecialist:
		case Scientist:
		case ChaosConscript:
		case NtfSergeant:
		case NtfCaptain:
		case NtfPrivate:
		case Tutorial:
		case FacilityGuard:
		case ChaosRifleman:
		case ChaosRepressor:
		case ChaosMarauder:
			return true;
		default:
			return false;
		}
	}

	bool IsNTF(int team) {
		auto role = (RoleType)team;

		switch (role)
		{
		case NtfSpecialist:
		case Scientist:
		case NtfSergeant:
		case NtfCaptain:
		case NtfPrivate:
		case FacilityGuard:
			return true;
		default:
			return false;
		}
	}

	bool IsChaos(int team) {
		auto role = (RoleType)team;

		switch (role)
		{
		case ClassD:
		case ChaosConscript:
		case ChaosRifleman:
		case ChaosRepressor:
		case ChaosMarauder:
			return true;
		default:
			return false;
		}
	}

	bool AimPermission(int local, int target, bool friendlyFire, bool scpFriendlyFire, bool targetSerpentsHand) {

		if (!targetSerpentsHand && target == 14) return false;

		if (IsNTF(local))
		{
			if (IsNTF(target))
				return friendlyFire;
			else
				return true;
		}

		if (IsChaos(local))
		{
			if (IsChaos(target))
				return friendlyFire;
			else
				return true;
		}

		if (IsSCP(local)) {
			if (IsSCP(target))
#if _DEVELOPER
				return scpFriendlyFire;
#else
				return false;
#endif
			else
				return true;
		}

		if (local == 14 && target == 14) return friendlyFire;

		return true;
	}

	float GetAimbotOffset(int hitbox, int classId) {

		switch (classId)
		{
		case 0: //173
			return 0.5f;
		case 3: //106
			return 0.65f;
		case 9: //096
			return 0.5f;
		case 5: //049
			return 0.45f;
		case 16://939
		case 17:
			return 0.13f;
		default:
			if (hitbox == 0) // body
				return 0.45f;
			else if (hitbox == 1) // neck
				return 0.75f;
			else
				return 0.8;
			break;
		}

		return 0.f;
	}
}