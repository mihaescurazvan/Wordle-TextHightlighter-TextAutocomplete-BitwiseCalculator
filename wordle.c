#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// functia care creeaza tabla de joc
void creareTabla(WINDOW* tabla[6][7], int cols) {
    int i, j;
    float lungime, latime, start_y, start_x;
    // initializez dimensiunile casutelor in care se vor scrie literele
    lungime = 3;
    latime = 7;
    start_y = 0;
    // creez cate 5 casute pe 6 randuri si le plasez in mijlocul ecranului
    for (i = 0; i < 6; i++) {
        start_y = lungime * i + 5;
        for (j = 0; j < 5; j++) {
            start_x = latime * j + (cols - 5 * latime) / 2;
            tabla[i][j] = newwin(lungime, latime, start_y, start_x);
            box(tabla[i][j], 0, 0);
            // functia de wrefresh face casuta sa apara pe ecran
            wrefresh(tabla[i][j]);
        }
    }
}
// functia care creeaza meniul
void creareMeniu(WINDOW* meniu, WINDOW* tabla[6][7], int cols) {
    int y, x, i;
    // aflu dimiensiunile ecranului
    getmaxyx(stdscr, y, x);
    // creez o fereastra de meniu cu dimensiunile jumatete din ecran si o afisez
    // in mijlocul ecranului cand functia este apelata
    meniu = newwin(y / 2, x / 2, y / 4, x / 4);
    box(meniu, 0, 0);
    refresh();
    wrefresh(meniu);
    // keypad(true) permite folosirea sagetilor
    keypad(meniu, true);
    // meniul va avea 2 optiuni simple
    char variante[2][15] = {"Play New Game", "Quit"};
    int decizie;
    // variabila subliniere va retine pe care dintre optiunile meniului ne aflam
    int subliniere = 0;

    while (1) {
        for (i = 0; i < 2; i++) {
            // scriu optiunile in meniu, iar optiunea cu indicele subliniere va
            // aparea evidentiata
            if (i == subliniere) {
                wattron(meniu, A_STANDOUT);
            }
            mvwprintw(meniu, i + 1, (x / 2 - strlen(variante[i])) / 2, "%s",
                      variante[i]);
            wattroff(meniu, A_STANDOUT);
            wrefresh(meniu);
        }
        decizie = wgetch(meniu);
        // daca decizie primeste ca input sageata in sus trebuie sa avem grija
        // ca subliniere sa nu scada sub 0
        if (decizie == KEY_UP) {
            subliniere--;
            if (subliniere == -1) {
                subliniere = 0;
            }
            // daca decizie primeste ca input sageata in jos trebuie sa avem
            // grija ca subliniere sa nu creasca peste 1
        } else if (decizie == KEY_DOWN) {
            subliniere++;
            if (subliniere == 2) {
                subliniere = 1;
            }
        }
        refresh();
        // vom iesi din loop cand se va apasa enter
        if (decizie == 10 && subliniere == 0) {
            werase(meniu);
            wrefresh(meniu);
            // daca se apasa enter pe prima varianta se va incepe un joc nou
            // prin crearea tablei de joc
            creareTabla(tabla, cols);
            refresh();
            break;
        } else if (decizie == 10 && subliniere == 1) {
            // daca se apasa enter pe a doua optiune, oprim programul
            endwin();
            exit(0);
        }
    }
}
// functia care selecteaza un cuvant aleator din lista de cuvinte
char* selectareCuvant(char (*lista)[6], char* cuvant) {
    // functia creeaza un seed diferit de fiecare data cand este apelata astfel
    // incat sa avem mereu cuvinte diferite selectate
    srand(time(NULL));
    int indice;
    // cum lista cuvintelor are doar 27 de elemente, numarul generat aleatoriu
    // trebuie impartit cu rest la 27
    indice = rand() % 27;
    // returnez cuvantul care trebuie ghicit prin parametrul cuvant
    strcpy(cuvant, lista[indice]);
    return cuvant;
}

