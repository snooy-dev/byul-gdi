// Copyright (c) 2026 snooy. All rights reserved.

module AssetManager;

namespace byul {
std::unordered_map<AssetId, std::shared_ptr<void>> AssetManager::m_loaded_assets;

AssetId AssetManager::GetAssetId(const std::filesystem::path& path)
{
	std::hash<std::filesystem::path> hasher{};
	return hasher(path);
}
}	// namespace byul