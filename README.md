# 312CC_Mihaescu_Razvan_Tema2 PCLP 2022

## Problem 1 - Text Highlight

For this problem, I used two vectors of vectors, **linie** and **sublinieri**, which I dynamically allocated, so that there is no unused memory.
I read each line into an auxiliary vector **aux**, and then copied its content into the corresponding position of the line vector, allocating exactly as many elements as were read. The corresponding **sublinieri** vector was filled with spaces.
Then, for each line, I called the **subliniereCuivinteCheie** function, which implements the highlighting mechanism as follows: I split the words on each line, and using the **cuvinteCheie** function, I checked whether they are on the list of words to be highlighted. If so, I highlighted it in the **subliniere** vector.
If the extracted word is **of**, **each** or **a** and, by concatenation, with the previous extracted word forms one of the special compound words on the list, I highlight it from the beginning of the position of the previously extracted word (which I store in the **antpoz** variable) to the end position of the current word, so that all the spaces between the two words are also highlighted.


## Problem 2 - Text Autocomplete 

For this problem, I used a vector of structures of type **dictionary_entry**, which I dynamically allocated, so that there is no unused memory.
Then, I read the words that need to be autocompleted into a vector **cuvinte**, and processed them one by one. If I encounter punctuation marks, I output them as they are, as standalone words.
Otherwise, I tackled the other three cases using distinct functions, as follows:

 * if the word ends with an asterisk (*), I used the **cuvantSpecial** function, which displays the word as it is written and increases its priority if it is in the dictionary or adds it to the dictionary with priority 1 using the **adaugareDictionar** function.
 * if the word is written normally, I check with the **potrivireDictionar** function if there is a match with a word in the dictionary. If so, the word with the highest priority that matches (if there are more than one, I choose the smallest one in lexicographic order) is selected and returned through the **potrivit** parameter, and then I output the word **potrivit**.
 * if the word is written normally, but there is no match in the dictionary, the word as typed is written and then added to the end of the dictionary with priority 1 using the   * daca cuvantul este scris normal, dar nu se gaseste nicio potrivire in dictionar, se va scrie cuvantul cum a fost introdus de la tastatura si apoi il adaug la finalul dictionarului cu proritatea 1, cu ajutorul functiei v (care realoca dictionarului un element in plus).
 function (which reallocates an additional element to the dictionary).


## Problem 3 - Bitwise Calculator 

For this problem, I used a pointer vector to the functions **adunare**, **interschimbare**, **rotatie**, **xxor** that implement the requested operations. I followed the order of functions in the vector to match the binary representation of operations.
I then extracted the numbers and operations by shifting the bits to the right and applying 4-bit masks for numbers and 2-bit masks for operations.
For each operation, I called the **aplicareOperatie** function which, as the name suggests, applies the corresponding operation to the 2 numbers and returns the result through the **nr1** parameter.
I implemented the 4 operations through separate functions in the following way:

 * for **adunare**, I went through the four bits on which the 2 numbers are written from LSB to MSB and applied XOR on each bit and the previous remainder (which was initially 0), and then calculated the remainder for the current step
 * for **interschimbare**, I extracted the positions p1 and p2 from the second number, extracted the bits from the respective positions in the first number, and using two masks I swapped them, and finally, I extracted only the last 4 bits from the new number
 * for **rotatie**, I used the fact that the numbers are written on 4 bits, and rotation x times is equivalent to rotation x%4 times. Then I rotated by one bit to the left, retaining the MSB that would have been lost, and assigned it to the LSB, and then repeated the process for nr2%4 times and finally saved only the last 4 bits
 * for **xor**, I used the logical XOR gate equivalency with A*!B + !A*B .


## Wordle 

To implement the **Wordle** game, I used the **ncurses C library** to create the graphical interface. Initially, I created a simple menu with two options: **Play New Game** and **Quit**. If the player chooses the first option, a game board with five windows arranged on six rows representing the player's six attempts to guess the word will be created. If the player chooses the second option, the program will stop.

When starting a new game, a word to be guessed by the player is randomly selected from the list of words given in the problem.

Rules:

 * The player is only allowed to enter lowercase letters of the alphabet, which will be placed in a word in the order they are entered.
 * The player is allowed to delete characters and enter new ones.
 * The player is not allowed to enter a word that does not have five letters. Otherwise, if the player enters a word with fewer letters, it will not be accepted, and a warning message will appear on the screen. If the player enters more than 5 characters, the extras will not be processed.
 * It is considered that the player has exhausted an attempt when they enter a 5-letter word followed by pressing the **Enter** key. If the word guessed by the player has letters that are in the same position in the word to be guessed, the boxes where those letters are located will be colored green. If there are letters that are in the word to be guessed but not in the same positions, the respective boxes will be colored yellow.
 * If the player presses the **:** key, the menu will be displayed, and the player will have the option to start a new game or quit.
 * If the player guesses the word, a corresponding message will be displayed, followed by the menu with the two options.
 * If the player exhausts all six attempts, another message will be displayed, followed by the menu.
 
The program will continue as long as the player does not access the **Quit** option from the menu.  
