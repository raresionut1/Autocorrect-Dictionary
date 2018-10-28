//311CD Constantin Rares
//Tema1 SD

#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// List element for Dictionary lists.
typedef struct ListNode {
	struct ListNode *next;
	struct ListNode *prev;
	char *key;
	char *value;
	int frequency;
} ListNode;

// Dictionary structure that includes the lists of elements and their number.
typedef struct Dictionary {
	ListNode **lists;		// lists of elements.
	int N;					// number of lists.
} Dictionary;

// Double linked list structure
//va fi folosita pentru functia "get"
typedef struct List{ 
	ListNode *first; // link to the first node
	ListNode *last; // link to the last node
} List;

// Initializes an empty Dictionary structure.
Dictionary* createDictionary(int N);

//functie ce intoarce numarul de elemente dintr-o lista din dictionar
int numberOfElementsInList(Dictionary *dictionary, int listNr);

//functie ce intoarce numarul de elemente dintr-un dictionar
int numberOfElementsInDictionary(Dictionary *dictionary);

//functie ce sterge ultimele elemente din fiecare lista din dictionar
void deleteLastElements(Dictionary *dictionary);

// Adds an element to the Dictionary structure.
void addElement(Dictionary *dictionary, char *key, char *value, int frequency);

// Removes an element from the Dictionary structure.
void removeElement(Dictionary *dictionary, char *key, char *value);

// Prints all the elements from all the lists of the Dictionary structure.
void printDictionary(FILE *f, Dictionary *dictionary);

//functie identica cu "printDictionary", doar ca afiseaza in terminal
//folosita pentru debugging
void printDictionaryTerminal(Dictionary *dictionary);

// Gets all the elements with the specified key and increments the frequencies.
ListNode* get(Dictionary *dictionary, char *key);

// Prints all the elements with the specified value.
void printValue(FILE *f, Dictionary *dictionary , char *value);

// Prints all the elements with the specified frequency.
void printFrequency(FILE *f, Dictionary *dictionary , int frequency);

// Returns a list containing the elements with the specified value.
ListNode* unionValues(Dictionary *dictionary, char *value);

// Returns a list containing the elements with maximum frequency in each list.
ListNode* unionMaxFrequencies(Dictionary *dictionary);

// Returns a new Dictionary with reversed lists of the input structure.
Dictionary* reverseLists(Dictionary *dictionary);

// Prints a double-linked non-circular list.
void printList(FILE *f, ListNode *list);

//functie identica cu "printList", doar ca afiseaza in terminal
//folosita pentru debugging
void printListTerminal(ListNode *list);

// Frees all the memory allocated for the Dictionary.
void freeDictionary(Dictionary *dictionary);

// Frees all the memory allocated for a double-linked list.
void freeList(ListNode *list);

//------------------------------------------------------------------------------

// Initializes an empty Dictionary structure.
Dictionary* createDictionary(int N) {
	//alocarea memoriei pentru o structura de tip dictionar
	Dictionary *a = (Dictionary*)calloc(1, sizeof(Dictionary));

	//verificare alocare
	if(a == NULL)
		return NULL;

	//numarul de elemente din vectorul de liste
	a->N = N;

	//alocarea memoriei pentru vectorul de liste
	a->lists = (ListNode**)calloc(N, sizeof(ListNode*));

	//verificare alocare
	if(a->lists == NULL){
		free(a);
		return NULL;
	}

	return a;
}
	
//functie ce intoarce numarul de elemente dintr-o lista din dictionar
int numberOfElementsInList(Dictionary *dictionary, int listNr){
	int n, nr = 0;

	//numarul de elemente din vectorul de liste
	n = dictionary->N;

	//output de eroare in cazul in care este introdus un indice gresit
	if((listNr >= n) || (listNr < 0)){
		printf("Lista cu indicele introdus nu exista.\n");
		return -1;
	}

	//lista respectiva
	ListNode *node = dictionary->lists[listNr];

	//caz de lista goala
	if(!node)
		return 0;

	//calculul numarului de elemente din lista
	else
		do{
			nr++;
			node = node->next;

		//conditia de oprire: parcurgerea unui ciclu intreg al listei
		}  while (node != dictionary -> lists[listNr]);

return nr;

}

