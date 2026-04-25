module Renderer;

namespace byul {
Renderer::Renderer(Application& application) : m_application(application)
{
	m_gdi = std::make_unique<Gdi>(m_application.GetWindowHandle());
}

void Renderer::Draw()
{
	m_gdi->Draw(render_queue);
}
}	// namespace byul