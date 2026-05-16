// Copyright (c) 2026 snooy. All rights reserved.

module Renderer;

import Gdiplus;

namespace byul {
void RenderCommandQueue::Enqueue(RenderCommand command)
{
	m_command_list.push_back(command);
}

void RenderCommandQueue::Clear()
{
	m_command_list.clear();
}

const std::vector<RenderCommand>& RenderCommandQueue::GetCommandList() const
{
	return m_command_list;
}

Renderer::Renderer(Application& application) : m_application(application)
{
	m_rhi = std::make_unique<GdiplusRhi>(m_application.GetWindowHandle());
}

void Renderer::SubmitRenderCommand(const RenderCommand& command)
{
	m_game_thread_queue.Enqueue(command);
}

void Renderer::SwapRenderQueue()
{
	std::lock_guard<std::mutex> lock{ m_mutex };
	std::swap(m_game_thread_queue, m_render_thread_queue);
	m_game_thread_queue.Clear();
}

void Renderer::Draw()
{
	m_rhi->BeginFrame();
	ExecuteRenderCommands();
	m_rhi->Present();
	m_rhi->EndFrame();
}

void Renderer::ExecuteRenderCommands()
{
	std::lock_guard<std::mutex> lock{ m_mutex };
	for (const auto& command : m_render_thread_queue.GetCommandList()) {
		command(*m_rhi);
	}
}
Rhi& Renderer::GetRhi()
{
	return *m_rhi;
}
}	// namespace byul