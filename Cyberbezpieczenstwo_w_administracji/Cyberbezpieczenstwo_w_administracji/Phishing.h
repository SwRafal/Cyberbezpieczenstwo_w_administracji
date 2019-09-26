#pragma once
#include "Engine/Engine.h"
#include "Functions.h"
#include <vector>
#include "PhishingMail.h"

#define PHISHING_POS_X 
#define PHISHING_POS_Y 
#define PHISHING_WIDTH 
#define PHISHING_HEIGHT 

#define MAIL_POS_X 403
#define MAIL_POS_Y 163
#define MAIL_WIDTH 597
#define MAIL_HEIGHT 70

class Phishing
{
private:
	//Good mail
	const sf::String g_senders[14] = {
		"plnbank@plnbank.pl",
		"news@urzedniczek.pl",
		"@urzedniczek.pl",
		"numizmatyka@nbp.gov.pl",
		"dzial.marketingu@msw.gov.pl",
		"wieslawa.noz@bufetmsw.pl",
		"mariola.nieuwazna@msw.gov.pl",
		"bartlomiej.kot@wsa.edu.pl",
		"m.drzesiak@coach.pl",
		"ksiegowosc@msw.gov.pl",
		"k.blysk@blyskpol.pl",
		"multisportek@multi.com",
		"edukacja@msw.gov.pl",
		"statystyki@msw.gov.pl"
	};
	const sf::String g_titles[14] = {
		L"Od 14 wrze�nia inaczej zalogujesz si� na konto!",
		L"Newsletter Urz�dniczka",
		L"Modna urz�dniczka -50% na garsonki",
		L"Katalog monet na rok 2020",
		L"Loteria pracownicza",
		L"promocja na sushi",
		L"zbi�rka karmy dla kot�w",
		L"Zaproszenie na konferencj�",
		L"[przekazane przez: aniela_dab@msw.gov.pl] Zyskaj PEWNO�� SIEBIE na warsztatach coachingowych",
		L"Zmiana numeru konta.",
		L"Faktura VAT 09.2019",
		L"Postaw na form�! Karnet fitness ju� za 39 z�!",
		L"Cotygodniowy katalog kurs�w jest ju� dost�pny",
		L"badanie zadowolenia pracownik�w"
	};
	const sf::String g_contents[14] = {
		L"Dzie� dobry,\n14 wrze�nia czeka Ci� du�o zmian, kt�re wynikaj� z dyrektywy PSD2.Przeczytaj o nich na naszej stronie.Mo�e jaki� szczeg� oka�e si� dla Ciebie wa�ny.\n \nZ pozdrowieniami\nzesp� plnBanku",
		L"W najnowszym wydaniu Urz�dniczka:\n- \"Korzystanie z klimatyzacji w urz�dzie � przywilej czy obowi�zek?\"\n- \"Urlop czy L4? Jak dokona� m�drego wyboru.\"\n- \"Phishing, czyli �owi� nas jak karpie na Wigili�\".\n \nSprawd� ju� dzi�!",
		L"Rozpoczynamy nowy sezon! Nic tak wspaniale si� nie prezentuje jak wakacyjna opalenizna w garsonce z nowej kolekcji jesie� 2019. Sprawd� nasz� gazetk� i dowiedz si� wi�cej. Odwied� urzedniczek.pl / moda i daj si� zaskoczy� nowym trendom!",
		L"Szanowni Pa�stwo, z przyjemno�ci� przesy�amy Pa�stwu Katalog monet, kt�re planujemy wyemitowa� w roku 2020. Z dum� informujemy, i� nowy rok rozpoczniemy od emisji monety �X lat Ministerstwa ds. Wszelakich�.\n \nZ wyrazami szacunku starszy specjalista, Eugeniusz Grosik.\nZa��cznik: Katalog Monet 2020.pdf",
		L"Z okazji dziesi�ciolecia istnienia Ministerstwo ds. Wszelakich organizuje koncert jubileuszowy na Stadionie Narodowym. Zagraj� na nim najwi�ksze �wiatowe s�awy. Do wygrania 100 bilet�w na to wydarzenie! Zg�oszenia nale�y wys�a� do 31.10.2019 r. Wz�r zg�oszenia w za��czeniu.\n \nZ wyrazami szacunku,\nKierownik dzia�u marketingu MSW,\nHelena Kopka\nZa��cznik : wz�r zg�oszenia konkursowego.doc",
		L"Szanowni Pracownicy, informuje, �e ulotki promocyjne kolportowane w ostatnich dniach na terenie ministerstwa nie pochodz� z mojej emisji. Ze wzgl�du jednak na du�e zainteresowanie nowo wprowadzonymi do Menu smakami Sushi, przesy�am tajne has�o na rabat -15% dla pierwszych 15 os�b: �PYSZNE SUSHI PANI WIESI�.\n \nPozdrawiam,\nWies�awa N�",
		L"Cze�� wszystkim. Jestem now� pracownic� tego dzia�u. Idzie zima, wiec pomy�la�am, �e warto by�oby zebra� karm� dla kot�w mieszkaj�cych przy Ministerstwie.\nW naszym dziale jest nasz 100 os�b, gdyby ka�dy z nas przyni�s� po worku karmy, kotom starczy�oby na ca�� zim�. Karm� b�d� zbiera� po swojej zmianie. �apcie m�j grafik.\nZa��cznik: grafik.mariolka.xcl",
		L"Szanowni Pa�stwo,\nw imieniu w�adz Wy�szej Szko�y Administracji mam zaszczyt zaprosi� Pa�stwa na konferencj� \"Cyberbezpiecze�stwo Administracji. �wiadomy urz�dnik � bezpieczny urz�d.\" Konferencja odb�dzie si� w dniach 24 - 25.10.2019 r.Szczeg�y w za��czonym programie.Zapisy do 30.09.2019 r.pod adresem cyberbezpiecze�two.wsa.edu.pl\nZa��cznik: Szczeg�owy Program Konferencji.",
		L"Witaj!\nCzy masz wra�enie, �e Tw�j potencja� jest marnowany ? Czujesz, �e nie osi�gasz tego, co powiniene� ? Nie dostajesz tego, Ci si� nale�y ?\nTo Porsche czeka, aby� do niego wsiad�!Opu�� swoj� stref� komfortu.\nZapraszam na warsztaty, gdzie odkryjesz siebie na nowo.\nWiecej na : mdrzesiak.pl\n \nPozdrawiam,\nMateusz Drzesiak � coach, filantrop",
		L"Szanowni Pracownicy,\nNumer konta Ministerstwa ulega zmianie w dniu 14.10.2019 r.z tego wzgl�du prosz� si� stawi� w dniach 7 - 11.10.2019 r.w sekretariacie dyrekcji waszego departamentu w celu podpisania aneksu do pa�stwa umowy o prac�.\n \nZ powa�aniem,\nHelena Orlicka,\nkierownik dzia�u ksi�gowo�ci MSW",
		L"Szanowni Pa�stwo,\nw za��czeniu przesy�am faktur� za nasze us�ugi za miesi�c wrzesie� br.\nWynagrodzenie prosz� wp�aci� na sta�y numer konta do dnia 10.10.2019 r.\n \nZ powa�aniem,\nKleofas B�ysk,\nDyrektor B�yskpol\n \nZa��cznik : faktura blyskpol.pdf",
		L"Zr�b form� do Sylwestra!\nCzy Tw�j pracodawca wie o Pakiecie sportowym Multisportek ? Jedna karta a tak wiele mo�liwo�ci!Nie przep�acaj, do��cz do naszego programu ju� dzi�!\n \nWi�cej informacji : multisportek.com\n \nPozdrawiamy,\nzesp� Multisportek\n \n---------------- - Moc, energia, multisportek!---------------- -",
		L"Drodzy Pracownicy,\nna naszej platformie edukacyjnej pojawi�y si� nowe kursy dost�pne od 1 pa�dziernika.Prosimy o zapoznanie si� z ofert�.Przypominamy o obowi�zku realizacji dw�ch wybranych kurs�w on - line do ko�ca tego roku.\n \nW razie dodatkowych pyta� lub problem�w technicznych zapraszamy do kontaktu: aneta_kaszle@msw.gov.pl\n \nPozdrawiam,\nW imieniu Departamentu Edukacji,\nAneta Kaszle",
		L"Dzie� dobry,\n \nPrzypominamy, i� na zlecenie Ministerstwa ds.Wszelakich realizujemy badanie dotycz�ce zadowolenia pracownik�w.Je�eli ju� uzupe�ni�/a Pan/i sw�j kwestionariusz - prosimy o zignorowanie tej wiadomo�ci.Je�li jednak jeszcze nie wype�ni�/a Pan/i ankiety, to zwracamy si� z serdeczn� pro�b� o mo�liwe jak najszybsze jej wype�nienie poprzez formularze dost�pne po zalogowaniu do systemu Ministerstwa.\nLogin: email @msw.gov.pl\nKod dost�powy : g8DBTEfcJmxd\n \nW razie dodatkowych pyta� lub problem�w technicznych zapraszamy do kontaktu.\n \nZesp� ds.Statystyki MSW"
	};

