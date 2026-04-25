export module Renderer;

import std; 
import Application; 
import Gdi;

export namespace byul {
class Renderer {
public:
	Renderer(Application& application);
	void Draw();

	std::queue<std::wstring> render_queue;

private:
	Application& m_application;
	std::unique_ptr<Gdi> m_gdi;
};
}	// namespace byul