// functia care implementeaza mecanismul jocului
int incercare(WINDOW* tabla[6][7], char cuvant[6], int i, int linii,
              WINDOW* meniu, int cols) {
    int j;
    int rows, columns;
    // initializez 2 perechi de culori
    start_color();
    // verde cu alb pentru cand litera se afla pe aceeasi pozitie in cuvantul de
    // ghicit
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    // galben cu alb pentru cand litera se afla in cuvantul de ghicit, dar pe
    // alta pozitie
    init_pair(2, COLOR_WHITE, COLOR_YELLOW);
    char ghicit[6];
    int c;
    j = 0;
    // pe linia urmatoare vor aparea mesajele in caz de victorie, pierdere sau
    // daca este introdus un cuvant care are sub 5 litere, iar prin urmatoarele
    // 2 functii predefinite sterg mesajele la fiecare incercare noua de ghicire
    // sau la inceput de joc nou
    wmove(stdscr, 3 * linii / 4, 0);
    wclrtoeol(stdscr);
    refresh();
    do {
        c = getch();
        // permit citirea doar a litelor mici
        if (c >= 'a' && c <= 'z' && j < 5) {
            ghicit[j] = c;
            // scriu caracterul in mijlocul casutei ca majuscula
            getmaxyx(tabla[i][j], rows, columns);
            wmove(tabla[i][j], rows / 2, columns / 2);
            attron(A_BOLD);
            mvwaddch(tabla[i][j], rows / 2, columns / 2, c - 32);
            attroff(A_BOLD);
            wrefresh(tabla[i][j]);
            j++;
        } else if ((c == 127 || c == 8) && j >= 1) {
            // daca este apasat backspace-ul, iar cursorul nu este in prima
            // casuta, se va sterge caracterul anterior
            j--;
            getmaxyx(tabla[i][j], rows, columns);
            wmove(tabla[i][j], rows / 2, columns / 2);
            werase(tabla[i][j]);
            box(tabla[i][j], 0, 0);
            wrefresh(tabla[i][j]);
            refresh();
        } else if ((int)c == 10 && j != 5) {
            // daca se incearca intorducerea unui cuvant mai mic de 5 litere se
            // va afisa un mesaj de atentionare
            attron(A_BOLD);
            mvprintw(3 * linii / 4,
                     (cols - strlen("Introdu un cuvant de 5 litere!")) / 2,
                     "Introdu un cuvant de 5 litere!");
            attroff(A_BOLD);
            refresh();
        } else if (c == 58) {
            // daca se apasa tasta ':' , se va afisa meniul
            creareMeniu(meniu, tabla, cols);
        }
    } while ((int)c != 10 || j != 5);  // loop-ul se termina cand se apasa
                                       // enter, cuvantul are 5 litere
    ghicit[j] = '\0';
    char copie[6], copie_ghicit[6];
    strcpy(copie, cuvant);
    strcpy(copie_ghicit, ghicit);
    for (j = 0; j < 5; j++) {
        if (ghicit[j] == cuvant[j]) {
            // daca o litera in cuvantul ghicit se afla si in cuvantul de ghicit
            // pe aceeasi pozitie, se va colora casuta in care se afla cu verde
            wbkgd(tabla[i][j], COLOR_PAIR(1));
            wrefresh(tabla[i][j]);
            // sterg litera respectiva pentru a nu se colora de mai multe ori
            // aceeasi litera
            copie[j] = '*';
            ghicit[j] = '#';
        }
        wrefresh(tabla[i][j]);
    }
    for (j = 0; j < 5; j++) {
        if (strchr(copie, ghicit[j]) != NULL) {
            // daca o litera in cuvantul ghicit se afla si in cuvantul de
            // ghicit, dar nu pe aceeasi pozitie, se va colora casuta in care se
            // afla cu galben
            wbkgd(tabla[i][j], COLOR_PAIR(2));
            wrefresh(tabla[i][j]);
            // sterg litera respectiva pentru a nu se colora de mai multe ori
            // aceeasi litera
            copie[j] = '*';
            ghicit[j] = '#';
        }
        wrefresh(tabla[i][j]);
    }
    // daca cuvantul ghicit este identic cu cel care trebuie ghicit, se
    // returneaza 1, iar -1 in caz contrar
    if (strcmp(cuvant, copie_ghicit) == 0) {
        return 1;
    }
    return -1;
}
int main() {
    // initializez ecranul pentru ncurses
    initscr();
    start_color();
    // functiile urmatoare fac ca inputul de la tastura sa nu apara
    noecho();
    // caracterele de la tastatura sa nu aiba valori speciale (de ex CTRL C sa
    // nu inchida programul)
    raw();
    // cursorul sa nu apara
    curs_set(0);
    int rows, cols;
    int i, j;
    int ok = 0;
    // aflu numarul de linii si coloane al ecranului
    getmaxyx(stdscr, rows, cols);
    // scriu titlul jocului pe primul rand in mijloc
    attron(A_BOLD);
    mvprintw(0, (cols - strlen("WORDLE")) / 2, "WORDLE");
    attroff(A_BOLD);
    refresh();
    WINDOW* tabla[6][7];
    WINDOW* meniu;
    // programul va incepe prin afisarea meniului
    creareMeniu(meniu, tabla, cols);
    refresh();
    creareTabla(tabla, cols);
    refresh();
    char lista_cuvinte[27][6] = {
        "arici", "atent", "baiat", "ceata", "debut", "peste", "fixat",
        "hamac", "harta", "jalon", "jucam", "lacat", "magie", "nufar",
        "oaste", "perus", "rigle", "roman", "sanie", "scris", "sonda",
        "texte", "tipar", "titan", "zebra", "vapor", "vatra"};
    char cuvant_de_ghicit[6];
    // se alege un cuvant aleatoriu din lista
    selectareCuvant(lista_cuvinte, cuvant_de_ghicit);
    while (1) {
        // se sterge orice fel de mesaj de la jocurile anterioare
        wmove(stdscr, 3 * rows / 4, 0);
        wclrtoeol(stdscr);
        refresh();
        // jucatorul are la dispozitie 6 incercari
        for (i = 0; i < 6; i++) {
            if (incercare(tabla, cuvant_de_ghicit, i, rows, meniu, cols) == 1) {
                // daca jucatorul a ghicit cuvantul se afiseaza un mesaj
                // corespunzator
                attron(A_BOLD);
                mvprintw(3 * rows / 4,
                         (cols - strlen("Felicitari! Ai ghicit cuvantul.")) / 2,
                         "Felicitari! Ai ghicit cuvantul.");
                attroff(A_BOLD);
                ok = 1;
                // dupa o secunda se afiseaza meniul pentru a da posibilitatea
                // jucatorului sa inceapa alt joc sau sa renunte
                sleep(1);
                creareMeniu(meniu, tabla, cols);
                refresh();
                break;
            }
        }
        // daca jucatorul nu a ghicit se afiseaza un alt mesaj si apoi meniul
        if (ok == 0) {
            attron(A_BOLD);
            mvprintw(
                3 * rows / 4,
                (cols - strlen("Din pacate ai pierdut! Mai incearca.")) / 2,
                "Din pacate ai pierdut! Mai incearca.");
            attroff(A_BOLD);
            sleep(1);
            creareMeniu(meniu, tabla, cols);
            refresh();
        }
    }
    return 0;
}
