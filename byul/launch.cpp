module Launch;

import Engine;
import EngineLoop;

namespace byul {
int Launch::GuardedMain()
{
	int error_code{};

	Engine engine{};
	EngineLoop engine_loop{ engine };
	engine_loop.Run();

	return error_code;
}
}	// namespace byul