//functie ce intoarce numarul de elemente dintr-un dictionar
int numberOfElementsInDictionary(Dictionary *dictionary){
	int i, n, nr = 0;

	//numarul de elemente din vectorul de liste
	n = dictionary->N;

	//calculul numarului de elemente din dictionar
	for(i = 0; i < n; i++)
		//calculul numarului de elemente din lista curenta
		nr = nr + numberOfElementsInList(dictionary, i);

	return nr;
}

//functie ce sterge ultimele elemente din fiecare lista din dictionar
void deleteLastElements(Dictionary *dictionary){
	int i, n;

	//numarul de elemente din vectorul de liste
	n = dictionary->N;

	//un element de lista
	ListNode *node;

	//parcurgerea fiecarei liste
	for(i = 0; i < n; i++){

		//lista curenta
		node = dictionary->lists[i];

		//verificarea daca lista este goala
		if(node){
			//cazul in care este 1 singur element in lista
			if(numberOfElementsInList(dictionary, i) == 1){

				node->next = NULL;
				node->prev = NULL;
				//eliberarea memoriei
				free(node);

				dictionary->lists[i] = NULL;
			}
			//cazul general
			else{
				//ultimul element din lista
				ListNode *aux = node->prev;

				//modificarea pointerilor vecinilor elementului
				//ce va urma sa fie eliminat
				aux->prev->next = aux->next;
				aux->next->prev = aux->prev;

				aux->prev = NULL;
				aux->next = NULL;
				//eliberarea memoriei
				free(aux);
			}

		}

	}
	
}

