#include "Assets.h"

namespace bu
{
	Assets::Assets(){}

	Assets::~Assets()
	{
		if (!_textures.empty())
		{
			_textures.clear();
		}
		if (_font != nullptr)
		{
			delete _font;
			_font = nullptr;
		}
		if (!_sounds.empty())
		{
			_sounds.clear();
		}
		if (_music != nullptr)
		{
			delete _music;
			_music = nullptr;
		}
	}

	void Assets::LoadIcon(std::string filepath)
	{
		EraseIcon();

		getSingleton()._icon = new sf::Image;
		if (!getSingleton()._icon->loadFromFile(filepath))
			getSingleton()._icon = nullptr;
	}
	void Assets::LoadTexture(std::string name, std::string filepath)
	{
		EraseTexture(name);
			
		sf::Texture* t = new sf::Texture;
		if (t->loadFromFile(filepath))
			getSingleton()._textures[name] = t;
	}
	void Assets::LoadFont(std::string filepath)
	{
		EraseFont();

		getSingleton()._font = new sf::Font;
		if (!getSingleton()._font->loadFromFile(filepath))
			getSingleton()._font = nullptr;
	}
	void Assets::LoadSound(std::string name, std::string filepath)
	{
		EraseSound(name);

		sf::SoundBuffer* soundbuffer = new sf::SoundBuffer;
		if (soundbuffer->loadFromFile(filepath))
			getSingleton()._sounds[name] = soundbuffer;
	}
	void Assets::LoadMusic(std::string filepath)
	{
		EraseMusic();

		getSingleton()._music = new sf::Music;
		if (!getSingleton()._music->openFromFile(filepath))
			getSingleton()._music = nullptr;
	}

	void Assets::EraseIcon()
	{
		delete getSingleton()._icon;
		getSingleton()._icon = nullptr;
	}
	void Assets::EraseTexture(std::string name)
	{
		delete getSingleton()._textures[name];
		getSingleton()._textures[name] = nullptr;
	}
	void Assets::EraseFont()
	{
		delete getSingleton()._font;
		getSingleton()._font = nullptr;
	}
	void Assets::EraseSound(std::string name)
	{
		delete getSingleton()._sounds[name];
		getSingleton()._sounds[name] = nullptr;
	}
	void Assets::EraseMusic()
	{
		delete getSingleton()._music;
		getSingleton()._music = nullptr;
	}

	sf::Image* Assets::getIcon()
	{
		return getSingleton()._icon;
	}
	sf::Texture* Assets::getTexture(std::string name)
	{
		return getSingleton()._textures[name];
	}
	sf::Font* Assets::getFont()
	{
		return getSingleton()._font;
	}
	sf::SoundBuffer* Assets::getSound(std::string name)
	{
		return getSingleton()._sounds[name];
	}
	sf::Music* Assets::getMusic()
	{
		return getSingleton()._music;
	}
}