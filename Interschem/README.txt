=========INTERSCHEM=========
Proiect realizat de: Radu Mihnea.
Profesor indrumator: Patrut Bogdan

=========INSTRUCTIUNI UTILIZARE==========
1) Accesati fisierul Debug
2) Rulati Interschem.exe
3) Creati o schema si vedeti cum functioneaza
4) Pentru a crea o legatura intre 2 piese trebuie sa faceti click pe amandoua in mod consecutiv. In cazul piesei
de comparatie, utilizarea click-dreapta va crea legatura pe ramura "FALS".
5) Pentru a muta o piesa, trebuie sa tineti apasat click pe aceasta si sa mutati cursorul in zona de lucru.
6) Pentru a importa/salva scheme, introduceti numele dorit in zona de input de jos si apasati butonul corespunzator.
7) Butonul R din dreapta sus va reseta intreaga zona de lucru.

*Proiectul vine cu 3 exemple de scheme. Puteti sa le importati utilizand numele: "factorial", "prim" si "swap" in casuta de import.

==========REGULI SCHEME==================
1) O schema TREBUIE sa aiba un loc de start si un loc de final, iar acestea trebuie sa fie conectate. In caz contrar, proiectul nu va functiona.
2) Operatiile care se pot face in blocurile de operatie si comparatie sunt cele din c++, singura diferenta fiind cea de atribuire
Pentru a atribui o valoare unei variabile, se va utiliza operatorul ":=".
3) Pentru a crea o noua piesa de input/output/operatie/comparatie, TREBUIE introdusa un nume/o expresie in inputul din stanga
inaintea apasarii butonului Create;
4) Chiar daca o variabila poate avea orice nume, aceasta este obligata sa aiba unul. Programul va functiona chiar daca piesele
nu vor contine niciun nume, insa comportamentul poate fi neprevazut. Asemenea si pentru expresiile in cazul operatiilor/comparatiilor.
5) In cazul existentei mai multor piese de start, programul va lua in considerare doar prima adaugata.

==========EDITARE COD====================
1) Codul a fost conceput in asa fel incat poate fi usor editabil. Fiecare componenta are un comentariu sugestiv si este indicat
ca si in viitor acest lucru sa ramana asa. Se pot adauga usor concepte noi fara a fi afectat codul anterior. Proiectul a fost
gandit pentru evolutie
2) Proiectul este facut in VisualStudio, pentru editarea acestuia este recomandata utilizarea acestui IDE. Se poate deschide fisierul
Interschem.sln si proiectul va fi incarcat in totalitate
3) Proiectul NU include libraria SFML, pentru editarea codului va trebui downloadata si refacute legaturile pentru linker.
4) In cazul editarilor viitoare, asigurati-va ca la sectiunea Project->C/C++->General->Additional Dependencies & 
Project->Linker->Additional Libraries sunt introduse path-urile corecte pentru libraria grafica SFML.

Librarii: SFML, Exprtk;
Creatorii proiectului nu asuma drepturi de licenta pentru fonturile/librariile existente in proiect. Proiectul acesta nu are
uz comercial. Pentru a utiliza 

Contact: radumihneaa@gmail.com
