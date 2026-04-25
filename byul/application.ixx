module;
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

export module Application;

export namespace byul {
class Application {
public:
	Application();
	void PumpMessage();

	HWND GetWindowHandle() const;

private:
	void RegisterWindowClass(HINSTANCE hinstance);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND m_hwnd;
};
}	// namespace byul