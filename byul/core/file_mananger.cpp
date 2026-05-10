// Copyright (c) 2026 snooy. All rights reserved.
module;
#include "thirdparty/json.hpp"

module FileManager;

namespace byul {
File FileManager::LoadFile(const std::string& file_path)
{
	std::ifstream file_stream{ "../" + file_path + ".json"};
	File j{};
	file_stream >> j;
	return j;
}
}	// namespace byul