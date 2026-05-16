// Copyright (c) 2026 snooy. All rights reserved.

module;
#include <windows.h>
#include <gdiplus.h>

module Sprite;

import AssetManager;

namespace byul {
Sprite::Sprite(const File file, const std::filesystem::path atlas_path, const std::string region_key, Renderer& renderer)
	: GameObject(file), m_atlas{ atlas_path }, m_region_key{ region_key }
{
	const AssetId id{ AssetManager::LoadAsset<Atlas>(m_atlas) };
	const Atlas& atlas{ AssetManager::GetLoadedAsset<Atlas>(id) };
	m_source = atlas.source;
	m_region = atlas.regions.at(m_region_key);

	m_texture = std::make_unique<Texture>(m_source);
	renderer.GetRhi().CacheBitmap(*m_texture);
}

void Sprite::Render(Renderer& renderer)
{
	renderer.SubmitRenderCommand([=](Rhi& rhi) {
		rhi.DrawBitmap(*m_texture,
			GetTransform().position.x, GetTransform().position.y,
			m_region.bound.w * GetTransform().scale.x, m_region.bound.h * GetTransform().scale.y,
			GetTransform().rotation,
			m_region.bound.x, m_region.bound.y,
			m_region.bound.w, m_region.bound.h,
			m_region.rotate != 0);
		});
}
}	// namespace byul