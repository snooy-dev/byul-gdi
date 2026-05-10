// Copyright (c) 2026 snooy. All rights reserved.
module;
#include "thirdparty/json.hpp"

export module FileManager;

import std;

export using File = nlohmann::json;

export namespace byul {
class FileManager {
public:
	static File LoadFile(const std::string& file_name);
};
}	// namespace byul