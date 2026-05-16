// Copyright (c) 2026 snooy. All rights reserved.

module;
#include <windows.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")

#ifdef DrawText
#undef DrawText
#endif

#ifdef LoadBitmap
#undef LoadBitmap
#endif

export module Gdiplus;

import std;
import Rhi;

export namespace byul {
class GdiplusRhi : public Rhi {
public:
	GdiplusRhi(HWND hwnd);
	~GdiplusRhi();

	virtual void BeginFrame() override;
	virtual void EndFrame() override;

	virtual void Present() override;

	virtual void DrawText() override;
	virtual void DrawBitmap(const Texture& texture,
		float x, float y, float w, float h, float angle,
		int src_x, int src_y, int src_w, int src_h, bool rotate) override;

	virtual void CacheBitmap(const Texture& texture) override;

private:
	HWND m_hwnd;

	ULONG_PTR m_gdiplus_token;

	HDC m_dc;
	HDC m_mem_dc;

	HBITMAP m_buffer_bitmap;
	HBITMAP m_default_bitmap;

	std::unique_ptr<Gdiplus::Graphics> m_graphics;

	std::unordered_map<unsigned int, std::unique_ptr<Gdiplus::Image>> m_cached_bitmap;
};
}	// namespace byul