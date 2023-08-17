#pragma once
//#include "SCPSL/InventorySystem_Searching/SearchCompletor.h"
//Renderer Code Here

namespace Renderer {

	ImFont* men;
	ImFont* myMenuFont;
	ImFont* myMenuFontScaled;

	wchar_t wbuffer[512];
	char buffer[512];

	ImDrawList* drawList = nullptr;

	int barId = 0;


	

	void InfoBarLabel(const char* text) {

		auto io = ImGui::GetIO();

		ImVec2 pos = ImVec2(io.DisplaySize.x, 0);

		auto size = ImGui::CalcTextSize(text);

		pos.x -= size.x;
		pos.y += size.y + (size.y * barId);

		drawList->AddText(pos, ImColor(255, 255, 255), text);

		barId++;
	}

	void InfoBar() {
		barId = 0;

		if (cvar::aimbot::active) InfoBarLabel(xorstr_("Aimbot"));
		if (cvar::aimbot::friendlyFire) InfoBarLabel(xorstr_("Friendly Fire"));
#if _DEVELOPER
		if (cvar::aimbot::scpFriendlyFire) InfoBarLabel(xorstr_("SCP Friendly Fire"));
#endif
		if (cvar::player::spinbot) InfoBarLabel(xorstr_("Spinbot"));
		if (cvar::player::antiTesla) InfoBarLabel(xorstr_("Anti-Tesla"));
#if _DEVELOPER
		if (cvar::speedhack::active) InfoBarLabel(xorstr_("Speedhack"));
#endif
		if (cvar::visuals::playerEsp) InfoBarLabel(xorstr_("Player ESP"));

	}

	void DrawPlayer(Player ply, ImColor col, vec2 out, float dist) {

		auto size = ImGui::CalcTextSize(xorstr_("SIZE"));
		ImColor tmp_color = col;
		static vec2 tmp;
		tmp = out;

		if (cvar::visuals::aimbot_target_rainbow)
			tmp_color = ImColor((float)(cvar::visuals::rainbow_color.r), (float)(cvar::visuals::rainbow_color.g), (float)(cvar::visuals::rainbow_color.b));
		else 
			tmp_color = ImColor((float)(cvar::visuals::aimbot_target_color[0]), (float)(cvar::visuals::aimbot_target_color[1]), (float)(cvar::visuals::aimbot_target_color[2]));

		if (aimbotTarget.object == ply.object)
		{
			if (!cvar::visuals::aimbot_target_rainbow)
				Utils::DrawTextCentered(drawList, tmp, ImColor(115, 77, 250), xorstr_("Aimbot"));
			else
				Utils::DrawTextCentered(drawList, tmp, tmp_color, xorstr_("Aimbot"));

			tmp.Y += (size.y + 2);
		}

		wsprintfW(wbuffer, xorstr_(L"%s"), ply.name.data);

		if (aimbotTarget.object == ply.object)
			Utils::DrawTextCentered(drawList, tmp, tmp_color, _bstr_t(wbuffer));
		else 
			Utils::DrawTextCentered(drawList, tmp, col, _bstr_t(wbuffer));

		tmp.Y += (size.y + 2);

		wsprintfW(wbuffer, xorstr_(L"%s"), ply.role.data);

		if (aimbotTarget.object == ply.object)
			Utils::DrawTextCentered(drawList, tmp, tmp_color, _bstr_t(wbuffer));
		else
			Utils::DrawTextCentered(drawList, tmp, col, _bstr_t(wbuffer));

		tmp.Y += (size.y + 2);

		wsprintfW(wbuffer, xorstr_(L"%i m"), (int)dist);

		Utils::DrawTextCentered(drawList, tmp, ImColor(255, 255, 255, 255), _bstr_t(wbuffer));
	}

