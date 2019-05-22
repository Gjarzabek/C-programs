Algorytm X
Wprowadzenie
Rozwiązaniem problemu dokładnego pokrycia, dla rodziny P podzbiorów dziedziny S, jest zbiór Q⊆P taki, że każdy element dziedziny S należy do dokładnie jednego elementu Q.

Problem dokładnego pokrycia jest NP-zupełny. Nie jest znany deterministyczny algorytm rozwiązujący go w czasie wielomianowym.
Algorytm o koszcie wykładniczym, stosujący metodę prób i błędów, jest przez Donalda Knutha nazywany Algorytmem X.

Wiele problemów, np. łamigłówki, można sprowadzić do problemu dokładnego pokrycia.
Pomimo wykładniczej złożoności, efektywność rozwiązania problemu za pomocą Algorytmu X może być dla użytkownika akceptowalna.

Polecenie
Napisz program czytający ciąg wierszy F,W1,…Wn, w którym F to filtr a W1,…Wn jest instancją problemu dokładnego pokrycia.

Wszystkie czytane wiersze są tej samej długości d. Wiersz F składa się ze znaków minus - i plus +. W każdym wierszu W1,…Wn jest co najmniej jeden znak różny od podkreślenia _.

Wynikiem programu jest ciąg wierszy reprezentujących rozwiązania instancji W1,…Wn, przekształconych następnie za pomoca filtru F przez usunięcie znaków z pozycji, na których w filtrze jest -.

Rozwiązaniem instancji W1,…Wn jest zbiór Q⊆{1,…n}, reprezentowany przez tekst R długości d. Tekst ten nie zawiera znaku podkreślenia _ i spełnia warunek

∀1≤i≤d∃j∈Q((Wj)i=Ri∧∀k∈Q∖{j}(Wk)i=_)

Rozwiązania budujemy ze znaków wierszy W1,…Wn, zgodnie z ich kolejnością. W danym rozwiązaniu, w kolejności od początku,
wybieramy metodą prób i błędów znaki nie kolidujące z wyborami dokonanymi wcześniej.

PRZYKŁAD

dla wejścia:
 
+ + - + + + +

_ _ a _ _ _ b

c _ d _ _ _ _

_ _ _ _ e f _

_ g _ _ _ _ _

_ _ h i _ _ _

j _ _ _ _ _ k 

_ l _ _ _ _ _

_ _ _ _ _ m _

_ _ _ _ n _ o

_ _ p _ _ _ _

q _ _ r _ _ _

_ _ _ s _ _ _

oczekiwany wynik:

cgsnmo

clsnmo

jgiefk

jgsefk

jliefk

jlsefk

qgrefb

qgrnmo

qlrefb

qlrnmo
