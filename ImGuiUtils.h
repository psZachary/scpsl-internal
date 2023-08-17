#pragma once

namespace Utils {
	
	void DrawTextShadowed(ImDrawList* drawList, ImVec2 out, ImColor color, const char* text) {

		static ImColor col = ImColor(0, 0, 0, 255);

		if (color == col)
		{
			col = ImColor(255, 255, 255, 255);
		}

		drawList->AddText(ImVec2(out.x - 1.f, out.y), col, text);
		drawList->AddText(ImVec2(out.x + 1.f, out.y), col, text);
		drawList->AddText(ImVec2(out.x, out.y + 1.f), col, text);
		drawList->AddText(ImVec2(out.x, out.y - 1.f), col, text);
		drawList->AddText(ImVec2(out.x, out.y), color, text);
	}

	void DrawTextShadowed(ImDrawList* drawList, vec2 out, ImColor color, const char* text) {
		DrawTextShadowed(drawList, ImVec2(out.X, out.Y), color, text);
	}

	void DrawTextCentered(ImDrawList* drawList, ImVec2 out, ImColor color, const char* text) {
		static ImVec2 ivec2 = ImVec2(0, 0);

		ivec2 = out;

		auto size = ImGui::CalcTextSize(text);

		ivec2.x -= size.x / 2;
		ivec2.y -= size.y / 2;

		DrawTextShadowed(drawList,ivec2,color,text);
	}

	void DrawTextCentered(ImDrawList* drawList, vec2 out, ImColor color, const char* text) {
		static ImVec2 ivec2 = ImVec2(0,0);

		ivec2.x = out.X;
		ivec2.y = out.Y;

		DrawTextCentered(drawList,ivec2,color,text);
	}
}