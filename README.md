//311CD Constantin Rares
//Tema1 SD

Voi incerca sa explic pe scurt cum am gandit sa implementez fiecare
functie, deoarece fiecare dintre acestea sunt explicate, pe bucati, sub forma 
de commenturi, in fisierul sursa.

	[createDictionary]:
		-mai intai aloc memorie pentru dictionar
		-apoi aloc memorie pentru vectorul de liste

	+[numberOfElementsInList]:
		-functie adaugata de mine pentru a ma ajuta in alte functii
		-calculeaza numarul de elemente din lista cu un anumit indice dintr-un
	dictionar

	+[numberOfElementsInDictionary]:
		-functie adaugata de mine pentru a ma ajuta in alte functii
		-cu ajutorul functiei "numberOfElementsInList", calculeaza numarul de
	elemente dintr-un dictionar


	+[deleteLastElements]:
		-functie adaugata de mine pentru a ma ajuta in alte functii
		-sterge ultimul element din fiecare lista din dictionar
		-va fi apelata in principal atunci cand se depaseseste memoria de 2N
	elemente a dictionarului


	[addElement]:
		- calculeaza indicele listei in care trebuie adaugat elementul
		- in implementarea mea am abordat urmatoarele cazuri:

			1) lista in care trebuie introdus este goala
			2) lista in care trebuie introdus nu este goala
				2.1) elementul exista deja in lista
				2.2) elementul nu exista deja in lista
					2.2.1) elementul trebuie introdus la inceputul listei
					2.2.2) elementul trebuie introdus undeva la mijloc
					2.2.3) elementul trebuie introdus la finalul listei

		- de asemenea, a trebuit sa tin cont si de cele 4 categorii de situatii:

			< Facand comparatia intre campurile elementului ce trebuie adaugat si
			elementul curent din lista, avem >

			1) frequency1 != frequency2

			2) frequency1 == frequency2
			   value1 != value2

			3) frequency1 == frequency2
			   value1 == value2
			   key1 != key2

			4) *cazul in care elementul exista deja in lista*
			   frequency1 == frequency2
			   value1 == value2
			   key1 == key2

		-pentru a implementa functia, m-am folosit de functiile implementate
	de mine mai sus


	[removeElement]:
		-calculeaza numarul listei in care ar trebui sa se gaseasca elementul
		-cauta in lista respectiva elementul, iar daca il gaseste, il elimina
	din lista


	[printDictionary]:
		-parcurge vectorul de liste din dictionar
		-printeaza in fisier indicele fiecarei liste iar apoi fiecare element
	din lista


	+[printDictionaryTerminal]:
		-face acelasi lucru cu functia "printDictionary", doar ca in loc sa
	scrie in fisier, afiseaza in terminal
		-folosita pentru debugging
		-am pastrat-o pentru a putea vizualiza mai bine anumite teste


	[get]:
		-pentru implementarea acestei functii m-am folosit de functiile
	add si remove
		-cauta toate elementele cu un anumit key si creeaza o lista dublu
	inlantuita necirculara cu acestea
		-de asemenea, incrementeaza valoarea frecventei tuturor acestor
	elemente in dictionar


	[printValue]:
		-cauta toate elementele cu un anumit value si le printeaza in fisier


	[printFrequency]:
		-cauta toate elementele cu un anumit frequency si le printeaza in fisier


	[unionValues]:
		-creeaza o lista dublu inlantuita necirculara
		-asemenatoare cu functia "printValue", cauta toate elementele cu un
	anumit value, doar ca in loc sa le printeze, le baga in noua lista

	[unionMaxFrequencies]:
		-creeaza o lista dublu inlantuita necirculara
		-parcurge dictionarul, iar la inceputul fiecarei liste calculeaza
	frecventa maxima aferenta acelei liste
		-adauga in lista nou creata elementele ce au "frecventa maxima"

	[reverseLists]:
		-creeaza un nou dictionar, cu elementele din fiecare lista asezate in
	ordine inversa
		-noul dictionar este parcurs in sens normal, in timp ce dictionarul
	luat ca referinta este parcurs in ordine inversa

	[printList]:
		-parcurge o lista dublu inlantuita necirculara si printeaza elementele
	acesteia in fisier


	+[printListTerminal]:
		-face acelasi lucru cu functia "printList", doar ca in loc sa
	scrie in fisier, afiseaza in terminal
		-folosita pentru debugging
		-am pastrat-o pentru a putea vizualiza mai bine anumite teste


	[freeDictionary]:
		-elibereaza toata memoria ocupata de dictionar, cu ajutorul functiei
	"freeList"


	[freeList]:
		-elibereaza memoria ocupata de o lista dublu inlantuita
		-parcurge lista, eliberand element cu element din memorie
		-pentru a nu fi nevoit sa fac inca o functie, am adaugat o conditie de
	verificare pentru ca functia sa poata elibera memoria chiar daca lista este
	circulara
