// Copyright (c) 2026 snooy. All rights reserved.

module;
#include <windows.h>
#include <gdiplus.h>

#ifdef DrawText
#undef DrawText
#endif

#ifdef LoadBitmap
#undef LoadBitmap
#endif

module Gdiplus;

namespace byul {
GdiplusRhi::GdiplusRhi(HWND hwnd) : m_hwnd{ hwnd }
{
	Gdiplus::GdiplusStartupInput gdiplus_startup_input{};
	Gdiplus::GdiplusStartup(&m_gdiplus_token, &gdiplus_startup_input, nullptr);

	m_dc = ::GetDC(m_hwnd);
	m_mem_dc = ::CreateCompatibleDC(m_dc);

	RECT cr{};
	::GetClientRect(m_hwnd, &cr);
	m_buffer_bitmap = ::CreateCompatibleBitmap(m_dc, cr.right - cr.left, cr.bottom - cr.top);
	m_default_bitmap = (HBITMAP)::SelectObject(m_mem_dc, m_buffer_bitmap);
}

GdiplusRhi::~GdiplusRhi()
{
	::SelectObject(m_mem_dc, m_default_bitmap);
	::DeleteObject(m_buffer_bitmap);
	::DeleteDC(m_mem_dc);
	::ReleaseDC(m_hwnd, m_dc);

	Gdiplus::GdiplusShutdown(m_gdiplus_token);
}

void GdiplusRhi::BeginFrame()
{
	m_graphics = std::make_unique<Gdiplus::Graphics>(m_mem_dc);
	m_graphics->SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);
	//m_graphics->SetCompositingMode(Gdiplus::CompositingModeSourceCopy);
	//graphics.SetSmoothingMode(Gdiplus::SmoothingModeNone);
	//graphics.SetCompositingQuality(Gdiplus::CompositingQualityHighSpeed);
	//graphics.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighSpeed);
}

void GdiplusRhi::EndFrame()
{
	m_graphics.release();
}

void GdiplusRhi::Present()
{
	DrawText(); // for test
	RECT cr{};
	::GetClientRect(m_hwnd, &cr);
	::BitBlt(m_dc, 0, 0, cr.right - cr.left, cr.bottom - cr.top, m_mem_dc, 0, 0, SRCCOPY);
	Gdiplus::SolidBrush bgBrush(Gdiplus::Color(255, 0, 0, 0));
	m_graphics->FillRectangle(&bgBrush, 0, 0, cr.right, cr.bottom);
}

void GdiplusRhi::DrawText()
{
	static int cnt = 0;
	static int fps = 0;
	static std::chrono::steady_clock::time_point m_lastTime{};
	static std::chrono::steady_clock::time_point m_lastTime2{};
	
	++cnt;
	auto currentTime = std::chrono::steady_clock::now();
	std::chrono::duration<double, std::milli> elapsedTime = currentTime - m_lastTime;
	std::chrono::duration<double, std::milli> d = currentTime - m_lastTime2;
	m_lastTime2 = currentTime;

	if (elapsedTime.count() >= 1000.0) {
		fps = cnt;
		cnt = 0;
		m_lastTime = currentTime;
	}

	Gdiplus::FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 32, Gdiplus::FontStyleRegular, Gdiplus::UnitPoint);
	Gdiplus::SolidBrush textBrush(Gdiplus::Color(255, 255, 255, 255));
	std::wstring testStr = L"fps: " + std::to_wstring(fps) + L"\nframe time: " + std::to_wstring(d.count());
	Gdiplus::PointF point(100.0f, 50.0f);
	m_graphics->DrawString(testStr.c_str(), -1, &font, point, &textBrush);
}

void GdiplusRhi::DrawBitmap(const Texture& texture, float x, float y, float w, float h, float angle, int src_x, int src_y, int src_w, int src_h, bool rotate)
{
	const float dpi_scale{ 1.0f };
	Gdiplus::RectF dest_rect{ 0, 0, w * dpi_scale, h * dpi_scale };

	Gdiplus::Matrix matrix{};
	matrix.Translate(x * dpi_scale, y * dpi_scale);
	matrix.Rotate(angle);	//At(angle, { 0, 0 });

	if (rotate) {
		std::swap(src_w, src_h);
		std::swap(dest_rect.Width, dest_rect.Height);
		matrix.Rotate(90);
		matrix.Translate(0, -dest_rect.Height);
	}
	m_graphics->SetTransform(&matrix);
	m_graphics->DrawImage(m_cached_bitmap.at(texture.GetId()).get(), dest_rect, src_x, src_y, src_w, src_h, Gdiplus::UnitPixel);
	m_graphics->ResetTransform();
}

void GdiplusRhi::CacheBitmap(const Texture& texture)
{
	if (!m_cached_bitmap.contains(texture.GetId())) {
		Gdiplus::Bitmap bitmap{ texture.GetPath().c_str() };
		Gdiplus::Bitmap* fast_bitmap = bitmap.Clone(
			Gdiplus::Rect(0, 0, bitmap.GetWidth(), bitmap.GetHeight()),
			PixelFormat32bppPARGB
		);
		m_cached_bitmap.insert({ texture.GetId(), std::unique_ptr<Gdiplus::Image>(fast_bitmap) });
	}
}
}	// namespace byul