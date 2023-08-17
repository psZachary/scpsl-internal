#pragma once

namespace MathUtil {
	quat ToEuler(vec3 vector) {
		return UnityEngine::Quaternion::Euler(vector.X,vector.Y,vector.Z);
	}

	vec3 GetEuler(quat rotation) {
		vec3 out;
		UnityEngine::Quaternion::Internal_ToEulerRad_Injected(rotation, out);
		return UnityEngine::Quaternion::Internal_MakePositive(out * 57.29578f);
	}

	vec3 LookAt(vec3 position) {
		vec3 angle = position - Local::cameraPosition;

		quat lookAngle = UnityEngine::Quaternion::LookRotation01(angle);

		vec3 eulerAngles = GetEuler(lookAngle);

		return eulerAngles;
	}
}