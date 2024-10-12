/*
Autores /a: Santino Bertola, Eduardo Ferreyra, Mateo García, Facundo Gordillo, Nicolas Moran 
Tema: Incendios en Argentina
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



int main() {
	
	char opcion=' ';
	
	
	do {
		printf("\n--------------------------------------------------------------------\n");
		printf("\nBienvenido/a al dataset oficial de incendios en Argentina:\n");
		printf("\n¿Qué desea investigar hoy?:\n");
		printf("a. Cantidad de superficie afectada por provincia \n");
		printf("b. Cantidad de focos de incendio por provincia \n");
		printf("c. Las 3 provincias más afectadas por los incendios por cantidad de hectáreas afectadas\n");
		printf("d. Las 3 provincias más afectadas por los incendios por cantidad de focos de incendios\n");
		printf("s. Salir.\n");
		printf("Seleccione una opcion: ");
		scanf(" %c", &opcion);
		getchar();
		
		switch(opcion) {
		case 'a':
		case 'A':
			printf("\n--------------------------------------------------------------------\n");
			
			break;
		case 'b':
		case 'B':
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
	
	
	
	return 0;
}


