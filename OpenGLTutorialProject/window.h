#pragma once
#include "core.h"

#include <string>
#include <SDL2\SDL.h>
#include <glm\glm.hpp>


class Window
{
private:
	int				m_width;
	int				m_height;
	std::string		m_title;
	SDL_Window*		m_window;
	SDL_GLContext	m_glContext;
	bool			m_isClosedRequested = false;
	bool			m_isShown = true;

private:
	static SDL_Window* current_window;
	static SDL_GLContext current_glContext;

public:
	Window(int width, int height, std::string title);
	virtual ~Window();

	Window()							= delete;
	Window(const Window&)				= delete;

	Window& operator=(const Window&)	= delete;

public:
	int			GetWidth()		const	{ return m_width; }
	int			GetHeight()		const	{ return m_height; }
	float		GetAspect()		const	{ return static_cast<float>(m_width) / m_height; }
	std::string GetTitle()		const	{ return m_title; }
	glm::vec2	GetCenter()		const	{ return glm::vec2{ (float) m_width / 2.0f, (float) m_height / 2.0f }; }
	SDL_Window* GetSDLWindow()			{ return m_window; }
	bool IsClosedRequested()	const	{ return m_isClosedRequested;  }
	bool IsShown()				const	{ return m_isShown; }

	
public:
	void Update();
	void Focus();
	void DrawTo();
	void Hide();
	void Clear(float r, float g, float b, float a);
	void SwapBuffers();
	void SetFullScreen(bool setFullSreen);
};

