#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nodo{
    char legislador[11];
    struct Nodo *next;
}nodo;

void inserta(char nombre[], nodo **puntero);
void suprime(char nombre[], nodo **puntero);
void menu();
int miembro(char nombre[], nodo **puntero);
void mostrar(nodo **puntero);

nodo *chicos_buenos = NULL;
nodo *chicos_malos = NULL;

void inserta(char nombre[], nodo **puntero){

    if((*puntero) == NULL){
        nodo *aux = malloc(sizeof(nodo));
        strcpy(aux->legislador, nombre);
        aux->next = NULL;
        (*puntero) = aux;
    }else if(strcmp(nombre, (*puntero)->legislador) < 0){
        nodo *aux = malloc(sizeof(nodo));
        strcpy((aux)->legislador, nombre);
        aux->next = (*puntero)->next;
        (*puntero)->next = aux;
    }else if(strcmp((*puntero)->legislador, nombre) == 0){
        printf("\nEl nombre ya esta cargado.\n");
    }else{
        inserta(nombre, &(*puntero)->next);
    }
}

void suprime(char nombre[], nodo **puntero){

    if((*puntero) == NULL){
        printf("Nombre no existente.\n");
        menu();
    }
    else{
        if(strcmp(nombre, (*puntero)->legislador) == 0){
            nodo *aux = (*puntero);
           (*puntero) = (*puntero)->next;
            free(aux);
            }
            else if((*puntero)->next != NULL && strcmp(nombre, (*puntero)->next->legislador) == 0){
               nodo *aux = (*puntero)->next;
              (*puntero)->next = (*puntero)->next->next;
               free(aux);
            }
            else{
                suprime(nombre, &(*puntero)->next);
            }
        }
        printf("Nombre eliminado.\n");
}

int miembro(char nombre[], nodo **puntero){

    if((*puntero) == NULL){
        printf("Lista vacia, no es un miembro.\n");
        menu();
        return 0;
    }
    if(strcmp(nombre, (*puntero)->legislador) == 0){
        printf("\n%s se encuentra en la lista.\n", nombre);
        return 1;
    }
    return miembro(nombre, &(*puntero)->next);
}

void mostrar(nodo ** puntero){
    if (*puntero != NULL) {
        printf("%s\n", (*puntero)->legislador);
        mostrar(&(*puntero)->next);
    }
}

void menu(){
    char nombre[11];
    char voto;

    while(1){
        printf("\nIngrese 'f' para voto favorable\nIngrese 'd' para voto desfavorable\nIngrese 'b' para eliminiar un legislador de chicos buenos.\nIngrese 'm' para eliminar un legislador de chicos malos.\nIngrese 'v' para verificar si estan los miembros en lista buena.\nIngrese 'n' para verificar si estan los miembros de lista mala.\nIngrese 'e' para salir del programa\n");
        printf("> ");
        scanf(" %c", &voto);

        switch(voto){
            case 'f':
                printf("Ingrese nombre de legislador\n");
                printf("> ");
                scanf(" %s", nombre);
                printf("\nNombre ingresado en chicos buenos\n");
                inserta(nombre, &chicos_buenos);
                break;

            case 'd':
                printf("Ingrese nombre de legislador\n");
                printf("> ");
                scanf(" %s", nombre);
                printf("\nNombre ingresado en chicos malos\n");
                inserta(nombre, &chicos_malos);
                break;

            case 'b':
                printf("Ingrese el nombre que desee eliminar\n");
                printf("> ");
                scanf(" %s", nombre);
                suprime(nombre, &chicos_buenos);
                break;

            case 'm':
                printf("Ingrese el nombre que desea eliminar\n");
                printf("> ");
                scanf(" %s", nombre);
                suprime(nombre, &chicos_malos);
                break;

            case 'v':
                printf("Ingrese el nombre que desee verificar\n");
                printf("> ");
                scanf(" %s", nombre);
                miembro(nombre, &chicos_buenos);
                break;

            case 'n':
                printf("Ingrese el nombre que desee verificar\n");
                printf("> ");
                scanf(" %s", nombre);
                miembro(nombre, &chicos_malos);
                break;

            case 'e':
                printf("\nChicos buenos: \n");
                mostrar(&chicos_buenos);

                printf("\nChicos malos: \n");
                mostrar(&chicos_malos);
                return 0;

            default:
                printf("\nOpcion incorrecta. Ingrese un caracter valido\n");
            }
    }
}

int main(){
    menu();
    return;
}
