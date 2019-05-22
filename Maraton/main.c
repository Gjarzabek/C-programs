#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "listy.h"
#include "tree.h"
#include "primary.h"


/* tablica wskaznikow na wezly drzewa uzytkownikow */
user *base[MAX_ID+1];

void zainicjalizuj_database() {
  int i;
  for( i = 0 ; i <= MAX_ID ; ++i )
    base[i] = NULL;
  base[0] = nowy_user();
}

/*wpisuje usera do tablicy wskaznikow*/
void wpisz_do_bazy( user *B , int ID ) {
  base[ID] = B;
}

/*wypisuje usera z tablicy wskaznikow*/
void wypisz_z_bazy( int ID ) {
  base[ID] = NULL;
}

void wejscie() {
  bool koniec_danych = false;
  while ( !koniec_danych ) {
    int Ch = getchar(); /* pierwszy znak w wierszu */
    switch ( Ch ) {
      case PUSTY_WIERSZ:
        break;
      case KOMENTARZ:
        wyczysc_wiersz(KOMENTARZ);
        break;
      case ' ':
        wyczysc_wiersz(DODATNI);
        error();
        break;
      case EOF:
        koniec_danych = true;
        break;
      default:
        ungetc(Ch,stdin);
        int argument1 = -1, argument2 = -1;
        int option  = sprawdz_polecenie(&argument1,&argument2);
        switch ( option ) {
          case AddUser:
            adduser(argument1,argument2);
            break;
          case DelUser:
            deluser(argument1);
            break;
          case AddMovie:
            addmovie(argument1,argument2);
            break;
          case DelMovie:
            delmovie(argument1,argument2);
            break;
          case Marathon:
            marathon(argument1,argument2);
            break;
          default:
            wyczysc_wiersz(DODATNI);
            error();
            break;
        }
    }
  }
}

int sprawdz_polecenie( int *a , int *b ) {
  char operacja[MAX_LEN];
  int i = 0;
  int C = getchar();
  while ( isalpha(C) && i < MAX_LEN-1 ) {
    operacja[i] = C;
    ++i;
    C = getchar();
  }
  if ( C == EOF ) {
    error();
    zwolnij_pamiec(0);
  }
  operacja[i] = '\0';
  if ( C != ' ' ) {
    ungetc(C,stdin);
    return BLAD;
  }
  else{
    if ( !strcmp( operacja , ADDUSER  ) ) {
      int parent = wczytaj_liczbe(ID_LEN,PIERWSZY);
      if( parent < 0 ) return BLAD;
      int child = wczytaj_liczbe(ID_LEN,DRUGI);
      if( child < 0 ) return BLAD;
      *a = parent;
      *b = child;
      return AddUser;
    }
    else if ( !strcmp( operacja , DELUSER ) ) {
      int removing = wczytaj_liczbe(ID_LEN,DRUGI);
      if( removing < 0 ) return BLAD;
      *a = removing;
      return DelUser;
    }
    else if ( !strcmp( operacja , ADDMOVIE ) || !strcmp( operacja , DELMOVIE ) || !strcmp( operacja , MARATHON ) ) {
      int who = wczytaj_liczbe(ID_LEN,PIERWSZY);
      if ( who < 0 ) return BLAD;
      int rating = wczytaj_liczbe(RATING_LEN,DRUGI);
      if ( rating < 0 ) return BLAD;
      *a = who;
      *b = rating;
      if ( !strcmp( operacja , ADDMOVIE ) ) return AddMovie;
      else if ( !strcmp( operacja , MARATHON ) ) return Marathon;
      else return DelMovie;
    }
    else {
      if ( i > 0 ) ungetc(operacja[0],stdin);
      return BLAD;
    }
  }
}

int wczytaj_liczbe( int len , int kolejnosc ) {
  char bufor[len];
  int i = 0;
  int znak = getchar();
  while ( isdigit(znak) && i  < len - 1 ) {
    bufor[i] = znak;
    ++i;
    znak = getchar();
  }
  if ( znak == EOF ) {
    error();
    zwolnij_pamiec(0);
  }
  if ( i == 0 ) return BLAD;
  if ( kolejnosc == DRUGI && znak != '\n' ) return BLAD;
  if ( kolejnosc == PIERWSZY && znak != ' ' ) {
    ungetc(znak,stdin);
    return BLAD;
  }
  if ( i > 1 && bufor[0] == '0') {
    if ( znak == '\n' ) ungetc(znak,stdin);
    return BLAD;
  }
  bufor[i] = '\0';
  int argument = BLAD;
  if ( sprawdz_zakres(bufor) ) {
    sscanf( bufor, "%d", &argument );
    return argument;
  }
  else {
    ungetc(znak,stdin);
    return argument;
  }
}

