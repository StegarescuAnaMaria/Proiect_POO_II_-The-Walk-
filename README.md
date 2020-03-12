# Proiect_The-Walk-joc-text-rpg.cpp
This is a OOP text-RPG game, where the main goal is for the "robot" to reach the destination. The map is a 2-dimensional array of 
characters where the destination is marked with an 'X'. There are also obstacles marked with '#', and special items to help the robot 
along the way (for example teleporting it a space closer to the destination, increasing its number of lives by 1 etc). There are 3 types of 
robots, their main difference being the trajectory they walk by. For example the first type moves in a zig zag like trajectory only on
lines and columns, and the second type makes only diagonal moves. The robots leave behind '-', '/', '|' depending on the kind of move
so that it's easier for us to follow. The items, destination and obstacles are placed on the map by random x and y coordinates, which are 
different for each game (every time the game is run on the console). This is insured by the ran() function and its seed = the exact time
the program is run. The game is finished if the user presses "No" when asked if they want to continue, when the robot reaches the 
endpoint or when it has no more lives.
The robot will have 3 lives at the beginning. Also, it sees 3 cells around, though there are items that expand its vision. The first 
priority when it comes to movement is the shape of the trajectory based on its type, but if the path is not clear (if there are items, 
for example, or 'X', either obstacles) it will change its predefined trajectory. If there is no way around the obstacles or if they 
make the robot move in circles, without being able to reach the 'X', then the robot will sacrifice a life and step other an obstacle.

![Game1](https://user-images.githubusercontent.com/48885998/76548013-c74ff700-6496-11ea-8426-eece7c5b726e.png)
![Game2](https://user-images.githubusercontent.com/48885998/76547998-c4550680-6496-11ea-8300-559b306d6f9b.png)
![Game3](https://user-images.githubusercontent.com/48885998/76548001-c5863380-6496-11ea-9196-8eea7319e03c.png)
![Game4](https://user-images.githubusercontent.com/48885998/76548002-c5863380-6496-11ea-971f-2866b728a4ec.png)
![Game5](https://user-images.githubusercontent.com/48885998/76548004-c61eca00-6496-11ea-965d-b484132710d2.png)
![Game6](https://user-images.githubusercontent.com/48885998/76548006-c61eca00-6496-11ea-991c-c18532881d59.png)
![Game7](https://user-images.githubusercontent.com/48885998/76548010-c6b76080-6496-11ea-8503-3889be9a2f1f.png)
![Game8](https://user-images.githubusercontent.com/48885998/76548012-c6b76080-6496-11ea-9239-9162fd9bfb5c.png)


(Am facut un mic joc text RPG in C++, avand un mic robot ca personaj de referinta cu scopul de a ajunge la destinatie. Harta este o matrice 
de caractere si marime constanta, iar destinatia este marcata de 'X' si are coordonate generate random, care difera la fiecare rulare a 
programului. Sunt 3 tipuri de roboti din care alege userul, care se diferentiaza prin modul in care se misca pe harta (o traiectorie intr-o
anumita forma, care e marcata cu '-' pentru fiecare pas pe linie si cu '|' pentru coloana). Exista si un numar de capcane (notate prin '#'),
la fel amplasate aleator conform unor coordonate random, coordonate ce difera la fiecare joc/rulare a programului. Fiecare robot poate 
vedea 3 celule in jurul sau, astfel modificandu-si traiectoria la nevoie (daca urmeaza sa cada intr-o capcana), si un numar variabil de 
vieti. Jocul se termina daca robotul ajunge la destinatie sau ramane fara vieti.  Pe harta mai exista anumite item-uri care ii ajuta pe 
roboti sa ajunga mai usor la destinatie (fie ii teleporteaza cu un spatiu mai aproape de destinatie, fie le mai adauga o viata in plus, le 
mai adauga +un spatiu de vizor).
Robotii se misca pe traiectoria lor normala daca calea e libera, iar daca depisteaza 'X' sau un item, se 'desprind' de pe traiectorie si 
merg direct catre 'X'/item, ocolind obstacolele. Daca robotii sunt inconjurati de obstacole, si nu se mai pot misca pe nici o directie, sau
daca obstacolele ii determina sa mearga in cercuri, acestia sacrifica o viata si trec peste un obstacol. Robotii sunt desemnati de 
marcajele 'I', 'II' sau 'III' in dependenta de tip. )
