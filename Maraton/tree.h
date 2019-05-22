#ifndef TREE_H
#define TREE_H

typedef struct lista_preferencji lista_preferencji;
typedef struct wezel wezel;
typedef struct Lista_z_atrapa Lista_z_atrapa;

/* wezly drzewa uzytkownikow */
struct user{
  lista_preferencji * preferencje;
  Lista_z_atrapa * potomkowie;
  wezel * poprzednik;// wezel poprzedni na liscie potomkow ojca
};
typedef struct user user;

/* tworzy nowego uzytkownika */
user *nowy_user();
/* usuwa uzytkownika */
void usun_usera( user **B );
/*tworzy nowy wezel listy potomkow*/
wezel *nowy_wezel( user  *A , wezel *nastepny );
/*tworzy nowa liste potomkow*/
Lista_z_atrapa *nowa_lista( wezel *p );
/*dodaje wezel na koniec listy potomkow*/
void dodaj_potomka( Lista_z_atrapa **l , user *dodawany );
/*dopisuje liste potomkow jednego usera do drugiego*/
void dopisz_potomkow( user *A );
/* usuwa wezel usera @B z listy potomkow ojca */
void usun_potomka( user *B );


#endif /* TREE_H */
