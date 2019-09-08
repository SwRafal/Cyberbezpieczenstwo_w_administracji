#include "Day_0.h"
#include "Engine/Core.h"
#include "GameState.h"

Day_0::Day_0()
{
	state = 0;
	showTextField = false;
	showButtons = false;
	part1Over = false;
	reset = false;
	init = false;
	reseText = false;


	//sprites
	gm::Assets::LoadTexture("screen",PC_SCREEN_TEXTURE);
	gm::Assets::LoadTexture("table", EMPTY_TABLE_TEXTURE);

	screen.setTexture(*gm::Assets::getTexture("screen"));
	table.setTexture(*gm::Assets::getTexture("table"));

	screen.setPosition(23,23);
	table.setPosition(725,481);

	background.setSize(sf::Vector2f(SCREEN_WIDTH,SCREEN_HEIGHT));
	background.setFillColor(sf::Color(0,0,0,200));

	
}

void Day_0::update(GameState* gs, sf::RenderWindow &win)
{
	

	if(gs->day == 0)
	{
		
		if(showButtons)
		{
			gs->choice1->setPosition(gs->officeLady->chat.getPosition().x ,gs->officeLady->chat.getPosition().y + gs->officeLady->chat.getGlobalBounds().height);
			gs->choice2->setPosition(gs->choice1->background.getPosition().x + gs->choice1->background.getGlobalBounds().width ,gs->choice1->background.getPosition().y );
		}
		else
		{
			gs->choice1->setPosition(0,-300);
			gs->choice2->setPosition(0,-300);
		}

		if(showTextField)
		{
			gs->textField->setPosition(gs->officeLady->chat.getPosition().x,gs->officeLady->chat.getPosition().y + gs->officeLady->chat.getGlobalBounds().height);
		}
		else
			gs->textField->setPosition(0,-300);
	}


	if(!part1Over)
	{
	if(gs->day == 0)
	{
		

		if(gs->dayShowScreen->finished && state == 0)
		{
			gs->officeLady->show();
			state = 1;
		}

		if(gs->data->characterChoice != 1) //mag + haker
		{
			if(gs->officeLady->state == 2 && state == 1)
			{
				state = 2;
				gs->officeLady->setButtonInactive();
			}
			
			if(state == 2)
			{
				showButtons = true;
			
				if(gs->choice1->clicked(gm::Core::getWindow()))
				{
					showButtons = false;
					showTextField = true;
					state = 5;
					gs->textField->setTextString(L"Wpisz imi� i zatwierd� klawiszem enter");
					//gs->officeLady->setButtonActive();
				}
				else if(gs->choice2->clicked(gm::Core::getWindow()))
				{
					state = 3;
					showButtons = false;
					gs->officeLady->nextLine();
					gs->popUpText->setBubblePosition(SCREEN_WIDTH / 2 - gs->popUpText->getGlobalBounds().width / 2,SCREEN_HEIGHT / 2 - gs->popUpText->getGlobalBounds().height / 2);
					gs->popUpText->showBubble();
					gs->time = gm::Core::getClock().getElapsedTime().asSeconds();
				}
			}

			if(state == 3)
			{
				if(gm::Core::getClock().getElapsedTime().asSeconds() - gs->time >= 5)
				{
					gs->popUpText->closeBubble();
					state = 5;
					showTextField = true;
					gs->textField->setTextString(L"Wpisz imi� i zatwierd� klawiszem enter");
				}
			}

			if(!reseText)
			{
				if(gs->textField->isActive())
				{
					gs->textField->setTextString(L"");
					reseText = true;
				}
			}

			if(state == 5)
			{
				if(gm::Core::getEnteredChar() == 13 && gs->textField->getTextString().getSize() > 0)
				{
					gs->data->name = gs->textField->getTextString();
					

					state = 6;
					showTextField = false;
					gs->officeLady->nextLine();
					gs->officeLady->nextLine();
					sf::String s = L"Mi�o mi Ci� pozna� ";
					s = s + gs->data->name + sf::String(L", wiele o Tobie s�ysza�am.");
					gs->officeLady->text.setTextString(s);
					gs->officeLady->setButtonActive();
				}
			}
		/*
		 *state:
		 *0- znika od razu
		 *1- po pierwszym kliknieciu w strzalke znika
		 *2- wybor z imieniem
		 *3- ( wybor z rodo) kolezanka mowi dalej
		 *4 - okienko na ekran
		 *5- wpisz imie
		 *6+ - ostateczne co mowi baba 
		 */
		}
	}
	}
 		if(gs->data->characterChoice == 1 && gs->officeLady->state == 4)
			part1Over = true;
		if((gs->data->characterChoice == 2 || gs->data->characterChoice == 3) && gs->officeLady->state == 6)
			part1Over = true;

	if(gs->data->characterChoice == 1)
		gs->data->name = L"Halina";

	if(part1Over)
	{
		if (!reset)
		{
			state = -1;
			gs->officeLady->state = 0;
			reset = true;
		}
		if (!init)
		{ 
			
			//kawa 0
			gs->officeLady->addToQueue(L"Nale�y zacz�� od podstaw. Kawa to podstawa. Takie mamy tu zasady. Niewa�ne czy lubisz kaw� � codziennie rano musisz j� wypi�. ");
			gs->officeLady->addToQueue(L"To fundament utrzymania cyberbezpiecze�stwa na wysokim poziomie.");
			gs->officeLady->addToQueue(L"Nie mo�emy ryzykowa�, �e niewyspany, zm�czony pracownik pope�ni b��dy.");
			gs->officeLady->addToQueue(L"Pami�taj, aby monitorowa� poziom swojej kawowej baterii.");
			gs->officeLady->addToQueue(L"Gdy za�wieci si� na pomara�czowo masz niewiele czasu aby uzupe�ni� kofein�, je�li tego nie zrobisz � za�niesz.");
			gs->officeLady->addToQueue(L"Spanie w pracy jest niedopuszczalne. Szef nienawidzi japo�skich zwyczaj�w. Nie radz� te� je�� sushi na lunch. ");


			// KSI��KA INFO/ 
			gs->officeLady->addToQueue(L"Szef kontaktuje si� z nami na wiele sposob�w.");
			gs->officeLady->addToQueue(L"Najwa�niejszym jest, aby codziennie rano sprawdzi� najnowsze wytyczne w Ksi��ce informacyjnej.");
			gs->officeLady->addToQueue(L"Bezwzgl�dnie ich przestrzegaj. Na bie��co te� sprawdzaj e-maile i odbieraj telefon s�u�bowy. Szef nie lubi by� ignorowany.");

			//monitor
			gs->officeLady->addToQueue(L"Po porannym �yku kawy i zapoznaniu si� z wytycznymi z ksi��ki logujesz si� na swoje konto w systemie.");
			gs->officeLady->addToQueue(L"Twoim podstawowym narz�dziem pracy jest system e-mailowy. Przed wyj�ciem wyloguj si� i zga� komputer. To proste.");

			//Telefon sluzbowy
			gs->officeLady->addToQueue(L"Fajny, prawda? Szef lubi na niego dzwoni�. Mo�esz te� �mia�o u�ywa� go do kontaktu z dzia�em IT � s� bardzo pomocni.");

			//okienko z petentem
			gs->officeLady->addToQueue(L"Podstaw� twojej pracy b�dzie na razie komputer.");
			gs->officeLady->addToQueue(L"Do czasu uko�czenia szkolenia petentami zasadniczo zajmuj� si� tylko ja.");
			gs->officeLady->addToQueue(L"Mo�e si� jednak zdarzy�, �e kto� przyjdzie do ciebie. Obs�u� go.");

			//puste miejsce na stole
			gs->officeLady->addToQueue(L"To tw�j st� operacyjny. To tu petenci sk�adaj� dokumenty - Zapoznawaj si� z nimi dok�adnie.");
			gs->officeLady->addToQueue(L"Ludzie s� przebiegli, tylko czyhaj� aby naruszy� nasze zasady bezpiecze�stwa.");
			gs->officeLady->addToQueue(L"W tym miejscu, w niekt�re poranki b�d� ci te� podrzuca� gazet� - warto j� przeczyta�.");
			gs->officeLady->addToQueue(L"Nasi informatycy s� niereformowalni zwykle k�ad� w to miejsce r�ne wa�ne dla nas rzeczy.");
			gs->officeLady->addToQueue(L"Pami�taj, �eby mie� je na oku a najlepiej zabra� je w inne miejsce.");

			//pieczatki
			gs->officeLady->addToQueue(L"Niegdy� g��wny or� w r�ku ka�dego urz�dnika. Dzi� stopniowo wypierany przez klawiatur� i myszk�.");
			gs->officeLady->addToQueue(L"C� szef kaza� ci je da�, wi�c mo�liwe, �e kiedy� ci si� przydadz�.");

			//zegar i kalendarz
			gs->officeLady->addToQueue(L"Co wi�cej mog� powiedzie�. Zegar i kalendarz ju� pewnie zosta� przez Ciebie zauwa�ony.");
			gs->officeLady->addToQueue(L"Pilnuj czasu. Jak to m�wi� sp�nienia to pierwszy stopie� na dywanik u Szefa.");

			//telefon prywatny
			sf::String s = L"O! Widz�, �e masz najnowszego smartfona! Poka�! ... O NIE! ";
			s = s + gs->data->name + L"! To produkcja japo�skiej firmy! Wiesz co to oznacza!";
			gs->officeLady->addToQueue(s);
			gs->officeLady->addToQueue(L"W dodatku Szef nie uznaje u�ywania prywatnych telefon�w w pracy. M�wi, �e zagra�a to bezpiecze�stwu firmy.");
			gs->officeLady->addToQueue(L"Gdy si� tu pojawi radz� Ci go schowa�, inaczej mo�esz mie� k�opoty!");

			//niszczarka
			gs->officeLady->addToQueue(L"Je�li dokument nie mo�e zosta� zatwierdzony nasz� piecz�tk� pami�taj, aby umie�ci� go w niszczarce.");
			gs->officeLady->addToQueue(L"Do kosza wyrzucasz wszystkie inne niepotrzebne rzeczy. Segregacja to podstawa, musisz si� jej nauczy�.");

			//last info
			gs->officeLady->addToQueue(L"To ju� wszystko czego mia�am Ci� nauczy�.");
			gs->officeLady->addToQueue(L"W ci�gu kolejnych dni dostaniesz wi�cej wyposa�ania.");
			gs->officeLady->addToQueue(L"Najpierw szef musi znale�� zeszyt ze spisem naszego elektronicznego inwentarza.");
			gs->officeLady->addToQueue(L"To co, mo�e p�jdziemy na kaw�?");

			gs->officeLady->addToQueue(L" ");

			init = true;
		}
	
		if(gs->officeLady->state == 1)
			state = 0;
		if(gs->officeLady->state == 7)
			state = 1;
		if(gs->officeLady->state == 10)
			state = 2;
		if(gs->officeLady->state == 12)
			state = 3;
		if(gs->officeLady->state == 13)
			state = 4;
		if(gs->officeLady->state == 16)
			state = 5;
		if(gs->officeLady->state == 21)
			state = 6;
		if(gs->officeLady->state == 23)
			state = 7;
		if(gs->officeLady->state == 25)
			state = 8;
		if(gs->officeLady->state == 28)
			state = 9;
		if(gs->officeLady->state == 30)
			state = 10;
		if(gs->officeLady->state == 34)
			state = 11;

	
		
		
	}
	

}

