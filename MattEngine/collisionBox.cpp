#include "collisionBox.h"

namespace MattEngine {

	CollisionBox makeCollBox(int top, int bottom, int left, int right) {
		CollisionBox collBox;
		collBox.top = top;
		collBox.bottom = bottom;
		collBox.left = left;
		collBox.right = right;

		return collBox;
	}

}