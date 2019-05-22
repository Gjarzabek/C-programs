#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "listy.h"
#include "tree.h"
#include "primary.h"

lista_preferencji *nowy_pref( int film , lista_preferencji *l ) {
  lista_preferencji *wsk = malloc( sizeof *wsk );
  if ( wsk == NULL ) zwolnij_pamiec(1);
  wsk->w = film;
  wsk->next = l;
  return wsk;
}

bool wstaw_sort( int film , lista_preferencji **l ) {
  bool taki_sam = false;
  lista_preferencji *wsk = NULL;
  if ( *l == NULL ) {
    *l = nowy_pref( film , NULL );
    return !taki_sam;
  }
  else if ( (*l)->w < film ) {
    wsk = nowy_pref( film , *l );
    *l = wsk;
    return !taki_sam;
  }
  else if ( (*l)->w == film ) return taki_sam;
  else {
    wsk = *l;
    while ( !taki_sam && wsk->next != NULL && wsk->next->w >= film ) {
      if ( !taki_sam )
        taki_sam = film == wsk->next->w;
      wsk = wsk->next;
    }
    if ( taki_sam ) return false;
    lista_preferencji *p = wsk->next;
    wsk->next = nowy_pref( film , p );
    return true;
  }
}

bool usun_film( int film , lista_preferencji **l ) {
  if ( *l == NULL ) return false;
  else {
    lista_preferencji *p = *l;
    lista_preferencji *poprzedni = NULL;
    while ( p != NULL && p->w != film ){
        poprzedni = p;
        p = p->next;
    }
    if ( p != NULL ) {
      if ( poprzedni == NULL ) {
        *l = p->next;
        free(p);
        return true;
      }
      else {
        poprzedni->next = p->next;
        free(p);
        return true;
      }
    }
    else return false;
  }
}

void zapomnij_preferencje( lista_preferencji **l ) {
  if ( *l != NULL ) {
    lista_preferencji *pom = (*l)->next;
    while ( pom != NULL ) {
        free(*l);
        *l = pom;
        pom = (*l)->next;
    }
    free(*l);
    *l = NULL;
  }
}
 void wypisz( lista_preferencji *l , int k ) {
   if ( l == NULL ) {
     none();
     return;
   }
   else {
     int i = 0;
     while ( i < k - 1 && l->next != NULL ) {
       if( l->w != l->next->w ) {
         printf("%d ", l->w );
         ++i;
       }
       l = l->next;
     }
     printf("%d\n", l->w );
   }
 }
