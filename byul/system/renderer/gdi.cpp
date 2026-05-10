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

module Gdi;

import std;

namespace byul {
Gdi::Gdi(HWND hwnd) : m_hwnd(hwnd)
{
	m_hinstance = GetModuleHandle(nullptr);

	m_dc = GetDC(m_hwnd);
	m_memory_dc = CreateCompatibleDC(m_dc);
	m_bitmap_dc = CreateCompatibleDC(m_memory_dc);

	RECT client_rect{};
	GetClientRect(m_hwnd, &client_rect);
	m_bitmap = CreateCompatibleBitmap(m_memory_dc, client_rect.right, client_rect.bottom);
	m_default_bitmap = (HBITMAP)SelectObject(m_memory_dc, (HBITMAP)m_bitmap);
}

Gdi::~Gdi()
{
	for (auto& pair : m_loaded_bitmap) {
		DeleteObject(pair.second);
	}
	m_loaded_bitmap.clear();

	SelectObject(m_memory_dc, (HBITMAP)m_default_bitmap);
	DeleteObject(m_bitmap);
	DeleteDC(m_bitmap_dc);
	DeleteDC(m_memory_dc);
	ReleaseDC(m_hwnd, m_dc);
}

void Gdi::Present()
{
	RECT client_rect{};
	GetClientRect(m_hwnd, &client_rect);
	BitBlt(m_dc, 0, 0, client_rect.right, client_rect.bottom, m_memory_dc, 0, 0, SRCCOPY);
}

void Gdi::DrawText()
{
	int x, y;
	std::wstring s{};
	RECT rect{};
	COLORREF color{};

	::SetTextColor(m_memory_dc, color);
	::DrawTextW(m_memory_dc, s.c_str(), s.length(), &rect, DT_CENTER | DT_VCENTER);
}

void Gdi::DrawBitmap(const std::wstring& path)
{
	HBITMAP& hbitmap{ m_loaded_bitmap[path] };
	HBITMAP old_hbitmap{ (HBITMAP)::SelectObject(m_bitmap_dc, hbitmap) };
	::StretchBlt(m_memory_dc, 0, 0, 0, 0, m_bitmap_dc, 0, 0, 0, 0, SRCCOPY);
	::SelectObject(m_bitmap_dc, old_hbitmap);
}

bool Gdi::LoadBitmap(const std::wstring& path)
{
	HBITMAP hbitmap{ (HBITMAP)::LoadImage(m_hinstance, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION)};
	m_loaded_bitmap.insert({ path, hbitmap });
	return hbitmap;
}

bool Gdi::UnloadBitmap(const std::wstring& path)
{
	bool result{ (bool)::DeleteObject(m_loaded_bitmap[path]) };
	m_loaded_bitmap.erase(path);
	return result;
}
}	// namespace byul