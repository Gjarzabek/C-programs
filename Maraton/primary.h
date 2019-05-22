#ifndef PRIMARY_H
#define PRIMARY_H
#include <stdbool.h>

#define NONE "NONE\n"
#define OK "OK\n"
#define ERROR "ERROR\n"
#define ADDUSER "addUser"
#define DELUSER "delUser"
#define ADDMOVIE "addMovie"
#define DELMOVIE "delMovie"
#define MARATHON "marathon"
#define MAX_LEN 9 /*maksymalna liczba znakow lancucha z poprawnym poleceniem*/
#define ID_LEN 6
#define RATING_LEN 11
#define MAX_ID 65535
#define MAX_MOVIE_RATING 2147483647
#define BLAD -1
#define DODATNI '+'
#define KOMENTARZ '#'
#define PUSTY_WIERSZ '\n'
/* kolejnosc wczytywanych argumentow dla operacji */
#define PIERWSZY 1
#define DRUGI 2


typedef enum polecenie { AddUser , DelUser , AddMovie , DelMovie , Marathon } polecenie;
/*zarzadza programem i wywoluje inne funkcje*/
void glowna();
/* obsluguje wejscie i odpowiednio na nie reaguje */
void wejscie();
/* przetwarza wiersz i informuje jaka operacje wykonac
  *na parametrach a i b przekazuje argumenty do tej operacji*/
int sprawdz_polecenie( int *a , int *b );
/* wczytuje liczbe z wejscia */
int wczytaj_liczbe( int len , int kolejnosc );
/* sprawdza czy liczba w lancuchu znakow miesci sie w int */
bool sprawdz_zakres( char lb[] );
/*usuwa znaki z wejscia az napotka @'\n'*/
void wyczysc_wiersz( char flaga );
/* sparawdza czy id jest w zakresie */
bool poprawne_id( int id );
/* sprawdza czy rating jest w zakresie */
bool poprawny_rating( int rating );
/* wypisuje komunikat o bledzie na standardowe wyjscie diagnostyczne */
void error();
/* wypisuje komunikat o operacji zakonczonej powodzeniem */
void ok();
/* wypisuje komunikat informujacy ze nie bylo filmow spelniajacych warunki maratonu*/
void none();
/* zwalnia cala pamiec i konczy dzialanie programu z kodem x */
void zwolnij_pamiec( int x );
/* rekurencyjna funkcja pomocnicza zwalniajaca pamiec */
void zwolnij_pomoc( user *A );
/* uzytkownik o nr @parentID dodaje uzytkownika o nr @userID*/
/* ***kazda z operacji ponizej sprawdza sama dla siebie poprawnosc danych*/
void adduser( int parentID , int userID );
/*user wypisuje sie*/
void deluser( int userID );
/* uzytkownik @userID dodaje film do swoich preferencji */
void addmovie( int userID , int MovieRating );
/* uzytkownik usuwa film ze swoich preferencji */
void delmovie( int userID , int MovieRating );
/* wyznacza conajwyzej k filmow o najwyzszych ocenach sposrod:
  *wlasnych preferencji uzytkownika @userID
  *preferencji filmowych wyodrębnionych w wyniku przeprowadzenia operacji marathon dla każdego z potomków użytkownika userId,
   przy czym w wynikowej grupie k filmów znajdą się tylko takie,
   które mają ocenę większą od maksymalnej oceny filmu spośród preferencji użytkownika userId */
void marathon( int userID , int k );
/* funkcja pomocnicza dla funckji maraton - przechodzi po wszystkich potomka uzytkonika z identyfikatorem userID*/
void spacer( int max , user *akt , lista_preferencji **wynikowa , int k );

/* tworzy wezel o indeksie 0 i wpisuje do tablicy wskaznikow */
void zainicjalizuj_database();
/*wpisuje usera do tablicy wskaznikow*/
void wpisz_do_bazy( user *B , int ID );
/*wypisuje usera z tablicy wskaznikow*/
void wypisz_z_bazy( int ID );

#endif /* PRIMARY_H */
