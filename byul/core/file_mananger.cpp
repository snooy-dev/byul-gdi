// Copyright (c) 2026 snooy. All rights reserved.
module;
#include "thirdparty/json.hpp"

module FileManager;

namespace byul {
File FileManager::LoadFile(const std::wstring& file_path)
{
	std::filesystem::path p{ file_path + L".json" };
	std::ifstream file_stream{ p.c_str() };

	File j{};
	if (file_stream) {
		file_stream >> j;
	}
	return j;
}
}	// namespace byul