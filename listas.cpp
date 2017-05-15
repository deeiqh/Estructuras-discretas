#include <iostream>
#include <string>

using namespace std;


struct Celda {
	int valor;
	Celda* next;
};

/* Reads in a list of values from the user and builds a linked list from them.
 * The list is in the reverse order in which the elements were added in.
 */
Celda* readList() {
    Celda* result = NULL;

    while (true) {
        int val;
        cout<<"Next entry? ";
        cin>>val;
        if (val == 0) break;

        /* Create a new cel. */
        Celda* cel = new Celda;
        cel->valor = val;

        /* Prepend it to the list. */
        cel->next = result;
        result = cel;
    }

    return result;
}

/* Recursively reads in a list of values from the user and builds a list out of them.
 * The elements will be in the order in which they were added.
 */
Celda* readListRec() {
        int val;
        cout<<"Next entry? ";
        cin>>val;
        if (val == 0) return NULL;

    /* Recursive Step: Make a new cell with this value, then fill in the rest of
     * the list recursively.
     */
    Celda* result = new Celda;
    result->valor = val;
    result->next = readListRec();
    return result;
}

/* Prints the contents of a linked list in order. */
void printList(Celda* list) {
    for (Celda* cel = list; cel != NULL; cel = cel->next) {
        cout << cel->valor << endl;
    }
}

/* Prints the contents of a linked list recursively. */
void printListRec(Celda* list) {
    /* Base Case: Empty list, nothing to print! */
    if (list == NULL) return;

    /* Recursive Step: Print the first element, then the remaining ones. */
    cout << list->valor << endl;
    printListRec(list->next);
}

int sumOfElementsIn(Celda* lista);
int ultimoElementoDe(Celda* lista);
Celda* concatena(Celda* uno, Celda* dos);
void concatena2(Celda*& uno, Celda* dos);
void ImprimeReversa(Celda* lista);

int main() {
    Celda* lista = readListRec();
    printListRec(lista);

	cout << sumOfElementsIn(lista) << '\n';
	cout << ultimoElementoDe(lista) << '\n';

	Celda* lista2 = readListRec();
	//printListRec(concatena(lista,lista2));

	concatena2(lista,lista2);
	printListRec(lista);
	ImprimeReversa(lista);

    return 0;
}


int sumOfElementsIn(Celda* lista)
{
	if (lista == NULL) 
		return 0;
	else
		return lista->valor + sumOfElementsIn(lista->next);
}

int ultimoElementoDe(Celda* lista)
{
	if (lista != NULL){
		if (lista->next != NULL) 
			return ultimoElementoDe(lista->next);
		return lista->valor;
	}
	cout << "Lista vacia";
}

Celda* concatena(Celda* uno, Celda* dos)
{
	
	Celda* resultado = new Celda;
	Celda* primero = resultado;
	while(uno != NULL){				
			resultado->valor = uno->valor;
			resultado->next = new Celda;
			resultado = resultado->next;
			uno = uno->next;				
	}		
	while(dos != NULL){				
			resultado->valor = dos->valor;
			resultado->next = new Celda;
			resultado = resultado->next;
			dos = dos->next;
	}
	return primero;	
}

void concatena2(Celda*& uno, Celda* dos)
{
	Celda* primero = uno;
	if(uno != NULL){	
		while(uno->next != NULL){
				uno = uno->next;
		}
		uno->next = dos;
	}
	uno = primero;
}

void ImprimeReversa(Celda* lista)
{
	if (lista == NULL) return;
   ImprimeReversa(lista->next);
   cout << lista->valor << '\n';
}























