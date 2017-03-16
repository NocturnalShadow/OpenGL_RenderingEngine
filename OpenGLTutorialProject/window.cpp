
#include "window.h"

#include <GL\glew.h>
#include <iostream>


SDL_Window* Window::current_window = nullptr;
SDL_GLContext Window::current_glContext = nullptr;

Window::Window(int width, int height, std::string title)
	: m_width{ width }, m_height{ height }, m_title { title }
{
	m_window = 
		SDL_CreateWindow(
		m_title.c_str(), 
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 
		m_width, m_height, 
		SDL_WINDOW_OPENGL);

	m_glContext = SDL_GL_CreateContext(m_window);

	GLenum initStatus = glewInit();
	if (initStatus != GLEW_OK) {
		std::cerr << "Error: " << glewGetErrorString(initStatus) << std::endl;
	}

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glViewport(0, 0, m_width, m_height);
}

Window::~Window()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
}

void Window::Update()
{
	// TO BE MOVED TO: Input System
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_WINDOWEVENT) {
			if (e.window.windowID == SDL_GetWindowID(m_window))
			{
				if (e.window.event == SDL_WINDOWEVENT_CLOSE)
				{
					m_isClosedRequested = true;
				}
			}
		}
	}
	SwapBuffers();
}

void Window::Focus()
{
	if (!m_isShown) {
		SDL_ShowWindow(m_window);
	}
	SDL_RaiseWindow(m_window);
}

void Window::DrawTo()
{
	current_window = m_window;
	current_glContext = m_glContext;

	SDL_GL_MakeCurrent(m_window, m_glContext);
}

void Window::Hide()
{
	if (m_isShown) {
		SDL_HideWindow(m_window);
		m_isShown = false;
	}
}

void Window::Clear(float r, float g, float b, float a)
{
	SDL_GL_MakeCurrent(m_window, m_glContext);
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SDL_GL_MakeCurrent(current_window, current_glContext);
}

void Window::SwapBuffers() {
	SDL_GL_MakeCurrent(m_window, m_glContext);
	SDL_GL_SwapWindow(m_window);
	SDL_GL_MakeCurrent(current_window, current_glContext);
}

void Window::SetFullScreen(bool setFullSreen)
{
	int mode = setFullSreen ? SDL_WINDOW_FULLSCREEN : 0;
	SDL_SetWindowFullscreen(m_window, mode);
}