	void DrawLocation(Location loc, vec2 out, float dist)
	{
		auto size = ImGui::CalcTextSize(xorstr_("SIZE"));

		wchar_t* result = xorstr_(L"");

		switch (loc.name)
		{
		case LczCheckpointA:
			result = xorstr_(L"Checkpoint A");
			break;
		case LczCheckpointB:
			result = xorstr_(L"Checkpoint B");
			break;
		case LczArmory:
			result = xorstr_(L"Armory");
			break;
		case Lcz173:
			result = xorstr_(L"173 CR");
			break;
		case Lcz012:
			result = xorstr_(L"012 CR");
			break;
		case Lcz914:
			result = xorstr_(L"SCP-914");
			break;
		case HczCheckpointToEntranceZone:
			result = xorstr_(L"Checkpoint");
			break;
		case HczCheckpointA:
			result = xorstr_(L"LCZ A");
			break;
		case HczCheckpointB:
			result = xorstr_(L"LCZ B");
			break;
		case HczWarhead:
			result = xorstr_(L"Alpha Warhead");
			break;
		case Hcz049:
			result = xorstr_(L"049 CR");
			break;
		case Hcz079:
			result = xorstr_(L"079 CR");
			break;
		case Hcz096:
			result = xorstr_(L"096 CR");
			break;
		case Hcz106:
			result = xorstr_(L"106 CR");
			break;
		case Hcz939:
			result = xorstr_(L"939 CR");
			break;
		case HczMicroHID:
			result = xorstr_(L"Micro HID");
			break;
		case HczArmory:
			result = xorstr_(L"Armory");
			break;
		case EzGateA:
			result = xorstr_(L"Gate A");
			break;
		case EzGateB:
			result = xorstr_(L"Gate B");
			break;
		}

		static vec2 tmp;
		tmp = out;

		wsprintfW(wbuffer, xorstr_(L"%s"), result);
		Utils::DrawTextCentered(drawList, tmp, ImColor(185, 150, 255), _bstr_t(wbuffer));

		tmp.Y += (size.y + 2);

		wsprintfW(wbuffer, xorstr_(L"%im"), (int)dist);
		Utils::DrawTextCentered(drawList, tmp, ImColor(255,255,255), _bstr_t(wbuffer));
	}

