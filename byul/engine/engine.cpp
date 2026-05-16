// Copyright (c) 2026 snooy. All rights reserved.

module Engine;

import FileManager;
import AssetManager;

namespace byul {
bool Engine::m_is_exiting{};

Engine::Engine()
{
	m_input = std::make_unique<Input>();
	m_application = std::make_unique<Application>(*m_input);
	m_renderer = std::make_unique<Renderer>(*m_application);
	m_scene = std::make_unique<Scene>();

	File project_file = FileManager::LoadFile(L"../byul_project");
	const std::string default_scene_path = project_file["default_scene"];
	m_scene->LoadScene(*m_renderer, default_scene_path);
}

bool Engine::IsExiting()
{
	return m_is_exiting;
}

void Engine::RequestExit()
{
	m_is_exiting = true;
}

Application& Engine::GetApplication()
{
	return *m_application;
}

Renderer& Engine::GetRenderer()
{
	return *m_renderer;
}

Scene& Engine::GetScene()
{
	return *m_scene;
}
}	// namespace byul