// Adds an element to the Dictionary structure.
void addElement(Dictionary *dictionary, char *key, char *value, int frequency) {
	int r = 0, i, n, exista = 0, ok;

	//numarul de elemente din vectorul de liste
	n = dictionary->N;

	//calculul indicelui listei in care trebuie adaugat elementul
	for (i = 0; i < strlen(key); i++)
		r = r + key[i];
	
	r = r % n;

	//lista in care trebuie adaugat elementul
	ListNode *node = dictionary->lists[r];

	//cazul in care lista este goala
	if(!node){
		//verificarea limitei de memorie a dictionarului
		if(numberOfElementsInDictionary(dictionary) >= 2*n)
			deleteLastElements(dictionary);

		//alocarea memoriei pentru noul element
		node = calloc(1, sizeof(ListNode));

		//verificarea alocarii
		if(!node)
			return;

		//atribuirea valorilor elementului
		node->key = key;
		node->value = value;
		node->frequency = frequency;

		//atribuirea pointerilor elementului
		node->next = node;
		node->prev = node;

		//setarea primului element din lista
		dictionary->lists[r] = node;

		return;
	}
	//cazul in care lista nu este goala
	else
		//parcurgerea listei
		do {
			//verificarea daca elementul exista deja in dictionar
			if((strcmp(node->key, key) == 0) &&
			   (strcmp(node->value, value) == 0)){

				//calculul noii frecvente a elementului
			   	int new_frequency = node->frequency + frequency;

				//modificarea pozitiei elementului in lista
				removeElement(dictionary, key, value);
				addElement(dictionary, key, value, new_frequency);

				//indica faptul ca elementul exista deja in lista
				exista = 1;
				break;
			}

			//elementul urmator din lista
			node = node->next;

		//conditia de oprire: parcurgerea unui ciclu intreg al listei
		} while (node != dictionary->lists[r]);

		//cazul in care elementul nu exista inainte in dictionar
		if(exista == 0){

			//alocarea memoriei pentru noul element
			ListNode *a = calloc(1, sizeof(ListNode));

			//verificarea alocarii
			if(!a)
				return;

			//atribuirea valorilor elementului
			a->key = key;
			a->value = value;
			a->frequency = frequency;

			//lista in care trebuie adaugat elementul
			node = dictionary->lists[r];

			//va fi folosit pentru a sti daca elementul va fi adaugat
			//pe ultima pozitie sau nu
			ok = 0;

			//parcurgerea listei
			do{	
				//verificarea daca frecventele sunt egale
				if(node->frequency == frequency){

					//verificarea daca campurile "value" sunt egale
					if(strcmp(node->value, value) == 0){
						
						//cazul in care frecventele sunt egale, campurile
						//"value" sunt egale, dar campurile "key"
						//sunt diferite
						if(strcmp(node->key, key) > 0){
							//indica faptul ca elementul nu trebuie
							//adaugat ultimul in lista
							ok = 1;

							//oprirea cautarii
							break;
						}
						
						else{
							//elementul urmator
							node = node->next;

							//continuarea cautarii
							continue;
						}		
					}

					//cazul in care frecventele sunt egale, dar
					//campurile "value" sunt diferite
					if(strcmp(node->value, value) > 0){
						//indica faptul ca elementul nu trebuie
						//adaugat ultimul in lista
						ok = 1;

						//oprirea cautarii
						break;
					}

					else{
						//elementul urmator
						node = node->next;

						//continuarea cautarii
						continue;
					}
				}

				//cazul in care frecventele sunt diferite
				if(node->frequency < frequency){
					//indica faptul ca elementul nu trebuie
					//adaugat ultimul in lista
					ok = 1;

					//oprirea cautarii
					break;
				}

				else{
					//elementul urmator
					node = node->next;

					//continuarea cautarii
					continue;
				}
			
			//conditia de oprire: parcurgerea unui ciclu intreg al listei
			} while (node != dictionary->lists[r]);

			//verificarea limitei de memorie a listei
			if(numberOfElementsInList(dictionary, r) >= n){
				//ultimul element din lista
				ListNode *aux = dictionary->lists[r]->prev;

				//cazul in care elementul ce trebuie adaugat trebuie sa
				//fie asezat in locul elementului ce va fi eliminat
				if(aux == node){

					//cazul in care elementul ce va fi eliminat este
					//singurul din lista
					if(numberOfElementsInList(dictionary, r) == 1){

						//eliminarea ultimului element din lista
						free(aux);

						//atribuirea pointerilor noului element
						a->next = a;
						a->prev = a;

						//setarea primului element din lista
						dictionary->lists[r] = a;

						return;
					}

					//indica faptul ca elementul trebuie adaugat ultimul
					//in lista
					ok = 0;

					//schimbarea pozitiei de adaugare a noului element,
					//deoarece pozitia actuala nu mai exista (a fost eliminata
					//din memorie)
					node = node->next;
				}

				//setarea pointerilor vecinilor elementului ce va fi eliminat
				dictionary->lists[r]->prev = aux->prev;
				aux->prev->next = dictionary->lists[r];

				//eliminarea ultimului element din lista
				free(aux);
			}
			else
				//verificarea limitei de memorie a dictionarului
				if(numberOfElementsInDictionary(dictionary) >= 2*n){
					
					//ultimul element din lista in care va trebui adaugat
					//noul element
					ListNode *aux = dictionary->lists[r]->prev;

					//cazul in care elementul ce trebuie adaugat trebuie sa
					//fie asezat in locul unui element ce va fi eliminat
					if(aux == node){

						//cazul in care elementul ce va fi eliminat este
						//singurul din lista 
						if(numberOfElementsInList(dictionary, r) == 1){

							//eliminarea ultimelor elemente din fiecare lista
							deleteLastElements(dictionary);

							//atribuirea pointerilor noului element
							a->next = a;
							a->prev = a;

							//setarea primului element din lista
							dictionary->lists[r] = a;

							return;
						}

					//indica faptul ca elementul trebuie adaugat ultimul
					//in lista
					ok = 0;

					//schimbarea pozitiei de adaugare a noului element,
					//deoarece pozitia actuala nu mai exista (a fost eliminata
					//din memorie)
					node = node->next;
					}

				//eliminarea ultimelor elemente din fiecare lista
				deleteLastElements(dictionary);
					
				}

				//setarea pointerilor noului element
				a->next = node;
				a->prev = node->prev;

				//schimbarea pointerilor vecinilor noului element
				node->prev->next = a;
				node->prev = a;

				//modificarea primului element din lista, in cazul in care
				//elementul a fost adaugat pe prima pozitie
				if((node == dictionary->lists[r]) && (ok == 1)){
					dictionary->lists[r] = a;
				}
		}

    return;
}

