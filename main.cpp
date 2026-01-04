//Amelia Lipińska 203721 Acir 3a "gra a la kono"

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <limits> 

using namespace std;

constexpr unsigned WIERSZE = 4;
constexpr unsigned KOLUMNY = 4;

struct Gracz
{
    char imie1[50];
    char imie2[50];
    int piongracz = 4;
    int pionkomp = 4;
    int plansza[WIERSZE][KOLUMNY] = { {0} };
    int czas_gracza1, czas_gracza2;
};
void tworzenie_planszy(Gracz* gracz)
{
    for (int i = 0; i < WIERSZE; i++)
    {
        for (int j = 0; j < KOLUMNY; j++)
        {
            if (i == 0) {
                gracz->plansza[i][j] = 1;
            }
            else if (i == WIERSZE - 1)
            {
                gracz->plansza[i][j] = 2;
            }
            else
            {
                gracz->plansza[i][j] = 0;
            }
        }
    }
}
void wyswietl_plansze(const Gracz* gracz)
{
    cout << endl;
    cout << "   ";
    for (unsigned j = 0; j < KOLUMNY; j++) {
        cout << "  " << char('A' + j) << " ";
    }
    cout << endl;

    cout << "   ╔";
    for (unsigned j = 0; j < KOLUMNY - 1; j++) {
        cout << "═══╦";
    }
    cout << "═══╗" << endl;

    for (int i = WIERSZE - 1; i >= 0; i--) 
    {
        cout << " " << i + 1 << " ║";
        for (unsigned j = 0; j < KOLUMNY; j++) {
            if (gracz->plansza[i][j] == 0)
                cout << "   ║";
            else if (gracz->plansza[i][j] == 2)
                cout << " c ║";
            else if (gracz->plansza[i][j] == 1)
                cout << " b ║";
        }
        cout << endl;

        if (i > 0) {
            cout << "   ╠";
            for (unsigned j = 0; j < KOLUMNY - 1; j++) {
                cout << "═══╬";
            }
            cout << "═══╣" << endl;
        }
    }

    cout << "   ╚";
    for (unsigned j = 0; j < KOLUMNY - 1; j++) {
        cout << "═══╩";
    }
    cout << "═══╝" << endl;
}
bool sprawdz_bicie(Gracz* gracz, int i, int j)
{
    if (i == 3 && gracz->plansza[i - 1][j] == 1 && gracz->plansza[i - 2][j] == 0 && gracz->plansza[i - 3][j] == 2)
    {
        gracz->plansza[i][j] = 0;
        gracz->plansza[i - 3][j] = 1; 
        return true;
    }

    if (i == 0 && gracz->plansza[i + 1][j] == 1 && gracz->plansza[i + 2][j] == 0 && gracz->plansza[i + 3][j] == 2)
    {
        gracz->plansza[i][j] = 0;
        gracz->plansza[i + 3][j] = 1; 
        return true;
    }

    if (j == 3 && gracz->plansza[i][j - 1] == 1 && gracz->plansza[i][j - 2] == 0 && j - 3 >= 0 && gracz->plansza[i][j - 3] == 2)
    {
        gracz->plansza[i][j] = 0;
        gracz->plansza[i][j - 3] = 1; 
        return true;
    }

    if (j == 0 && gracz->plansza[i][j + 1] == 1 && gracz->plansza[i][j + 2] == 0 && j + 3 < KOLUMNY && gracz->plansza[i][j + 3] == 2)
    {
        gracz->plansza[i][j] = 0;
        gracz->plansza[i][j + 3] = 1; 
        return true;
    }

    return false;
}
//typ pionka(1/2)
int licz_pionki(const Gracz* gracz, int typ_pionka) {
    int licznik = 0;
    for (int i = 0; i < WIERSZE; i++) {
        for (int j = 0; j < KOLUMNY; j++) {
            if (gracz->plansza[i][j] == typ_pionka) {
                licznik++;
            }
        }
    }
    return licznik;
}
bool czy_mozliwy_ruch(const Gracz* gracz, int typ_pionka) {
    for (int i = 0; i < WIERSZE; i++) 
    {
        for (int j = 0; j < KOLUMNY; j++) 
        {
            if (gracz->plansza[i][j] == typ_pionka) 
            {
                if (i > 0 && gracz->plansza[i - 1][j] == 0) return true;
                if (i < WIERSZE - 1 && gracz->plansza[i + 1][j] == 0) return true;
                if (j > 0 && gracz->plansza[i][j - 1] == 0) return true;
                if (j < KOLUMNY - 1 && gracz->plansza[i][j + 1] == 0) return true;
            }
        }
    }
    return false;
}

void podanie_czasu(Gracz* gracz) {
    cout << "Podaj czas gry dla pojedynczego gracza (w sekundach): ";
    cin >> gracz->czas_gracza1;

    gracz->czas_gracza2 = gracz->czas_gracza1;
}