	//Bad mails
	const sf::String b_senders[20] = 
	{
		"dotekpay@pay.pl",
		"abay@abay.com",
		"allekexpress@allek.com",
		"ammegro@paczka.pl",
		"hosting@hosting.com",
		"security@facebook.com",
		"rat@securexlsd.com",
		"hackerman@ehncdms.dv",
		"xxxpron@hub.se",
		"infosadowe@sad.pl",
		"legalsowaw@ius.com",
		"6gh9jk0@bait.gh",
		"arek.lowca@drukarek.pl",
		"biuro.wsp�pracy@msvvia.gow.pl ",
		"k.laskowski@mssw.gow.pl",
		"janusz.pracz@co2.pl",
		"kadry@ministerstwo.pl",
		"blysexpol@sprzatanie.pl",
		"John.Cnr@juhuu.bg",
		"polska.policja@pp.pl"
	};
	const sf::String b_titles[20] =
	{
		L"Sprawd� status swojej p�atno�ci (C 1CBA XX15678931XX (PL))",
		L"Chro� swoje konto",
		L"Nowa polityka",
		L"Ammegro � potwierdzenie wygranej aukcji",
		L"Incydent bezpiecze�stwa � reset has�a",
		L"Logowanie � zesp� Facebook",
		L"Twoje sekretne �ycie",
		L"Twoje konto zosta�o zhackowane",
		L"Mam dla ciebie z�e wie�ci.",
		L"Inkwizycja s�dowa",
		L"Rozpocz�cie egzekucji",
		L"fajny gust",
		L"Awaria twojej drukarki",
		L"Pro�ba o list� pracownik�w uczestnicz�cych w warsztatach",
		L"Sprawdzenie Dyrektora Stefa�skiego ",
		L"Wniosek",
		L"Dane do premii",
		L"Zmiana numeru konta i Faktura za miesi�c Wrzesie�",
		L"Nowy numer konta",
		L"Wezwanie do pomocy w operacji"
	};
	const sf::String b_contents[20] = 
	{
		L"Witaj,\n \nzarejestrowali�my zlecenie p�atno�ci dla VXHXNE Sp.z o.o.\nMo�esz w dowolnym momencie sprawdzi� status transakcji loguj�c si� do serwisu transakcyjnego.\n \n[LOGOWANIE]\n \nW przypadku pyta� o t� transakcj�, po zalogowaniu skontaktuj si� z konsultantem na czacie.\n \nZesp� DotekPay S.A",
		L"Witaj,\n \nmin�� ju� ponad rok od czasu, gdy po raz ostatni aktualizowa�e� swoje informacje osobiste.Regularna aktualizacja pomaga nam lepiej chroni� twoje konto.Musisz tylko zalogowa� si� do aBay, poni�szym linkiem, aby sprawdzi� swoje informacje.Je�li niedawno zaktualizowa�e� swoje informacje osobiste zignoruj to przypomnienie.\n \n[ZALOGUJ DO ABAY]\n \nPozdrawiamy,\nzesp� aBay ds.kont",
		L"Witaj,\n \nw zwi�zku z dyrektyw� PSD2 zmieniamy polityk� p�atno�ci.Niezaakceptowanie nowych warunk�w spowoduje zablokowanie konta w serwisie allekexpress.Poni�szy link poprowadzi Pa�stwa krok po kroku przez procedur� weryfikacji Pa�stwa konta.\n \n[LINK]\n \nPozdrawiamy,\nzesp� Allekexpress",
		L"Witamy,\n \nprzesy�amy potwierdzenie wygranej aukcji i numer konta, na kt�ry nale�y dokona� przelewu w ci�gu 48h.\n \nPOTWIERDZENIE.EXE\n \nPozdrawiamy,\nZesp� Ammegro",
		L"Witamy,\n \nw zwi�zku z incydentem bezpiecze�stwa Twoje has�o zosta�o zresetowane.Zaloguj si� do systemu  i zmie� swoje dotychczasowe has�o.\n \n[ZALOGUJ]\n \nZesp� hosting.com",
		L"Witaj,\nWygl�da na to, �e masz problem z zalogowaniem si� do Facebooka.Kliknij poni�szy przycisk, a my Ci� zalogujemy.\n \n[Zaloguj si� jednym klikni�ciem]",
		L"Cze��, drogi u�ytkowniku Ministerstwo ds. Wszelakich!\nW tym momencie Twoje konto e - mail zosta�o zhakowane, a ja pobra�em wszystkie poufne informacje z twojego systemu.Je�li chcesz usun�� wszystkie zebrane dane, wy�lij mi 300$ w BTC(kryptowaluta).To jest m�j portfel Bitcoin : 1EBMu3FdAXiEK52JkStPd99f5a7RNuJB7A\nMasz 48 godzin po przeczytaniu tego listu.Od teraz b�d� ostro�ny!",
		L"Wgra�em wirusa na stron� http//www.rndw.gov.pl, kt�r� odwiedza�e�, a nast�pnie zainstalowa�e� go w swoim systemie operacyjnym. M�j trojan zosta� pobrany na twoje urz�dzenie.\nW tej chwili, oprogramowanie zebra�o wszystkie twoje dane kontaktowe z sieci spo�eczno�ciowych i adres�w e - mail.,Je�li chcesz usun�� wszystkie zebrane dane, wy�lij mi 50$ w BTC(kryptowaluta).To jest m�j portfel Bitcoin : 1EBGX3H74kStPd99f5a7RNuJB7A\n \nOdwied� tylko bezpieczne strony!PA!",
		L"20/08/2019 � w tym dniu w�ama�em si� do twojego systemu operacyjnego i uzyska�em pe�ny dost�p do twojego konta !  Chcia�em zablokowa� Twoje urz�dzenie i poprosi� o niewielk� kwot�, aby odblokowa�. Ale patrzy�em na strony, kt�re regularnie odwiedzasz i chc� powiedzie� � jeste� wielkim, wielkim zbocze�cem. Masz nieokie�znan� fantazj� !!! Za pomoc� kamery twojego urz�dzenia widzialem wszystko. Nie chcia�by� pokaza� tych zdj�� swoim krewnym, przyjacio�om lub wsp�pracownikom. 640 $ to bardzo ma�a kwota za moje milczenie. Akc\n \nP.S.Gwarantuj� ci, �e nie b�d� ci przeszkadza� po wyp�acie, poniewa� nie jeste�\nmoj� jedyn� ofiar�.\nTo jest kodeks hakerski.",
		L"Inkwizycja s�dowa informuje o wszcz�ciu post�powania za brak op�aty zad�u�enia 2,25 PLN. Aby zapobiec rozprawie prosimy o sp�at� https://inkwizytornia.cf/7301/ \nTa wiadomo�� zosta�a wygenerowana automatycznie.Prosz� na ni� nie odpowiada�",
		L"Informujemy o rozpoczeciu egzekucji Sygn. Akt 8710/19 z tytulu zaleglosci skarbowej 11.80 PLN. Uruchomilismy splate przez PayU https://wezwanie24.eu/us. \n \nTa wiadomo�� zosta�a wygenerowana automatycznie.Prosz� na ni� nie odpowiada�.",
		L"Hej, urz�dniku zhakowa�em twoje s�uzbowy komputer. To co na tym znalaz�em�.\nTwoje fantazja erotyczna sa bardzo ciekawy.Myslimy, ze prasa chce si�  tego wiedziec.\nPamietasz jak nie mogles polaczenie z Internet ? To wtedy wgralismy Trojan.Nagralismy twoje chwile relaksu, twoja kamerka�\nW mailu jest gif, wiemy ze otworzyles go wlasnie teraz.Gra rozpoczyna sie TERAZ, masz 24 godziny aby wplacic 1000 zl w Bitcoin na m�j portfel X3G6HW2XXG!A@X%S^H ^ 11G1.Jesli nie, twoje figlarne filmy wysle najpierw twojemu ma��onkowi i przyjaciolom po kolejnych 12 godzinach ministrowi i prasie.Nie badz zly, kazdy jakos na siebie zarabia�\nJa przynajmniej dalem ci dobra lekcje.Jeszcze mi za to podzienkujesz",
		L"Witam,\n \ntu serwisant twojej drukarki s�u�bowej.\nSystem pokazuje nam, �e pami�� twojej drukarki jest pe�na i nied�ugo przestanie dzia�a� poprawnie.\nSzef zabroni� usuwa� plik�w z pami�ci drukarki � sam wiesz, �e chce mie� kopie zapasow�.\nUzgodnili�my z ministrem, ze zawarto�� pami�ci drukarki przechowamy u nas.\nW mailu masz instrukcj� jak tego dokona�. (kliknij ok.aby wys�a�)\n \nPozdrawiam,\nArkadiusz �owiecki � autoryzowany serwis drukarek",
		L"Witam,\n \nzwracam si� z uprzejm� pro�b� o przekazanie mi listy pracownik�w uczestnicz�cych w warsztatach organizowanych w ramach wsp�pracy mi�dzyresortowej w dniach 05.10..2019 - 07.10.2019.\nZ informacji jakie uzyskali�my od Sekretarza Ministra 5.10 uczestniczy� ma ca�e pi�tro 1 � pokoje 101 - 115. 6.10 pi�tro 2. Pokoje 201 - 215. 7.10 pi�tro 3 pokoje 301 - 315.\nBardzo prosz� o przes�anie 3 list, na ka�dy dzie�.\nZ wyrazami szacunku\nHonorata Nowak � szef sekretariatu MSWIA",
		L"Szanowny pracowniku Ministerstwa ds. Wszelakich,\n \nAgencja Bezpiecze�stwa Wewn�trznego przedstawi�a mi wczoraj raport jasno wskazuj�cy na przest�pcz� dzia�alno�� dyrektora pa�stwa dzia�u.Zgodnie z wytycznymi ABW mamy przeprowadzi� obserwacj� �w Dyrektora Stefa�skiego.Z tego wzgl�du wszystkie raporty dotycz�ce mieszka�c�w stolicy(bez anonimizacji) prosz� przekazywa� r�wnie� mi.Musimy sprawdzi� czy Stefa�ski nie zmienia ich tre�ci przed wys�aniem do mnie.\nTo nie s� �wiczenia.Sytuacja jest powa�na.Zagro�one s� dane mieszka�c�w stolicy.\n \nZ powa�aniem,\nMinister ds.Wszelakich\nKazimierz Laskowski",
		L"Witam,\n \nW nawi�zaniu do rozmowy telefonicznej z Pani� Krystyn�, w imieniu mojego taty Jaros�awa Pracza, w za��czeniu przesy�am wniosek o pozwolenia na budow� kraw�nika wok� trawnika okalaj�cego hu�tawk� pod klatk� nr. 14 na ulicy brunatnej 88.\n \nZ wyrazami szacunku,\nJanusz Pracz\n \nZa�acznik : Wniosek.rar",
		L"Szanowny Pracowniku,\n \nNa mocy decyzji ministra nr 351 / MSW / 19 uzyska� / a Pan / Pani premi� za wzorowe wykonywanie obowi�zk�w pracowniczych.Prosz� o przes�anie swoich danych osobowych(imi�, nazwisko, PESEL) oraz numer konta bankowego.\n \nZ wyrazami szacunku,\nDzia� Kadr.\nW za��czeniu tre�� decyzji.\n \nZa��cznik Premia.bat",
		L"Szanowni Pa�stwo, z przyczyn od nas niezale�nych musieli�my zmieni� bank prowadz�cy nasze konto bankowe. Nowy numer konta to�: 90 3211 9167 3622 0000 3569 3563.\n \nProsimy o wprowadzenie tego numeru do waszego systemu.\nW za��czeniu przesy�amy te� faktur� za nasze us�ugi we Wrze�niu.Kwot� naszego wynagrodzenia prosz� przela� od razu na nowy numer konta.\n \nZ wyrazami szacunku,\nZesp� B�ysexPol � �Wyczy�cimy ci� na b�ysk�.\n \nZa�acznik: FV 256 / 2019 / 09.PDF",
		L"Hej,\ntu wujek Anieli.Ona nie ma dostep do jej e - mail.\nMam nadzieja, ze znalaz�em dobry email do ksi�gowej.Jesli nie, przekaz ten e - mail do ksi�gowa.\nAniela prosi�am o przekazanie � �Oto moj nowy numer konta : 19 9252 2521 0000 7925 8250 9876 - Prosze przekaz na niego moja wynagrodzenia�.\n \nWyrazy szacunku,\nJohn i Aniela.",
		L"Szanowni Pa�stwo!\n \nDzia�aj�c w imieniu Komendanta G��wnego Policji, wzywam Pana / Pani� do wsparcia dzia�a� operacyjnych Policji.Otrzymali�my wiele zg�osze� o pr�bach wy�udzania poufnych danych przy pomocy maili phishingowych.\nMinisterstwo poinformowa�o nas, �e takie ataki kierowano r�wnie� przeciw pa�stwu.\nTechnicy Policyjny opracowali program umo�liwiaj�cy wy�ledzenie miejsc sk�d nadano takie maile � przekazujemy go w za��czniku.\nZgodnie z decyzj� Ministra(w za��czeniu) ka�dy pracownik Ministerstwa musi zainstalowa� ten program i wspom�c Policj� w jej dzia�aniach operacyjnych.\n \nDecyzja.pdf \nProgramPolicja.rar"
	};

public:
	bool turned_on;
	bool show_content;
	bool good_mail;
	bool game_lost;
	sf::Sprite background;
	sf::Sprite screen;
	int which_mail;

	int points;
	sf::Text text_points;

	sf::Int32 randomize_time;

	std::vector<PhishingMail*>mails;

	gm::Information* content = nullptr;
	gm::TextButton *accept = nullptr;
	gm::TextButton *decline = nullptr;

	Phishing();
	~Phishing();

	void draw(sf::RenderWindow &win);
	void update(sf::RenderWindow &win);

	void pos_mails();
};