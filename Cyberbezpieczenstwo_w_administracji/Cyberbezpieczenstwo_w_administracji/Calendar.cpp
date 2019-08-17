#include "Calendar.h"

Calendar::Calendar(sf::Font *font, sf::Texture *texture, MONTHS month, unsigned short day, WEEKDAYS weekday)
{
	if (font == nullptr || texture == nullptr)
		error_win_close();

	this->setTexture(*texture);
	this->setPosition(sf::Vector2f(CALENDAR_POS_X, CALENDAR_POS_Y));

	_month_txt.setFont(*font);
	_month_txt.setCharacterSize(MONTH_FONT_SIZE);
	_month_txt.setFillColor(sf::Color::Black);
	setMonth(month);

	_day_txt.setFont(*font);
	_day_txt.setCharacterSize(DAY_FONT_SIZE);
	_day_txt.setFillColor(sf::Color::Black);
	setDay(day);

	_weekday_txt.setFont(*font);
	_weekday_txt.setCharacterSize(WEEKDAY_FONT_SIZE);
	_weekday_txt.setFillColor(sf::Color::Black);
	setWeekDay(weekday);
}

/*Overrides*/
void Calendar::setPosition(float x, float y)
{
	sf::Sprite::setPosition(x, y);
	sf::Vector2f new_month_pos;
	new_month_pos.x = this->getPosition().x + (TEXTURE_OFFSET + this->getTexture()->getSize().x - _month_txt.getLocalBounds().width - _month_txt.getLocalBounds().left) / 2;
	new_month_pos.y = this->getPosition().y + MONTH_POS_Y;
	_month_txt.setPosition(new_month_pos);

	sf::Vector2f new_day_pos;
	new_day_pos.x = this->getPosition().x + (TEXTURE_OFFSET + this->getTexture()->getSize().x - _day_txt.getLocalBounds().width - _day_txt.getLocalBounds().left) / 2;
	new_day_pos.y = this->getPosition().y + DAY_POS_Y;
	_day_txt.setPosition(new_day_pos);

	sf::Vector2f new_weekday_pos;
	new_weekday_pos.x = this->getPosition().x + (TEXTURE_OFFSET + this->getTexture()->getSize().x - _weekday_txt.getLocalBounds().width - _weekday_txt.getLocalBounds().left) / 2;
	new_weekday_pos.y = this->getPosition().y + WEEKDAY_POS_Y;
	_weekday_txt.setPosition(new_weekday_pos);
}
void Calendar::setPosition(const sf::Vector2f &position)
{
	this->setPosition(position.x, position.y);
}
void Calendar::move(float offsetX, float offsetY)
{
	this->setPosition(this->getPosition().x + offsetX, this->getPosition().y + offsetY);
}
void Calendar::move(const sf::Vector2f &offset) 
{
	this->setPosition(this->getPosition()+offset);
}

/*Setters*/
void Calendar::setMonth(const MONTHS month)
{
	if (month > 0 && month < 13)
		_month = month;
	else
		_month = MONTHS_NONE;

	switch (_month)
	{
	case JANUARY:
		_month_txt.setString(L"Styczeñ");
		break;
	case FEBRUARY:
		_month_txt.setString(L"Luty");
		break;
	case MARCH:
		_month_txt.setString(L"Marzec");
		break;
	case APRIL:
		_month_txt.setString(L"Kwiecieñ");
		break;
	case MAY:
		_month_txt.setString(L"Maj");
		break;
	case JUNE:
		_month_txt.setString(L"Czerwiec");
		break;
	case JULY:
		_month_txt.setString(L"Lipiec");
		break;
	case AUGUST:
		_month_txt.setString(L"Sierpieñ");
		break;
	case SEPTEMBER:
		_month_txt.setString(L"Wrzesieñ");
		break;
	case OCTOBER:
		_month_txt.setString(L"PaŸdziernik");
		break;
	case NOVEMBER:
		_month_txt.setString(L"Listopad");
		break;
	case DECEMBER:
		_month_txt.setString(L"Grudzieñ");
		break;
	default:
		_month_txt.setString("NULL");
		break;
	}

	sf::Vector2f new_month_pos;
	new_month_pos.x = this->getPosition().x + (TEXTURE_OFFSET + this->getTexture()->getSize().x - _month_txt.getLocalBounds().width - _month_txt.getLocalBounds().left) / 2;
	new_month_pos.y = this->getPosition().y + MONTH_POS_Y;
	_month_txt.setPosition(new_month_pos);
}
void Calendar::setDay(unsigned short day)
{
	setWeekDay(_weekday + ((unsigned int)day - (unsigned int)_day));

	if (day < 1)
		_day = 1;
	else
		_day = day;
		
	if (_month == FEBRUARY && _day > 28)
	{
		setMonth(_month + (unsigned int)1);
		_day = 1;
	}
	else if ((_month == JANUARY || _month == MARCH || _month == MAY || _month == JULY || _month == AUGUST || _month == OCTOBER || _month == DECEMBER) && _day > 31)
	{
		setMonth(_month + (unsigned int)1);
		_day = 1;
	}
	else if ((_month == APRIL || _month == JUNE || _month == SEPTEMBER || _month == NOVEMBER) && _day > 30)
	{
		setMonth(_month + (unsigned int)1);
		_day = 1;
	}

	_day_txt.setString(std::to_string(_day));

	sf::Vector2f new_day_pos;
	new_day_pos.x = this->getPosition().x + (TEXTURE_OFFSET + this->getTexture()->getSize().x - _day_txt.getLocalBounds().width - _day_txt.getLocalBounds().left) / 2;
	new_day_pos.y = this->getPosition().y + DAY_POS_Y;
	_day_txt.setPosition(new_day_pos);
}
void Calendar::setWeekDay(const WEEKDAYS weekday)
{
	if (weekday < 8 && weekday > 0)
		_weekday = weekday;
	else
		_weekday = WEEKDAYS_NONE;

	switch (_weekday)
	{
	case MONDAY:
		_weekday_txt.setString(L"pon.");
		break;
	case TUESDAY:
		_weekday_txt.setString(L"wt.");
		break;
	case WEDNESDAY:
		_weekday_txt.setString(L"œr.");
		break;
	case THURSDAY:
		_weekday_txt.setString(L"czw.");
		break;
	case FRIDAY:
		_weekday_txt.setString(L"pt.");
		break;
	case SATURDAY:
		_weekday_txt.setString(L"sob.");
		break;
	case SUNDAY:
		_weekday_txt.setString(L"ndz.");
		break;
	default:
		_weekday_txt.setString(L"NULL");
		break;
	}
	
	sf::Vector2f new_weekday_pos;
	new_weekday_pos.x = this->getPosition().x + (TEXTURE_OFFSET + this->getTexture()->getSize().x - _weekday_txt.getLocalBounds().width - _weekday_txt.getLocalBounds().left) / 2;
	new_weekday_pos.y = this->getPosition().y + WEEKDAY_POS_Y;
	_weekday_txt.setPosition(new_weekday_pos);
}

