#pragma once
#include <Windows.h>

namespace SpecialHooks {
	HWND _stdcall hkFindWindowA(LPCSTR arg1, LPCSTR arg2) {
		return NULL;
	}

	HWND _stdcall hkFindWindowW(LPCWSTR arg1, LPCWSTR arg2) {
		return NULL;
	}
}