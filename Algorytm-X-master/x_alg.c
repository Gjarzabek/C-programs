/**
    *"Algorytm X"

    *Program zaliczeniowy.
    *Autor: Grzegorz Jarz¹bek <g.jarzabek@student.uw.edu.pl>
    *wersja: 1.4
    *data: 3 stycznia 2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define PUSTE_MIEJSCE '_'
#define WYPISZ_ZNAK '+'

/**przechowuje wczytane wiersze*/
struct w{
    char *wiersz;
    struct w * nastepny;
};
typedef struct w wezel;

/**przechowuje indeksy ktore mozna dopisac do aktualnego wiersza*/
struct l{
    int indeks;
    struct l * nastepny;
};
typedef struct l L_indeksow;

/**inicjalizuje wiersz podkresleniami*/

void podkresl( char str[] , int n )
{
    int i;
    for( i = 0 ; i < n ; ++i )
        str[i] = PUSTE_MIEJSCE;
    str[n] = '\0';
}
/** alokuje pamiec na nowy wezel listy wierszy i zwraca do niego wskaznik*/
wezel *nowa( char * str , wezel * next )
{
    wezel *p = malloc( sizeof( wezel ) );
    if( p == NULL )
    {
        exit(1);
    }
    (*p).wiersz = str;
    (*p).nastepny = next;
    return p;
}
/** alokuje pamiec na nowy wezel listy indeksow i zwraca wskaznik na niego*/
L_indeksow * nowa_L_indeksow( int x , L_indeksow * next)
{
    L_indeksow *p = malloc( sizeof( L_indeksow ) );
    p->indeks = x;
    p->nastepny = next;
    return p;
}
/** inicjalizuje liste indeksow*/
void wypelnij( L_indeksow * poczatek , int wiersze )
{
    if( wiersze > 1 )
    {
        poczatek->indeks = 1;
        int i;
        for( i = 2 ; i < wiersze ; ++i )
        {
            poczatek->nastepny = nowa_L_indeksow( i , NULL );
            poczatek = poczatek->nastepny;
        }
    }
}
/**zwraca wskaznik na k-ty wezel listy wierszy*/
wezel * dostep( int k , wezel * L)
{
    int i;
    for( i = 0 ; i < k ; ++i )
    {
        L = L->nastepny;
    }
    return L;
}
/**dodaje wiersz na koniec listy wierszy */
void dodaj( char str[] , wezel * lista )
{
    while( lista->nastepny != NULL )
        lista = lista->nastepny;
    lista->wiersz = malloc( (strlen(str)+1) * sizeof(char));
    strcpy(lista->wiersz,str);
    lista->nastepny = nowa(NULL,NULL);
}
/**
    *Wczytuje wiersze z wejscia
    *zwraca dlugosc wiersza
*/
int wejscie( wezel * lst , int *linie )
{
    char * wers = NULL;
    int j = 0;
    char C = getchar();
    if( C == EOF || C == '\n' )
    {
        exit(0);
    }
    while( C != '\n' )
    {
        ++j;
        wers = realloc( wers , (j + 1) * sizeof( char ) );
        wers[j-1] = C;
        C = getchar();
    }
    wers[j] = '\0';
    lst->wiersz = wers;
    /** wczytywanie kolejnych wierszy */
    wezel * ostatnia = lst;
    int koniec = 1;
    int wiersze = 1;
    char bufor[j+1];
    koniec = scanf("%s",bufor);
    while( koniec != EOF )
    {
        wezel * akt_nowa = nowa(NULL,NULL);
        akt_nowa->wiersz = malloc( (j+1) * sizeof( char ) );
        bufor[j] = '\0';
        strcpy(akt_nowa->wiersz,bufor);
        ostatnia->nastepny = akt_nowa;
        ostatnia = akt_nowa;
        wiersze++;
        koniec = scanf("%s",bufor);
    }
    *linie = wiersze;
    if( *linie == 1 )
        exit(0);
    return j;
}
/**sprawdza czy mozna wpisac jeden wiersz do drugiego, jesli tak to wpisuje i zwraca true */
bool sprawdz( char * wlasciwy , char * sprawdzany , int n )
{
    bool da_sie = true;
    int i;
    for( i = 0 ; i < n ; ++i )
    {
        if( wlasciwy[i] != PUSTE_MIEJSCE && sprawdzany[i] != PUSTE_MIEJSCE )
            da_sie = false;
    }
    if( da_sie )
    {
        for( i = 0 ; i < n ; ++i )
        {
            if( wlasciwy[i] == PUSTE_MIEJSCE && sprawdzany[i] != PUSTE_MIEJSCE )
            {
                wlasciwy[i] = sprawdzany[i];
            }
        }
    }
    return da_sie;
}
/** sprawdza czy wiersz jest pelny(nie ma zadnego pustego miejsca) */
bool pelny( char str[] , int n )
{
    int i;
    bool zapelniony = true;
    for( i = 0 ; i < n ; ++i )
    {
        if( str[i] == PUSTE_MIEJSCE )
            zapelniony = false;
    }
    return zapelniony;
}
/** usuwa wezel z listy */
void usun( L_indeksow ** usuwany , L_indeksow * lista )
{
    L_indeksow * Wsk = lista;
    while( Wsk->nastepny != *usuwany )
    {
        Wsk = Wsk->nastepny;
    }
    Wsk->nastepny = (*usuwany)->nastepny;
    (*usuwany)->nastepny = NULL;
    free(*usuwany);
    *usuwany =  Wsk;
}
/** sprawdza czy lista indeksow jest puta*/
bool pusta( L_indeksow * lst )
{
    return lst == NULL;
}
/** sprawdza czy podany idenks jest na liscie */
bool nie_wystepuje( L_indeksow * dostepne , int x )
{
    while( dostepne != NULL )
    {
        if( dostepne->indeks == x )
            return false;
        dostepne = dostepne->nastepny;
    }
    return true;
}
/** dodaje indeksy z tablicy do listy zachowujac rosnaca kolejnosc*/
void dodaj_indeks( int * id, int n , L_indeksow ** dostepne )
{
    L_indeksow * wsk = *dostepne;
    if( wsk == NULL )
    {
        int i = 0;
        wsk = nowa_L_indeksow( id[i] , NULL );
        for( i = 1 ; i < n ; ++i )
        {
            wsk->nastepny = nowa_L_indeksow( id[i] , NULL );
            wsk = wsk->nastepny;
        }
    }
    else
    {
        int i;
        for( i = 0; i < n ; ++i )
        {
            if( nie_wystepuje( *dostepne , id[i] ) )
            {
                L_indeksow * p = wsk;
                if( p->indeks <= id[i] )
                {
                    while( p->nastepny != NULL && (p->nastepny)->indeks < id[i] )
                        p = p->nastepny;
                    L_indeksow * W = nowa_L_indeksow(id[i],p->nastepny);
                    p->nastepny = W;
                    wsk = W;
                }
                else if( wsk == *dostepne )
                {
                    p = nowa_L_indeksow(id[i],*dostepne);
                    *dostepne = p;
                }
            }
        }
    }
}
/** sprawdza czy podana liczba wystepuje w tablicy*/
bool bez_powtorki( int * tab , int n , int x )
{
    int i;
    for( i = 0 ; i < n ; ++i )
    {
        if( tab[i] == x )
            return false;
    }
    return true;
}
/** funkcja rekurencyjna , znajdujaca rozwiazania */
void rozwiazania( char str[] , wezel * wsk , int poziom , L_indeksow * dostepne , int len , wezel * poprawne)
{
    if( pelny( str , len ) )
    {
        dodaj( str , poprawne );
    }
    else if( poziom < len )
    {
        int * mozliwe_wybory = NULL;
        int ile = 0;
        L_indeksow * T = dostepne;
        while( T != NULL && str[poziom] == PUSTE_MIEJSCE )
        {
            if( dostep(T->indeks,wsk)->wiersz[poziom] != PUSTE_MIEJSCE && bez_powtorki( mozliwe_wybory , ile , T->indeks ) )
            {
                mozliwe_wybory = realloc( mozliwe_wybory , (ile + 1) * sizeof( int ) );
                mozliwe_wybory[ile] = T->indeks;
                ++ile;
                if( T == dostepne )
                {
                    dostepne = dostepne->nastepny;
                }
                else
                {
                    usun( &T , dostepne );
                }
                T = T->nastepny;
            }
            else
                T = T->nastepny;
        }
        if( ile == 0 && !pusta( dostepne ) && str[poziom] != PUSTE_MIEJSCE )
        {
            char bufor[len];
            strcpy(bufor,str);
            rozwiazania( str , wsk , poziom + 1 , dostepne , len , poprawne );
            strcpy(str,bufor);
        }
        else if( ile > 0 )
        {
            int i;
            for( i = 0; i < ile ; ++i)
            {
                char bufor[len];
                strcpy(bufor,str);
                if( sprawdz( str , dostep( mozliwe_wybory[i] , wsk )->wiersz , len ) )
                {
                    rozwiazania(str,wsk,poziom+1,dostepne,len,poprawne);
                }
                strcpy(str,bufor);
            }
        }
        dodaj_indeks( mozliwe_wybory , ile , &dostepne );
        free(mozliwe_wybory);
    }
}
/** wypisuje rozwiazania z filtrem */
void wypisz_z_filtrem( wezel * poprawne , wezel * glowa )
{
    while( poprawne->wiersz != NULL )
    {
        unsigned int i;
        for( i = 0 ; i < strlen(glowa->wiersz) ; i++ )
        {
            if( glowa->wiersz[i] == WYPISZ_ZNAK )
            {
                putchar(poprawne->wiersz[i]);
            }
        }
        putchar('\n');
        poprawne = poprawne->nastepny;
    }
}
/** urchamia program */
int main()
{
    wezel *glowa = nowa( NULL , NULL );
    wezel *poprawne = nowa( NULL , NULL );
    int ile_wierszy = -1;
    int dlugosc_wiersza = wejscie( glowa , &ile_wierszy );
    L_indeksow * mozliwosci = nowa_L_indeksow(-1,NULL);
    wypelnij(mozliwosci,ile_wierszy);
    char napis[dlugosc_wiersza];
    podkresl( napis , dlugosc_wiersza );
    rozwiazania( napis , glowa , 0 , mozliwosci , dlugosc_wiersza , poprawne );
    wypisz_z_filtrem( poprawne , glowa );
    free(glowa);
    free(poprawne);
    free(mozliwosci);
    return 0;
}
