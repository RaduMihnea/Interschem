#pragma once
#include <SFML/Graphics.hpp>

struct wWrap {

	static sf::RenderWindow* m_window;

	static void setWindow(sf::RenderWindow &window) {
		m_window = &window;
	}

	static sf::RenderWindow& getWindow() {
		return *m_window;
	}
};
