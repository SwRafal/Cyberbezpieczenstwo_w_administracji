#include "Day_4.h"
#include "GameState.h"

Day_4::Day_4()
{
	showButtons = false;
	state = -1;

	thought = new textBubble(gm::Assets::getTexture("text bubble"));
	thought->setBubblePosition(0, -300);

	if (gm::Assets::getTexture("boss") == nullptr)
	{
		gm::Assets::LoadTexture("boss", BOSS_TEXTURE);

		if (gm::Assets::getTexture("boss") == nullptr)
			error_win_close();
	}
	boss = new OfficeApplicant(gm::Assets::getTexture("boss"));

	itGuy = new OfficeApplicant(gm::Assets::getTexture("itGuy"));
	itGuy->move(0,10);
	offset = 20;
	itGuy->chat.move(offset,0);
	itGuy->text.move(offset,0);
	itGuy->button.move(offset,0);
	itGuy->img.move(offset,0);

	//quest1
	gm::Assets::LoadTexture("gazeta",GAZETA);
	newspaper.setTexture(*gm::Assets::getTexture("gazeta"));
	newspaper.setPosition(400,10);

	gm::Assets::LoadTexture("petent1", PETENT1);
	petent1 = new OfficeApplicant(gm::Assets::getTexture("petent1"));
	petent1->move(0,2);
	petent1->moveChatBox(30,0);
	
	gm::Assets::LoadTexture("dowod1", DOWOD1);
	dowod1.setTexture(*gm::Assets::getTexture("dowod1"));
	
	gm::Assets::LoadTexture("petent2", PETENT2);
	petent2 = new OfficeApplicant(gm::Assets::getTexture("petent2"));
	petent2->move(0,2);
	petent2->moveChatBox(30,0);

	callIn = false;
	drawDowod = false;
}

Day_4::~Day_4()
{
	
}

