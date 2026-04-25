module;
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

export module Gdi;

import std;

export namespace byul {
class Gdi {
public:
	Gdi(HWND hwnd);
	~Gdi();
	void Draw(std::queue<std::wstring>& queue);

private:
	HWND m_hwnd;
	HDC m_front_dc;
	HDC m_back_dc;
	HBITMAP m_bitmap;
};
}	// namespace byul