bool sprawdz_zakres( char liczba[] ) {
  char maks[MAX_LEN+2];
  sprintf( maks, "%d", MAX_MOVIE_RATING );
  int N = strlen( liczba );
  int M = strlen( maks );
  if ( M > N ) return true;
  else if ( M < N ) return false;
  else {
    int i = 0;
    bool rowne = true;
    bool w_zakresie = true;
    while ( i < M && rowne ) {
      if( liczba[i] != maks[i] ) {
        rowne = false;
        w_zakresie = maks[i] > liczba[i];
      }
      ++i;
    }
    return w_zakresie;
  }
}

void wyczysc_wiersz( char flaga ) {
  char ch = getchar();
  while ( ch != '\n' && ch != EOF )
    ch = getchar();
  if ( ch == EOF ) {
    if ( flaga != KOMENTARZ )  error();
    zwolnij_pamiec(0);
  }
}

bool poprawne_id( int id ) {
  return id >= 0 && id <= MAX_ID;
}

bool poprawny_rating( int rating ) {
  return rating >= 0 && rating <= MAX_MOVIE_RATING;
}

void ok() {
  printf(OK);
}

void none() {
  printf(NONE);
}

void error() {
  fprintf( stderr , ERROR );
}

void adduser( int parent , int us ) {
  if ( !poprawne_id(parent) || !poprawne_id(us) || base[parent] == NULL ) {
    error();
    return;
  }
  else if ( base[us] != NULL ) {
    error();
    return;
  }
  else {
    user *C = nowy_user();
    wpisz_do_bazy( C , us );
    dodaj_potomka( &(base[parent]->potomkowie) , C );
    ok();
  }
}

void deluser( int us ) {
  if ( us == 0 || !poprawne_id(us) || base[us] == NULL ) {
    error();
    return;
  }
  else {
    user *D = base[us];
    dopisz_potomkow(D);
    usun_potomka(D);
    usun_usera(&D);
    wypisz_z_bazy(us);
    ok();
  }
}

void addmovie( int userID , int MovieRating ) {
  if ( !poprawne_id(userID) || base[userID] == NULL || !poprawny_rating(MovieRating) ) {
    error();
    return;
  }
  else {
    if ( wstaw_sort( MovieRating , &(base[userID]->preferencje) ) )
      ok();
    else
      error();
  }
}

void delmovie( int userID , int MovieRating ) {
  if ( !poprawne_id(userID) || base[userID] == NULL || !poprawny_rating(MovieRating) ) {
    error();
    return;
  }
  else {
    if ( usun_film( MovieRating , &(base[userID]->preferencje) ) )
      ok();
    else
      error();
  }
}

void spacer( int max , user * akt , lista_preferencji ** wynikowa , int k ) {
  if ( akt != NULL ) {
    int i = 0;
    lista_preferencji * sprawdzana = akt->preferencje;
    while ( i < k && sprawdzana != NULL && sprawdzana->w > max ) {
      wstaw_sort( sprawdzana->w , wynikowa );
      sprawdzana = sprawdzana->next;
      ++i;
    }
    if ( akt->preferencje != NULL && akt->preferencje->w > max )
      max = akt->preferencje->w;
    if ( akt->potomkowie != NULL ) {
      wezel *wsk = akt->potomkowie->poczatek->next;
      while ( wsk != NULL && wsk->A != NULL ) {
        spacer( max , wsk->A , wynikowa , k );
        wsk = wsk->next;
      }
    }
  }
}

void marathon( int userID , int k ) {
    if ( !poprawne_id( userID ) || base[userID] == NULL || !poprawny_rating( k ) ) {
      error();
    }
    else if ( k == 0 ) none();
    else {
      lista_preferencji *wynikowa = NULL;
      user *p = base[userID];
      spacer( -1 , p , &wynikowa , k );
      wypisz( wynikowa , k );
      zapomnij_preferencje(&wynikowa);
    }
}

void zwolnij_pomoc( user *A ) {
  if ( A != NULL ) {
    if ( A->potomkowie != NULL ) {
      wezel *wsk = A->potomkowie->poczatek->next;
      while ( wsk != NULL && wsk->A != NULL ) {
        wezel *pom = wsk->next;
        zwolnij_pomoc( wsk->A );
        wsk = pom;
      }
    }
    usun_potomka( A );
    usun_usera( &A );
  }
}

void zwolnij_pamiec( int x ) {
  zwolnij_pomoc( base[0] );
  exit( x );
}

void glowna() {
  zainicjalizuj_database();
  wejscie();
  zwolnij_pamiec(0);
}

int main()
{
  glowna();
  return 0;
}
