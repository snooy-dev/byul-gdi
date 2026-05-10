// Copyright (c) 2026 snooy. All rights reserved.

export module AssetManager;

import std;
import FileManager;

export namespace byul {
class AssetManager {
public:
	template<class T>
	static std::unique_ptr<T> LoadAsset(const std::string& path);
};

template<class T>
std::unique_ptr<T> AssetManager::LoadAsset(const std::string& path)
{
	File asset_file{ FileManager::LoadFile(path) };
	std::unique_ptr<T> asset = std::make_unique<T>();
	asset_file.get_to(*asset);
	return asset;
}
}	// namespace byul