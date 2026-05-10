// Copyright (c) 2026 snooy. All rights reserved.

module Engine;

import FileManager;
import AssetManager;

namespace byul {
bool Engine::m_is_exiting{};

Engine::Engine()
{
	m_application = std::make_unique<Application>();
	m_renderer = std::make_unique<Renderer>(*m_application);
	m_scene = std::make_unique<Scene>();

	/*File project_file = FileManager::LoadFile("byul_project");
	const std::string default_scene_path = project_file["default_scene"];
	AssetManager::LoadAsset(default_scene_path);*/
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
}	// namespace byul