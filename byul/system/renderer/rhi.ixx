// Copyright (c) 2026 snooy. All rights reserved.

export module Rhi;

import std;

export namespace byul {
class Rhi {
public:
	virtual void Present() = 0;

	virtual void DrawText() = 0;
	virtual void DrawBitmap(const std::wstring& path) = 0;

	virtual bool LoadBitmap(const std::wstring& path) = 0;
	virtual bool UnloadBitmap(const std::wstring& path) = 0;
};
}	// namespace byul