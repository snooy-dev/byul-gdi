export module Engine;

import std;
import Application;
import Renderer;

export namespace byul {
class Engine {
public:
	Engine();

	static bool IsExiting();
	static void RequestExit();

	Application& GetApplication();
	Renderer& GetRenderer();

private:
	static bool m_is_exiting;

	std::unique_ptr<Application> m_application;
	std::unique_ptr<Renderer> m_renderer;
};
}	// namespace byul