void Day_0::draw(GameState* gs)
{
	if(gs->day==0)
	{
	sf::RenderWindow& win = gm::Core::getWindow();

	switch (state)
	{
	case -1:
		win.clear();

		/*Background*/
		win.draw(gs->wall);
		gs->calendar->draw(win);
		gs->bell->draw(win);
		gs->watch->draw(win);
		gs->doc->draw(win);
		
		gs->book->draw(win);
		gs->computer->draw(win);
		gs->no_stamp->draw(win);
		gs->yes_stamp->draw(win);
		gs->phone->draw(win);
		gs->mobile->draw(win);
		

		gs->bin->draw(win);
		gs->battery->draw(win);

		

		gs->coffee->draw(win);

		

		gs->officeLady->draw(win);

		win.display();
		break;
	case 0:
		win.clear();

		/*Background*/
		win.draw(gs->wall);
		gs->calendar->draw(win);
		gs->bell->draw(win);
		gs->watch->draw(win);
		gs->doc->draw(win);
		
		gs->book->draw(win);
		gs->computer->draw(win);
		gs->no_stamp->draw(win);
		gs->yes_stamp->draw(win);
		gs->phone->draw(win);
		gs->mobile->draw(win);

		gs->bin->draw(win);
		gs->battery->draw(win);

		//border
		win.draw(background);

		gs->coffee->draw(win);

		

		gs->officeLady->draw(win);

		win.display();
		break;
	case 1:
		win.clear();

		/*Background*/
		win.draw(gs->wall);
		gs->calendar->draw(win);
		gs->bell->draw(win);
		gs->watch->draw(win);
		gs->doc->draw(win);
		
		gs->coffee->draw(win);
		gs->computer->draw(win);
		gs->no_stamp->draw(win);
		gs->yes_stamp->draw(win);
		gs->phone->draw(win);
		gs->mobile->draw(win);
		
		gs->bin->draw(win);
		gs->battery->draw(win);

		//border
		win.draw(background);

		gs->book->draw(win);

		gs->officeLady->draw(win);

		win.display();
		break;
	case 2:
		/*Background*/
		win.draw(gs->wall);
		gs->calendar->draw(win);
		gs->bell->draw(win);
		gs->watch->draw(win);
		gs->doc->draw(win);
		
		gs->book->draw(win);
		
		gs->no_stamp->draw(win);
		gs->yes_stamp->draw(win);
		gs->phone->draw(win);
		gs->mobile->draw(win);
		gs->bin->draw(win);
		gs->battery->draw(win);

		

		gs->coffee->draw(win);

		win.draw(background); //border

		gs->computer->draw(win);

		gs->officeLady->draw(win);

		win.display();
		break;
	case 3:

		/*Background*/
		win.draw(gs->wall);
		gs->calendar->draw(win);
		gs->bell->draw(win);
		gs->watch->draw(win);
		gs->doc->draw(win);
		
		gs->book->draw(win);
		gs->computer->draw(win);
		gs->no_stamp->draw(win);
		gs->yes_stamp->draw(win);
		gs->mobile->draw(win);
		gs->bin->draw(win);
		gs->battery->draw(win);

		

		gs->coffee->draw(win);

		win.draw(background); //border
		gs->phone->draw(win);
		

		gs->officeLady->draw(win);

		win.display();
		break;
	case 4:
		/*Background*/
		win.draw(gs->wall);
		gs->calendar->draw(win);
		gs->bell->draw(win);
		gs->watch->draw(win);
		gs->doc->draw(win);
		
		gs->book->draw(win);
		gs->computer->draw(win);
		gs->no_stamp->draw(win);
		gs->yes_stamp->draw(win);
		gs->phone->draw(win);
		gs->mobile->draw(win);
		gs->bin->draw(win);
		gs->battery->draw(win);

		

		gs->coffee->draw(win);

		win.draw(background); //border

		//ekran z licznikiem petentow

		gs->officeLady->draw(win);

		win.display();
		break;
	case 5:
		/*Background*/
		win.draw(gs->wall);
		gs->calendar->draw(win);
		gs->bell->draw(win);
		gs->watch->draw(win);
		gs->doc->draw(win);
		
		gs->book->draw(win);
		gs->computer->draw(win);
		gs->no_stamp->draw(win);
		gs->yes_stamp->draw(win);
		gs->phone->draw(win);
		gs->mobile->draw(win);
		gs->bin->draw(win);
		gs->battery->draw(win);

		

		gs->coffee->draw(win);

		win.draw(background); //border

		win.draw(table);

		gs->officeLady->draw(win);

		win.display();
		break;
	case 6:
		/*Background*/
		win.draw(gs->wall);
		gs->calendar->draw(win);
		gs->bell->draw(win);
		gs->watch->draw(win);
		gs->doc->draw(win);
		
		gs->book->draw(win);
		gs->computer->draw(win);
		gs->no_stamp->draw(win);
		gs->yes_stamp->draw(win);
		gs->phone->draw(win);
		gs->mobile->draw(win);
		gs->bin->draw(win);
		gs->battery->draw(win);

		

		gs->coffee->draw(win);

		win.draw(background); //border

		gs->no_stamp->draw(win);
		gs->yes_stamp->draw(win);

		gs->officeLady->draw(win);

		win.display();
		break;
	case 7:
		/*Background*/
		win.draw(gs->wall);
		//gs->calendar->draw(win);
		gs->bell->draw(win);
		gs->watch->draw(win);
		gs->doc->draw(win);
		
		gs->book->draw(win);
		gs->computer->draw(win);
		gs->no_stamp->draw(win);
		gs->yes_stamp->draw(win);
		gs->phone->draw(win);
		gs->mobile->draw(win);
		gs->bin->draw(win);
		gs->battery->draw(win);

		

		gs->coffee->draw(win);

		win.draw(background); //border

		gs->watch->draw(win);
		gs->calendar->draw(win);

		gs->officeLady->draw(win);

		win.display();
		break;
	case 8:
		/*Background*/
		win.draw(gs->wall);
		gs->calendar->draw(win);
		gs->bell->draw(win);
		gs->watch->draw(win);
		gs->doc->draw(win);
		
		gs->book->draw(win);
		gs->computer->draw(win);
		gs->no_stamp->draw(win);
		gs->yes_stamp->draw(win);
		gs->phone->draw(win);
		
		gs->bin->draw(win);
		gs->battery->draw(win);

		

		gs->coffee->draw(win);

		win.draw(background); //border
		gs->mobile->draw(win);
		//telefon prywatny

		gs->officeLady->draw(win);

		win.display();
		break;
	case 9:
		win.clear();

		/*Background*/
		win.draw(gs->wall);
		gs->calendar->draw(win);
		gs->bell->draw(win);
		gs->watch->draw(win);
		//gs->doc->draw(win);
		
		gs->book->draw(win);
		gs->computer->draw(win);
		gs->no_stamp->draw(win);
		gs->yes_stamp->draw(win);
		gs->phone->draw(win);
		gs->mobile->draw(win);
		gs->bin->draw(win);
		gs->battery->draw(win);

		gs->coffee->draw(win);

		win.draw(background); //border
		gs->doc->draw(win);
		gs->open_doc->draw(win);
		

		gs->officeLady->draw(win);
		gs->bin->draw(win);

		win.display();
		break;

		break;
	case 10:
		win.clear();

		/*Background*/
		win.draw(gs->wall);
		gs->calendar->draw(win);
		gs->bell->draw(win);
		gs->watch->draw(win);
		gs->doc->draw(win);
		
		gs->book->draw(win);
		gs->computer->draw(win);
		gs->no_stamp->draw(win);
		gs->yes_stamp->draw(win);
		gs->phone->draw(win);
		gs->mobile->draw(win);
		gs->bin->draw(win);
		gs->battery->draw(win);

		

		gs->coffee->draw(win);

		

		gs->officeLady->draw(win);

		win.display();
		
		break;
	case 11:
		gs->nextDay = true;
		gs->officeLady->hide();
		break;
	}
	}
}

//poprawic miejsce monitora i moze zmienic grafike zeby nie zaslanialo, poprawic miejsce table