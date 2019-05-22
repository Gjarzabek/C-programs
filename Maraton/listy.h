#ifndef LISTY_H
#define LISTY_H
#include <stdbool.h>

typedef struct user user;

/* lista preferencji filmowych */
struct lista_preferencji{
  int w;
  struct lista_preferencji *next;
};
typedef struct lista_preferencji lista_preferencji;

/*wezel listy*/
struct wezel{
  user *A;
  struct wezel *next;
};
typedef struct wezel wezel;

/*lista potomkow danego wezla w drzewie ze wskaznikiem na ostatni element listy
  *pierwszy i ostatni element listy nie ma zadnego uzytkownika
*/
struct Lista_z_atrapa{
  wezel *ostatni;
  wezel *poczatek;
};
struct Lista_z_atrapa;
typedef struct Lista_z_atrapa Lista_z_atrapa;

/* tworzy nowy element listy preferencji*/
lista_preferencji *nowy_pref( int w , lista_preferencji *l );
/*dodaje film do listy preferencji zachowujac porzadek malejacy*/
bool wstaw_sort( int film , lista_preferencji **l );
/* usuwa film z preferencji zwraca true gdy operacja sie powiedzie else false*/
bool usun_film( int film , lista_preferencji **l );
/* usuwa liste preferencji */
void zapomnij_preferencje( lista_preferencji **l );
/* wypisuje liste */
void wypisz( lista_preferencji *l , int k );

#endif /* LISTY_H */
