#include "vector2.h"

namespace MattEngine {

	Vector2 makeVector2(float x, float y) {
		Vector2 newVector;
		newVector.x = x;
		newVector.y = y;
		return newVector;
	}

	Vector2 addVector2(Vector2 first, Vector2 second) {
		Vector2 newVector;
		newVector.x = first.x + second.x;
		newVector.y = first.y + second.y;
		return newVector;
	}

}