#pragma once

namespace MattEngine {

	typedef struct {
		int top;
		int bottom;
		int left;
		int right;
	} CollisionBox;

	CollisionBox makeCollBox(int top, int bottom, int left, int right);

}