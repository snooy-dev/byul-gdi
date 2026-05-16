// Copyright (c) 2026 snooy. All rights reserved.

module;
#include "thirdparty/json.hpp"

export module Core;

export namespace byul {
using uint = unsigned int;
using AssetId = size_t;

struct Vector2D {
	float x;
	float y;

	Vector2D operator-(const Vector2D& rhs) const
	{
		return { x - rhs.x, y - rhs.y };
	}
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Vector2D, x, y)

struct Transform2D {
	Vector2D position;
	float rotation;
	Vector2D scale{ 1.0, 1.0 };
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Transform2D, position, rotation, scale)
}	// namespace byul