void Day_4::update(GameState* gs, sf::RenderWindow& win)
{
	if(showButtons)
	{
		if(state == 17 || state == 20)
		{
			gs->choice2->setPosition(SCREEN_WIDTH / 2 - gs->choice2->background.getGlobalBounds().width / 2,SCREEN_HEIGHT * 0.6);
			gs->choice1->setPosition(gs->choice2->background.getPosition().x - gs->choice1->background.getGlobalBounds().width - 5,SCREEN_HEIGHT * 0.6);
			gs->choice3->setPosition(gs->choice2->background.getPosition().x + gs->choice2->background.getGlobalBounds().width + 5,SCREEN_HEIGHT * 0.6);
		}
		else
		{
			gs->choice1->setPosition(SCREEN_WIDTH / 2 - gs->choice1->background.getGlobalBounds().width - 5,SCREEN_HEIGHT * 0.6);
			gs->choice2->setPosition(SCREEN_WIDTH / 2 + 5,SCREEN_HEIGHT * 0.6);
		}
			
	}
	else
	{
		gs->choice1->setPosition(0,-300);
		gs->choice2->setPosition(0,-300);
		gs->choice3->setPosition(0,-300);
	}

	if(!gs->dayShowScreen->finished)
		return;

	thought->animate();
	itGuy->animate();
	boss->animate();
	petent1->animate();
	petent2->animate();

	switch (state)
	{
	case -1: //init
		gs->openedbook->setInfoL(L"Minimalizacja danych osobowych � tylko dane niezb�dne do celu przetwarzania");
		gs->xero->setPosition(XERO_POS_X, XERO_POS_Y);
		gs->card->setPosition( 830,500);
		gs->openedcomputer->getLogin() = gs->data->login;
		gs->openedcomputer->getPassword() = gs->data->password;
		gs->cardReader->hidden = false;
		gs->cardReader->update();
		state = 14;
		state++;
		break;
	case 0: //wypij kawe
		if (gs->coffee->update_drunk(win))
		{
			gs->battery->setActivation(true);
			coffeeClicked = true;
			state = 2;
			gs->book->setFillColor(sf::Color(230, 230, 230));
		}
		else if (gs->book->clicked(win) || gs->bell->clicked(win) || gs->bin->clicked(win) || gs->no_stamp->clicked(win) || gs->yes_stamp->clicked(win) || gs->computer->clicked(win) || gs->card->clicked(win))
		{
			thought->changeText(L"Nie �pij w pracy!");
			gs->data->nagany++;
			thought->setBubblePosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			thought->showBubble();
			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + THOUGHT_TIME;
			state++;
		}
		//thought->animate();
		break;
	case 1: //nie spij w pracy
		//thought->animate();
		if (thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			thought->closeBubble();
			state = 0;
		}
		break;
	case 2: //read book
		//thought->animate();
		gs->book->update(win);
		gs->openedbook->update(win);
		if(gs->book->isOpened())
			bookOpened = true;
		if(bookOpened && !gs->book->isOpened())
			state++;
		break;
	case 3:
		gs->card->update(win);
		gs->cardReader->update();
		if(gs->cardReader->isCardInside())
		{
			gs->computer->update(win);
			gs->openedcomputer->update(win);
			if(gs->computer->powerOn)
			{
				if(gs->openedcomputer->getState() == OpenPC::DESKTOP)
				{
					gs->computer->close();
					state++;
				}
			}
		}
		break;
	case 4: //gosc z it
		itGuy->setButtonActive();
		itGuy->state = 0;
		itGuy->text.setTextString(L"Hej widzia�e� dzisiejsz� gazet�?");
		itGuy->addToQueue(L" ");
		itGuy->show();
		state++;
		break;
	case 5: //pokaz gazete
		if(itGuy->state == 1)
		{
			showNewspaper = true;
			if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				showNewspaper = false;
				itGuy->state = 0;
				itGuy->text.setTextString(L"Ooooo widz�, �e pami�� naszego kombajnu jest totalnie zapchana");
				itGuy->addToQueue(L"woooaaa!!! Zeskanowa�e� wczoraj ca�� baz� pracownik�w Ministerstwa?");
				itGuy->addToQueue(L"No tak, szef pewnie nie powiedzia� ci, �e po zako�czonym skanowaniu,");
				itGuy->addToQueue(L"drukowaniu czy kserowaniu trzeba czy�ci� pami�� takiego urz�dzenia?");
				itGuy->addToQueue(L"Nie? To w jego stylu� przecie� ''Drukarka to nie komputer''");
				itGuy->addToQueue(L"''Nikt przez nas przez ni� nie zaatakuje.''");
				itGuy->addToQueue(L"Na przysz�o�� pami�taj, �e\n drukarka pod��czona do sieci");
				itGuy->addToQueue(L"jest najs�abszym ogniwem obrony naszych urz�d�w");
				itGuy->addToQueue(L"G�ra �a�uje nam funduszy na prawid�owe ich zabezpieczenie");
				itGuy->addToQueue(L"Postaraj si�, �eby czy�ci� jej pami�� zanim p�jdziesz do domu");
				itGuy->addToQueue(L"Mieli�my szcz�cie, �e tym razem nie zaatakowano nas");
				itGuy->addToQueue(L"OK, zrobi�em co mia�em zrobi�.");
				itGuy->addToQueue(L"Masz zainstalowny nowy system pozwalaj�cy sprawniej zaprasza� petent�w. Powodzenia!");
				itGuy->addToQueue(L" ");
				state++;
			}
			
		}
		break;
	case 6: //monolog itguya
		if(itGuy->state == 13)
		{
			itGuy->hide();
			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 3000;
			thought->changeText(L"By wezwa� interesanta, naci�nij dzwonek");
			thought->showBubble();
			thought->setBubblePosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			state++;
		}
		break;
	case 7: //info bubble
		//thought->animate();
		//thought->setBubblePosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		if(thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			thought->closeBubble();
			state++;
		}
		break;
	case 8:
		thought->animate();
		if(thought->hidden)
			{
				state++;
			}
		break;
	case 9: //1 petent
		
		if(callIn)
		{
			petent1->setButtonInactive();
			petent1->text.setTextString(L"Dzie� dobry, chcia�bym si� dowiedzie� czy moje prawo jazdy ju� jest gotowe do odbioru?");
			petent1->show();
			gs->choice1->setText(L"Prosz� o okazanie\ndowodu osobistego");
			gs->choice2->setText(L"Prosze o podanie imienia,\nnazwiska i numeru PESEL");
			showButtons = true;
			state++;
		}
		break;
	case 10:
		if(gs->choice1->clicked(win))
		{
			drawDowod = true;
			state++;
		}
		if(gs->choice2->clicked(win))
		{
			petent1->text.setTextString(L"Nazywam si� Jan Kowalski, numer PESEL to 93030215201");
			gs->choice1->setText(L"Dokument jest gotowy do odbioru,\nprosz� o okazanie dowodu osobistego");
			gs->choice2->setText(L"Dokument jest gotowy do odbioru");
			state = 14;
		}
		break;
	case 11:
		gs->choice1->setText(L"Wydaj prawo jazdy");
		gs->choice2->setText(L"Skseruj dow�d i wydaj prawo jazdy");
		if(gs->choice1->clicked(win))
		{
			showButtons = false;
			drawDowod = false;
			dowod1.setPosition(SCREEN_WIDTH,SCREEN_HEIGHT);
			petent1->text.setTextString(L"Dzi�kuj�");
			petent1->addToQueue(L" ");
			quest1completed = true;
			petent1->setButtonActive();
			petent1->state = 0;
			state++;
		}
		if(gs->choice2->clicked(win))
		{
			showButtons = false;
			drawDowod = false;
			dowod1.setPosition(SCREEN_WIDTH,SCREEN_HEIGHT);
			petent1->text.setTextString(L"Dzi�kuj�");
			petent1->addToQueue(L" ");
			petent1->setButtonActive();
			petent1->state = 0;

			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 3000;
			thought->changeText(L"Kserowanie dowodu nie jest niezb�dne do wykonania zadania, a nara�a urz�d na wyciek danych");
			thought->showBubble();

			gs->data->nagany++;
			state = 13;
			
		}
		break;
	case 12:
		if(petent1->state == 1)
		{
			petent1->hide();
			callIn = false;
			state = 15;
		}
		break;
	case 13:
		thought->animate();
		if(thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
			thought->closeBubble();

		if(thought->hidden)
			state = 12;
		break;
	case 14:
		if(gs->choice1->clicked(win))
		{
			drawDowod = true;
			state = 11;
		}
		if(gs->choice2->clicked(win))
		{
			showButtons = false;
			gs->gameover(L"Przekaza�e� dokument zawierajacy dane osobowe (wyciek danych) osobie, kt�rej uprawnienia do otrzymania tych danych nie zweryfikowa�e�.\nFa�szywy Jan Kowalski pos�u�y� si� prawem jazdy do wyp�aty got�wki w banku prawowitego w�a�ciciela.\nZostajesz zwolniony dyscyplinarnie w trybie natychmiastowym");
		}
		break;
	case 15: //quest 2;
		if(callIn)
		{
			petent2->state = 0;
			petent2->text.setTextString(L"Dzie� dobry, chcia�abym zap�aci�  za mandaty, kt�re dosta�am.");
			petent2->addToQueue(L"Przy okazji jak ju� tu jestem chcia�abym zap�aci� za mandaty m�a, bo te� m�wi�, �e co� tam ma zaleg�ego. Piotr Nowak");
			petent2->show();
			state++;
		}
		break;
	case 16:
		if(petent2->state == 1)
		{
			showButtons = true;
			gs->choice1->setText(L"Zg�d� si�");
			gs->choice2->setText(L"Popro� o dodatkowe informacje");
			gs->choice3->setText(L"Odm�w");
			state++;
		}
		break;
	case 17:
		if(gs->choice1->clicked(win))//sciezka 1
		{
			gs->playerIco.text.setTextString(L"Dobrze, podam Pani informacje o mandatach m�a. Poprosz� o PESEL m�a");
			gs->playerIco.show();
			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 3000;
			showButtons = false;
			state++;
		}
		if(gs->choice2->clicked(win)) //sciezka 2
		{
			showButtons = false;
			gs->playerIco.text.setTextString(L"Nie ma problemu, poprosz� o upowa�nie od m�a dla Pani do za�atwienia tej sprawy w jego imieniu lub upowa�nienie og�lne");
			gs->playerIco.show();
			state = 26;
		}
		if(gs->choice3->clicked(win)) //sciezka 3
		{
			showButtons = false;
			gs->playerIco.text.setTextString(L"Przepraszam, ale nie mog� przekaza� danych dotycz�cych innych os�b, RODO, rozumie Pani");
			gs->playerIco.show();
			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 3000;
			state = 30;
		}
		break;
	case 18: //sciezka 1
		if(thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			gs->playerIco.hide();
			petent2->state = 0;
			petent2->text.setTextString(L"Czyli jednak ma jakie� mandaty! Pirat jeden! Teraz b�d� mia�a na niego haka!");
			petent2->addToQueue(L"Czyli jednak ma jakie� mandaty! Pirat jeden! Teraz b�d� mia�a na niego haka!");
			petent2->setButtonActive();
			state++;
		}
		break;
	case 19:
		if(petent2->state == 1)
		{
			petent2->setButtonInactive();
			gs->playerIco.text.setTextString(L"Chwila, czyli nie ma Pani upowa�nienia od m�a?");
			gs->playerIco.show();
			showButtons = true;
			gs->choice1->setText(L"Zignoruj ma�ze�sk� sprzeczk�");
			gs->choice2->setText(L"Zg�o� wyciek danych do UODO");
			gs->choice3->setText(L"Zg�o� wyciek danych do IOD");
			state++;
		}
		break;
	case 20:
		if(gs->choice1->clicked(win))
		{
			petent2->hide();
			gs->playerIco.hide();
			showButtons = false;
			gs->data->nagany++;
			thought->setBubblePosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			thought->showBubble();
			thought->changeText(L"Nie tylko dopuszczono do wycieku danych, ale w dodatku nie podj�to �adnych dzia�a�, przez co nara�ono instytuj� na dalsze ryzyko.");
			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 4000;
			state++;
		}
		if(gs->choice2->clicked(win))
		{
			petent2->hide();
			gs->playerIco.hide();
			showButtons = false;
			gs->data->nagany++;
			thought->setBubblePosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			thought->showBubble();
			thought->changeText(L"Masz dobre intencje, ale pope�ni�e� b��d! Formularz na stronie UODO przyjmie Twoje zg�oszenie, ale zg�oszenie zostanie bez rozpatrzenia.");
			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 4000;
			state++;
		}
		if(gs->choice3->clicked(win))
		{
			petent2->hide();
			gs->playerIco.hide();
			if(gs->phone->pickedUp)
				state = 25;
			showButtons = false;
			gs->phone->call();
			gs->phone->addToQueue(L"Dobrze, �e to zg�osi�e� do IOD, kt�ry nada temu zg�oszeniu dalszy bieg.");
			gs->phone->addToQueue(L"Otrzymujesz pouczenie i incydent ostaje odnotowany w rejestrach IOD.");
			gs->phone->addToQueue(L"Musisz wzi�� udzia� w szkoleniu z zakresu ochrony danych osobowych.");
		}
		break;
	case 21: //sciezka 1 koniec 1
		if(thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			thought->changeText(L"Innymi s�owy - jak b�dziesz mi dalej dok�ada� tylu stres�w to nied�ugo b�dziesz mie� nowego szefa");
			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 4000;
			state++;
		}
		break;
	case 22: //sciezka 1 koniec 1
		if(thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			thought->closeBubble();
			state = 33;
		}
		break;
	case 23: //sciezka 1 koniec 2
		if(thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			thought->changeText(L" wyciek danych, kt�ry spowodowa�e�, nie nara�a podmiotu danych (Piotra Nowaka) na szkod�. Sprawa wycieku wzi�� nie jest zako�czona!");
			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 4000;
			state++;
		}
		break;
	case 24: //sciezka 1 koniec 2
		if(thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			thought->closeBubble();
			state = 33;
		}
		break;
	case 25: //sciezka 1 koniec 3 
		if(!gs->phone->pickedUp)
		{
			state = 33;
		}
		break;
	case 26: //sciezka 2
		if(gs->playerIco.ready)
		{
			petent2->state = 0;
			petent2->text.setTextString(L"Nie mam �adnego upowa�nienia, a po co mi to?");
			petent2->addToQueue(L"Nie mam �adnego upowa�nienia, a po co mi to?");
			state++;
		}
		break;
	case 27:
		if(petent2->state == 1)
		{
			gs->playerIco.text.setTextString(L"Potrzebuj� upowa�nienia, �eby m�c udost�pni� dane m�a");
			petent2->state = 0;
			petent2->text.setTextString(L"Akurat, napewno mi je da, pirat jeden. I na co ja si� t�uk�am. Dzi�kuj� za nic");
			petent2->addToQueue(L"Akurat, napewno mi je da, pirat jeden. I na co ja si� t�uk�am. Dzi�kuj� za nic");
			state++;
		}
		break;
	case 28:
		if(petent2->state == 1)
		{
			gs->playerIco.text.setTextString(L"A Pani mandaty?");
			petent2->state = 0;
			petent2->text.setTextString(L"Jednak nie mam �adnych manadat�w. Ale on na pewno ma. Wiem to!");
			petent2->addToQueue(L"Jednak nie mam �adnych manadat�w. Ale on na pewno ma. Wiem to!");
			state++;
		}
		break;
	case 29:
		if(petent2->state == 1) //koniec sciezki 2
		{
			petent2->hide();
			gs->playerIco.hide();
			state = 33;
		}
		break;
	case 30: //sciezka 3
		if(thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			gs->playerIco.hide();
			petent2->setButtonInactive();
			petent2->text.setTextString(L"Przecie� nie prosz� o dane osobowe m�a, wi�c RODO nie ma tu nic do rzeczy");
			gs->choice1->setScale(0.8,0.8);
			gs->choice2->setScale(0.8,0.8);
			gs->choice1->setText(L"Owszem, RODO dotyczy przetwarzania danych osobowych,\na zatem mi�dzy innymi danych os�b zobowi�zanych do\nzap�aty mandat�w. Musz� odm�wi�.");
			gs->choice2->setText(L" Rzeczywi�cie, RODO obejmuje tylko imi�, nazwisko,\nPESEL, adres itd, a o mandatach nic tam nie ma,\nwi�c je�eli poda mi Pani dane m�a to b�dzie\nwszystko w porz�dku. Ju� sprawdzamy.");
			showButtons = true;
			state++;
		}
		break;
	case 31:
		if(gs->choice1->clicked(win)) //sciezka 3 koniec
		{
			petent2->hide();
			gs->playerIco.hide();
			gs->choice1->setScale(0.6,0.6);
			gs->choice2->setScale(0.6,0.6);
			showButtons = false;
			quest2completed = true;
			state = 33;
		}
		if(gs->choice2->clicked(win))
		{
			gs->choice1->setScale(0.6,0.6);
			gs->choice2->setScale(0.6,0.6);
			petent2->hide();
			gs->playerIco.hide();
			showButtons = false;
			gs->data->nagany++;
			thought->setBubblePosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			thought->showBubble();
			thought->changeText(L"Niezgodnie z obowi�zuj�cym prawem przetworzono dane osobowe osoby nie b�d�cej petentem.");
			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 4000;
			state++;
		}
		break;
	case 32:
		if(thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			thought->changeText(L"Innymi s�owy - jak przyjdzie ''uradowany'' ma� by ''podzi�kowa�'' odsy�amy go do Ciebie");
			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 4000;
			state++;
		}
		break;
	case 33: //sciezka 1 koniec 1
		if(thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			thought->closeBubble();
			state = 33;
		}
		break;
	case 34: //quest 3
		
		break;
	}

}

void Day_4::draw(GameState* gs, sf::RenderWindow& win)
{
	thought->draw(win);
	itGuy->draw(win);
	boss->draw(win);
	petent1->draw(win);
	petent2->draw(win);
	

	if(drawDowod)
	{
		win.draw(dowod1);
	}

	if(showNewspaper)
		win.draw(newspaper);

	gs->choice1->draw(win);
	gs->choice2->draw(win);
	gs->choice3->draw(win);

	win.display();
}

