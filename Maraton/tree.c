#include "listy.h"
#include "tree.h"
#include "primary.h"
#include <stdlib.h>
#include <stdbool.h>

wezel *nowy_wezel( user *B , wezel *nastepny ) {
  wezel *p = malloc( sizeof *p );
  if ( p == NULL ) zwolnij_pamiec(1);
  p->A = B;
  p->next = nastepny;
  return p;
}
/*pierwszy i ostatni wezel listy nie przechowuja zadnego uzytkownika\
  *wezel 'next' dla ostatniego to przedostatni*/
Lista_z_atrapa *nowa_lista( wezel *p ) {
  Lista_z_atrapa *L = malloc( sizeof *L );
  if ( L == NULL ) zwolnij_pamiec(1);
  L->ostatni = nowy_wezel( NULL , p );
  L->poczatek = nowy_wezel( NULL , p );
  p->next = L->ostatni;
  p->A->poprzednik = L->poczatek;
  return L;
}

void dodaj_potomka( Lista_z_atrapa **l , user *dodawany ) {
  if ( *l == NULL ){
    *l = nowa_lista(nowy_wezel(dodawany,NULL));
  }
  else{
    wezel *wsk = (*l)->ostatni->next;
    wezel *Nowy = nowy_wezel( dodawany , (*l)->ostatni );
    wsk->next = Nowy;
    (*l)->ostatni->next = Nowy;
    Nowy->A->poprzednik = wsk;
  }
}

/*wykonujemy tylko gdy user ma potomkow
 *do listy potomkow ojca @B dopisujemy potomkow urzytkownika @B
 *przed uzytkownikiem @B*/
void dopisz_potomkow( user *B ) {
  if( B != NULL && B->potomkowie != NULL ) {
    if( B->potomkowie->poczatek->next != B->potomkowie->ostatni && B->potomkowie->poczatek != B->potomkowie->ostatni->next ) {
      wezel *p = B->poprzednik;
      wezel *q = p->next;
      p->next = B->potomkowie->poczatek->next;
      B->potomkowie->poczatek->next->A->poprzednik = p;
      B->potomkowie->ostatni->next->next = q;
      B->poprzednik = B->potomkowie->ostatni->next;
      B->potomkowie->poczatek->next = NULL;
      B->potomkowie->ostatni->next = NULL;
    }
  }
}

/* usuwa wezel usera @B z listy potomkow ojca */
void usun_potomka( user *B ) {
  if( B != NULL ) {
    wezel *przed = B->poprzednik;
    if ( przed != NULL ) {
      wezel *akt = przed->next;
      przed->next = akt->next;
      if ( akt->next->A == NULL ) {
        akt->next->next = przed;
      }
      else {
        akt->next->A->poprzednik = przed;
      }
      free(akt);
      B->poprzednik = NULL;
    }
  }
}

/* tworzy nowego uzytkownika */
user *nowy_user() {
  user *nowy = malloc( sizeof *nowy );
  if ( nowy == NULL ) zwolnij_pamiec(1);
  nowy->preferencje = NULL;
  nowy->potomkowie = NULL;
  nowy->poprzednik = NULL;
  return nowy;
}

/* usuwa uzytkownika */
void usun_usera( user **B ) {
  if ( *B != NULL ) {
    zapomnij_preferencje( &((*B)->preferencje) );
    if ( (*B)->potomkowie != NULL ){
      free((*B)->potomkowie->poczatek);
      free((*B)->potomkowie->ostatni);
    }
    free((*B)->potomkowie);
    free(*B);
    *B = NULL;
  }
}
