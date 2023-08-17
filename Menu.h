#pragma once
#include <imgui/imgui_internal.h>

static const ImVec2 button_size = ImVec2(120, 51.999f);

namespace Menu {

	int curTab = 0;
	int curSubTab = 0;

	static float misc_size = 192;

	void ChangeSubTab(int id) {
		curSubTab = id;
	}

	void ChangeTab(int id) {
		curTab = id;
		curSubTab = 0;
	}

	Input::KeyCode getStored() {
		auto tmp = cvar::Keybinding::stored;
		cvar::Keybinding::stored = Input::KeyCode::None;
		return tmp;
	}

	bool KeybindButton(const char* text, int keybindId) {
		bool res = (cvar::Keybinding::active && cvar::Keybinding::activeId == keybindId) ? ImGui::Button(xorstr_("PRESS ANY KEY")) : ImGui::Button(text);

		if (res)
		{
			if (!cvar::Keybinding::active)
			{
				cvar::Keybinding::active = true;
				cvar::Keybinding::activeId = keybindId;
			}
		}

		if (cvar::Keybinding::activeId == keybindId && cvar::Keybinding::finished) {
			cvar::Keybinding::activeId = -1;
			cvar::Keybinding::active = false;
			cvar::Keybinding::finished = false;
			return true;
		}

		return false;
	}

	void Visuals() {
		ImGui::Checkbox(xorstr_("BOBUCK!!!!!!"), &cvar::bobuck);
		ImGui::Checkbox(xorstr_("Player ESP"), &cvar::visuals::playerEsp);
		if (cvar::visuals::playerEsp) {
			ImGui::Checkbox(xorstr_("Aimbot Target"), &cvar::visuals::aimbot_target);
			if (cvar::visuals::aimbot_target) {
				ImGui::Text(xorstr_("Color"));
				InsertColorPicker3NoSpace(xorstr_("    "), cvar::visuals::aimbot_target_color, false);
				ImGui::Checkbox(xorstr_("Rainbow "), &cvar::visuals::aimbot_target_rainbow);
				if (cvar::visuals::aimbot_target_rainbow) {
					ImGui::SliderFloat(xorstr_("Rainbow Speed"), &cvar::visuals::rainbow_speed, 0, 5);
					ImGui::Separator();
				}
			}
			ImGui::SliderInt(xorstr_("Player Update Delay"), &cvar::visuals::entityListUpdateCooldown, 1, 50000);
			ImGui::Separator();
		}
		//ImGui::Checkbox(xorstr_("Chams"), &cvar::visuals::chams);
		ImGui::Checkbox(xorstr_("Location ESP"), &cvar::visuals::locationEsp);
		if (cvar::visuals::locationEsp)
		{
			ImGui::SliderFloat(xorstr_("Location Render Distance"), &cvar::visuals::locationRenderDistance, 1, 1000);
			ImGui::Separator();
		}
		ImGui::Checkbox(xorstr_("Player List"), &cvar::visuals::playerList);
		ImGui::Checkbox(xorstr_("Item ESP"), &cvar::visuals::itemEsp);

		if (cvar::visuals::itemEsp)
		{

			ImGui::SliderFloat(xorstr_("Item Render Distance"), &cvar::visuals::itemRenderDistance, 5, 500);
			ImGui::Separator();
		}
		ImGui::Checkbox(xorstr_("Ambience"), &cvar::visuals::ambience_enabled);
		if (cvar::visuals::ambience_enabled) {

			ImGui::Text(xorstr_("Color"));
			InsertColorPicker3NoSpace(xorstr_("   "), cvar::etc::ambientColor, false);
			ImGui::Checkbox(xorstr_("Rainbow   "), &cvar::etc::ambientRainbow);
			if (cvar::etc::ambientRainbow) {
				ImGui::SliderFloat(xorstr_("Rainbow Speed"), &cvar::visuals::rainbow_speed, 0, 5);
				ImGui::Separator();
			}
			ImGui::Separator();


		}
	}