void ruch_komp(Gracz* gracz)
{
    bool wykonano_ruch = false;

    clock_t czas_poczatek2 = clock();

    for (int i = 0; i < WIERSZE; i++)
    {
        for (int j = 0; j < KOLUMNY; j++)
        {
            if (gracz->plansza[i][j] == 1)
            {
                if (sprawdz_bicie(gracz, i, j))
                {
                    cout << "Komputer zbil pionek!" << endl;
                    wykonano_ruch = true;
                    return;
                }
            }
        }
    }

    while (!wykonano_ruch)
    {
        int los_kolumna;
        int los_wiersz;

        do {
            los_kolumna = rand() % 4;
            los_wiersz = rand() % 4;
        } while (gracz->plansza[los_wiersz][los_kolumna] != 1);

        int ruch_pion;
        ruch_pion = rand() % 4;

        switch (ruch_pion)
        {
        case 0:
        {
            if (los_wiersz > 0 && gracz->plansza[los_wiersz - 1][los_kolumna] == 0)
            {
                gracz->plansza[los_wiersz][los_kolumna] = 0;
                gracz->plansza[los_wiersz - 1][los_kolumna] = 1;
                wykonano_ruch = true;
            }
            break;
        }
        case 1:
        {
            if (los_wiersz < WIERSZE - 1 && gracz->plansza[los_wiersz + 1][los_kolumna] == 0)
            {
                gracz->plansza[los_wiersz][los_kolumna] = 0;
                gracz->plansza[los_wiersz + 1][los_kolumna] = 1;
                wykonano_ruch = true;
            }
            break;
        }
        case 2:
        {
            if (los_kolumna > 0 && gracz->plansza[los_wiersz][los_kolumna - 1] == 0)
            {
                gracz->plansza[los_wiersz][los_kolumna] = 0;
                gracz->plansza[los_wiersz][los_kolumna - 1] = 1;
                wykonano_ruch = true;
            }
            break;
        }
        case 3:
        {
            if (los_kolumna < KOLUMNY - 1 && gracz->plansza[los_wiersz][los_kolumna + 1] == 0)
            {
                gracz->plansza[los_wiersz][los_kolumna] = 0;
                gracz->plansza[los_wiersz][los_kolumna + 1] = 1;
                wykonano_ruch = true;
            }
            break;
        }
        default:
        {
            // nie powinno się zdarzyć
            cout << "Brak ruchu komputera." << endl;
            return;
        }

        }

    }

    clock_t czas_koniec2 = clock();
    double spedzony_czas2 = double(czas_koniec2 - czas_poczatek2) / CLOCKS_PER_SEC;
    int zaokraglony_spedzony_czas2 = static_cast<int>(round(spedzony_czas2));

    gracz->czas_gracza2 -= zaokraglony_spedzony_czas2;
    cout << endl;
    cout << "Czas komputera spędzony na ruchu: " << zaokraglony_spedzony_czas2 << " sekund." << endl;
    cout << "Pozostaly czas gracza " << gracz->imie2 << ": " << gracz->czas_gracza2 << " sekund." << endl;
    cout << endl;
}

