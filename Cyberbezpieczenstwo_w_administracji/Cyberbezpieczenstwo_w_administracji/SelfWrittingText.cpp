#include "SelfWrittingText.h"
#include <stdio.h>
#include <codecvt>

namespace gm
{

bool SelfWrittingText::loadNewText(std::string fileName)
{
	while(!text_queue.empty())
		text_queue.pop();
	this->setString("");

	
	std::wfstream file;
	
	file.open(fileName,std::ios::in | std::ios::binary);

	//file.imbue(std::locale("pl_PL.UTF-8"));

	if(file.good())
	{
		wchar_t junk;
		file.get(junk);
		while(!file.eof())
		{
			wchar_t c;
			
			file.get(c);
			text_queue.push(c);
		}
	}
	else
	{
		MessageBoxA(NULL, "Nie znaleziono pliku", "b³¹d", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	file.close();

	return true;
}



SelfWrittingText::SelfWrittingText(std::string fileName,sf::Font* font)
{
	std::locale::global(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

	std::wfstream file;
	
	file.open(fileName,std::ios::in | std::ios::binary);
	

	
	
	
	


	
	
	
	if(file.good())
	{
		wchar_t junk;
		file.get(junk);
		while(!file.eof())
		{
			wchar_t c;
			
			file.get(c);
			text_queue.push(c);
		}
	}
	else
	{
		MessageBoxA(NULL, "Nie znaleziono pliku", "b³¹d", MB_OK | MB_ICONEXCLAMATION);
	}

	file.close();

	this->setCharacterSize(20);
	this->setFont(*font);
	this->setFillColor(sf::Color::White);
	this->setStyle(sf::Text::Style::Regular);
	this->setPosition(0,0);
}

void SelfWrittingText::setTextProperties(sf::Font* font, int characterSize, sf::Color textColor, sf::Text::Style textStyle, int posX, int posY)
{
	this->setCharacterSize(characterSize);
	this->setFont(*font);
	this->setFillColor(textColor);
	this->setStyle(textStyle);
	this->setPosition(posX,posY);
}

void SelfWrittingText::updateText()
{
	if(!text_queue.empty())
	{
		sf::String temp;
		temp = this->getString() + text_queue.front();
		
		text_queue.pop();
		this->setString(temp);
	}
	
}

bool SelfWrittingText::isQueueEmpty()
{
	return this->text_queue.empty();
}


}