	void Player() {
		ImGui::Checkbox(xorstr_("Anti-Tesla"), &cvar::player::antiTesla);
#if _DEVELOPER
		ImGui::Checkbox(xorstr_("Deaf 939"), &cvar::player::deaf939_enable);
#endif
		ImGui::Checkbox(xorstr_("Suicide"), &cvar::player::teslaKill);
		ImGui::Separator();
		ImGui::Checkbox(xorstr_("SCP:CB Door Interactive"), &cvar::player::scpcbDoorInteractive);
#if _DEVELOPER
		ImGui::Checkbox(xorstr_("Speedhack"), &cvar::speedhack::active);
		if (cvar::speedhack::active) {
			ImGui::SliderFloat(xorstr_("Multiplier"), &cvar::speedhack::multiplier, 1, 1.3f);
			ImGui::SliderFloat(xorstr_("Jump Multiplier"), &cvar::speedhack::jumpMultiplier, 0, 5);
			ImGui::Separator();
		}

		ImGui::SliderFloat(xorstr_("Minecraft Step"), &cvar::step, 0.3, 10);

		ImGui::Checkbox(xorstr_("Spinbot"), &cvar::player::spinbot);
		if (cvar::player::spinbot) {
			ImGui::SliderFloat(xorstr_("Spinbot Speed"), &cvar::player::spinbotSpeed, 1, 500);
		}

#endif
	}

	void Aimbot() {
		ImGui::Checkbox(xorstr_("Active"), &cvar::aimbot::active);
		ImGui::Checkbox(xorstr_("Friendly Fire"), &cvar::aimbot::friendlyFire);
#if _DEVELOPER
		ImGui::Checkbox(xorstr_("Silent"), &cvar::aimbot::silent);
#endif
		ImGui::Checkbox(xorstr_("Prioritize Humans"), &cvar::aimbot::prioritizeHumans);




		ImGui::Checkbox(xorstr_("Target Tutorial"), &cvar::aimbot::targetTutorial);

		if (cvar::aimbot::targetTutorial)
		{
			ImGui::Checkbox(xorstr_("Tutorial as Serpents Hand"), &cvar::aimbot::tutorialAsSerpentsHand);
		}
		ImGui::Separator();
		ImGui::Checkbox(xorstr_("FOV Circle"), &cvar::visuals::drawFovCircle);
		ImGui::SliderInt(xorstr_("Aimbot FOV"), &cvar::aimbot::fov, 10, 1500);

		if (ImGui::Button(xorstr_("<"))) {
			cvar::aimbot::hitbox--;
			if (cvar::aimbot::hitbox < 0)
				cvar::aimbot::hitbox = 2;
		}

		ImGui::SameLine();

		switch (cvar::aimbot::hitbox)
		{
		case 0:
			ImGui::Text(xorstr_("Body Hitbox"));
			break;
		case 1:
			ImGui::Text(xorstr_("Neck Hitbox"));
			break;
		case 2:
			ImGui::Text(xorstr_("Head Hitbox"));
			break;
		}

		ImGui::SameLine();

		if (ImGui::Button(xorstr_(">"))) {
			cvar::aimbot::hitbox++;
			if (cvar::aimbot::hitbox > 2)
				cvar::aimbot::hitbox = 0;
		}
	}

	void Misc_Mods() {

#if _DEVELOPER
		ImGui::Checkbox(xorstr_("SCP Friendly Fire"), &cvar::aimbot::scpFriendlyFire);
#endif
		ImGui::Checkbox(xorstr_("No Recoil"), &cvar::aimbot::noRecoil);
		ImGui::Checkbox(xorstr_("Full Auto"), &cvar::aimbot::fullAuto);
		ImGui::Checkbox(xorstr_("Custom Firerate"), &cvar::aimbot::customFirerate);
		if (cvar::aimbot::customFirerate) {
			ImGui::SliderFloat(xorstr_("Firerate"), &cvar::aimbot::customFirerate_c, 0, 0.5f);
		}
#if _DEVELOPER
		ImGui::Checkbox(xorstr_("Double Tap"), &cvar::aimbot::doubleTap);
#endif
	}

	void Misc_Keybinding() {
		if (KeybindButton(xorstr_("NOCLIP KEY"), 0))
			cvar::Keybinds::noclip = getStored();

		if (KeybindButton(xorstr_("MENU KEY"), 1))
			cvar::Keybinds::toggleMenu = getStored();

#if _DEVELOPER

		if (KeybindButton(xorstr_("SPINBOT KEY"), 2))
			cvar::Keybinds::spinbot = getStored();

#endif

		if (KeybindButton(xorstr_("FRIENDLY FIRE KEY"), 3))
			cvar::Keybinds::friendlyfire = getStored();

		if (KeybindButton(xorstr_("SPEEDHACK KEY"), 4))
			cvar::Keybinds::speedhack = getStored();

		if (KeybindButton(xorstr_("AIMBOT KEY"), 5))
			cvar::Keybinds::aimbot = getStored();

#if _DEVELOPER

		if (KeybindButton(xorstr_("DOUBLE TAP KEY"), 6))
			cvar::Keybinds::doubleTap = getStored();

#endif
	}