// Removes an element from the Dictionary structure.
void removeElement(Dictionary *dictionary, char *key, char *value) {
	int r = 0, i, n;

	//numarul de elemente din vectorul de liste
	n = dictionary->N;

	//calculul indicelui listei in care se afla elementul ce trebuie eliminat
	for (i = 0; i < strlen(key); i++){
	r = r + key[i];
	}
	r = r % n;

	//lista in care trebuie adaugat elementul
	ListNode *node = dictionary->lists[r];

	//cazul in care lista este goala
	if(!node)
		return;

	//parcurgerea listei
	do {
		//verificarea daca elementul curent este cel ce trebuie eliminat
		if((strcmp(node->key, key) == 0) &&
		   (strcmp(node->value, value) == 0)){

			ListNode *aux = node;

			//verificarea daca elementul ce trebuie eliminat 
			//este primul in lista
			if(node == dictionary->lists[r]){

				//cazul in care elementul ce trebuie eliminat 
				//este singurul in lista
				if(numberOfElementsInList(dictionary, r) == 1){

					node->next = NULL;
					node->prev = NULL;

					dictionary->lists[r] = NULL;

					//eliberarea elementului din dictionar
					free(node);

					//oprirea cautarii
					break;
				}

				//cazul in care elementul ce trebuie eliminat
				//este primul in lista, dar nu este singurul in lista
				else{
					//modificarea pointerilor vecinilor elementului
					//ce va fi eliminat
					node->next->prev = node->prev;
					node->prev->next = node->next;

					//setarea primului element din lista
					dictionary->lists[r] = node->next;

					//eliberarea elementului din dictionar
					free(aux);

					//oprirea cautarii
					break;
				}
			}
			
			//modificarea pointerilor vecinilor elementului
			//ce va fi eliminat
			node->next->prev = node->prev;
			node->prev->next = node->next;

			//eliberarea elementului din dictionar
			free(aux);

			//oprirea cautarii
			break;
		}

		//urmatorul element
		node = node->next;

		//conditia de oprire: parcurgerea unui ciclu intreg al listei
		} while (node != dictionary->lists[r]);

return;
}

// Prints all the elements from all the lists of the Dictionary structure.
void printDictionary(FILE *f, Dictionary *dictionary) {
	int i, n;

	//numarul de elemente din vectorul de liste
	n = dictionary->N;

	//parcurgerea listei
	for(i = 0; i < n; i++){

		//printarea numarului listei curente
		fprintf(f, "List %d: ", i);

		//lista curenta
		ListNode *node = dictionary->lists[i];

		//cazul in care lista curenta este goala
		if(node)
			//parcurgerea listei
			do{
				//printarea elementului curent
				fprintf(f, "(%s, %s, %d) ", node->key,
			 								node->value,
											node->frequency);

				//elementul urmator
				node = node->next;

			//conditia de oprire: parcurgerea unui ciclu intreg al listei
			} while (node != dictionary->lists[i]);

		//enterul de la capat de rand
		fprintf(f, "\n");
	}
		
	return;
}

//functie identica cu "printDictionary", doar ca afiseaza in terminal
//folosita pentru debugging
void printDictionaryTerminal(Dictionary *dictionary) {
	int i, n;

	//numarul de elemente din vectorul de liste
	n = dictionary->N;

	//parcurgerea listei
	for(i = 0; i < n; i++){

		//printarea numarului listei curente
		printf("List %d: ", i);

		//lista curenta
		ListNode *node = dictionary->lists[i];

		//cazul in care lista curenta este goala
		if(node)
			//parcurgerea listei
			do{
				//printarea elementului curent
				printf("(%s, %s, %d) ", node->key,
			 							node->value,
										node->frequency);

				//elementul urmator
				node = node->next;

			//conditia de oprire: parcurgerea unui ciclu intreg al listei
			} while (node != dictionary->lists[i]);

		//enterul de la capat de rand
		printf("\n");
	}
		
	return;
}

