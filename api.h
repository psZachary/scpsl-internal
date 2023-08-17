#pragma once
#pragma warning(disable : 4244 4996 ) 
#include <Windows.h>
#include <cstdint>
#include "xorstr.hpp"
#include "WindowsFunctions.h"
#include "./math.h"
#include "utils.h"
#include "offsets.h"
#include <cwchar>
#include <xorstr.hpp>

struct UnityColor {
	UnityColor() {
		r = 1;
		g = 1;
		b = 1;
		a = 1;
	}

	UnityColor(float r, float g, float b, bool override255 = false) {

		if (!override255) {
			this->r = r / 255;
			this->g = g / 255;
			this->b = b / 255;
		}
		else {
			this->r = r;
			this->g = g;
			this->b = b;
		}
		a = 1;
	}

	UnityColor(float r, float g, float b, float a) {
		this->r = r / 255;
		this->g = g / 255;
		this->b = b / 255;
		this->a = a / 255;
	}

	float r, g, b, a;
};

struct UObject
{
	// UnityObject
	char pad[0x10];
};

struct Object : UObject
{
	uintptr_t m_CachedPtr; // System.IntPtr
};

struct Il2CppString : UObject
{
	int length;
	wchar_t data[120];
};

Il2CppString* IlString(const wchar_t* t) {
	Il2CppString data{};
	data.length = wcslen(t);
	std::wmemcpy(data.data, t, data.length);
	return &data;
}

Il2CppString IlString01(const wchar_t* t) {
	Il2CppString data{};
	data.length = wcslen(t);
	std::wmemcpy(data.data, t, data.length);
	return data;
}

namespace api {

	uintptr_t assemblyBase = 0;

	uintptr_t GetModuleBase()
	{
		if (assemblyBase == 0)
		{
			assemblyBase = GetModuleBaseAddressInternalPEB(xorstr_(L"GameAssembly.dll"));
		}
		return assemblyBase;
	}

	vec3 get_camera_position(uintptr_t camera) {
		if (camera != NULL) {
			camera = Read<uintptr_t>((uintptr_t)camera + offset::camera);
			return Read<vec3>(camera + offset::camera_position);
		}
		return vec3{};
	}

	Il2CppString EmptyStr() {
		static Il2CppString empt = IlString01(xorstr_(L""));
		return empt;
	}

	Il2CppString* EmptyStr01() {
		static Il2CppString* empt = IlString(xorstr_(L""));
		return empt;
	}

	Matrix get_viewmatrix(uintptr_t camera) {
		if (camera != NULL) {
			camera = Read<uintptr_t>((uintptr_t)camera + offset::camera);
			return Read<Matrix>(camera + offset::matrix);
		}
		return Matrix{};
	}
}