	void Misc_Main() {
		ImGui::Checkbox(xorstr_("Hear Spectators"), &cvar::etc::hearAll);
		ImGui::Checkbox(xorstr_("Anti-Desync"), &cvar::player::antiDesync);
		ImGui::SliderFloat(xorstr_("SCP:CB Door Interactive"), &cvar::visuals::doorYpos, -2000, 2000);

#if _DEVELOPER

		ImGui::SliderInt(xorstr_("Coin Earrape"), &cvar::callAmount, 1, 5000);
#endif



		ImGui::SliderFloat(xorstr_("Camera FOV"), &cvar::cameraFov, 10, 360);
	}

	void Misc() {

		if (ImGui::Button(xorstr_("MAIN"), ImVec2(misc_size, 25)))
			curSubTab = 0;

		ImGui::SameLine();
		if (ImGui::Button(xorstr_("KEYBINDING"), ImVec2(misc_size, 25)))
			curSubTab = 1;

		ImGui::SameLine();
		if (ImGui::Button(xorstr_("MODS"), ImVec2(misc_size, 25)))
			curSubTab = 2;

		ImGui::Separator();

		if (curSubTab == 0) {
			Misc_Main();
		}
		else if (curSubTab == 1) {
			Misc_Keybinding();
		}
		else {
			Misc_Mods();
		}
	}

	void Style() {
		ImGuiStyle* style = &ImGui::GetStyle();
		ImVec4* colors = style->Colors;

		colors[ImGuiCol_Text] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.500f, 0.500f, 0.500f, 1.000f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.280f, 0.280f, 0.280f, 0.000f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
		colors[ImGuiCol_Border] = ImVec4(0.266f, 0.266f, 0.266f, 1.000f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.000f, 0.000f, 0.000f, 0.000f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.200f, 0.200f, 0.200f, 1.000f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.280f, 0.280f, 0.280f, 1.000f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.277f, 0.277f, 0.277f, 1.000f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.300f, 0.300f, 0.300f, 1.000f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_CheckMark] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_Button] = ImVec4(1.000f, 1.000f, 1.000f, 0.000f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
		colors[ImGuiCol_ButtonActive] = ImVec4(1.000f, 1.000f, 1.000f, 0.391f);
		colors[ImGuiCol_Header] = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
		colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(1.000f, 1.000f, 1.000f, 0.250f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.670f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_Tab] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.352f, 0.352f, 0.352f, 1.000f);
		colors[ImGuiCol_TabActive] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.586f, 0.586f, 0.586f, 1.000f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_NavHighlight] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);

		style->ChildRounding = 4.0f;
		style->FrameBorderSize = 1.0f;
		style->FrameRounding = 2.0f;
		style->GrabMinSize = 7.0f;
		style->PopupRounding = 2.0f;
		style->ScrollbarRounding = 12.0f;
		style->ScrollbarSize = 13.0f;
		style->TabBorderSize = 1.0f;
		style->TabRounding = 0.0f;
		style->WindowRounding = 0.f;

		style->WindowTitleAlign = ImVec2(0.500f, 0.500f);
	}

	void DrawTab() {
		switch (curTab) {
		case 0:
			Visuals();
			break;
		case 1:
			Player();
			break;
		case 2:
			Aimbot();
			break;
		case 3:
			Misc();
			break;
		}
	}

	void DrawMenu()
	{
		ImGui::SetNextWindowSize(ImVec2(608.000f, 400.000f), ImGuiCond_Once);
		ImGui::Begin("Temperate SCP:SL", NULL, 34);

		if (ImGui::Button("VISUALS", ImVec2(142.f, 25.000f)))
			ChangeTab(0);

		ImGui::SameLine();
		if (ImGui::Button("PLAYER", ImVec2(142.f, 25.000f)))
			ChangeTab(1);

		ImGui::SameLine();
		if (ImGui::Button("AIMBOT", ImVec2(142.f, 25.000f)))
			ChangeTab(2);

		ImGui::SameLine();
		if (ImGui::Button("MISC", ImVec2(142.f, 25.000f)))
			ChangeTab(3);

		ImGui::Separator();

		DrawTab();

		ImGui::End();
	}
}