	void DoESP(float sx, float sy) {

		auto io = ImGui::GetIO();

		int playerListId = 0;

		static Player bestTarget = Player();
		static Pickup bestItem = Pickup();

		bestTarget.Reset();
		bestItem.Reset();

		float bestDistance = 5000;

		static vec2 out;

		static ImColor locationColor = ImColor(128, 168, 255);
		static ImColor itemColor = RoleHelper::GetTeamColor(6);

		if (cvar::visuals::itemEsp)
		{
			for (auto item : itemList)
			{
				if (GetDistance(Local::position, item.position) > cvar::visuals::itemRenderDistance)
					continue;

				if (WorldToScreen(Local::viewMatrix, item.position, out, sx, sy))
				{
					wchar_t* itemName = xorstr_(L"UNDEFINED");

					switch (item.itemId)
					{
					case KeycardJanitor:
						itemName = xorstr_(L"Janitor Keycard");
						break;
					case KeycardScientist:
						itemName = xorstr_(L"Scientist Keycard");
						break;
					case KeycardResearchCoordinator:
						itemName = xorstr_(L"Major Researcher Keycard");
						break;
					case KeycardZoneManager:
						itemName = xorstr_(L"Zone Manager Keycard");
						break;
					case KeycardGuard:
						itemName = xorstr_(L"Facility Guard Keycard");
						break;
					case KeycardNTFOfficer:
						itemName = xorstr_(L"Private Keycard");
						break;
					case KeycardContainmentEngineer:
						itemName = xorstr_(L"Containment Engineer Keycard");
						break;
					case KeycardNTFLieutenant:
						itemName = xorstr_(L"Sergeant Keycard");
						break;
					case KeycardNTFCommander:
						itemName = xorstr_(L"Captain Keycard");
						break;
					case KeycardFacilityManager:
						itemName = xorstr_(L"Facility Manager Keycard");
						break;
					case KeycardChaosInsurgency:
						itemName = xorstr_(L"Chaos Insurgency Hacking Device");
						break;
					case KeycardO5:
						itemName = xorstr_(L"O5 Keycard");
						break;
					case Radio:
						itemName = xorstr_(L"Radio");
						break;
					case GunCOM15:
						itemName = xorstr_(L"COM-15");
						break;
					case Medkit:
						itemName = xorstr_(L"Medkit");
						break;
					case Flashlight:
						itemName = xorstr_(L"Flashlight");
						break;
					case MicroHID:
						itemName = xorstr_(L"Micro-HID");
						break;
					case SCP500:
						itemName = xorstr_(L"SCP-500");
						break;
					case SCP207:
						itemName = xorstr_(L"SCP-207");
						break;
					case Ammo12gauge:
						itemName = xorstr_(L"Ammo 12 gauge");
						break;
					case GunE11SR:
						itemName = xorstr_(L"AR-15");
						break;
					case GunCrossvec:
						itemName = xorstr_(L"Crossvec");
						break;
					case Ammo556x45:
						itemName = xorstr_(L"Ammo 556x45");
						break;
					case GunFSP9:
						itemName = xorstr_(L"FSP-9");
						break;
					case GunLogicer:
						itemName = xorstr_(L"Logicer");
						break;
					case GrenadeHE:
						itemName = xorstr_(L"HE Grenade");
						break;
					case GrenadeFlash:
						itemName = xorstr_(L"Flash Grenade");
						break;
					case Ammo44cal:
						itemName = xorstr_(L"Ammo 44 cal");
						break;
					case Ammo762x39:
						itemName = xorstr_(L"Ammo 762x39");
						break;
					case Ammo9x19:
						itemName = xorstr_(L"Ammo 9x19");
						break;
					case GunCOM18:
						itemName = xorstr_(L"COM-18");
						break;
					case SCP018:
						itemName = xorstr_(L"SCP-018");
						break;
					case SCP268:
						itemName = xorstr_(L"SCP-268");
						break;
					case Adrenaline:
						itemName = xorstr_(L"Adrenaline");
						break;
					case Painkillers:
						itemName = xorstr_(L"Painkillers");
						break;
					case Coin:
						itemName = xorstr_(L"Coin");
						break;
					case ArmorLight:
						itemName = xorstr_(L"Light Armor");
						break;
					case ArmorCombat:
						itemName = xorstr_(L"Combat Armor");
						break;
					case ArmorHeavy:
						itemName = xorstr_(L"Heavy Armor");
						break;
					case GunRevolver:
						itemName = xorstr_(L"Revolver");
						break;
					case GunAK:
						itemName = xorstr_(L"AK-47");
						break;
					case GunShotgun:
						itemName = xorstr_(L"Shotgun");
						break;
					case SCP330:
						itemName = xorstr_(L"SCP-330");
						break;
					case SCP2176:
						itemName = xorstr_(L"SCP-2176");
						break;
					case SCP244a:
						itemName = xorstr_(L"SCP-244-A");
						break;
					case SCP244b:
						itemName = xorstr_(L"SCP-244-B");
						break;
					default:
						itemName = xorstr_(L"");
						break;
					}

#if _DEVELOPER
					if (cvar::sniper::active) {
						auto distance2d = AimbotHelper::CalculateDistance(sx, sy, out.X, out.Y);

						bool canLock = true;

						if (distance2d < bestDistance) {
							bool permission = ItemHelper::CanSnipe(item.itemId);

							if (!permission) canLock = false;

							if (canLock) {
								bestItem = item;
								bestDistance = distance2d;

								//InventorySystem_Searching::SearchCompletor::_ctor()
							}
						}
					}
#endif

					static auto size = ImGui::CalcTextSize(xorstr_("U24IWHGIBEFWIUGUERGDFK"));
					static auto sniperColor = ImColor(149, 66, 245);

					static vec2 tmp;
					tmp = out;

					wsprintfW(wbuffer, XOR(L"%s - %im"), itemName, (int)GetDistance(Local::position, item.position));

					Utils::DrawTextCentered(drawList, tmp, itemColor, _bstr_t(wbuffer));
				}
			}
		}

		bestDistance = 5000;

		cvar::visuals::eluc += 1;

		for (int i = 0; i < entityList.size(); i++) {
			

			if (entityList[i].ccm == NULL || entityList[i].object == NULL)
				continue;

			auto pos = entityList[i].position;
			pos.Y += 1;

			auto distance3d = GetDistance(Local::position, entityList[i].position);

			auto color = RoleHelper::GetTeamColor(entityList[i].team);

			if (RoleHelper::IsAlive(entityList[i].team, true) && cvar::visuals::playerList) {
				playerListId++;
				float y = (14 * playerListId) + 5;

				wsprintfW(wbuffer, xorstr_(L"%s - %s"), entityList[i].role.data, entityList[i].name.data);

				Utils::DrawTextShadowed(drawList, vec2{ 5,y }, color, _bstr_t(wbuffer));
			}

			if (!cvar::visuals::playerEsp) continue;

			if (distance3d >= 200) continue;

			if (!RoleHelper::IsAlive(entityList[i].team, false) || entityList[i].isLocalPlayer) continue;

			if (WorldToScreen(Local::viewMatrix, pos, out, sx, sy)) {

				if (cvar::aimbot::active) {
					auto distance2d = AimbotHelper::CalculateDistance(sx, sy, out.X, out.Y);

					bool canLock = true;

					if (distance2d < bestDistance && distance2d <= cvar::aimbot::fov) {

#if _DEVELOPER
						bool ff = cvar::aimbot::scpFriendlyFire;
#else
						bool ff = false;
#endif

						bool permission = RoleHelper::AimPermission(Local::role, entityList[i].team, cvar::aimbot::friendlyFire, ff, cvar::aimbot::targetTutorial);

						if (!permission) canLock = false;
						if (!entityList[i].visible) canLock = false;
						if (cvar::aimbot::prioritizeHumans && RoleHelper::IsSCP(entityList[i].team) && bestTarget.object != NULL && !RoleHelper::IsSCP(bestTarget.team)) canLock = false;

						if (canLock) {
							bestTarget = entityList[i];
							bestDistance = distance2d;
						}
					}
				}

				DrawPlayer(entityList[i], color, out, distance3d);
			}
		}

		if (cvar::visuals::eluc >= cvar::visuals::entityListUpdateCooldown) {

			entityList.clear();
			cvar::visuals::eluc = 0;
		}

		if (cvar::visuals::locationEsp)
		{
			for (auto loc : locationList)
			{
				if (WorldToScreen(Local::viewMatrix, loc.position, out, sx, sy)) {
					float distance = GetDistance(Local::position, loc.position);
					if (distance < cvar::visuals::locationRenderDistance)
					DrawLocation(loc, out, distance);
				}
			}
		}

		aimbotTarget = bestTarget;
	}

