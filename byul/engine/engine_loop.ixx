// Copyright (c) 2026 snooy. All rights reserved.

export module EngineLoop;

import Engine;

export namespace byul {
class EngineLoop {
public:
	EngineLoop(Engine& engine);
	void Run();

private:
	void Tick();

	Engine& m_engine;
};
}	// namespace byul