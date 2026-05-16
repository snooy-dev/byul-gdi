// Copyright (c) 2026 snooy. All rights reserved.

module;
#include "thirdparty/json.hpp"

export module GameObject;

import Core;
import FileManager;
import Renderer;

export namespace byul {
class GameObject {
public:
	virtual void Tick(double delta_second) {};
	virtual void Render(Renderer& renderer) {};

	const Transform2D& GetTransform() const { return transform; };

private:
	Transform2D transform;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(GameObject, transform);
};
}	// namespace byul