// Copyright (c) 2026 snooy. All rights reserved.

export module Core;

export namespace byul {
struct Vector2D {
	double x;
	double y;
};

struct Transform2D {
	Vector2D position;
	double rotation;
	Vector2D scale;
};
}	// namespace byul