#pragma once
#ifndef FONTS_INCLUDED
#define FONTS_INCLUDED
#include <SFML/Graphics.hpp>
#include <mutex>


/*
*	Worst part of all of them. This file imports the fonts used into local memory so they can be used in the SFML Library. 
*	Because many conflicts appeared with multiple declarations of the same font in different files, the mutex flag has been chosen to only import the files once.
*	Afterwards, the function get_fonts() returns all available font without importing them more than once. 
*	This function makes the font avaliable globally in the project without setting up global variables ( that SFML didn't allow )
*/
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
		if (!WorkSans_Black.loadFromFile("Fonts/WorkSans-Black.ttf"))
		{
			std::cout << "ERROR LOADING FONT";
		}
		if (!WorkSans_BlackItalic.loadFromFile("Fonts/WorkSans-BlackItalic.ttf"))
		{
			std::cout << "ERROR LOADING FONT";
		}
		if (!WorkSans_Bold.loadFromFile("Fonts/WorkSans-Bold.ttf"))
		{
			std::cout << "ERROR LOADING FONT";
		}
		if (!WorkSans_BoldItalic.loadFromFile("Fonts/WorkSans-BoldItalic.ttf"))
		{
			std::cout << "ERROR LOADING FONT";
		}
		if (!WorkSans_ExtraBoldItalic.loadFromFile("Fonts/WorkSans-ExtraBoldItalic.ttf"))
		{
			std::cout << "ERROR LOADING FONT";
		}
		if (!WorkSans_ExtraLight.loadFromFile("Fonts/WorkSans-ExtraLight.ttf"))
		{
			std::cout << "ERROR LOADING FONT";
		}
		if (!WorkSans_ExtraLightItalic.loadFromFile("Fonts/WorkSans-ExtraLightItalic.ttf"))
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