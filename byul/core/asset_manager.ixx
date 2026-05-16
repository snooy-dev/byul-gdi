// Copyright (c) 2026 snooy. All rights reserved.

export module AssetManager;

import std;
import Core;
import FileManager;

export namespace byul {
class AssetManager {
public:
	static AssetId GetAssetId(const std::filesystem::path& path);
	
	template<typename T>
	static AssetId LoadAsset(const std::filesystem::path& path);

	template<typename T>
	static T& GetLoadedAsset(const AssetId& id);

private:
	static std::unordered_map<AssetId, std::shared_ptr<void>> m_loaded_assets;
};

template<typename T>
AssetId AssetManager::LoadAsset(const std::filesystem::path& path)
{
	const AssetId id{ GetAssetId(path) };
	if (m_loaded_assets.find(id) == m_loaded_assets.end()) {
		const File file{ FileManager::LoadFile(path) };
		m_loaded_assets.insert({ id, std::make_shared<T>(file.get<T>()) });
	}
	return id;
}

template<typename T>
T& AssetManager::GetLoadedAsset(const AssetId& id)
{
	return *std::static_pointer_cast<T>(m_loaded_assets.at(id));
}
}	// namespace byul