/*Draw & Update*/
void Calendar::draw(sf::RenderWindow &win)
{
	win.draw((sf::Sprite)*this);
	win.draw(_month_txt);
	win.draw(_day_txt);
	win.draw(_weekday_txt);
}

void Calendar::update(sf::RenderWindow &win)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		setDay(_day+1);
	}
}

Calendar::MONTHS operator++(Calendar::MONTHS& m, int)
{
	switch (m)
	{
	case Calendar::MONTHS::JANUARY:
		m = Calendar::MONTHS::FEBRUARY;
		break;
	case Calendar::MONTHS::FEBRUARY:
		m =  Calendar::MONTHS::MARCH;
		break;
	case Calendar::MONTHS::MARCH:
		m = Calendar::MONTHS::APRIL;
		break;
	case Calendar::MONTHS::APRIL:
		m = Calendar::MONTHS::MAY;
		break;
	case Calendar::MONTHS::MAY:
		m = Calendar::MONTHS::JUNE;
		break;
	case Calendar::MONTHS::JUNE:
		m = Calendar::MONTHS::JULY;
		break;
	case Calendar::MONTHS::JULY:
		m = Calendar::MONTHS::AUGUST;
		break;
	case Calendar::MONTHS::AUGUST:
		m = Calendar::MONTHS::SEPTEMBER;
		break;
	case Calendar::MONTHS::SEPTEMBER:
		m = Calendar::MONTHS::OCTOBER;
		break;
	case Calendar::MONTHS::OCTOBER:
		m =  Calendar::MONTHS::NOVEMBER;
		break;
	case Calendar::MONTHS::NOVEMBER:
		m = Calendar::MONTHS::DECEMBER;
		break;
	case Calendar::MONTHS::DECEMBER:
		m = Calendar::MONTHS::JANUARY;
		break;
	default:
		m = Calendar::MONTHS::MONTHS_NONE;
		break;
	}
	return m;
}

Calendar::MONTHS operator+(Calendar::MONTHS& m, unsigned int n)
{
	for (unsigned int i = 0; i < n; i++)
	{
		m++;
	}

	return m;
}

Calendar::WEEKDAYS operator++(Calendar::WEEKDAYS& w, int)
{
	switch (w)
	{
	case Calendar::WEEKDAYS::MONDAY:
		w = Calendar::WEEKDAYS::TUESDAY;
		break;
	case Calendar::WEEKDAYS::TUESDAY:
		w = Calendar::WEEKDAYS::WEDNESDAY;
		break;
	case Calendar::WEEKDAYS::WEDNESDAY:
		w = Calendar::WEEKDAYS::THURSDAY;
		break;
	case Calendar::WEEKDAYS::THURSDAY:
		w = Calendar::WEEKDAYS::FRIDAY;
		break;
	case Calendar::WEEKDAYS::FRIDAY:
		w = Calendar::WEEKDAYS::SATURDAY;
		break;
	case Calendar::WEEKDAYS::SATURDAY:
		w = Calendar::WEEKDAYS::SUNDAY;
		break;
	case Calendar::WEEKDAYS::SUNDAY:
		w = Calendar::WEEKDAYS::MONDAY;
		break;
	default:
		w = Calendar::WEEKDAYS::WEEKDAYS_NONE;
		break;
	}
	return w;
}

Calendar::WEEKDAYS operator+(Calendar::WEEKDAYS& w, unsigned int n)
{
	for (unsigned int i = 0; i < n; i++)
	{
		w++;
	}

	return w;
}