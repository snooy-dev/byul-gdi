// Copyright (c) 2026 snooy. All rights reserved.

export module Scene;

import std;
import Renderer;
import GameObject;

export namespace byul {
class Scene {
public:
	void LoadScene(Renderer& renderer, const std::filesystem::path path);
	void UnloadScene();
	void RenderScene(Renderer& renderer);

private:
	bool m_loaded;
	std::vector<std::unique_ptr<GameObject>> m_objects;
};
}	// namespace byul