// Gets all the elements with the specified key and increments the frequencies.
ListNode* get(Dictionary *dictionary, char *key) {
	int i, n, r = 0;

	//numarul de elemente din vectorul de liste
	n = dictionary->N;

	//alocarea unei structuri de tip lista dublu inlantuita
	List *a = calloc(1, sizeof(List));

	//verificarea alocarii
	if(!a)
		return NULL;

	//calculul indicelui listei in care se afla elementele cautate
	for (i = 0; i < strlen(key); i++)
		r = r + key[i];
	
	r = r % n;

	//lista in care se afla elementele cautate
	ListNode *node = dictionary->lists[r];

	//cazul in care lista este goala
	if(!node){
		//eliberarea memoriei pentru structura de tip lista dublu inlantuita
		free(a);

		return NULL;
	}

	//parcurgerea listei
	do{
		//verificarea daca elementul curent are campul "key" identic
		//cu cel cautat
		if(strcmp(node->key, key) == 0){
			//alocarea memoriei pentru un element de lista
			ListNode *aux = calloc(1, sizeof(ListNode));

			//verificarea alocarii
			if(!aux){
				//eliberarea memoriei pentru intreaga lista
				freeList(a->first);

				return NULL;
			}

			//atribuirea valorilor elementului din noua lista
			aux->key = node->key;
			aux->value = node->value;
			aux->frequency = node->frequency;

			//verificarea daca lista este goala
			if(!a->first){
				//atribuirea pointerilor primului element
				a->first = aux;
				a->last = aux;
			}

			else{
				//atribuirea pointerilor elementului curent si
				//elementului precedent
				a->last->next = aux;
				aux->prev = a->last;
				a->last = aux;
			}
		}
		
		//elementul urmator
		node = node->next;

	//conditia de oprire: parcurgerea unui ciclu intreg al listei
	} while (node != dictionary->lists[r]);
	
	//primul element din noua lista
	node = a->first;

	//parcurgerea listei
	while(node){
		//adaugarea elementului din lista din dictionar in noua lista
		addElement(dictionary, node->key, node->value, 1);

		//elementul urmator
		node = node->next;
	}

	//primul element din noua lista
	ListNode *lista = a->first;

	//eliberarea memoriei pentru structura de tip lista dublu inlantuita
	free(a);

	return lista;
}

// Prints all the elements with the specified value.
void printValue(FILE *f, Dictionary *dictionary , char *value) {
	int i, n;

	//numarul de elemente din vectorul de liste
	n = dictionary->N;

	//parcurgerea dictionarului
	for(i = 0; i < n; i++){

		//primul element din lista curenta
		ListNode *node = dictionary->lists[i];

		//verificarea daca lista este goala
		if(!node)
			//urmatoarea lista
			continue;

		//parcurgerea listei
		do{
			//verificarea daca elementul curent are campul "value" identic
			//cu cel cautat
			if(strcmp(node->value, value) == 0)
				//printarea elementului
				fprintf(f, "(%s, %s, %d) ", node->key,
			 								node->value,
											node->frequency);

			//elementul urmator
			node = node->next;

		//conditia de oprire: parcurgerea unui ciclu intreg al listei
		} while (node != dictionary->lists[i]);
	}

	//enterul de la capat de rand
	fprintf(f, "\n");

	return;
}

// Prints all the elements with the specified frequency.
void printFrequency(FILE *f, Dictionary *dictionary , int frequency) {
	int i, n;

	//numarul de elemente din vectorul de liste
	n = dictionary->N;

	//parcurgerea dictionarului
	for(i = 0; i < n; i++){

		//primul element din lista curenta
		ListNode *node = dictionary->lists[i];

		//verificarea daca lista este goala
		if(node)	
			//parcurgerea listei
			do{
				//verificarea daca elementul curent are frecventa egala cu
				//cu frecventa cautata
				if(node->frequency == frequency)
					//printarea elementului
					fprintf(f, "(%s, %s, %d) ",  node->key,
			 									node->value,
												node->frequency);

				//elementul urmator
				node = node->next;

			//conditia de oprire: parcurgerea unui ciclu intreg al listei
			} while (node != dictionary->lists[i]);
	}

	//enterul de la capat de rand
	fprintf(f, "\n");

	return;
}

