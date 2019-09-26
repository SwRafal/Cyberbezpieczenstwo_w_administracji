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
		L"Od 14 wrzeœnia inaczej zalogujesz siê na konto!",
		L"Newsletter Urzêdniczka",
		L"Modna urzêdniczka -50% na garsonki",
		L"Katalog monet na rok 2020",
		L"Loteria pracownicza",
		L"promocja na sushi",
		L"zbiórka karmy dla kotów",
		L"Zaproszenie na konferencjê",
		L"[przekazane przez: aniela_dab@msw.gov.pl] Zyskaj PEWNOŒÆ SIEBIE na warsztatach coachingowych",
		L"Zmiana numeru konta.",
		L"Faktura VAT 09.2019",
		L"Postaw na formê! Karnet fitness ju¿ za 39 z³!",
		L"Cotygodniowy katalog kursów jest ju¿ dostêpny",
		L"badanie zadowolenia pracowników"
	};
	const sf::String g_contents[14] = {
		L"Dzieñ dobry,\n14 wrzeœnia czeka Ciê du¿o zmian, które wynikaj¹ z dyrektywy PSD2.Przeczytaj o nich na naszej stronie.Mo¿e jakiœ szczegó³ oka¿e siê dla Ciebie wa¿ny.\n \nZ pozdrowieniami\nzespó³ plnBanku",
		L"W najnowszym wydaniu Urzêdniczka:\n- \"Korzystanie z klimatyzacji w urzêdzie – przywilej czy obowi¹zek?\"\n- \"Urlop czy L4? Jak dokonaæ m¹drego wyboru.\"\n- \"Phishing, czyli ³owi¹ nas jak karpie na Wigiliê\".\n \nSprawdŸ ju¿ dziœ!",
		L"Rozpoczynamy nowy sezon! Nic tak wspaniale siê nie prezentuje jak wakacyjna opalenizna w garsonce z nowej kolekcji jesieñ 2019. SprawdŸ nasz¹ gazetkê i dowiedz siê wiêcej. OdwiedŸ urzedniczek.pl / moda i daj siê zaskoczyæ nowym trendom!",
		L"Szanowni Pañstwo, z przyjemnoœci¹ przesy³amy Pañstwu Katalog monet, które planujemy wyemitowaæ w roku 2020. Z dum¹ informujemy, i¿ nowy rok rozpoczniemy od emisji monety „X lat Ministerstwa ds. Wszelakich”.\n \nZ wyrazami szacunku starszy specjalista, Eugeniusz Grosik.\nZa³¹cznik: Katalog Monet 2020.pdf",
		L"Z okazji dziesiêciolecia istnienia Ministerstwo ds. Wszelakich organizuje koncert jubileuszowy na Stadionie Narodowym. Zagraj¹ na nim najwiêksze œwiatowe s³awy. Do wygrania 100 biletów na to wydarzenie! Zg³oszenia nale¿y wys³aæ do 31.10.2019 r. Wzór zg³oszenia w za³¹czeniu.\n \nZ wyrazami szacunku,\nKierownik dzia³u marketingu MSW,\nHelena Kopka\nZa³¹cznik : wzór zg³oszenia konkursowego.doc",
		L"Szanowni Pracownicy, informuje, ¿e ulotki promocyjne kolportowane w ostatnich dniach na terenie ministerstwa nie pochodz¹ z mojej emisji. Ze wzglêdu jednak na du¿e zainteresowanie nowo wprowadzonymi do Menu smakami Sushi, przesy³am tajne has³o na rabat -15% dla pierwszych 15 osób: „PYSZNE SUSHI PANI WIESI”.\n \nPozdrawiam,\nWies³awa Nó¿",
		L"Czeœæ wszystkim. Jestem now¹ pracownic¹ tego dzia³u. Idzie zima, wiec pomyœla³am, ¿e warto by³oby zebraæ karmê dla kotów mieszkaj¹cych przy Ministerstwie.\nW naszym dziale jest nasz 100 osób, gdyby ka¿dy z nas przyniós³ po worku karmy, kotom starczy³oby na ca³¹ zimê. Karmê bêdê zbieraæ po swojej zmianie. £apcie mój grafik.\nZa³¹cznik: grafik.mariolka.xcl",
		L"Szanowni Pañstwo,\nw imieniu w³adz Wy¿szej Szko³y Administracji mam zaszczyt zaprosiæ Pañstwa na konferencjê \"Cyberbezpieczeñstwo Administracji. Œwiadomy urzêdnik – bezpieczny urz¹d.\" Konferencja odbêdzie siê w dniach 24 - 25.10.2019 r.Szczegó³y w za³¹czonym programie.Zapisy do 30.09.2019 r.pod adresem cyberbezpieczeñœtwo.wsa.edu.pl\nZa³¹cznik: Szczegó³owy Program Konferencji.",
		L"Witaj!\nCzy masz wra¿enie, ¿e Twój potencja³ jest marnowany ? Czujesz, ¿e nie osi¹gasz tego, co powinieneœ ? Nie dostajesz tego, Ci siê nale¿y ?\nTo Porsche czeka, abyœ do niego wsiad³!Opuœæ swoj¹ strefê komfortu.\nZapraszam na warsztaty, gdzie odkryjesz siebie na nowo.\nWiecej na : mdrzesiak.pl\n \nPozdrawiam,\nMateusz Drzesiak – coach, filantrop",
		L"Szanowni Pracownicy,\nNumer konta Ministerstwa ulega zmianie w dniu 14.10.2019 r.z tego wzglêdu proszê siê stawiæ w dniach 7 - 11.10.2019 r.w sekretariacie dyrekcji waszego departamentu w celu podpisania aneksu do pañstwa umowy o pracê.\n \nZ powa¿aniem,\nHelena Orlicka,\nkierownik dzia³u ksiêgowoœci MSW",
		L"Szanowni Pañstwo,\nw za³¹czeniu przesy³am fakturê za nasze us³ugi za miesi¹c wrzesieñ br.\nWynagrodzenie proszê wp³aciæ na sta³y numer konta do dnia 10.10.2019 r.\n \nZ powa¿aniem,\nKleofas B³ysk,\nDyrektor B³yskpol\n \nZa³¹cznik : faktura blyskpol.pdf",
		L"Zrób formê do Sylwestra!\nCzy Twój pracodawca wie o Pakiecie sportowym Multisportek ? Jedna karta a tak wiele mo¿liwoœci!Nie przep³acaj, do³¹cz do naszego programu ju¿ dziœ!\n \nWiêcej informacji : multisportek.com\n \nPozdrawiamy,\nzespó³ Multisportek\n \n---------------- - Moc, energia, multisportek!---------------- -",
		L"Drodzy Pracownicy,\nna naszej platformie edukacyjnej pojawi³y siê nowe kursy dostêpne od 1 paŸdziernika.Prosimy o zapoznanie siê z ofert¹.Przypominamy o obowi¹zku realizacji dwóch wybranych kursów on - line do koñca tego roku.\n \nW razie dodatkowych pytañ lub problemów technicznych zapraszamy do kontaktu: aneta_kaszle@msw.gov.pl\n \nPozdrawiam,\nW imieniu Departamentu Edukacji,\nAneta Kaszle",
		L"Dzieñ dobry,\n \nPrzypominamy, i¿ na zlecenie Ministerstwa ds.Wszelakich realizujemy badanie dotycz¹ce zadowolenia pracowników.Je¿eli ju¿ uzupe³ni³/a Pan/i swój kwestionariusz - prosimy o zignorowanie tej wiadomoœci.Jeœli jednak jeszcze nie wype³ni³/a Pan/i ankiety, to zwracamy siê z serdeczn¹ proœb¹ o mo¿liwe jak najszybsze jej wype³nienie poprzez formularze dostêpne po zalogowaniu do systemu Ministerstwa.\nLogin: email @msw.gov.pl\nKod dostêpowy : g8DBTEfcJmxd\n \nW razie dodatkowych pytañ lub problemów technicznych zapraszamy do kontaktu.\n \nZespó³ ds.Statystyki MSW"
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
		"biuro.wspó³pracy@msvvia.gow.pl ",
		"k.laskowski@mssw.gow.pl",
		"janusz.pracz@co2.pl",
		"kadry@ministerstwo.pl",
		"blysexpol@sprzatanie.pl",
		"John.Cnr@juhuu.bg",
		"polska.policja@pp.pl"
	};
	const sf::String b_titles[20] =
	{
		L"SprawdŸ status swojej p³atnoœci (C 1CBA XX15678931XX (PL))",
		L"Chroñ swoje konto",
		L"Nowa polityka",
		L"Ammegro – potwierdzenie wygranej aukcji",
		L"Incydent bezpieczeñstwa – reset has³a",
		L"Logowanie – zespó³ Facebook",
		L"Twoje sekretne ¿ycie",
		L"Twoje konto zosta³o zhackowane",
		L"Mam dla ciebie z³e wieœci.",
		L"Inkwizycja s¹dowa",
		L"Rozpoczêcie egzekucji",
		L"fajny gust",
		L"Awaria twojej drukarki",
		L"Proœba o listê pracowników uczestnicz¹cych w warsztatach",
		L"Sprawdzenie Dyrektora Stefañskiego ",
		L"Wniosek",
		L"Dane do premii",
		L"Zmiana numeru konta i Faktura za miesi¹c Wrzesieñ",
		L"Nowy numer konta",
		L"Wezwanie do pomocy w operacji"
	};
	const sf::String b_contents[20] = 
	{
		L"Witaj,\n \nzarejestrowaliœmy zlecenie p³atnoœci dla VXHXNE Sp.z o.o.\nMo¿esz w dowolnym momencie sprawdziæ status transakcji loguj¹c siê do serwisu transakcyjnego.\n \n[LOGOWANIE]\n \nW przypadku pytañ o tê transakcjê, po zalogowaniu skontaktuj siê z konsultantem na czacie.\n \nZespó³ DotekPay S.A",
		L"Witaj,\n \nmin¹³ ju¿ ponad rok od czasu, gdy po raz ostatni aktualizowa³eœ swoje informacje osobiste.Regularna aktualizacja pomaga nam lepiej chroniæ twoje konto.Musisz tylko zalogowaæ siê do aBay, poni¿szym linkiem, aby sprawdziæ swoje informacje.Jeœli niedawno zaktualizowa³eœ swoje informacje osobiste zignoruj to przypomnienie.\n \n[ZALOGUJ DO ABAY]\n \nPozdrawiamy,\nzespó³ aBay ds.kont",
		L"Witaj,\n \nw zwi¹zku z dyrektyw¹ PSD2 zmieniamy politykê p³atnoœci.Niezaakceptowanie nowych warunków spowoduje zablokowanie konta w serwisie allekexpress.Poni¿szy link poprowadzi Pañstwa krok po kroku przez procedurê weryfikacji Pañstwa konta.\n \n[LINK]\n \nPozdrawiamy,\nzespó³ Allekexpress",
		L"Witamy,\n \nprzesy³amy potwierdzenie wygranej aukcji i numer konta, na który nale¿y dokonaæ przelewu w ci¹gu 48h.\n \nPOTWIERDZENIE.EXE\n \nPozdrawiamy,\nZespó³ Ammegro",
		L"Witamy,\n \nw zwi¹zku z incydentem bezpieczeñstwa Twoje has³o zosta³o zresetowane.Zaloguj siê do systemu  i zmieñ swoje dotychczasowe has³o.\n \n[ZALOGUJ]\n \nZespó³ hosting.com",
		L"Witaj,\nWygl¹da na to, ¿e masz problem z zalogowaniem siê do Facebooka.Kliknij poni¿szy przycisk, a my Ciê zalogujemy.\n \n[Zaloguj siê jednym klikniêciem]",
		L"Czeœæ, drogi u¿ytkowniku Ministerstwo ds. Wszelakich!\nW tym momencie Twoje konto e - mail zosta³o zhakowane, a ja pobra³em wszystkie poufne informacje z twojego systemu.Jeœli chcesz usun¹æ wszystkie zebrane dane, wyœlij mi 300$ w BTC(kryptowaluta).To jest mój portfel Bitcoin : 1EBMu3FdAXiEK52JkStPd99f5a7RNuJB7A\nMasz 48 godzin po przeczytaniu tego listu.Od teraz b¹dŸ ostro¿ny!",
		L"Wgra³em wirusa na stronê http//www.rndw.gov.pl, któr¹ odwiedza³eœ, a nastêpnie zainstalowa³eœ go w swoim systemie operacyjnym. Mój trojan zosta³ pobrany na twoje urz¹dzenie.\nW tej chwili, oprogramowanie zebra³o wszystkie twoje dane kontaktowe z sieci spo³ecznoœciowych i adresów e - mail.,Jeœli chcesz usun¹æ wszystkie zebrane dane, wyœlij mi 50$ w BTC(kryptowaluta).To jest mój portfel Bitcoin : 1EBGX3H74kStPd99f5a7RNuJB7A\n \nOdwiedŸ tylko bezpieczne strony!PA!",
		L"20/08/2019 – w tym dniu w³ama³em siê do twojego systemu operacyjnego i uzyska³em pe³ny dostêp do twojego konta !  Chcia³em zablokowaæ Twoje urz¹dzenie i poprosiæ o niewielk¹ kwotê, aby odblokowaæ. Ale patrzy³em na strony, które regularnie odwiedzasz i chcê powiedzieæ – jesteœ wielkim, wielkim zboczeñcem. Masz nieokie³znan¹ fantazjê !!! Za pomoc¹ kamery twojego urz¹dzenia widzialem wszystko. Nie chcia³byœ pokazaæ tych zdjêæ swoim krewnym, przyjacio³om lub wspó³pracownikom. 640 $ to bardzo ma³a kwota za moje milczenie. Akc\n \nP.S.Gwarantujê ci, ¿e nie bêdê ci przeszkadza³ po wyp³acie, poniewa¿ nie jesteœ\nmoj¹ jedyn¹ ofiar¹.\nTo jest kodeks hakerski.",
		L"Inkwizycja s¹dowa informuje o wszczêciu postêpowania za brak op³aty zad³u¿enia 2,25 PLN. Aby zapobiec rozprawie prosimy o sp³atê https://inkwizytornia.cf/7301/ \nTa wiadomoœæ zosta³a wygenerowana automatycznie.Proszê na ni¹ nie odpowiadaæ",
		L"Informujemy o rozpoczeciu egzekucji Sygn. Akt 8710/19 z tytulu zaleglosci skarbowej 11.80 PLN. Uruchomilismy splate przez PayU https://wezwanie24.eu/us. \n \nTa wiadomoœæ zosta³a wygenerowana automatycznie.Proszê na ni¹ nie odpowiadaæ.",
		L"Hej, urzêdniku zhakowa³em twoje s³uzbowy komputer. To co na tym znalaz³em….\nTwoje fantazja erotyczna sa bardzo ciekawy.Myslimy, ze prasa chce siê  tego wiedziec.\nPamietasz jak nie mogles polaczenie z Internet ? To wtedy wgralismy Trojan.Nagralismy twoje chwile relaksu, twoja kamerka…\nW mailu jest gif, wiemy ze otworzyles go wlasnie teraz.Gra rozpoczyna sie TERAZ, masz 24 godziny aby wplacic 1000 zl w Bitcoin na mój portfel X3G6HW2XXG!A@X%S^H ^ 11G1.Jesli nie, twoje figlarne filmy wysle najpierw twojemu ma³¿onkowi i przyjaciolom po kolejnych 12 godzinach ministrowi i prasie.Nie badz zly, kazdy jakos na siebie zarabia…\nJa przynajmniej dalem ci dobra lekcje.Jeszcze mi za to podzienkujesz",
		L"Witam,\n \ntu serwisant twojej drukarki s³u¿bowej.\nSystem pokazuje nam, ¿e pamiêæ twojej drukarki jest pe³na i nied³ugo przestanie dzia³aæ poprawnie.\nSzef zabroni³ usuwaæ plików z pamiêci drukarki – sam wiesz, ¿e chce mieæ kopie zapasow¹.\nUzgodniliœmy z ministrem, ze zawartoœæ pamiêci drukarki przechowamy u nas.\nW mailu masz instrukcjê jak tego dokonaæ. (kliknij ok.aby wys³aæ)\n \nPozdrawiam,\nArkadiusz £owiecki – autoryzowany serwis drukarek",
		L"Witam,\n \nzwracam siê z uprzejm¹ proœb¹ o przekazanie mi listy pracowników uczestnicz¹cych w warsztatach organizowanych w ramach wspó³pracy miêdzyresortowej w dniach 05.10..2019 - 07.10.2019.\nZ informacji jakie uzyskaliœmy od Sekretarza Ministra 5.10 uczestniczyæ ma ca³e piêtro 1 – pokoje 101 - 115. 6.10 piêtro 2. Pokoje 201 - 215. 7.10 piêtro 3 pokoje 301 - 315.\nBardzo proszê o przes³anie 3 list, na ka¿dy dzieñ.\nZ wyrazami szacunku\nHonorata Nowak – szef sekretariatu MSWIA",
		L"Szanowny pracowniku Ministerstwa ds. Wszelakich,\n \nAgencja Bezpieczeñstwa Wewnêtrznego przedstawi³a mi wczoraj raport jasno wskazuj¹cy na przestêpcz¹ dzia³alnoœæ dyrektora pañstwa dzia³u.Zgodnie z wytycznymi ABW mamy przeprowadziæ obserwacjê ów Dyrektora Stefañskiego.Z tego wzglêdu wszystkie raporty dotycz¹ce mieszkañców stolicy(bez anonimizacji) proszê przekazywaæ równie¿ mi.Musimy sprawdziæ czy Stefañski nie zmienia ich treœci przed wys³aniem do mnie.\nTo nie s¹ æwiczenia.Sytuacja jest powa¿na.Zagro¿one s¹ dane mieszkañców stolicy.\n \nZ powa¿aniem,\nMinister ds.Wszelakich\nKazimierz Laskowski",
		L"Witam,\n \nW nawi¹zaniu do rozmowy telefonicznej z Pani¹ Krystyn¹, w imieniu mojego taty Jaros³awa Pracza, w za³¹czeniu przesy³am wniosek o pozwolenia na budowê krawê¿nika wokó³ trawnika okalaj¹cego huœtawkê pod klatk¹ nr. 14 na ulicy brunatnej 88.\n \nZ wyrazami szacunku,\nJanusz Pracz\n \nZa³acznik : Wniosek.rar",
		L"Szanowny Pracowniku,\n \nNa mocy decyzji ministra nr 351 / MSW / 19 uzyska³ / a Pan / Pani premiê za wzorowe wykonywanie obowi¹zków pracowniczych.Proszê o przes³anie swoich danych osobowych(imiê, nazwisko, PESEL) oraz numer konta bankowego.\n \nZ wyrazami szacunku,\nDzia³ Kadr.\nW za³¹czeniu treœæ decyzji.\n \nZa³¹cznik Premia.bat",
		L"Szanowni Pañstwo, z przyczyn od nas niezale¿nych musieliœmy zmieniæ bank prowadz¹cy nasze konto bankowe. Nowy numer konta to”: 90 3211 9167 3622 0000 3569 3563.\n \nProsimy o wprowadzenie tego numeru do waszego systemu.\nW za³¹czeniu przesy³amy te¿ fakturê za nasze us³ugi we Wrzeœniu.Kwotê naszego wynagrodzenia proszê przelaæ od razu na nowy numer konta.\n \nZ wyrazami szacunku,\nZespó³ B³ysexPol – „Wyczyœcimy ciê na b³ysk”.\n \nZa³acznik: FV 256 / 2019 / 09.PDF",
		L"Hej,\ntu wujek Anieli.Ona nie ma dostep do jej e - mail.\nMam nadzieja, ze znalaz³em dobry email do ksiêgowej.Jesli nie, przekaz ten e - mail do ksiêgowa.\nAniela prosi³am o przekazanie – „Oto moj nowy numer konta : 19 9252 2521 0000 7925 8250 9876 - Prosze przekaz na niego moja wynagrodzenia”.\n \nWyrazy szacunku,\nJohn i Aniela.",
		L"Szanowni Pañstwo!\n \nDzia³aj¹c w imieniu Komendanta G³ównego Policji, wzywam Pana / Pani¹ do wsparcia dzia³añ operacyjnych Policji.Otrzymaliœmy wiele zg³oszeñ o próbach wy³udzania poufnych danych przy pomocy maili phishingowych.\nMinisterstwo poinformowa³o nas, ¿e takie ataki kierowano równie¿ przeciw pañstwu.\nTechnicy Policyjny opracowali program umo¿liwiaj¹cy wyœledzenie miejsc sk¹d nadano takie maile – przekazujemy go w za³¹czniku.\nZgodnie z decyzj¹ Ministra(w za³¹czeniu) ka¿dy pracownik Ministerstwa musi zainstalowaæ ten program i wspomóc Policjê w jej dzia³aniach operacyjnych.\n \nDecyzja.pdf \nProgramPolicja.rar"
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