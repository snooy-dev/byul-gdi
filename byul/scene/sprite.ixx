// Copyright (c) 2026 snooy. All rights reserved.

export module Sprite;

import std;
import Core;
import GameObject;

export namespace byul {
class Sprite : public GameObject {
private:
	std::wstring source_path;
	Transform2D transform;
};
}	// namespace byul