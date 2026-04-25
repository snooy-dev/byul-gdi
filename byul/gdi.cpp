module;
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

module Gdi;

namespace byul {
Gdi::Gdi(HWND hwnd) : m_hwnd(hwnd)
{
	m_front_dc = GetDC(m_hwnd);
	m_back_dc = CreateCompatibleDC(m_front_dc);
}

Gdi::~Gdi()
{
	DeleteDC(m_back_dc);
	ReleaseDC(m_hwnd, m_front_dc);
}

void Gdi::Draw(std::queue<std::wstring>& queue)
{
	RECT client_rect{};
	GetClientRect(m_hwnd, &client_rect);

	m_bitmap = CreateCompatibleBitmap(m_back_dc, client_rect.right, client_rect.bottom);
	SelectObject(m_back_dc, (HBITMAP)m_bitmap);

	while (!queue.empty()) {
		const std::wstring out = queue.front();
		queue.pop();
		::TextOut(m_back_dc, 100, 100, out.c_str(), out.size());
	}

	BitBlt(m_front_dc, 0, 0, client_rect.right, client_rect.bottom, m_back_dc, 0, 0, SRCCOPY);

	DeleteObject(m_bitmap);
}
}	// namespace byul