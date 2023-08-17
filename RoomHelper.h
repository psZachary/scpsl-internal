#pragma once

#ifndef ROOMS_ENUM
enum RoomName
{
	Unnamed,
	LczClassDSpawn,
	LczComputerRoom,
	LczCheckpointA,
	LczCheckpointB,
	LczToilets,
	LczArmory,
	Lcz173,
	LczGlassroom,
	Lcz012,
	Lcz914,
	LczGreenhouse,
	LczAirlock,
	HczCheckpointToEntranceZone,
	HczCheckpointA,
	HczCheckpointB,
	HczWarhead,
	Hcz049,
	Hcz079,
	Hcz096,
	Hcz106,
	Hcz939,
	HczMicroHID,
	HczArmory,
	HczServers,
	HczTesla,
	EzCollapsedTunnel,
	EzGateA,
	EzGateB,
	EzRedroom,
	EzEvacShelter,
	EzIntercom,
	EzOfficeStoried,
	EzOfficeLarge,
	EzOfficeSmall,
	Outside,
	Pocket
};
#define ROOMS_ENUM
#endif

namespace RoomHelper {
	bool isValidEspRoom(RoomName name) {
		switch (name)
		{
		case RoomName::Unnamed:
		case RoomName::LczClassDSpawn:
		case RoomName::LczComputerRoom:
		case RoomName::LczToilets:
		case RoomName::LczGlassroom:
		case RoomName::LczGreenhouse:
		case RoomName::LczAirlock:
		case RoomName::HczServers:
		case RoomName::HczTesla:
		case RoomName::EzCollapsedTunnel:
		case RoomName::EzRedroom:
		case RoomName::EzEvacShelter:
		case RoomName::EzIntercom:
		case RoomName::EzOfficeStoried:
		case RoomName::EzOfficeLarge:
		case RoomName::EzOfficeSmall:
		case RoomName::Outside:
		case RoomName::Pocket:
			return false;
		default:
			return true;
		}
	}
}