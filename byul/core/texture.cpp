// Copyright (c) 2026 snooy. All rights reserved.

module Texture;

namespace byul {
Texture::Texture(const std::filesystem::path& path) : m_path{ path }
{
	std::hash<std::filesystem::path> hasher{};
	m_bitmap_id = hasher(m_path);
}

const std::filesystem::path& Texture::GetPath() const
{
	return m_path;
}

const unsigned int Texture::GetId() const
{
	return m_bitmap_id;
}
}	// namespace byul