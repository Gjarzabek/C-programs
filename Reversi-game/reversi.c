/**
    *"Reversi"

    *Program zaliczeniowy.
    *Autor: Grzegorz Jarzšbek <g.jarzabek@student.uw.edu.pl>
    *wersja: 1.4
    *data: 25 listopada 2017
*/
#include <stdio.h>
#include <stdbool.h>

/** liczba wierszy i kolumn planszy */
#define N 8
/** stale do zamiany int - char , char - int */
#define znak_a 97
#define znak_h 104
#define znak_0 48
/**symbole reprezentujace piony biale i czarne na planszy*/
#define gracz_C 'C'
#define gracz_B 'B'
/** znak reprezentujacy pole bez piona na planszy */
#define puste '-'
/** znak zrezygnowania z ruchu */
#define pas '='
/** wczytanie tego znaku bedzie oznaczalo koniec wejscia*/
#define nast_wiersz '\n'
/** poczatkowe ilosci pionow */
#define Na_start 2

/**
    *Funkcja zwraca liczbe zetonow ktore mialyby sie odwrocic
    po potencjalnych wykonaniu ruchu na pole o zadanych wspolrzednych.
    *Funkcja wskazuje ktore zetony mialyby sie odwrocic,
    zmieniajac wartosci w tablicy bool na true.
    *Zmienna @gracz informuje ktorych zetonow szukac.
*/
int Szukaj( char tab[][N], int x, int y,bool tab_bol[][N], char gracz )
{
    char op;
    int zeton = 0;
    if( gracz == gracz_C )
        op = gracz_B;
    else
        op = gracz_C;
    if( tab[y][x] == puste )
    {
        bool east = (x + 2) < N;
        bool west = x > 1;
        if( east && tab[y][x+1] == op )
        {
            int p = x + 1;
            while( (tab[y][p] == op) && (p < N - 1) )
            {
                ++p;
            }
            if( tab[y][p] == gracz )
            {
                zeton += p - x - 1 ;
                --p;
                while ( x <=  p )
                {
                    tab_bol[y][p] = true;
                    --p;
                }
            }
        }
        if( west && tab[y][x-1] == op )
        {
            int p2 = x - 1;
            while( tab[y][p2] == op && p2 > 0 )
            {
                --p2;
            }
            if( tab[y][p2] == gracz )
            {
                zeton += x - p2 - 1;
                ++p2;
                while( p2 <= x )
                {
                    tab_bol[y][p2] = true;
                    ++p2;
                }
            }
        }
        bool north = y > 1;
        bool south = y < N - 1;
        if( north && tab[y-1][x] == op )
        {
            int q = y - 1;
            while( tab[q][x] == op && q > 0 )
            {
                --q;
            }
            if( tab[q][x] == gracz )
            {
                zeton += y - q - 1;
                ++q;
                while( q <= y )
                {
                    tab_bol[q][x] = true;
                    ++q;
                }
            }
        }
        if( south && tab[y+1][x] == op )
        {
            int q2 = y + 1;
            while( tab[q2][x] == op && q2 < N - 1 )
            {
                ++q2;
            }
            if( tab[q2][x] == gracz )
            {
                zeton += q2 - y - 1;
                --q2;
                while( q2 >= y )
                {
                    tab_bol[q2][x] = true;
                    --q2;
                }
            }
        }
        if( north && east && tab[y-1][x+1] == op )
        {
            int p = x + 1;
            int q = y - 1;
            while( tab[q][p] == op && q > 0 && N - 1 > p )
            {
                --q;
                ++p;
            }
            if( tab[q][p] == gracz )
            {
                zeton += y - q - 1;
                --p;
                ++q;
                while( p >= x && q <= y )
                {
                    tab_bol[q][p] = true;
                    --p;
                    ++q;
                }
            }
        }
        if( north && west && tab[y-1][x-1] == op )
        {
            int p = x - 1;
            int q = y - 1;
            while( tab[q][p] == op && q > 0 && p > 0 )
            {
                --q;
                --p;
            }
            if( tab[q][p] == gracz )
            {
                zeton += y - q - 1;
                ++p;
                ++q;
                while( p <= x && q <= y )
                {
                    tab_bol[q][p] = true;
                    ++p;
                    ++q;
                }
            }
        }
        if( south && east && tab[y+1][x+1] == op )
        {
            int p = x + 1;
            int q = y + 1;
            while( tab[q][p] == op && N - 1 > q && N - 1 > p )
            {
                ++q;
                ++p;
            }
            if( tab[q][p] == gracz )
            {
                zeton += q - y - 1;
                --p;
                --q;
                while( p >= x && q >= y )
                {
                    tab_bol[q][p] = true;
                    --p;
                    --q;
                }
            }
        }
        if( south && west && tab[y+1][x-1] == op )
        {
            int p = x - 1;
            int q = y + 1;
            while( tab[q][p] == op && N - 1 > q && p > 0 )
            {
                ++q;
                --p;
            }
            if( tab[q][p] == gracz )
            {
                zeton += q - y - 1;
                ++p;
                --q;
                while( p <= x && q >= y )
                {
                    tab_bol[q][p] = true;
                    ++p;
                    --q;
                }
            }
        }
    }
    return zeton;
}
/**
    aktualizuje,odwraca zetony na planszy na kolor o przekazanym argumencie - "gracz",
    jesli napotka w tablicy bool true odwraca zeton o odpowiednich wspolrzednych na planszy
*/
void zamien_zet( char plansza[][N], bool tab[][N], char gracz )
{
    int i ;
    for( i = 0; i < N ; ++ i)
    {
        int j;
        for( j = 0; j < N ; ++ j )
        {
            if( tab[i][j] )
                plansza[i][j] = gracz;
        }
    }
}
/**
    Rysuje plansze z aktualnym stanem na ekranie.
*/
void diagram(char a[][N])
{
    int w;
    int s;
    for( w = 0 ; w < N ; ++w )
    {
        for( s = 0 ; s <  N  ; ++s )
        {
            printf( "%c", a[w][s] );
        }
        printf("%d\n", w + 1);
    }
    for( s = 0 ; s < N  ; ++s)
    {
        printf("%c", znak_a + s);
    }
    putchar(nast_wiersz);
}
/**
    Nadaje poczatkowy stan planszy.
*/
void wypelnij(char tab[][N])
{
    int i;
    for( i = 0 ; i < N  ; ++i )
    {
        int j;
        for( j = 0 ; j < N  ; ++ j)
        {
            tab[i][j] = puste;
        }
    }
    int poz = N/2;
    tab[poz-1][poz-1] = gracz_B;
    tab[poz][poz-1] = gracz_C;
    tab[poz-1][poz] = gracz_C;
    tab[poz][poz] = gracz_B;
}
/**
    Ustawia wszystkie wartosci tablicy bool na false.
*/
void zeruj( bool tab[][N] )
{
    int i ;
    for( i = 0 ; i < N ; ++ i )
    {
        int j;
        for( j = 0 ; j < N ; ++ j )
        {
            tab[i][j] = false;
        }
    }
}
/**
    wykonuje ruch jako gracz bialy , szuka ruchu(pozycji) odwracajacego najwiecej pionow,
    korzysta z pomocniczej tablicy bool dla aktualnie sprawdzanej pozycji
    jesli nie istnieje ruch ktory jest legalny wypisuje znak zrezygnowania z ruchu
    jesli istnieje, wykonuje ten ruch,aktualizuje plansze i wypisuje pozycje ruchu
    *Aktualizuje i pisze roznice miedzy pionami czarnymi i bialymi.
*/
void ruch_komp( char plansz[][N], bool tab[][N], int * B, int * C )
{
    int ile = 0;
    int i, x, y ;
    for( i = 0; i < N ; ++i )
    {
        int j;
        for( j = 0; j < N ; ++j )
        {
            bool temp[N][N];
            zeruj(temp);
            int ch = Szukaj(plansz,j,i,temp,gracz_B);
            if( ch > ile )
            {
                ile = ch;
                x = j;
                y = i;
                zeruj(tab);
                int k;
                for( k = 0; k < N ; ++k )
                {
                    int l;
                    for( l = 0; l < N ; ++l )
                    {
                        if(temp[k][l])
                            tab[k][l] = temp[k][l];
                    }
                }
            }
        }
    }
    if( ile > 0 )
    {
        x = x + 2*znak_0 + 1;
        y++;
        *B += ile + 1;
        *C -= ile;
        int o = *C - *B;
        printf("%c%d %d\n",x , y , o );
        zamien_zet(plansz,tab,gracz_B);
        zeruj(tab);
    }
    else
    {
        int o = *C - *B;
        printf("= %d\n" , o);
    }
}
/**
    *Sprawdza czy ruch na podane wspolrzedne jest legalny
    jesli jest wykonuje go i aktualizuje stan planszy.
    *Aktualizuje liczbe bialych i czarnych pionow.
*/
bool gracz( char plansza[][N] , bool tab[][N] , int *B , int *C , int *a , int *b )
{
    bool legal;
    int x = *a - 2*znak_0 - 1;
    int g = Szukaj(plansza,x,*b,tab,gracz_C);
    legal = g > 0;
    if( legal )
    {
        zamien_zet(plansza,tab,gracz_C);
        zeruj(tab);
        *B -= g;
        *C += g + 1;
        printf( "%c%d " ,*a, *b + 1 );
    }
    return legal;
}
/**
    *Czyta pierwszy znak jesli jest to @pas zwraca true.
    Jesli nie czyta nastepny i zwraca false.
    *Po wczytaniu dwoch pierwszych znakow lub tylko pierwszego,
    pozbywa sie reszty znakow z wejscia az do znaku nowego wiersza.
*/
bool wejscie( int * a , int * b , bool * end ,bool * fine )
{
    *a = getchar();
    bool omin = true;
    if( *a == EOF )
        *end = true;
    else
    {
        if( *a != pas )
        {
            omin = false;
            if( *a >= znak_a && *a <= znak_h )
            {
                *b = getchar();
                *b = *b - znak_0 - 1;
                if( !(*b >= 0 && *b <= N-1) )
                    *fine = false;
            }
            else
                *fine = false;
        }
        while( getchar() != nast_wiersz )
            *fine = false;
    }
    return omin;
}
/**
    Prowadzi rozgywke.
    Sprawdza czy podane wspolrzedne nie wychodza poza plansze.
*/
bool gra( int * B,int * C,char tab[][N], bool tab_bol[][N] , int * a , int * b )
{
    bool koniec = false;
    bool fine = true;
    if( wejscie(a,b,&koniec,&fine) && !koniec && fine )
    {
        printf("%c ",*a);
        ruch_komp(tab,tab_bol,B,C);
    }
    else if(!koniec)
    {
        if( fine )
        {
            if( gracz(tab,tab_bol,B,C,a,b) )
            {
                ruch_komp(tab,tab_bol,B,C);
            }
            else
            {
                int y = *C - *B;
                printf("? %d\n", y);
            }
        }
        else
        {
            int y = *C - *B;
            printf("? %d\n", y);
        }
    }
    return koniec;
}
/**
    Uruchamia gre reversi.
*/
int main(void)
{
    int B = Na_start, C = Na_start;
    int a,b;
    char plansza[N][N];
    bool zmiany[N][N];
    zeruj(zmiany);
    wypelnij(plansza);
    bool koniec = false;
    while(!koniec)
    {
        diagram( plansza );
        koniec = gra( &B , &C , plansza , zmiany , &a , &b );
    }
    return 0;
}
