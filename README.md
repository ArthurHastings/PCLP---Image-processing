Task 1:
In task-ul 1 am avut de implementat 3 comenzi: edit, save si quit. Primul lucru pe care l-am facut este sa creez
un vector alocat dinamic numit cerinta[] si altul tot alocat dinamic numit comanda[]. In primul vector se
stocheaza cate un rand din 'interactive console' dupa ce este parcurs vectorul cerinta[] se stocheaza in
vectorul comanda[] cele 3 intructiuni aparuta la Task 1: edit, save sau quit. Daca comanda este "edit" atunci
citesc de la path-ul indicat o poza in format binar cu ajutorul structurilor de tip bmp oferite din exercitiu
si introduc fiecare byte al pixelilor, vectorului alocat dinamic pixel_p1[].  Daca comanda este "save" atunci
se afiseaza in path-ul corespunzator poza din vectorul pixel_p1[];
Comanda quit elibereaza memoria vectorilor alocati dinamici si returneaza 0.



Task 2:

     Daca comanda este "insert" atunci se citeste de la path-ul insert-ului poza in format binar si se introduce
fiecare byte al pixelilor pozei de inserat, intr-un vector alocat dinamic numit pixel_p2[].Dupa aceasta este 
parcurs vectorul pixel_p1[] si se inlocuiesc pixelii acestuia cu cei ai pozei inserate.

Task 3:

	Daca comanda este "set" se verifica si 'cuvantul' de dupa aceasta comanda, pentru ca exista comanda "set
line_width" si "set draw_color". Daca comanda de dupa este "draw_color" atunci se citesc cele 3 valori care 
reprezinta Rosu, Verde si Albastru si se stocheaza in valoarea rosu, verde si albastru.
Daca comanda este "line_width" se citeste numarul de dupa aceasta comanda si se stocheaza in valoarea line_width.
Daca comanda este "draw" se verifica si cuvantul de dupa aceasta. Daca acesta este "line" atunci se citesc cele 
4 numere de dupa care reprezinta coordonatele celor 2 puncte care formeaza dreapta si se stocheaza in variabilele
line_y1, line_x1, line_y2 si line_x2, dupa asta se calculeaza diferenta minima pe linie (adica pe axa x sau y)
dintre cele doua si se apeleaza functia linie_ingrosata() care primeste ca parametrii coordonatele celor 2 puncte
,diferenta maxima si minima, matricea care este initializata cu 0 si lungimea si latimea pozei. Aceasta functie
compara la inceput diferenta mai mare dintre cele doua axe si cand a ales-o pe cea mai mare o parcurge de la 
valoarea mica la cea mare si introduce in cei 2 vectori alocati dinamic numiti poz_x si poz_y care contin
toate coordonatele punctelor de pe dreapta (acesti pixeli au fost calculati cu formula de calcul al ecuatiei
unei drepte de la matematica). Dupa ce avem cei 2 vectori de coordonate x si y introducem in matricea de pixeli
(initial plica cu 0) valoarea 1 numai in coordonatele calculate mai devreme, adica cele ale liniei noastre
dupa aceasta, apelam functi fill_function() care are ca parametrii matricea lungimea si inaltimea pozei pe care
trasam dreapta si line_width dorit pentru latimea dreptei. Aceasta functie fill_function() parcurge matricea de 
pixeli si cauta numerele curente. La gasirea numarului curent in matrice se "bordeaza" pixelul respectiv in toate
directiile(sus jos stanga dreapta si pe diagonale) cu numarul curent + 1. Aceasta operatie este executata de 
line_width/2 ori pentru a ajunge la latimea dreptei dorite. Dupa iesirea din functia fill_function() tot ce ne
mai ramane sa facem este sa parcurgem matricea de pixeli si sa cautam valori != 0, astfel adaugam in vectorul 
nostru de bytes pixel_p1 dreapta "ingrosata" dorita.
Pentru comanda "rectangle" se citeste o coordonata urmata de lungimea si latimea dreptungiului. Cu aceste "date
de intrare" calculam coordonatele fiecarui colt al dreptungiului si apelam functia linie_ingrosata() explicata
mai sus de 4 ori, pentru fiecare dreapta trasa intre cele 4 puncte.
Pentru comanda "triangle" citim coordonatele a 3 puncte care reprezinta varfurile triunghiului nostru. Tot ce ne
ramane sa facem este sa apelam functia linie_ingrosata() de 3 ori pentru cele 3 drepte corespondente. Am uitat 
sa mentionez mai sus ca dupa fiecare apelare de linie_ingrosata(), doresc sa "sterg" continutul matricei mele de
pixeli, pentru ca aceasta reprezinta matricea de pixel a fiecarei linii, astfel am creeat o functi numita 
resetare_matrice() care introduce in toata matricea valoarea 0.

Task 4:
	Daca comanda este "fill" se citesc 2 numere care reprezinta coordonatele unui punct de pe poza, aceasta 
functie se doreste a umple fiecare pixel de culoarea(R G B-ul) pixelului initial(adica cel a carui coordonate 
se dau) cu o culoare aleasa mai devreme in comanda "set draw_color". La inceput cream 3 variabile care reprezinta
R G B - ul pixelului selectat pentru functia fill numite albastru_og, verde_og si rosu_og dupa asta verificam
daca numarul de pixeli cu valoarea originala este egala cu numarul de pixeli totali din poza, in acest caz se 
'coloreaza' toata poza cu o singura culoare, acest lucru este important pentru ca salveaza mult timp pe testele
in care se cere sa se coloreze toata poza. Daca numarul de pixeli de schimbat NU coincide cu 
numarul total de pixeli din poza, se apeleaza functia Fill() care primeste ca parametrii coordonatele punctului
in care se da fill, R G B - ul pixelului selectat, R G B - ul setat la functia "set draw_color", si dimensiunile
pozei. La intrarea in functia Fill() primul lucru facut este sa se verifice daca pixelul curent este de culoarea
pixelului original. Daca este, atunci este transformat in R G B - ul selectat la functia "set draw_color" si se 
verifica daca pixelii din jurul acestuia sunt tot de culoarea pixelului original, daca da, atunci se apeleaza 
recursiv functia Fill() din interiorul acestora, singurul lucru schimbat fiind pixelul actual (adica pentru SUS 
avem i-1 j; JOS i+1 j; STANGA i j-1 si DREAPTA i j+1).
Dupa apelarea functiei fill() imaginea noastra initiala este modificata astfel incat in jurul coordonatei punctul
ui in care se face fill() acum avem aceeasi culoare.













