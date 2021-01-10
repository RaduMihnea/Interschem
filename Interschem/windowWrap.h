#pragma once
#include <SFML/Graphics.hpp>

/*
*	This header file makes the SFML Window available globally without actually making a global variable (inneficient + won't work great with SFML)
*	Made static because it wouldn't allow us to make it any other way.
* 
*	@function setWindow(@param sf::RenderWindow) @return void - sets the address of the window in the local pointer m_window so it can be accesed later.
*	@function getWindow() @return sf::RenderWindow& - return the address of the main window of the application
*/
struct wWrap {

	static sf::RenderWindow* m_window;

	static void setWindow(sf::RenderWindow &window) {
		m_window = &window;
	}

	static sf::RenderWindow& getWindow() {
		return *m_window;
	}
};
