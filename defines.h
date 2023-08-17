#pragma once

typedef void(__fastcall* tMethod)(uintptr_t);

enum TriggerType : uint8_t
{
	Nil = 0,
	Proximity = 1,
	Role = 2,
	Intercom = 4
};

enum DissonanceRoleType
{
	Ghost,
	SCP,
	Null
};

enum SpeakingFlags : uint8_t
{
	RadioAsHuman = 1,
	IntercomAsHuman = 2,
	MimicAs939 = 4,
	SpeakerAs079 = 8,
	SpectatorChat = 16,
	SCPChat = 32
};

enum KeycardPermissions : uint16_t
{
	Nonekc = 0,
	Checkpoints = 1,
	ExitGates = 2,
	Intercomkc = 4,
	AlphaWarhead = 8,
	ContainmentLevelOne = 16,
	ContainmentLevelTwo = 32,
	ContainmentLevelThree = 64,
	ArmoryLevelOne = 128,
	ArmoryLevelTwo = 256,
	ArmoryLevelThree = 512,
	ScpOverride = 1024
};

typedef unsigned long long ulong_t;

DEFINE_ENUM_FLAG_OPERATORS(TriggerType)
DEFINE_ENUM_FLAG_OPERATORS(SpeakingFlags)
DEFINE_ENUM_FLAG_OPERATORS(KeycardPermissions)

bool HasKeycardFlag(KeycardPermissions perm, KeycardPermissions flag) {

	return (perm & flag) == flag;
}

bool IsArmory(KeycardPermissions perms)
{
	return HasKeycardFlag(perms, KeycardPermissions::ArmoryLevelOne);
}

bool IsCheckpoint(KeycardPermissions perms)
{
	return HasKeycardFlag(perms, KeycardPermissions::Checkpoints);
}

bool IsGate(KeycardPermissions perms)
{
	return HasKeycardFlag(perms, KeycardPermissions::ExitGates);
}