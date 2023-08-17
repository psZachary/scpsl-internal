#include "includes.h"
#include "xorstr.hpp"
#include <comdef.h>
#include <structs.h>
#include <D3DX11tex.h>
#pragma comment(lib, "D3DX11.lib")
#include <mathn.h>
#include <ImGuiUtils.h>
#include <global.h>
#include "RoomHelper.h"
#include "AimbotHelper.h"
#include "RoleHelper.h"
#include "memory.h"
#include "MenuFonts.h"
#include "MenuControls.h"
#include "hooks.h"
#include "Menu.h"
#include "Renderer.h"
#include <conio.h>
#include "rainbow.h"
#include <string>
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;




void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = NULL;
	io.WantSaveIniSettings = false;
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

	Renderer::myMenuFont = io.Fonts->AddFontFromMemoryCompressedTTF(&menuFontRaw_compressed_data, menuFontRaw_compressed_size, 14.f);
	Renderer::myMenuFontScaled = io.Fonts->AddFontFromMemoryCompressedTTF(&menuFontRaw_compressed_data, menuFontRaw_compressed_size, 28.f);
	Renderer::men = io.Fonts->AddFontFromMemoryCompressedTTF(&menuFontRaw_compressed_data, menuFontRaw_compressed_size, 18.f);

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
	Menu::Style();
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

bool init = false;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{

			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
		
			Hooks::Initialize();
			
			
			

			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGuiIO& io = ImGui::GetIO();

	io.IniFilename = NULL;
	io.WantSaveIniSettings = false;

	static bool d_init = false;

	if (!d_init)
	{
		cvar::DefaultSettings();
		d_init = true;

	}

	rainbow::do_rainbow();

	if (cvar::menu::show) {

		ImGui::PushFont(Renderer::men);
		Menu::DrawMenu();
		ImGui::PopFont();
	}

#pragma region  OVERLAY_WINDOW
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(io.DisplaySize);
	ImGui::Begin(xorstr_("###OverlayWindow"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);
#pragma endregion

	Renderer::Draw(io);

	ImGui::End();
	ImGui::Render();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	
	return oPresent(pSwapChain, SyncInterval, Flags);
}

void MainThread()
{
	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{

			kiero::bind(8, (void**)&oPresent, hkPresent);
			init_hook = true;
		}
	} while (!init_hook);
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		MainThread();
		//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MainThread, NULL, NULL, NULL);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}