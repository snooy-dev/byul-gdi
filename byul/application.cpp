module;
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

module Application;

import Engine;

namespace byul {
Application::Application()
{
	HINSTANCE hinstance{ GetModuleHandle(nullptr) };
	RegisterWindowClass(hinstance);

	m_hwnd = ::CreateWindowEx(0UL, L"Engine", L"", WS_OVERLAPPEDWINDOW, 0, 0, 0, 0, nullptr, nullptr, hinstance, nullptr);

	double dpi = ::GetDpiForWindow(m_hwnd);
	::SetWindowPos(m_hwnd, nullptr, 0, 0, static_cast<int>((1920 * dpi) / 96), static_cast<int>((1080 * dpi) / 96), SWP_NOMOVE);
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
	switch (uMsg) {
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
			break;
		}
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
}	// namespace byul