	void DrawTarget(ImGuiIO& io) {
		if (aimbotTarget.object != NULL)
		{
			ImGui::PushFont(myMenuFontScaled);
			wsprintfW(wbuffer, xorstr_(L"[ %s ] - %s"), aimbotTarget.name.data, aimbotTarget.role.data);

			static ImVec2 position = ImVec2(0, 0);
			const char* text = _bstr_t(wbuffer);
			auto a = ImGui::CalcTextSize(text);

			position.x = io.DisplaySize.x / 2;
			position.y = io.DisplaySize.y * 0.8f;

			Utils::DrawTextCentered(drawList, position, RoleHelper::GetTeamColor(aimbotTarget.team), text);
			ImGui::PopFont();
		}
	}

	void DrawFovCircle(ImGuiIO& io, float sx, float sy) {
		if (!cvar::visuals::drawFovCircle)
			return;
		drawList->AddCircle(ImVec2(sx, sy), cvar::aimbot::fov, ImColor(255, 255, 255), 128);
	}

	void DrawOpenableDoor(float sx, float sy) {

		if (cvar::visuals::doorYpos == -65535.f)
			cvar::visuals::doorYpos = (sy * 0.8f);

		if (Local::camera == NULL || scpDoor.object == NULL || scpDoor.distance() > 4.69f)
			return;

		ImGui::PushFont(myMenuFontScaled);
		auto size = ImGui::CalcTextSize(xorstr_("[CAN OPEN DOOR]"));

		static ImVec2 position = ImVec2(0, 0);
		position.x = sx;
		position.y = cvar::visuals::doorYpos + size.y;
		Utils::DrawTextCentered(drawList, position, ImColor(255,255,0), xorstr_("[CAN OPEN DOOR]"));
		ImGui::PopFont();
	}

	void DrawAmmoCounter(ImGuiIO& io) {
		sprintf(buffer, xorstr_("%i"), Local::curAmmo);

		auto text = _bstr_t(buffer);

		ImGui::PushFont(myMenuFontScaled);

		auto size = ImGui::CalcTextSize(text);

		auto x = io.DisplaySize.x - size.x;
		auto y = io.DisplaySize.y - size.y;

		drawList->AddText(ImVec2(x,y), ImColor(255,255,255), text);

		ImGui::PopFont();
	}

	void DrawCustomCrosshair(ImGuiIO& io) {
		Utils::DrawTextCentered(drawList, ImVec2(io.DisplaySize.x/2, io.DisplaySize.y/2), ImColor(0, 255, 0), xorstr_("+"));
	}

	void Draw(ImGuiIO& io) {

		auto sx = io.DisplaySize.x / 2;
		auto sy = io.DisplaySize.y / 2;

		drawList = ImGui::GetBackgroundDrawList();

		DrawFovCircle(io, sx, sy);

		if (Local::camera != NULL)
		{
			DoESP(sx, sy);
			DrawTarget(io);
			DrawAmmoCounter(io);
			DrawCustomCrosshair(io);
		}
		DrawOpenableDoor(sx, sy);
		InfoBar();
	}
}