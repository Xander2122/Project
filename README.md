+======================================== | Maze | =========================================+

Hra je dvojrozmerný svet, v ktorom musíte princa ">" viesť mätúcou suterénnou chodbou hradu, ktorá má dve poschodia a ľahké pochodne iba v najtmavších rohoch, takže všetko brnenie je dobre osvetlené.

Prvé poschodie je pravidelné bludisko, kde princ potrebuje nájsť a vyzdvihnúť zápalku. Potom nájde pochodeň a osvetli ho.

Keď princ zapálil prvú pochodeň, nevšimol si, ako vytiahol páku a teleportoval sa na podlahu vyššie. Tu princ musí nájsť a vyzdvihnúť 2 zápasy a zapáliť 2 pochodne.

Tu princ musí nájsť a vyzdvihnúť 2 zápalky a zapáliť 2 pochodne.

Ale na jeho ceste sú prekážky: neviditeľné steny "*", koliky "@" a portály "O", ktoré sa presúvajú na iný portál, ktorý mu nie je známy.

Hroty sú veľmi nebezpečné. Aspoň jeden vyrážkový krok a princ môže ísť do neba. (Hra končí ako strata).

Keď princ nájde neviditeľnú stenu a prechádza cez ňu, ta bezpečne zmizne.

Po zapálení všetkých pochodní v miestnosti sa objavil zahusťujúci dym, po ktorom princ padol na zem a po chvíli sa prebudil vo svojom sídle(hra končí ako víťazstvo).

============================================================================================

+----------------+

| Prvé spustenie |

+----------------+

Hra kompiluje pomocou súboru Makefile, ktorý je v priečinku hry. Ak je potrebne skompilovat hru, stačí napísať príkaz "make" na príkazovom riadku. 

Potom príkazový riadok zobrazí dve správy, čo hra úspešne skompilovala:

1. gcc -std=c99 -lcurses -c program.c -o program.o

2. gcc -std=c99 -lcurses program.o -o program

Ak chcete začať hrať, musíte napísať príkaz "./program". Potom sa hra začne a bude fungovať.

============================================================================================

+------------------+

| Základné funkcie |

+------------------+

int position [] – počiatočná pozícia princa na mape. Pole čísel, pretože existujú dve pozície - na prvej mape a na druhej

char labyrith a char maze – mapa prvého a druhého bludiska

void setPosition(int y, int x) – zmení pozíciu princa

int getHorizontal() – vráti pozíciu princa podľa X

int getVertical() – vráti pozíciu princa podľa Y

void lose() – zobrazí obrazovku porážky

void won() – zobrazí obrazovku víťazstvo

void generate_map() – generovanie prvého poschodia

void generate_second() – generácia druhého poschodia

int main() – toto je hlavná funkcia, ktorá vykonáva inicializáciu a prípravu ncurses. Potom začne bežať herný cyklus ,v ktorom je switch (tlačidlo spracovania stlačí vpravo, vľavo, hore, dole na klávesnici).

============================================================================================
