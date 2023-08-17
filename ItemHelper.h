#pragma once

namespace ItemHelper {
	bool CanSnipe(ItemType item) {
#ifndef _DEVELOPER
		return false;
#else
		if (!cvar::sniper::active)
			return false;

		switch (item)
		{
		case KeycardJanitor:
		case KeycardScientist:
		case KeycardResearchCoordinator:
		case KeycardZoneManager:
		case KeycardGuard:
		case KeycardNTFOfficer:
		case KeycardContainmentEngineer:
		case KeycardNTFLieutenant:
		case KeycardNTFCommander:
		case KeycardFacilityManager:
		case KeycardChaosInsurgency:
		case KeycardO5:
			return cvar::sniper::snipeKeycards;
		case Radio:
			return cvar::sniper::snipeOther;
		case GunCOM15:
			return cvar::sniper::snipeWeapons;
		case Medkit:
			return cvar::sniper::snipeMedicals;
		case Flashlight:
			return cvar::sniper::snipeOther;
		case MicroHID:
			return cvar::sniper::snipeWeapons;
		case SCP500:
		case SCP207:
			return cvar::sniper::snipeScps;
		case Ammo12gauge:
			return cvar::sniper::snipeAmmo;
		case GunE11SR:
		case GunCrossvec:
			return cvar::sniper::snipeWeapons;
		case Ammo556x45:
			return cvar::sniper::snipeAmmo;
		case GunFSP9:
		case GunLogicer:
			return cvar::sniper::snipeWeapons;
		case GrenadeHE:
		case GrenadeFlash:
			return cvar::sniper::snipeGrenades;
		case Ammo44cal:
		case Ammo762x39:
		case Ammo9x19:
			return cvar::sniper::snipeAmmo;
		case GunCOM18:
			return cvar::sniper::snipeWeapons;
		case SCP018:
		case SCP268:
			return cvar::sniper::snipeScps;
		case Adrenaline:
		case Painkillers:
			return cvar::sniper::snipeMedicals;
		case Coin:
			return cvar::sniper::snipeOther;
		case ArmorLight:
		case ArmorCombat:
		case ArmorHeavy:
			return cvar::sniper::snipeArmours;
		case GunRevolver:
		case GunAK:
		case GunShotgun:
			return cvar::sniper::snipeWeapons;
		case SCP330:
		case SCP2176:
		case SCP244a:
		case SCP244b:
			return cvar::sniper::snipeScps;
		default:
			return true;
		}
#endif
	}
}