// Copyright (c) 2026 snooy. All rights reserved.

export module Renderer;

import std;
import Application;
import Rhi;

export namespace byul {
using RenderCommand = std::function<void(Rhi&)>;

class RenderCommandQueue {
public:
	void Enqueue(RenderCommand command);
	void Clear();
	const std::vector<RenderCommand>& GetCommandList() const;

private:
	std::vector<RenderCommand> m_command_list;
};

class Renderer {
public:
	Renderer(Application& application);

	void Draw();

	void SubmitRenderCommand(const RenderCommand& command);
	void SwapRenderQueue();

	void ExecuteRenderCommands();

	Rhi& GetRhi();

private:
	Application& m_application;
	std::unique_ptr<Rhi> m_rhi;

	RenderCommandQueue m_game_thread_queue;
	RenderCommandQueue m_render_thread_queue;
	std::mutex m_mutex;
};
}	// namespace byul