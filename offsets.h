#pragma once
namespace offset {

	// camera
	constexpr uintptr_t camera = 0x10;
	constexpr uintptr_t matrix = 0xDC;
	constexpr uintptr_t camera_position = 0x42C;

	// unit3d
	constexpr uintptr_t unity_list_len = 0x18;
	constexpr uintptr_t unity_list_start = 0x20;
	constexpr uintptr_t unity_list_offset = 0x8;

	//NetworkClient.Send<RequestMessage>
	constexpr uintptr_t nc_msgRequest = 0x1788D40;

	//NetworkClient.Send<CoinNetworkHandler.CoinFlipMessage>
	constexpr uintptr_t nc_msgCoin = 0x1788230;
	
	//NetworkClient.Send<ShotMessage>
	constexpr uintptr_t nc_msgShot = 0x178A170;

	//NetworkConnection.Send<CommandMessage>
	constexpr uintptr_t nc_cmd = 0x178B5C0;
}
