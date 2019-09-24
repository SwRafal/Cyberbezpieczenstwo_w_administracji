#include "Day_4.h"
#include "GameState.h"

Day_4::Day_4() : b1(*gm::Assets::getFont()), b2(*gm::Assets::getFont()), b3(*gm::Assets::getFont()), b4(*gm::Assets::getFont()), b5(*gm::Assets::getFont()), b6(*gm::Assets::getFont()), b7(*gm::Assets::getFont()),b8(*gm::Assets::getFont())
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

	gm::Assets::LoadTexture("letter", LETTER);
	gm::Assets::LoadTexture("letterOpen", LETTER_OPEN);
	letter.setTexture(*gm::Assets::getTexture("letter"));
	letterOpen.setTexture(*gm::Assets::getTexture("letterOpen"));

	gm::Assets::LoadTexture("L1", L1);
	gm::Assets::LoadTexture("L2", L2);
	gm::Assets::LoadTexture("L3", L3);

	gm::Assets::LoadTexture("finalResponse", FINAL_RESPONSE);
	finalResponse.setTexture(*gm::Assets::getTexture("finalResponse"));

	gm::Assets::LoadTexture("checkingGameBG", CHECKING_GAME);
	checkingGameBG.setTexture(*gm::Assets::getTexture("checkingGameBG"));
	checkingGameBG.setPosition(235, 120);

	b1.setSize(20,20);
	b2.setSize(20,20);
	b3.setSize(20,20);
	b4.setSize(20,20);
	b5.setSize(20,20);
	b6.setSize(20,20);
	b7.setSize(20,20);
	b8.setSize(20,20);

	b1.setPosition( 320, 242);
	b2.setPosition( 320, 316);
	b3.setPosition( 320, 414);
	b4.setPosition( 320, 500);

	b5.setPosition( 672, 242);
	b6.setPosition( 672, 316);
	b7.setPosition( 672, 414);
	b8.setPosition( 672, 500);

}

Day_4::~Day_4()
{
	
}

