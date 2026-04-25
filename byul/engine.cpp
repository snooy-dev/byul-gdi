module Engine;

namespace byul {
bool Engine::m_is_exiting{};

Engine::Engine()
{
	m_application = std::make_unique<Application>();
	m_renderer = std::make_unique<Renderer>(*m_application);
}

bool Engine::IsExiting()
{
	return m_is_exiting;
}

void Engine::RequestExit()
{
	m_is_exiting = true;
}

Application& Engine::GetApplication()
{
	return *m_application;
}

Renderer& Engine::GetRenderer()
{
	return *m_renderer;
}
}	// namespace byul