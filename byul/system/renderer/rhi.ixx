// Copyright (c) 2026 snooy. All rights reserved.

export module Rhi;

import std;
import Core;
import Texture;

export namespace byul {
class Rhi {
public:
	virtual void BeginFrame() = 0;
	virtual void EndFrame() = 0;

	virtual void Present() = 0;

	virtual void DrawText() = 0;
	virtual void DrawBitmap(const Texture& texture,
		float x, float y, float w, float h, float angle,
		int src_x, int src_y, int src_w, int src_h, bool rotate) = 0;

	virtual void CacheBitmap(const Texture& texture) = 0;
};
}	// namespace byul