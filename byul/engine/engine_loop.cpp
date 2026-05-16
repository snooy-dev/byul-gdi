// Copyright (c) 2026 snooy. All rights reserved.

module EngineLoop;

import std;

namespace byul {
EngineLoop::EngineLoop(Engine& engine) : m_engine(engine)
{
}

void EngineLoop::Run()
{

	std::thread render_thread{ [&]() {
		while (!Engine::IsExiting()) {
			m_engine.GetRenderer().Draw();
		}
	}};

	std::chrono::steady_clock::time_point prev_time{ std::chrono::steady_clock::now() };

	while (!Engine::IsExiting()) {
		std::chrono::steady_clock::time_point current_time = std::chrono::steady_clock::now();
		std::chrono::duration duration{ current_time - prev_time };
		prev_time = current_time;

		const double delta_second{ std::chrono::duration<double>(duration).count() };
		
		Tick();

		m_engine.GetScene().RenderScene(m_engine.GetRenderer());
		m_engine.GetRenderer().SwapRenderQueue();
	}

	render_thread.join();
}

void EngineLoop::Tick()
{
	m_engine.GetApplication().PumpMessage();
}
}	// namespace byul