// Copyright (c) 2026 snooy. All rights reserved.

module;
#include <windows.h>
#include <gdiplus.h>

export module Sprite;

import std;
import FileManager;
import GameObject;
import Atlas;
import Texture;

export namespace byul {
class Sprite : public GameObject {
public:
	Sprite(const File file, const std::filesystem::path atlas_path, const std::string region_key, Renderer& renderer);

	virtual void Render(Renderer& renderer) override final;

private:
	std::filesystem::path m_atlas;
	std::string m_region_key;

	std::filesystem::path m_source;
	Region m_region;

	std::unique_ptr<Texture> m_texture;
};
}	// namespace byul