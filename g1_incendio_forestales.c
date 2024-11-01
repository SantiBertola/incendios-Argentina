/*
Autores /a: Santino Bertola, Eduardo Ferreyra, Mateo García, Facundo Gordillo, Nicolas Moran
Tema: Incendios en Argentina
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.c" 

int main()
{
	
	struct datos *carga;
	struct provincia *provincias;
	int cant_provincias;
	int cant_cargas;
	
	char opcion = ' ';
	
	do
	{
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
		
		switch (opcion)
		{
		case 'a':
		case 'A':
			// Cargar los datos
			carga = asignar_valores(&cant_cargas);
			// Agrupar por provincia
			provincias = agrupar_por_provincia(carga, cant_cargas, &cant_provincias);
			// Mostrar la cantidad de superficie afectada por provincia
			cant_supAfectada_por_provincia(provincias, cant_provincias);
			printf("\n--------------------------------------------------------------------\n");
			break;
			
		case 'b':
		case 'B':
			carga = asignar_valores(&cant_cargas);
			provincias = agrupar_por_provincia(carga, cant_cargas, &cant_provincias);
			cant_focos_por_provincia(provincias, cant_provincias);
			printf("\n--------------------------------------------------------------------\n");
			break;
			
		case 'c':
		case 'C':
			carga = asignar_valores(&cant_cargas);
			provincias = agrupar_por_provincia(carga, cant_cargas, &cant_provincias);
			top_3_hectareas(provincias, cant_provincias);
			printf("\n--------------------------------------------------------------------\n");
			break;
			
		case 'd':
		case 'D':
			carga = asignar_valores(&cant_cargas);
			provincias = agrupar_por_provincia(carga, cant_cargas, &cant_provincias);
			top_3_focos(provincias, cant_provincias);
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
	
	// Liberar memoria para la carga y provincias si fueron asignadas
	free(carga);
	free(provincias); // Es importante liberar todas las estructuras que uses
	
	return 0;
}

