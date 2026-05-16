// Copyright (c) 2026 snooy. All rights reserved.

module;
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#ifdef DrawText
#undef DrawText
#endif

#ifdef LoadBitmap
#undef LoadBitmap
#endif

export module Gdi;

import Rhi;

export namespace byul {
class Gdi : public Rhi {
public:
	Gdi(HWND hwnd);
	~Gdi();

	virtual void Present() override;

	virtual void DrawText() override;
	virtual void DrawBitmap(const std::wstring& path, int x, int y, int w, int h, float angle, int src_x, int src_y, int src_w, int src_h, bool rotate) override;

	virtual bool LoadBitmap(const std::wstring& filename) override;
	virtual bool UnloadBitmap(const std::wstring& filename) override;

private:
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	HDC m_dc;
	HDC m_memory_dc;
	HDC m_bitmap_dc;
	HBITMAP m_bitmap;
	HBITMAP m_default_bitmap;

	std::unordered_map<std::wstring, HBITMAP> m_loaded_bitmap;
};
}	// namespace byul