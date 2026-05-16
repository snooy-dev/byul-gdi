// Copyright (c) 2026 snooy. All rights reserved.

module Scene;

import FileManager;
import Sprite;

namespace byul {
void Scene::LoadScene(Renderer& renderer, const std::filesystem::path path)
{
	if (m_loaded) {
		UnloadScene();
	}

	File file{ FileManager::LoadFile(path) };
	for (const auto object : file["objects"]) {
		if (object["class"] == "sprite") {
			auto sprite = std::make_unique<Sprite>(object, object["atlas"].get<std::string>(), object["region_key"], renderer);
			m_objects.push_back(std::move(sprite));
		}
	}

	m_loaded = true;
}

void Scene::UnloadScene()
{
	m_loaded = false;
}

void Scene::RenderScene(Renderer& renderer)
{
	for (const auto& object : m_objects) {
		object->Render(renderer);
	}
}
}	// namespace byul