// Returns a list containing the elements with the specified value.
ListNode* unionValues(Dictionary *dictionary, char *value) {
	int i, n;

	//numarul de elemente din vectorul de liste
	n = dictionary->N;

	//alocarea unei structuri de tip lista dublu inlantuita
	List *a = calloc(1, sizeof(List));

	//verificarea alocarii
	if(!a)
		return NULL;

	//parcurgerea dictionarului
	for(i = 0; i < n; i++){

		//primul element din lista curenta
		ListNode *node = dictionary->lists[i];

		//verificarea daca lista este goala
		if(!node)
			//urmatoarea lista
			continue;

		//parcurgerea listei
		do{	
			//verificarea daca elementul curent are campul "value" identic
			//cu cel cautat
			if(strcmp(node->value, value) == 0){

				//alocarea unui element din noua lista
				ListNode *aux = calloc(1, sizeof(ListNode));

				//verificarea alocarii
				if(!aux){
					//eliberarea memoriei listei
					freeList(a->first);

					return NULL;
				}

				//atribuirea valorilor elementului
				aux->key = node->key;
				aux->value = node->value;
				aux->frequency = node->frequency;

				//cazul in care elementul adaugat va fi primul din noua lista
				if(!a->first){
					//setarea pointerilor elementului
					a->first = aux;
					a->last = aux;
				}

				//cazul in care elementul adaugat nu va fi primul din lista
				else{
					//setarea pointerilor elementului adaugat
					//si a elementului anterior din lista
					a->last->next = aux;
					aux->prev = a->last;
					a->last = aux;
				}
			}
				
			//urmatorul element
			node = node->next;

		//conditia de oprire: parcurgerea unui ciclu intreg al listei
		} while (node != dictionary->lists[i]);
	}

	//folosit pentru a putea elibera memoria ocupata de
	//structura de tip lista dublu inlantuita
	ListNode *lista = a->first;

	//eliberarea memoriei pentru structura de tip lista dublu inlantuita
	free(a);

	return lista;
}

// Returns a list containing the elements with maximum frequency in each list.
ListNode* unionMaxFrequencies(Dictionary *dictionary) {
	int i, n;

	//numarul de elemente din vectorul de liste
	n = dictionary->N;

	//alocarea unei structuri de tip lista dublu inlantuita
	List *a = calloc(1, sizeof(List));

	//verificarea alocarii
	if(!a)
		return NULL;

	//parcurgerea dictionarului
	for(i = 0; i < n; i++){

		//primul element din lista curenta
		ListNode *node = dictionary->lists[i];

		//verificarea daca lista este goala
		if(!node)
			//urmatoarea lista
			continue;

		//frecventa maxima din lista curenta
		int max_frequency = node->frequency;

		//parcurgerea listei
		do{
			//verificarea daca elementul curent are frecventa egala cu
			//cu frecventa cautata
			if(node->frequency != max_frequency)
				//urmatoarea lista (deoarece nu mai exista elemente cu
				//frecventa maxima in lista curenta)
				break;

			//alocarea unui element din noua lista
			ListNode *aux = calloc(1, sizeof(ListNode));

			//verificarea alocarii
			if(!aux){
				//eliberarea memoriei listei
				freeList(a->first);

				return NULL;
			}

			//atribuirea valorilor elementului
			aux->key = node->key;
			aux->value = node->value;
			aux->frequency = node->frequency;

			//cazul in care elementul adaugat va fi primul din noua lista
			if(!a->first){
				//setarea pointerilor elementului
				a->first = aux;
				a->last = aux;
			}

			//cazul in care elementul adaugat nu va fi primul din lista
			else{
				//setarea pointerilor elementului adaugat
				//si a elementului anterior din lista
				a->last->next = aux;
				aux->prev = a->last;
				a->last = aux;
			}
			
			//urmatorul element
			node = node->next;

		//conditia de oprire: parcurgerea unui ciclu intreg al listei
		} while (node != dictionary->lists[i]);
	}

	//folosit pentru a putea elibera memoria ocupata de
	//structura de tip lista dublu inlantuita
	ListNode *lista = a->first;

	//eliberarea memoriei pentru structura de tip lista dublu inlantuita
	free(a);

	return lista;
}