void Day_4::update(GameState* gs, sf::RenderWindow& win)
{
	if(showButtons)
	{
		if(state == 17 || state == 20 || state == 42 || state == 56)
		{
			gs->choice2->setPosition(SCREEN_WIDTH / 2 - gs->choice2->background.getGlobalBounds().width / 2,SCREEN_HEIGHT * 0.6);
			gs->choice1->setPosition(gs->choice2->background.getPosition().x - gs->choice1->background.getGlobalBounds().width - 5,SCREEN_HEIGHT * 0.6);
			gs->choice3->setPosition(gs->choice2->background.getPosition().x + gs->choice2->background.getGlobalBounds().width + 5,SCREEN_HEIGHT * 0.6);
		}
		else if(state == 52)
		{
			gs->choice1->setPosition(SCREEN_WIDTH / 2 - gs->choice1->background.getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.85);
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
	gs->mariolka->animate();

	switch (state)
	{
	case -1: //init
		gs->openedbook->setInfoL(L"Minimalizacja danych osobowych – tylko dane niezbêdne do celu przetwarzania");
		gs->xero->setPosition(XERO_POS_X, XERO_POS_Y);
		gs->card->setPosition( 830,500);
		gs->openedcomputer->getLogin() = gs->data->login;
		gs->openedcomputer->getPassword() = gs->data->password;
		gs->cardReader->hidden = false;
		gs->cardReader->update();
		state = 53;
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
			thought->changeText(L"Nie œpij w pracy!");
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
		itGuy->text.setTextString(L"Hej widzia³eœ dzisiejsz¹ gazetê?");
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
				itGuy->text.setTextString(L"Ooooo widzê, ¿e pamiêæ naszego kombajnu jest totalnie zapchana");
				itGuy->addToQueue(L"woooaaa!!! Zeskanowa³eœ wczoraj ca³¹ bazê pracowników Ministerstwa?");
				itGuy->addToQueue(L"No tak, szef pewnie nie powiedzia³ ci, ¿e po zakoñczonym skanowaniu,");
				itGuy->addToQueue(L"drukowaniu czy kserowaniu trzeba czyœciæ pamiêæ takiego urz¹dzenia?");
				itGuy->addToQueue(L"Nie? To w jego stylu… przecie¿ ''Drukarka to nie komputer''");
				itGuy->addToQueue(L"''Nikt przez nas przez ni¹ nie zaatakuje.''");
				itGuy->addToQueue(L"Na przysz³oœæ pamiêtaj, ¿e\n drukarka pod³¹czona do sieci");
				itGuy->addToQueue(L"jest najs³abszym ogniwem obrony naszych urzêdów");
				itGuy->addToQueue(L"Góra ¿a³uje nam funduszy na prawid³owe ich zabezpieczenie");
				itGuy->addToQueue(L"Postaraj siê, ¿eby czyœciæ jej pamiêæ zanim pójdziesz do domu");
				itGuy->addToQueue(L"Mieliœmy szczêœcie, ¿e tym razem nie zaatakowano nas");
				itGuy->addToQueue(L"OK, zrobi³em co mia³em zrobiæ.");
				itGuy->addToQueue(L"Masz zainstalowny nowy system pozwalaj¹cy sprawniej zapraszaæ petentów. Powodzenia!");
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
			thought->changeText(L"By wezwaæ interesanta, naciœnij dzwonek");
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
			petent1->text.setTextString(L"Dzieñ dobry, chcia³bym siê dowiedzieæ czy moje prawo jazdy ju¿ jest gotowe do odbioru?");
			petent1->show();
			gs->choice1->setText(L"Proszê o okazanie\ndowodu osobistego");
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
			petent1->text.setTextString(L"Nazywam siê Jan Kowalski, numer PESEL to 93030215201");
			gs->choice1->setText(L"Dokument jest gotowy do odbioru,\nproszê o okazanie dowodu osobistego");
			gs->choice2->setText(L"Dokument jest gotowy do odbioru");
			state = 14;
		}
		break;
	case 11:
		gs->choice1->setText(L"Wydaj prawo jazdy");
		gs->choice2->setText(L"Skseruj dowód i wydaj prawo jazdy");
		if(gs->choice1->clicked(win))
		{
			showButtons = false;
			drawDowod = false;
			dowod1.setPosition(SCREEN_WIDTH,SCREEN_HEIGHT);
			petent1->text.setTextString(L"Dziêkujê");
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
			petent1->text.setTextString(L"Dziêkujê");
			petent1->addToQueue(L" ");
			petent1->setButtonActive();
			petent1->state = 0;

			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 3000;
			thought->changeText(L"Kserowanie dowodu nie jest niezbêdne do wykonania zadania, a nara¿a urz¹d na wyciek danych");
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
			gs->gameover(L"Przekaza³eœ dokument zawierajacy dane osobowe (wyciek danych) osobie, której uprawnienia do otrzymania tych danych nie zweryfikowa³eœ.\nFa³szywy Jan Kowalski pos³u¿y³ siê prawem jazdy do wyp³aty gotówki w banku prawowitego w³aœciciela.\nZostajesz zwolniony dyscyplinarnie w trybie natychmiastowym");
		}
		break;
	case 15: //quest 2;
		if(callIn)
		{
			petent2->state = 0;
			petent2->text.setTextString(L"Dzieñ dobry, chcia³abym zap³aciæ  za mandaty, które dosta³am.");
			petent2->addToQueue(L"Przy okazji jak ju¿ tu jestem chcia³abym zap³aciæ za mandaty mê¿a, bo te¿ mówi³, ¿e coœ tam ma zaleg³ego. Piotr Nowak");
			petent2->show();
			state++;
		}
		break;
	case 16:
		if(petent2->state == 1)
		{
			showButtons = true;
			gs->choice1->setText(L"ZgódŸ siê");
			gs->choice2->setText(L"Poproœ o dodatkowe informacje");
			gs->choice3->setText(L"Odmów");
			state++;
		}
		break;
	case 17:
		if(gs->choice1->clicked(win))//sciezka 1
		{
			gs->playerIco.text.setTextString(L"Dobrze, podam Pani informacje o mandatach mê¿a. Poproszê o PESEL mê¿a");
			gs->playerIco.show();
			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 3000;
			showButtons = false;
			state++;
		}
		if(gs->choice2->clicked(win)) //sciezka 2
		{
			showButtons = false;
			gs->playerIco.text.setTextString(L"Nie ma problemu, poproszê o upowa¿nie od mê¿a dla Pani do za³atwienia tej sprawy w jego imieniu lub upowa¿nienie ogólne");
			gs->playerIco.show();
			state = 26;
		}
		if(gs->choice3->clicked(win)) //sciezka 3
		{
			showButtons = false;
			gs->playerIco.text.setTextString(L"Przepraszam, ale nie mogê przekazaæ danych dotycz¹cych innych osób, RODO, rozumie Pani");
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
			petent2->text.setTextString(L"Czyli jednak ma jakieœ mandaty! Pirat jeden! Teraz bêdê mia³a na niego haka!");
			petent2->addToQueue(L"Czyli jednak ma jakieœ mandaty! Pirat jeden! Teraz bêdê mia³a na niego haka!");
			petent2->setButtonActive();
			state++;
		}
		break;
	case 19:
		if(petent2->state == 1)
		{
			petent2->setButtonInactive();
			gs->playerIco.text.setTextString(L"Chwila, czyli nie ma Pani upowa¿nienia od mê¿a?");
			gs->playerIco.show();
			showButtons = true;
			gs->choice1->setText(L"Zignoruj ma³zeñsk¹ sprzeczkê");
			gs->choice2->setText(L"Zg³oœ wyciek danych do UODO");
			gs->choice3->setText(L"Zg³oœ wyciek danych do IOD");
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
			thought->changeText(L"Nie tylko dopuszczono do wycieku danych, ale w dodatku nie podjêto ¿adnych dzia³añ, przez co nara¿ono instytujê na dalsze ryzyko.");
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
			thought->changeText(L"Masz dobre intencje, ale pope³ni³eœ b³¹d! Formularz na stronie UODO przyjmie Twoje zg³oszenie, ale zg³oszenie zostanie bez rozpatrzenia.");
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
			gs->phone->addToQueue(L"Dobrze, ¿e to zg³osi³eœ do IOD, który nada temu zg³oszeniu dalszy bieg.");
			gs->phone->addToQueue(L"Otrzymujesz pouczenie i incydent ostaje odnotowany w rejestrach IOD.");
			gs->phone->addToQueue(L"Musisz wzi¹æ udzia³ w szkoleniu z zakresu ochrony danych osobowych.");
		}
		break;
	case 21: //sciezka 1 koniec 1
		if(thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			thought->changeText(L"Innymi s³owy - jak bêdziesz mi dalej dok³adaæ tylu stresów to nied³ugo bêdziesz mieæ nowego szefa");
			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 4000;
			state++;
		}
		break;
	case 22: //sciezka 1 koniec 1
		if(thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			thought->closeBubble();
			state = 34;
		}
		break;
	case 23: //sciezka 1 koniec 2
		if(thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			thought->changeText(L" wyciek danych, który spowodowa³eœ, nie nara¿a podmiotu danych (Piotra Nowaka) na szkodê. Sprawa wycieku wzi¹¿ nie jest zakoñczona!");
			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 4000;
			state++;
		}
		break;
	case 24: //sciezka 1 koniec 2
		if(thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			thought->closeBubble();
			state = 34;
		}
		break;
	case 25: //sciezka 1 koniec 3 
		if(!gs->phone->pickedUp)
		{
			state = 34;
		}
		break;
	case 26: //sciezka 2
		if(gs->playerIco.ready)
		{
			petent2->state = 0;
			petent2->text.setTextString(L"Nie mam ¿adnego upowa¿nienia, a po co mi to?");
			petent2->addToQueue(L"Nie mam ¿adnego upowa¿nienia, a po co mi to?");
			state++;
		}
		break;
	case 27:
		if(petent2->state == 1)
		{
			gs->playerIco.text.setTextString(L"Potrzebujê upowa¿nienia, ¿eby móc udostêpniæ dane mê¿a");
			petent2->state = 0;
			petent2->text.setTextString(L"Akurat, napewno mi je da, pirat jeden. I na co ja siê t³uk³am. Dziêkujê za nic");
			petent2->addToQueue(L"Akurat, napewno mi je da, pirat jeden. I na co ja siê t³uk³am. Dziêkujê za nic");
			state++;
		}
		break;
	case 28:
		if(petent2->state == 1)
		{
			gs->playerIco.text.setTextString(L"A Pani mandaty?");
			petent2->state = 0;
			petent2->text.setTextString(L"Jednak nie mam ¿adnych manadatów. Ale on na pewno ma. Wiem to!");
			petent2->addToQueue(L"Jednak nie mam ¿adnych manadatów. Ale on na pewno ma. Wiem to!");
			state++;
		}
		break;
	case 29:
		if(petent2->state == 1) //koniec sciezki 2
		{
			petent2->hide();
			gs->playerIco.hide();
			state = 34;
		}
		break;
	case 30: //sciezka 3
		if(thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			gs->playerIco.hide();
			petent2->setButtonInactive();
			petent2->text.setTextString(L"Przecie¿ nie proszê o dane osobowe mê¿a, wiêc RODO nie ma tu nic do rzeczy");
			gs->choice1->setScale(0.8,0.8);
			gs->choice2->setScale(0.8,0.8);
			gs->choice1->setText(L"Owszem, RODO dotyczy przetwarzania danych osobowych,\na zatem miêdzy innymi danych osób zobowi¹zanych do\nzap³aty mandatów. Muszê odmówiæ.");
			gs->choice2->setText(L" Rzeczywiœcie, RODO obejmuje tylko imiê, nazwisko,\nPESEL, adres itd, a o mandatach nic tam nie ma,\nwiêc je¿eli poda mi Pani dane mê¿a to bêdzie\nwszystko w porz¹dku. Ju¿ sprawdzamy.");
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
			state = 34;
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
			thought->changeText(L"Niezgodnie z obowi¹zuj¹cym prawem przetworzono dane osobowe osoby nie bêd¹cej petentem.");
			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 4000;
			state++;
		}
		break;
	case 32:
		if(thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			thought->changeText(L"Innymi s³owy - jak przyjdzie ''uradowany'' ma¿ by ''podziêkowaæ'' odsy³amy go do Ciebie");
			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 4000;
			state++;
		}
		break;
	case 33: 
		if(thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			thought->closeBubble();
			state = 34;
		}
		break;
	case 34: //quest 3
		gs->mariolka->state = 0;
		gs->playerIco.state = 0;

		gs->mariolka->text.setTextString(L"Hej, zapl¹ta³o mi siê coœ z Twojej korespondencji.");  //0
		gs->mariolka->addToQueue(L"Chyba wa¿ne bo od NIK-u. I grube, sporo tego. Zobaczmy czego chc¹"); //1
		gs->mariolka->addToQueue(L"No i?"); //2
		gs->mariolka->addToQueue(L"No co ty, nie ufasz mi? Znamy siê ju¿ 4 dni... Czyli praktycznie jesteœmy rodzin¹."); //3
		gs->mariolka->addToQueue(L"Oj wyluzuj. Czepiasz siê bardziej ni¿ IOD."); //4
		gs->mariolka->addToQueue(L"Dobra – trzymaj."); //5

		gs->mariolka->setButtonActive();

		gs->playerIco.text.setTextString(L"Emm, to chyba by³o adresowane bezpoœrednio do mnie...");
		gs->playerIco.addToQueue(L"S¹dzê, ¿e nie powinnaœ tego czytaæ jak nie ma potrzeby.");
		gs->playerIco.addToQueue(L"Po prostu mi to daj.");
		gs->playerIco.addToQueue(L"Inspektorowii Ochrony Danych to zaraz zg³oszê naruszenie bezpieczeñstwa danych jak mi tego nie dasz.");
		gs->mariolka->show();

		state++;
		break;
	case 35:
		if(gs->mariolka->state == 1)
		{
			gs->playerIco.show();
			state++;
		}
		break;
	case 36:
		if(gs->mariolka->state == 2)
		{
			gs->playerIco.nextLine();
			state++;
		}
		break;
	case 37:
		if(gs->mariolka->state == 3)
		{
			gs->playerIco.nextLine();
			state++;
		}
		break;
	case 38:
		if(gs->mariolka->state == 4)
		{
			gs->playerIco.nextLine();
			state++;
		}
		break;
	case 39:
		if(gs->mariolka->state == 5)
		{
			gs->playerIco.hide();
			gs->mariolka->hide();
			letter.setPosition(LETTER_START_X,LETTER_START_Y);
			state++;
		}
		break;
	case 40:
		drawLetter = true;
		if(letter.getPosition().x < LETTER_FINISH_X)
			letter.move(2,0);
		if(letter.getPosition().y < LETTER_FINISH_Y)
			letter.move(0,2);
		if(letter.getPosition().x == LETTER_FINISH_X || letter.getPosition().y == LETTER_FINISH_Y )
		{
			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 500;
			state++;
		}
		break;
	case 41:
		if(thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			//drawLetter = false;
			drawLetterOpen = true;
			showButtons = true;
			gs->choice1->setText(L"Przeœlij dane");
			gs->choice2->setText(L"Odmów przes³ania danych");
			gs->choice3->setText(L"Zapytaj o cel pozyskania danych");
			state++;
		}
		break;
	case 42: //response choice
		if(gs->choice1->clicked(win))
		{
			drawLetterOpen = false;
			showButtons = false;
			response.setTexture(*gm::Assets::getTexture("L1"));
			rChoice = 1;
			state++;
		}
		if(gs->choice2->clicked(win))
		{
			drawLetterOpen = false;
			showButtons = false;
			response.setTexture(*gm::Assets::getTexture("L2"));
			rChoice = 2;
			state++;
		}
		if(gs->choice3->clicked(win))
		{
			drawLetterOpen = false;
			showButtons = false;
			response.setTexture(*gm::Assets::getTexture("L3"));
			rChoice = 3;
			state++;
		}
		break;
	case 43:
		drawResponse = true;
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			drawResponse = false;
			state++;
		}
		break;
	case 44:
		if(letter.getPosition().x < SCREEN_WIDTH + 10);
			letter.move(1,0);
		if(letter.getPosition().y > 0)
			letter.move(0,-2);
		if(letter.getPosition().x >= SCREEN_WIDTH + 10 && letter.getPosition().y <= 0)
		{
			if(rChoice == 1) //sciezka 1
				state++;
			if(rChoice == 2 || rChoice == 3)
				state = 50; // sciezka 2;
		}
		break;
	case 45: //sciezka 1
		gs->mariolka->text.setTextString(L"Zrobisz kopiê danych, zanim je wyœlesz do NIK?");
		gs->choice1->setScale(0.8,0.8);
		gs->choice2->setScale(0.8,0.8);
		
		gs->choice1->setText(L"Tak, muszê w koñcu zachowaæ integraloœæ bazy.\nJak tylko dokumenty wróc¹ z NIK to kopie zniszczê.\nMuszê tylko to wszystko uzgodniæ z IOD.");
		gs->choice2->setText(L"Nie zrobiê kopii. Zasady przetwarzania tych danych\nnie przewidywa³y tworzenia kopii.\nW NIK przecie¿ te dane nie zgin¹.");
		showButtons = true;
		gs->mariolka->setButtonInactive();
		gs->mariolka->show();
		state++;
		break;
	case 46:
		if(gs->choice1->clicked(win))
		{
			showButtons = false;
			gs->choice1->setScale(0.6,0.6);
			gs->mariolka->hide();
			state++;
		}
		if(gs->choice2->clicked(win))
		{
			showButtons = false;
			gs->choice2->setScale(0.6,0.6);
			gs->mariolka->hide();
			state++;
		}
		break;
	case 47:
		gs->computer->open();
		gs->openedcomputer->newMail(L"Nagana", L"IOD",L"Szanowna Pani/Panie,\nZosta³em poinformowany, i¿ niezgodnie z obowi¹zuj¹cym prawem przekaza³a Pani/Pan dane petentów do instytucji zewnêtrznej w ramach procedur kontrolnych prowadzonych przez tê instytucjê.\nTakie dzia³anie jest niezgodne z celem, dla którego zosta³y pozyskane i nie jest uzasadnione celem konktroli.\nProszê o niezw³oczne przekazanie szczegó³owego raportu ze zdarzenia w celu nadania biegu sprawie w ramach procedur ochrony danych osobowych");
		gs->openedcomputer->setState(OpenPC::MAIL);
		state++;
		break;
	case 48:
		if(gs->openedcomputer->getState() != OpenPC::MAIL)
		{
			gs->computer->close();
			gs->data->nagany++;
			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + THOUGHT_TIME;
			thought->changeText(L"Wielki Szef patrzy i widza³ maila. Pilnuj siê...");
			thought->setBubblePosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			thought->showBubble();
			state++;
		}
		break;
	case 49:
		if(thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			thought->closeBubble();
			state = 54;
		}
		break;
	case 50: //sciezka 2
		if(letter.getPosition().x > LETTER_FINISH_X)
			letter.move(-1,0);
		if(letter.getPosition().y < LETTER_FINISH_Y)
			letter.move(0,2);
		if(letter.getPosition().x == LETTER_FINISH_X || letter.getPosition().y == LETTER_FINISH_Y )
		{
			drawFinalResponse = true;
			state++;
		}
		break;
	case 51:
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			drawFinalResponse = false;
			drawLetter = false;
			showMinigame = true;
			showButtons = true;
			gs->choice1->setText(L"Drukuj");
			state++;
		}
		break;
	case 52: //minigame;
		b1.update(win);
		b2.update(win);
		b3.update(win);
		b4.update(win);
		b5.update(win);
		b6.update(win);
		b7.update(win);
		b8.update(win);

		if(gs->choice1->clicked(win))
		{//1 2 4 5
			if(b1.isChecked() && b2.isChecked() && b4.isChecked() && b5.isChecked() && !b3.isChecked() && !b6.isChecked() && !b7.isChecked() && !b8.isChecked())
			{
				showButtons = false;
				selectedProperly = true;
			}
			else
			{
				showButtons = false;
				selectedProperly = false;
			}
			state++;
			showMinigame = false;
		}
		break;
	case 53:
		if(selectedProperly)
		{
			state = 54;
		}
		else
			state = 47;
		break;

	case 54: //last quest
		gs->mariolka->show();
		gs->mariolka->setButtonActive();
		gs->mariolka->state = 0;
		gs->mariolka->text.setTextString(L"Czeœæ, s³ysza³am, ¿e trafi³o Ci siê zestawienie NIKu za ostatnie 3 miesi¹ce.");
		gs->mariolka->addToQueue(L"Mo¿esz mi przes³aæ pe³n¹ listê swoich interesantów z ostatniego kwarta³u?");
		gs->mariolka->addToQueue(L"Muszê coœ takiego przygotowaæ dla szefa w ramach szkolenia.");
		state++;
		break;
	case 55:
		if(gs->mariolka->state == 2)
		{
			gs->mariolka->setButtonInactive();
			showButtons = true;
			gs->choice1->setText(L"Ok, nie ma sprawy");
			gs->choice2->setText(L"Nie mogê Ci pomóc");
			gs->choice3->setText(L"A w jakim celu s¹ Ci te dane potrzebne?");
			state++;
		}
		break;
	case 56:
		if(gs->choice1->clicked(win)) //sciezka 1
		{
			showButtons = false;
			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + THOUGHT_TIME;
			thought->setBubblePosition(SCREEN_WIDTH /2, SCREEN_HEIGHT /2);
			thought->changeText(L"Wykryto nieupranion¹ próbê skopiowania danych z systemu\nSzef-bot 3000 jest z³y :(");
			thought->showBubble();
			gs->data->nagany++;
			state++;
		}
		if(gs->choice2->clicked(win))
		{
			showButtons = false;
			gs->playerIco.text.setTextString(L"Nie mogê Ci ich przes³aæ, poniewa¿ zajmujesz siê nimi w innym celu, wiêc by³oby to nieuprawnion¹ zmian¹ celu przetwarzania");
			gs->playerIco.show();
			gs->mariolka->text.setTextString(L"No wiesz, myœla³am, ¿e jesteœ moj¹ kole¿ank¹...");
			gs->mariolka->addToQueue(L" ");
			gs->mariolka->state = 0;
			gs->mariolka->setButtonActive();
			state = 58;
		}
		if(gs->choice3->clicked(win)) //sciezka 3;
		{
			
		}
		break;
	case 57:
		if(thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			thought->closeBubble();
			//last conversation
		}
		break;
	case 58: //sciezka 2
		if(gs->mariolka->state == 1)
		{
			gs->mariolka->hide();
			gs->playerIco.hide();
			//last conversation;
		}
		break;
	case 59: //sciezka 3 

		break;
	
	
	}

}

void Day_4::draw(GameState* gs, sf::RenderWindow& win)
{
	gs->mariolka->draw(win);
	thought->draw(win);
	itGuy->draw(win);
	boss->draw(win);
	petent1->draw(win);
	petent2->draw(win);
	

	if(drawDowod)
	{
		win.draw(dowod1);
	}
	if(drawLetter)
		win.draw(letter);
	if(drawLetterOpen)
		win.draw(letterOpen);
	if(drawResponse)
		win.draw(response);
	if(drawFinalResponse)
		win.draw(finalResponse);
	if(showNewspaper)
		win.draw(newspaper);

	if(state == 52)
	{
		win.draw(checkingGameBG);
		win.draw(b1);
		win.draw(b2);
		win.draw(b3);
		win.draw(b4);
		win.draw(b5);
		win.draw(b6);
		win.draw(b7);
		win.draw(b8);
	}

	gs->choice1->draw(win);
	gs->choice2->draw(win);
	gs->choice3->draw(win);

	win.display();
}

