#pragma once
#include "./math.h"
#include "./mathn.h"
#include "./api.h"

enum RoleType
{
	None = -1,
	Scp173,
	ClassD,
	Spectator,
	Scp106,
	NtfSpecialist,
	Scp049,
	Scientist,
	Scp079,
	ChaosConscript,
	Scp096,
	Scp0492,
	NtfSergeant,
	NtfCaptain,
	NtfPrivate,
	Tutorial,
	FacilityGuard,
	Scp93953,
	Scp93989,
	ChaosRifleman,
	ChaosRepressor,
	ChaosMarauder
};

enum ItemType
{
	NoneIT = -1,
	KeycardJanitor,
	KeycardScientist,
	KeycardResearchCoordinator,
	KeycardZoneManager,
	KeycardGuard,
	KeycardNTFOfficer,
	KeycardContainmentEngineer,
	KeycardNTFLieutenant,
	KeycardNTFCommander,
	KeycardFacilityManager,
	KeycardChaosInsurgency,
	KeycardO5,
	Radio,
	GunCOM15,
	Medkit,
	Flashlight,
	MicroHID,
	SCP500,
	SCP207,
	Ammo12gauge,
	GunE11SR,
	GunCrossvec,
	Ammo556x45,
	GunFSP9,
	GunLogicer,
	GrenadeHE,
	GrenadeFlash,
	Ammo44cal,
	Ammo762x39,
	Ammo9x19,
	GunCOM18,
	SCP018,
	SCP268,
	Adrenaline,
	Painkillers,
	Coin,
	ArmorLight,
	ArmorCombat,
	ArmorHeavy,
	GunRevolver,
	GunAK,
	GunShotgun,
	SCP330,
	SCP2176,
	SCP244a,
	SCP244b
};

struct RecoilSettings {

	float AnimationTime;
	float ZAxis;
	float FovKick;
	float UpKick;
	float SideKick;
	float AutoBack;

	RecoilSettings() {
		this->AnimationTime = 0;
		this->ZAxis = 0;
		this->FovKick = 0;
		this->UpKick = 0;
		this->SideKick = 0;
		this->AutoBack = 0;
	}
};

struct RagdollInfo {
	int RoleType;
	Il2CppString Nickname;
	uintptr_t Handler;
	UVector3 StartPosition;
	UQuaternion StartRotation;
	double CreationTime;
	uintptr_t OwnerHub;
};

struct FirearmStatus {
	uint8_t Ammo;
	uint8_t Flags;
	uint16_t Attachments;
};

struct ShotMessage {
	uint32_t TargetNetId;
	vec3 TargetPosition;
	quat TargetRotation;
	int ShooterWeaponSerial;
	vec3 ShooterPosition;
	float ShooterCharacterRotation;
	float ShooterCameraRotation;
};

struct RaycastHit {
	vec3 m_Point;
	vec3 m_Normal;
	uint16_t m_FaceID;
	float m_Distance;
	vec2 m_UV;
	int m_Collider;
};

struct Footprint {
	uintptr_t Hub;
	bool IsSet;
	int PlayerId;
	uint16_t NetId;
	RoleType Role;
	Il2CppString Unit;
	Il2CppString Nickname;
	Il2CppString LogUserID;
	uintptr_t Stopwatch;
};

struct ItemIdentifier {
	int TypeId;
	uint16_t SerialNumber;
};

struct HitmarkerMessage {
	uint8_t size;
};

struct tPickupSyncInfo {
	static tPickupSyncInfo NonePSI;
	ItemType ItemId;
	uint16_t Serial;
	float Weight;
	vec3 Position;
	uintptr_t Rotation;
	uint8_t _flags;
};

struct Keyframe
{
	float m_Time;
	float m_Value;
	float m_InTangent;
	float m_OutTangent;
	int m_WeightedMode;
	float m_InWeight;
	float m_OutWeight;

	Keyframe(float time, float value, float inTangent, float outTangent, int weightedMode, float inWeight, float outWeight)
	{
		m_Time = time;
		m_Value = value;
		m_InTangent = inTangent;
		m_OutTangent = outTangent;
		m_WeightedMode = weightedMode;
		m_InWeight = inWeight;
		m_OutWeight = outWeight;
	}
};

namespace Array {
	int Length(uintptr_t arrayPtr)
	{
		if (!arrayPtr)
			return -1;

		return Read<int>(arrayPtr + offset::unity_list_len);
	}

	uintptr_t GetAddress(uintptr_t arrayPtr, int i)
	{
		return arrayPtr + offset::unity_list_start + offset::unity_list_offset * i;
	}

	template <typename T>
	T Get(uintptr_t arrayPtr, int i)
	{
		return Read<T>(GetAddress(arrayPtr,i));
	}

	uintptr_t Get(uintptr_t arrayPtr, int i)
	{
		return Read<uintptr_t>(GetAddress(arrayPtr, i));
	}
}