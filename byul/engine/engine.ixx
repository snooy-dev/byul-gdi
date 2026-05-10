// Copyright (c) 2026 snooy. All rights reserved.

export module Engine;

import std;
import Application;
import Renderer;
import Scene;

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
	std::unique_ptr<Scene> m_scene;
};
}	// namespace byul