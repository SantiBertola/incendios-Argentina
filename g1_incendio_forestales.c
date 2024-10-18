/*
Autores /a: Santino Bertola, Eduardo Ferreyra, Mateo Garc�a, Facundo Gordillo, Nicolas Moran 
Tema: Incendios en Argentina
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funciones.c"


int main() {
	
	struct datos *focos;
	int num_focos;
	
	char opcion=' ';
	
	
	do {
		printf("\n--------------------------------------------------------------------\n");
		printf("\nBienvenido/a al dataset oficial de incendios en Argentina:\n");
		printf("\n�Qu� desea investigar hoy?:\n");
		printf("a. Cantidad de superficie afectada por provincia \n");
		printf("b. Cantidad de focos de incendio por provincia \n");
		printf("c. Las 3 provincias m�s afectadas por los incendios por cantidad de hect�reas afectadas\n");
		printf("d. Las 3 provincias m�s afectadas por los incendios por cantidad de focos de incendios\n");
		printf("s. Salir.\n");
		printf("Seleccione una opcion: ");
		scanf(" %c", &opcion);
		getchar();
		
		switch(opcion) {
		case 'a':
		case 'A':
			focos = asignar_valores(&num_focos);
			mostrar(focos, num_focos);
			printf("\n--------------------------------------------------------------------\n");
			
			break;
		case 'b':
		case 'B':
			focos = asignar_valores(&num_focos);
			mostrar_focos_por_provincia(focos, num_focos);
			printf("\n--------------------------------------------------------------------\n");
			
			break;
		case 'c':
		case 'C':
			printf("\n--------------------------------------------------------------------\n");
			
			break;
		case 'd':
		case 'D':
			printf("\n--------------------------------------------------------------------\n");
			
			break;	
		case 's':
		case 'S':
			printf("\n--------------------------------------------------------------------\n");
			printf("Fin del programa.\n");
			break;
		default:
			printf("Opcion no valida. Intente nuevamente.\n");
			break;
		}
	} while (opcion != 's' && opcion != 'S');
	
	free(focos);
	
	return 0;
}


