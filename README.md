# 312CC_Mihaescu_Razvan_Tema2 PCLP 2022

## Problema 1 - Text Highlight | Timp de lucru: 40 de minute

Pentru aceasta problema am utilizat 2 vectori de vectori, **linie** si **sublinieri**, pe care i-am alocat dinamic, astfel incat sa nu existe memorie neutilizata. 
Am citit intr-un vector **aux** fiecare linie, iar continutul l-am copiat in vectorul linie de pe pozitia corespunzatoare, alocand exact atatea elemente cate au fost citite, iar vectorul sublinieri corespunzator pozitiei l-am umplut cu spatii.
Apoi, pentru fiecare linie am apelat functia **subliniereCuivinteCheie** care implementeaza mecanismul de subliniere in felul urmator: am despartit cuvintele de pe fiecare linie si prin functia **cuvinteCheie** am verificat daca se afla in lista cuvintelor care trebuie subliniate. Daca da, il subliniez in vectorul **subliniere**.
Daca cuvantul extras este **of**, **each** sau **a** si, prin concatenare, cu anteriorul cuvant extras formeaza unul dintre cuvintele compuse speciale din lista, il subliniez de la inceputul pozitiei cuvantului anterior extras (pozitie pe care o retin in variabila **antpoz**) si pana la pozitia de final a cuvantului actual, astfel incat sa fie sublimiate si toate spatiile dintre cele 2 cuvinte. 

## Problema 2 - Text Autocomplete | Timp de lucru: 2h

Pentru aceasta problema am folosit un vector de structuri de tipul **dictionary_entry**, pe care l-am alocat dinamic astfel incat sa nu existe memorie neutilizata. 
Apoi, am citit intr-un vector **cuvinte**, cuvintele care trebuie autocompletate si le-am parcurs pe rand. Daca intalnesc semne de punctuatie le afisez asa cum sunt scrise, cuvinte de sine statatoare.
In caz contrar, am abordat celelalte 3 cazuri prin functii distincte, astfel: 
  * daca cuvantul se termina cu *, am folosti functia **cuvantSpecial** care afiseaza cuvantul asa cum este scris si ii creste prioritatea daca se afla in dictionar sau il introduc in dictionar cu prioritatea 1, cuajutorul functiei **adaugareDictionar**
  * daca cuvantul este scris normal, verific prin functia **potrivireDictionar** daca se gaseste o potrivire cu un cuvant din dictionar. Daca da, se alege cuvantul cu prioritatea cea mai mare cu care se potriveste (daca sunt mai multe, il aleg pe cel mai mic in oridine lexicografica) si se returneaza prin parametrul **potrivit**, iar apoi afisez cuvantul **potrivit**
  * daca cuvantul este scris normal, dar nu se gaseste nicio potrivire in dictionar, se va scrie cuvantul cum a fost introdus de la tastatura si apoi il adaug la finalul dictionarului cu proritatea 1, cu ajutorul functiei **adaugareDictionar** (care realoca dictionarului un element in plus).
  
## Problema 3 - Calculator pe biti | Timp de lucru: 4h
  
Pentru aceasta problema am folosit un vector de pointeri la functiile **adunare**, **interschimbare**, **rotatie**, **xxor** care implementeaza operatiile cerute. Am respectat oridinea functiilor in vector pentru a se potrivi cu codificarea operatiilor in binar. 
Am extras apoi numerele si operatiile prin deplasari la dreapta pe biti si masti de 4 biti pentru numere si 2 biti pentru operatii.
Pentru fiecare operatie am apelat functia **aplicareOperatie** care, dupa cum sugereaza si numele, aplica operatia corespunzatoare celor 2 numere si returneaza rezultatul prin parametrul **nr1**.
Am implementat cele 4 operatii prin functii distincte in urmatorul mod:
  * pentru **adunare** am parcurs cei patru biti pe are sunt scrise cele 2 numere de la LSB la MSB si am aplicat xor pe ficare bit si restul anterior (care a fost initial 0), iar apoi am calculat restul pentru pasul respectiv
  * pentru **interschimbare** am extras pozitile p1 si p2 din al doilea numar, am extras bitii de la pozitiile respective in primul numar si cu ajutorul a doua masti i-am interschimbat, iar in final, am extras doar ultimii 4 biti din numarul nou obtinut
  * pentru **rotatie** am folisit faptul ca numerele sunt scris pe 4 biti, iar rotatia de x ori este echivalenta cu rotatia de x%4 ori. Apoi am rotit cu cate un bit la stanga retinand MSB-ul care s-ar fi pierdut si l-am atribuit LSB-ului, iar apoi am repetat procesul de nr2%4 ori si in final am salvat doar ultimii 4 biti
  * pentru **xor** am folosit echivalenta portii logice XOR cu A*!B + !A*B .
  
## **Wordle** | Timp de lucru: 18-20h