// Returns a new Dictionary with reversed lists of the input structure.
Dictionary* reverseLists(Dictionary *dictionary) {
	int i, n;

	//numarul de elemente din vectorul de liste
	n =  dictionary->N;

	//crearea unui nou dictionar
	Dictionary *a = createDictionary(n);

	//verificarea alocarii dictionarului
	if(!a)
		return NULL;
	
	//parcurgerea vechiului dictionar
	for(i = 0; i < n; i++){

		//numarul de elemente din lista curenta
		int nr = numberOfElementsInList(dictionary, i);

		int j;

		//verificarea daca lista este goala
		if(!nr)
			continue;

		//alocarea unui element de lista din noul dictionar
		a->lists[i] = calloc(1, sizeof(ListNode));

		//verificarea alocarii
		if(!a->lists[i]){

			//eliberarea memoriei dictionarului
			freeDictionary(a);

			return NULL;
		}

		//lista curenta din noul dictionar
		ListNode *node_a = a->lists[i];

		//setarea pointerilor elementului
		node_a->next = node_a;
		node_a->prev = node_a;

		//alocarea listei curente din noul dictionar
		for(j = 1; j < nr; j++){

			//alocarea unui element de lista din noul dictionar
			ListNode *aux = calloc(1, sizeof(ListNode));

			//verificarea alocarii
			if(!aux){
				//eliberarea memoriei dictionarului
				freeDictionary(a);

				return NULL;
			}
			
			//setarea pointerilor elementelor din lista;
			node_a->next = aux;
			a->lists[i]->prev = aux;

			aux->next = a->lists[i];
			aux->prev = node_a;

			node_a = aux;
		}                

		node_a = a->lists[i];

		//verificarea daca lista curenta este goala
		if(!dictionary->lists[i])
			//urmatoarea lista
			continue;

		ListNode *node = dictionary->lists[i]->prev;

		//parcurgerea celor doua liste:
		//lista cea noua este parcursa de la stanga la dreapta, in timp ce
		//lista din dictionar este parcursa de la dreapta la stanga
		do{ 
			//copierea valorilor elementului
			node_a->key = node->key;
			node_a->value = node->value;
			node_a->frequency = node->frequency;

			//setarea pointerilor elementului
			node = node->prev;
			node_a = node_a->next;

		//conditia de oprire: parcurgerea unui ciclu intreg al listei
		} while (node != dictionary->lists[i]->prev);
	}

	return a;
}

// Prints a double-linked non-circular list.
void printList(FILE *f, ListNode *list) {

	ListNode *node = list;

	//parcurgerea listei
	while(node){

		//printarea unui element
		fprintf(f, "(%s, %s, %d) ", node->key,
			 						node->value,
									node->frequency);

		//urmatoarul element
		node = node->next;
	}

	//enterul de la capat de rand
	fprintf(f, "\n");

	return;
}

//functie identica cu "printList", doar ca afiseaza in terminal
//folosita pentru debugging
void printListTerminal(ListNode *list) {
	
	ListNode *node = list;

	//parcurgerea listei
	while(node){

		//printarea unui element
		printf("(%s, %s, %d) ", node->key,
			 						node->value,
									node->frequency);

		//urmatoarul element
		node = node->next;
	}

	//enterul de la capat de rand
	printf("\n");

	return;
}

// Frees all the memory allocated for the Dictionary.
void freeDictionary(Dictionary *dictionary) {
	int i, n;

	//numarul de elemente din vectorul de liste
	n = dictionary->N;

	//parcurgerea dictionarului
	for(i = 0; i < n; i++)
		//eliberarea listei curente din dictionar
		freeList(dictionary->lists[i]);

	//eliberarea vectorului de liste
	free(dictionary->lists);

	//eliberarea dictionarului
	free(dictionary);

	return;
}

// Frees all the memory allocated for a double-linked list.
void freeList(ListNode *list) {

	//cazul in care lista este goala
	if(!list){
		free(list);
		return;
	}

	//cazul in care lista este circulara
	if(list->prev){
		//transformarea listei intr-o lista necirculara
		list->prev->next = NULL;
		list->prev = NULL;
	}
		
	//primul element din lista
	ListNode *a = list;
	ListNode *b;

	//parcurgerea listei
	while(a){
		b = a->next;
		//eliberarea memoriei pentru elementul
		free(a);
		a = b;
	}

	list = NULL;

	return;
}

#endif