// Copyright (c) 2026 snooy. All rights reserved.

module;
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

export module Application;

import Input;

export namespace byul {
class Application {
public:
	Application(Input& input);

	void PumpMessage();
	void ProcessMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	HWND GetWindowHandle() const;

private:
	void RegisterWindowClass(HINSTANCE hinstance);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND m_hwnd;

	Input& m_input;
};
}	// namespace byul