// Copyright (c) 2026 snooy. All rights reserved.

module;
#include "thirdparty/json.hpp"

export module Atlas;

import std;

export namespace byul {
struct Bound {
	int x;
	int y;
	int w;
	int h;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Bound, x, y, w, h)

struct Region {
	Bound bound;
	int rotate;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Region, bound, rotate)

struct Atlas {
	std::filesystem::path source;
	float scale{ 1.0 };
	std::unordered_map<std::string, Region> regions;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Atlas, source, regions)
}