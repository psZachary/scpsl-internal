#pragma once
#include <memory.h>
#include <structs.h>

enum class DangerType {
	NoDanger,
	Scp173,
	Scp096,
	Combo173_096
};

namespace PlayerHelper {
	/// <summary>
	/// Not used until spinbot is fixed.
	/// </summary>
	/// <param name="out">: SCP-173 Instance if found</param>
	/// <returns></returns>
	DangerType GetDanger(Player &out) {

		bool found173;
		bool found096;
		bool scp173visible;
		bool scp096visible;
		float scp173distance;
		float scp096distance;
		static Player scp173 = Player();
		scp173.Reset();

		out = Player();

		for (auto player : entityList) {
			auto role = (RoleType)player.team;
			if (role == RoleType::Scp173)
			{
				found173 = true;
				scp173 = player;
				scp173visible = player.visible;
				scp173distance = GetDistance(Local::position, player.position);
			}

			if (role == RoleType::Scp096)
			{
				found096 = true;
				scp096visible = player.visible;
				scp096distance = GetDistance(Local::position, player.position);
			}

			if (found096 && found173)
				break;
		}

		if (found173 && found096)
		{
			float delta = abs(scp173distance - scp096distance);

			if (delta < 10) {
				if (scp173visible && scp096visible)
					return DangerType::Combo173_096;

				if (!scp096visible && !scp173visible)
					return DangerType::NoDanger;

				if (scp173visible)
					return DangerType::Combo173_096;

				if (scp096visible)
					return DangerType::Scp096;
			}
		}
		else {
			if (found096 && scp096distance < 45)
				return DangerType::Scp096;

			if (found173 && scp173visible && scp173distance < 45)
				return DangerType::Scp173;
		}

		out = scp173;

		return DangerType::NoDanger;
	}
}