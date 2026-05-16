// Copyright (c) 2026 snooy. All rights reserved.

export module Texture;

import std;

export namespace byul {
class Texture {
public:
	Texture(const std::filesystem::path& path);

	const std::filesystem::path& GetPath() const;
	const unsigned int GetId() const;

private:
	std::filesystem::path m_path;
	unsigned int m_bitmap_id;
};
}	// namespace byul