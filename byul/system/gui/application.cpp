// Copyright (c) 2026 snooy. All rights reserved.

module;
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

module Application;

import std;
import Engine;
import Core;
import FileManager;

namespace byul {
Application::Application(Input& input) : m_input{ input }
{
	HINSTANCE hinstance{ GetModuleHandle(nullptr) };
	RegisterWindowClass(hinstance);

	File project_file{ FileManager::LoadFile(L"../byul_project") };
	const std::string project_name{ project_file["project_name"] };

	int size{ MultiByteToWideChar(CP_UTF8, 0, project_name.c_str(), -1, nullptr, 0) };
	std::wstring window_name(size, 0);
	MultiByteToWideChar(CP_UTF8, 0, project_name.c_str(), -1, window_name.data(), size);

	m_hwnd = ::CreateWindow(L"Engine", window_name.c_str(), WS_OVERLAPPEDWINDOW, 0, 0, 0, 0, nullptr, nullptr, hinstance, this);

	// TODO: adjust res
	RECT cr{ 0, 0, 1920, 1080 };
	DWORD dwStyle = WS_OVERLAPPEDWINDOW;
	::AdjustWindowRect(&cr, dwStyle, false);

	double dpi = ::GetDpiForWindow(m_hwnd);
	::SetWindowPos(m_hwnd, nullptr, 0, 0, cr.right - cr.left, cr.bottom - cr.top, SWP_NOMOVE);
	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);
}

void Application::PumpMessage()
{
	MSG msg{};
	while (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
}

void Application::ProcessMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	static bool is_pressed{};
	static bool is_drag{};

	static Vector2D start_pos{};

	switch (msg) {
		case WM_LBUTTONDOWN: {
			is_pressed = true;
			if (!is_pressed) {
				m_input.ProcessInput(InputEvent::kPressed);
			}
			m_input.ProcessInput(InputEvent::kHold);
			break;
		}
		case WM_LBUTTONUP: {
			is_pressed = false;
			is_drag = false;
			m_input.ProcessInput(InputEvent::kReleased);
			break;
		}
		case WM_MOUSEMOVE: {
			Vector2D end_pos{ LOWORD(lparam), HIWORD(lparam) };

			if (!is_drag && is_pressed) {
				is_drag = true;
			}

			if (is_drag) {
				m_input.ProcessInput(InputEvent::kDrag, end_pos - start_pos);
				start_pos = end_pos;
			}
			break;
		}
	}
}

HWND Application::GetWindowHandle() const
{
	return m_hwnd;
}

void Application::RegisterWindowClass(HINSTANCE hinstance)
{
	WNDCLASSEX window_class{};
	window_class.cbSize = sizeof(WNDCLASSEX);
	window_class.style = CS_DBLCLKS;
	window_class.lpfnWndProc = WndProc;
	window_class.cbClsExtra = 0;
	window_class.cbWndExtra = 0;
	window_class.hInstance = hinstance;
	window_class.hIcon = LoadIcon(hinstance, IDI_APPLICATION);
	window_class.hCursor = LoadCursor(hinstance, IDC_ARROW);
	window_class.hbrBackground = nullptr;
	window_class.lpszMenuName = nullptr;
	window_class.lpszClassName = L"Engine";
	window_class.hIconSm = nullptr;
	::RegisterClassEx(&window_class);
}

LRESULT Application::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static Application* application{};

	switch (uMsg) {
		case WM_CREATE: {
			CREATESTRUCT* create = reinterpret_cast<CREATESTRUCT*>(lParam);
			application = static_cast<Application*>(create->lpCreateParams);
			break;
		}
		case WM_CLOSE: {
			Engine::RequestExit();
			::DestroyWindow(hWnd);
			break;
		}
		case WM_DESTROY: {
			::PostQuitMessage(0);
			break;
		}
		default: {
			application->ProcessMessage(hWnd, uMsg, wParam, lParam);
			break;
		}
	}

	return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}
}	// namespace byul