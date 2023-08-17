#pragma once
#include <cstdint>
#include "./math.h"
#include "api.h"
#include <vector>

static const vec3 vector3zero = vec3(0, 0, 0);

struct Entity {
	uintptr_t object;
	vec3 position;
};

struct Player : Entity {
	uintptr_t ccm, pms, referenceHub;
	Il2CppString name, role;
	int team;
	uint32_t netId;
	bool visible;
	bool isLocalPlayer;
	int id, hp;
	int itemId;
	vec3 screenPos;

	void Reset() {
		object = NULL;
		position = vector3zero;
		ccm = NULL;
		team = 0;
		visible = false;
		isLocalPlayer = false;
		name = api::EmptyStr();
		role = api::EmptyStr();
	}

	Player() {
		Reset();
	}
};

struct Pickup : Entity {
	ItemType itemId;

	void Reset()
	{
		object = NULL;
		position = vector3zero;
		itemId = ItemType::NoneIT;
	}

	Pickup() {
		Reset();
	}
};

struct Location : Entity {

	RoomName name;

	void Reset() {
		object = NULL;
		position = vector3zero;
		name = RoomName::Unnamed;
	}

	Location() {
		Reset();
	}
};

std::vector<Player> entityList;
std::vector<Pickup> itemList;
std::vector<Location> locationList;

Player aimbotTarget = Player();


int aimbotMask = 0;
bool cachedMask = false;

uintptr_t curRole, oldRole;

uintptr_t CustomNetManagerTransform;

void EspReset() {
	entityList.clear();
	locationList.clear();
	itemList.clear();
}

namespace Local {
	vec3 position, serverPosition;
	int role;
	uintptr_t camera, address, transform, hub, mouseLook, cameraTransform;
	vec3 cameraPosition;
	Matrix viewMatrix;
	uintptr_t interactCoordinator;
	int curItem;
	int curItemSerial;
	int curAmmo;

	void Reset() {
		role = -1;
		position.Reset();
		serverPosition.Reset();
		camera = NULL;
		address = NULL;
		transform = NULL;
		hub = NULL;
		mouseLook = NULL;
		cameraTransform = NULL;
		interactCoordinator = NULL;
		cameraPosition.Reset();
		viewMatrix.Reset();
	}

	vec3 getPos() {
		if (serverPosition == vector3zero)
			return position;
		return serverPosition;
	}
}

struct Door : Entity {
	uintptr_t transform, interactable, interactableTransform;
	vec3 interactablePosition;

	void Reset() {
		object = NULL;
		position = vector3zero;
		transform = NULL;
		interactable = NULL;
		interactableTransform = NULL;
		interactablePosition = vector3zero;
	}

	Door() {
		Reset();
	}


	float distance() {
		if (object == NULL)
			return -1;

		static vec3 myPos;

		myPos = Local::serverPosition;

		if (myPos == vector3zero)
			myPos = Local::position;

		return GetDistance(myPos, interactablePosition);
	}

	bool valid() {
		float dist = distance();
		return dist <= 4.69f && dist >= 0;
	}
};

Door scpDoor = Door();