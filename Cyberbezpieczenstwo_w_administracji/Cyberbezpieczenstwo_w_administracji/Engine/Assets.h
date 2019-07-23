#pragma once

#include <iostream>
#include <exception>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define NO_TEXTURE_PATH "notexture.png"
#define NO_FONT_PATH "nofont.ttf"

namespace gm
{
	class Assets
	{
	private:
		
		static Assets& getSingleton()
		{
			static Assets singleton;
			return singleton;
		}

		sf::Image *_icon = nullptr;
		std::map <std::string, sf::Texture*> _textures;
		sf::Font *_font = nullptr;
		std::map <std::string, sf::SoundBuffer*> _sounds;
		sf::Music *_music = nullptr;
	public:
		Assets();
		~Assets();

		static void LoadIcon(std::string filepath);
		static void LoadTexture(std::string name, std::string filepath);
		static void LoadTextureFromImage(std::string name, sf::Image img);
		static void LoadFont(std::string filepath);
		static void LoadSound(std::string name, std::string filepath);
		static void LoadMusic(std::string filepath);

		static void EraseIcon();
		static void EraseTexture(std::string name);
		static void EraseFont();
		static void EraseSound(std::string name);
		static void EraseMusic();

		static sf::Image* getIcon();
		static sf::Texture *getTexture(std::string name);
		static sf::Font *getFont();
		static sf::SoundBuffer *getSound(std::string name);
		static sf::Music *getMusic();
	};
}