// Copyright (c) 2026 snooy. All rights reserved.

module Renderer;

import Gdi;

namespace byul {
void RenderCommandQueue::Enqueue(RenderCommand command)
{
	m_command_list.push_back(command);
}

const std::vector<RenderCommand>& RenderCommandQueue::GetCommandList() const
{
	return m_command_list;
}

Renderer::Renderer(Application& application) : m_application(application)
{
	m_rhi = std::make_unique<Gdi>(m_application.GetWindowHandle());
}

void Renderer::SubmitRenderCommand(const RenderCommand& command)
{

}

void Renderer::SwapRenderQueue()
{
	std::lock_guard<std::mutex> lock{ m_mutex };
	std::swap(m_game_thread_queue, m_render_thread_queue);
}

void Renderer::Draw()
{
	ExecuteRenderCommands();
	m_rhi->Present();
}

void Renderer::ExecuteRenderCommands()
{
	std::lock_guard<std::mutex> lock{ m_mutex };
	for (const auto& command : m_render_thread_queue.GetCommandList()) {
		command(*m_rhi);
	}
}
}	// namespace byul