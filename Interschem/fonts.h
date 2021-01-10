#pragma once
#ifndef FONTS_INCLUDED
#define FONTS_INCLUDED
#include <SFML/Graphics.hpp>
#include <mutex>

struct Fonts {
	sf::Font& WorkSans_Black;
	sf::Font& WorkSans_BlackItalic;
	sf::Font& WorkSans_Bold;
	sf::Font& WorkSans_BoldItalic;
	sf::Font& WorkSans_ExtraBoldItalic;
	sf::Font& WorkSans_ExtraLight;
	sf::Font& WorkSans_ExtraLightItalic;

	Fonts(
		sf::Font& WorkSans_Black,
		sf::Font& WorkSans_BlackItalic,
		sf::Font& WorkSans_Bold,
		sf::Font& WorkSans_BoldItalic,
		sf::Font& WorkSans_ExtraBoldItalic,
		sf::Font& WorkSans_ExtraLight,
		sf::Font& WorkSans_ExtraLightItalic
	) : WorkSans_Black(WorkSans_Black),
		WorkSans_BlackItalic(WorkSans_BlackItalic),
		WorkSans_Bold(WorkSans_Bold),
		WorkSans_BoldItalic(WorkSans_BoldItalic),
		WorkSans_ExtraBoldItalic(WorkSans_ExtraBoldItalic),
		WorkSans_ExtraLight(WorkSans_ExtraLight),
		WorkSans_ExtraLightItalic(WorkSans_ExtraLightItalic)
	{
	}
};

inline Fonts get_fonts()
{
	static std::once_flag flag;
	static sf::Font WorkSans_Black;
	static sf::Font WorkSans_BlackItalic;
	static sf::Font WorkSans_Bold;
	static sf::Font WorkSans_BoldItalic;
	static sf::Font WorkSans_ExtraBoldItalic;
	static sf::Font WorkSans_ExtraLight;
	static sf::Font WorkSans_ExtraLightItalic;

	std::call_once(flag, []() {
		if (!WorkSans_Black.loadFromFile("WorkSans-Black.ttf"))
		{
			std::cout << "ERROR LOADING FONT";
		}
		if (!WorkSans_BlackItalic.loadFromFile("WorkSans-BlackItalic.ttf"))
		{
			std::cout << "ERROR LOADING FONT";
		}
		if (!WorkSans_Bold.loadFromFile("WorkSans-Bold.ttf"))
		{
			std::cout << "ERROR LOADING FONT";
		}
		if (!WorkSans_BoldItalic.loadFromFile("WorkSans-BoldItalic.ttf"))
		{
			std::cout << "ERROR LOADING FONT";
		}
		if (!WorkSans_ExtraBoldItalic.loadFromFile("WorkSans-ExtraBoldItalic.ttf"))
		{
			std::cout << "ERROR LOADING FONT";
		}
		if (!WorkSans_ExtraLight.loadFromFile("WorkSans-ExtraLight.ttf"))
		{
			std::cout << "ERROR LOADING FONT";
		}
		if (!WorkSans_ExtraLightItalic.loadFromFile("WorkSans-ExtraLightItalic.ttf"))
		{
			std::cout << "ERROR LOADING FONT";
		}
		});

	return Fonts{
		WorkSans_Black,
		WorkSans_BlackItalic,
		WorkSans_Bold,
		WorkSans_BoldItalic,
		WorkSans_ExtraBoldItalic,
		WorkSans_ExtraLight,
		WorkSans_ExtraLightItalic
	};
}
#endif