void ruch_gracza(Gracz* gracz)
{
    char kolumna_poczatek, kolumna_koniec;
    int wiersz_poczatek, wiersz_koniec;
    bool poprawny_ruch = false;

    clock_t czas_poczatek1 = clock();

    while (!poprawny_ruch)
    {

        if (gracz->czas_gracza1 <= 0)
        {
            cout << "Czas dla gracza " << gracz->imie1 << " dobiegł końca! Wygrywa " << gracz->imie2 << "." << endl;
            exit(0);
        }

        cout << "Wybierz pionek(np. 4C): ";
        cin >> wiersz_poczatek >> kolumna_poczatek;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Nieprawidlowy wybor! Podaj wspolrzedne ponownie." << endl;
            continue;
        }

        int kolumna_index_p = toupper(kolumna_poczatek) - 'A';
        int wiersz_index_p = wiersz_poczatek - 1;

        if (wiersz_index_p < 0 || wiersz_index_p >= WIERSZE || kolumna_index_p < 0 || kolumna_index_p >= KOLUMNY || gracz->plansza[wiersz_index_p][kolumna_index_p] != 2)
        {
            cout << "Nieprawidlowy wybor pionka!" << endl;
            continue;
        }

        cout << "Podaj wspolrzedne ruchu pionka(np. 1A): ";
        cin >> wiersz_koniec >> kolumna_koniec;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Nieprawidlowy wybor! Podaj wspolrzedne ponownie." << endl;
            continue;
        }

        int wiersz_index_k = wiersz_koniec - 1;
        int kolumna_index_k = -1;

        switch (toupper(kolumna_koniec))
        {
        case 'A': kolumna_index_k = 0; break;
        case 'B': kolumna_index_k = 1; break;
        case 'C': kolumna_index_k = 2; break;
        case 'D': kolumna_index_k = 3; break;
        default:
        {
            cout << "Nieprawidlowy wybor kolumny!" << endl;
            continue;
        }
        }

        if (abs(wiersz_index_k - wiersz_index_p) == 2 ||
            abs(kolumna_index_k - kolumna_index_p) == 2)
        {
            int wiersz_bity = (wiersz_index_p + wiersz_index_k) / 2;
            int kolumna_bity = (kolumna_index_p + kolumna_index_k) / 2;

            int wiersz_za = wiersz_index_k + (wiersz_index_k - wiersz_index_p) / 2;
            int kolumna_za = kolumna_index_k + (kolumna_index_k - kolumna_index_p) / 2;

            if (gracz->plansza[wiersz_bity][kolumna_bity] == 2 &&
                gracz->plansza[wiersz_index_k][kolumna_index_k] == 0 &&
                wiersz_za >= 0 && wiersz_za < WIERSZE && kolumna_za >= 0 && kolumna_za < KOLUMNY &&
                gracz->plansza[wiersz_za][kolumna_za] == 1)
            {
                gracz->plansza[wiersz_index_p][kolumna_index_p] = 0;
                gracz->plansza[wiersz_za][kolumna_za] = 2; 
                poprawny_ruch = true;
                cout << "Zbiłeś pionek przeciwnika b!" << endl;
            }
            else
            {
                cout << "Nieprawidlowe bicie!" << endl;
                continue;
            }
        }

        if (gracz->plansza[wiersz_index_k][kolumna_index_k] == 0 && (
            (abs(wiersz_index_k - wiersz_index_p) == 1 && kolumna_index_k == kolumna_index_p) ||
            (abs(kolumna_index_k - kolumna_index_p) == 1 && wiersz_index_k == wiersz_index_p) 
            ))
        {
            gracz->plansza[wiersz_index_p][kolumna_index_p] = 0;
            gracz->plansza[wiersz_index_k][kolumna_index_k] = 2;
            poprawny_ruch = true;
        }

        else {
            cout << "Nieprawidlowy ruch! Mozesz przesunac sie tylko o jedno pole na puste miejsce." << endl;
        }

        clock_t czas_koniec1 = clock();
        double spedzony_czas1 = double(czas_koniec1 - czas_poczatek1) / CLOCKS_PER_SEC; 
        int zaokraglony_spedzony_czas1 = static_cast<int>(round(spedzony_czas1)); 

        gracz->czas_gracza1 -= zaokraglony_spedzony_czas1;
        cout << endl;
        cout << "Czas gracza spędzony na ruchu: " <<zaokraglony_spedzony_czas1 << " sekund." << endl;
        cout << "Pozostaly czas gracza " << gracz->imie1 << ": " << gracz->czas_gracza1 << " sekund." << endl;
        cout << endl;
    }
}

int main()
{
    Gracz gracz;
    cout << "Podaj swoje imie: ";
    cin >> gracz.imie1;
    cout << "Nazwij komputer: ";
    cin >> gracz.imie2;
    cout << "Gracz o imieniu " << gracz.imie1 << " porusza sie pionkami C. Pionkami B porusza sie gracz " << gracz.imie2<<"." << endl;
    cout << endl;
    cout << "-INSTRUNKCJA-" << endl;
    cout << endl;
    cout << "By poruszac sie wybierz wspolrzedne pionka a nastepnie wspolrzedne ruchu."<<endl;
    cout << "By zbic pionek przeciwnika wybierz pionek i podaj wspolrzedne miejsca przeskoczenia pionka. Jezeli bicie jest mozliwe, pionek zbije przeciwnika i pojawi sie na jego miejscu."<<endl;
    cout << endl;

    podanie_czasu(&gracz);

    tworzenie_planszy(&gracz);
    srand(static_cast<unsigned int>(time(0)));

    while (true)
    {
        wyswietl_plansze(&gracz);

        int pionki_gracza = licz_pionki(&gracz, 2);
        int pionki_komputera = licz_pionki(&gracz, 1);
        bool gracz_moze_ruszyc = czy_mozliwy_ruch(&gracz, 2);
        bool komputer_moze_ruszyc = czy_mozliwy_ruch(&gracz, 1);


        cout << "Ruch gracza(twoj): " << endl;
        ruch_gracza(&gracz);

        if (pionki_gracza <= 1 || !gracz_moze_ruszyc ||gracz.czas_gracza1<=0)
        {
            cout << "Koniec gry! Wygral gracz " << gracz.imie2 << "!" << endl;
            break;
        }

        cout << "Ruch komputera: " << endl;
        ruch_komp(&gracz);

        if (pionki_komputera <= 1 || !komputer_moze_ruszyc || gracz.czas_gracza2<=0)
        {
            cout << "Koniec gry! Wygral gracz " << gracz.imie1 << "!" << endl;
            break;
        }
    }

    return 0;
}
