#pragma once
#ifndef FONTS_INCLUDED
#define FONTS_INCLUDED
#include <SFML/Graphics.hpp>

sf::Font WorkSans_Black;
sf::Font WorkSans_BlackItalic;
sf::Font WorkSans_Bold;
sf::Font WorkSans_BoldItalic;
sf::Font WorkSans_ExtraBoldItalic;
sf::Font WorkSans_ExtraLight;
sf::Font WorkSans_ExtraLightItalic;

void fonts()
{
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
}
#endif