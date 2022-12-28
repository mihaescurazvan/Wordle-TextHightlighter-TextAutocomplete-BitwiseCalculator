#include <stdio.h>
#include <stdlib.h>

typedef unsigned int (*ptrFunct)(unsigned int *, unsigned int *);
// functia care implementeaza adunarea pe biti
unsigned int adunare(unsigned int *nr1, unsigned int *nr2) {
    unsigned int rezultat, rest, bit1, bit2;
    rezultat = 0;
    rest = 0;
    int i;
    // stiind ca numerele sunt scrise pe 4 biti, le parcurg de la LSB la MSB
    for (i = 0; i < 4; i++) {
        // extrag bitul de la pozitia i (de la dreapta la stanga) din primul
        // numar
        bit1 = ((*nr1) >> i) & 0b1;
        // si din al doilea
        bit2 = ((*nr2) >> i) & 0b1;
        // adunarea a doi biti reprezinta un xor in care se retine restul
        // am implementat a xor b prin echivalenta (a and !b)or(!a and b)
        bit1 = (bit1 & ~(bit2)) | (~(bit1)&bit2);
        // fac xor si cu restul retinut anterior (care initial e 0) si retin
        // rezultatul in bit1
        bit1 = (bit1 & ~(rest)) | (~(bit1)&rest);
        // rezultatul adunarii va fi retinut in rezultat si atribui bitului de
        // la pozitia i din rezultat valoarea lui bit1
        rezultat = rezultat | (bit1 << i);
        // extrag din nou bitul de pe pozitia i din primul numar
        bit1 = ((*nr1) >> i) & 0b1;
        // daca vreunul dintre "si"-urile urmatoare este 1 inseamna ca adunarea
        // trece peste ordin si fac restul 1
        rest = (bit1 & bit2) | (bit1 & rest) | (rest & bit2);
    }
    *nr1 = rezultat;
    return *nr1;
}
// functia pentru interschimbare
unsigned int interschimbare(unsigned int *nr1, unsigned int *nr2) {
    unsigned int bit1, bit2, poz1, poz2;
    // aflu pozitia p1
    poz1 = (*nr2 >> 2);
    // aflu pozitia p2
    poz2 = *nr2 & 0b11;
    // aflu bitul de la pozitia p1 care trebuie schimbat
    bit1 = (*nr1 >> (3 - poz1)) & 0b1;
    // aflu bitul de la pozitia p2 care trebuie schimbat
    bit2 = (*nr1 >> (3 - poz2)) & 0b1;
    // fac bitii care urmeaza sa fie interchimbati 0
    *nr1 = *nr1 & ~(0b1 << (3 - poz1)) & ~(0b1 << (3 - poz2));
    // interschimb bitii
    *nr1 = *nr1 | (bit1 << (3 - poz2)) | (bit2 << (3 - poz1));
    // extrag doar ultimii 4 biti
    *nr1 = *nr1 & 0b1111;
    return *nr1;
}
// functia care implementeaza rotatia
unsigned int rotatie(unsigned int *nr1, unsigned int *nr2) {
    // stiind ca numerele sunt scrise pe 4 biti, roatia cu x biti este
    // echivalenta cu rotatia cu x%4 biti
    unsigned int rotatii = *nr2 % 4;
    unsigned int i, masca;
    // rotesc primul numar la stanga cu o pozitie si retin MSB-ul pe care il pun
    // dupa ca LSB si repet procedeul de "rotatii" ori
    for (i = 0; i < rotatii; i++) {
        masca = (*nr1 >> 3) & 0b1;
        *nr1 = *nr1 << 1;
        *nr1 = *nr1 | masca;
    }
    // extrag doar ultimii 4 biti
    *nr1 = *nr1 & 0b1111;
    return *nr1;
}
// functia care implementeaza xor pe biti
unsigned int xxor(unsigned int *nr1, unsigned int *nr2) {
    // poarta logica xor este echivalenta cu (a and !b)or(!a and b)
    *nr1 = (*nr1 & ~(*nr2)) | (~(*nr1) & *nr2);
    return *nr1;
}
// functia primeste operatia care trebuie aplicata celor 2 numere si returneaza
// rezultatul prin primul numar
unsigned int aplicareOperatie(unsigned int (*f)(unsigned int *, unsigned int *),
                              unsigned int *nr1, unsigned int *nr2) {
    *nr1 = f(nr1, nr2);
    return *nr1;
}
int main() {
    int n, i;
    unsigned int m;
    // am folosit un pointer la functii care contine operatiile ce trebuie
    // aplicate
    ptrFunct operatii[] = {adunare, interschimbare, rotatie, xxor};
    scanf("%u", &n);
    scanf("%u", &m);
    unsigned int nr1, nr2, deplasare, operatie;
    // extrag primul numar din m
    nr1 = (m >> (n * 6)) & 0b1111;
    for (i = 0; i < n; i++) {
        // stiind numarul de operatii, extrag la fiecare pas operatia si al
        // doilea numar
        deplasare = (m >> ((n * 6) - 6 * (i + 1)));
        operatie = (deplasare >> 4) & 0b11;
        nr2 = deplasare & 0b1111;
        // aplic apoi operatia corespunzatoare
        nr1 = aplicareOperatie(operatii[operatie], &nr1, &nr2);
    }
    printf("%u", nr1);
    return 0;
}
