/*
Autores /a: Santino Bertola, Eduardo Ferreyra, Mateo García, Facundo Gordillo, Nicolas Moran 
Tema: Incendios en Argentina
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct datos {
	int pais_id;
	char pais[100];
	int provincia_id;
	char nombre_provincia[100];
	int dpto_id;
	char nombre_dpto[100];
	float sup_afectadas;
	char unidad_medida[10];
	int cant_focos;
	int anio;
};

void asignar_memoria(FILE **fp);
struct datos* asignar_valores(FILE *fp, int *num_focos);
void mostrar(const struct datos *focos, int num_focos);



int main() {
	
	struct datos *focos;
	FILE *fp;
	int num_focos;
	
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
			asignar_memoria(&fp);
			focos = asignar_valores(fp, &num_focos);
			fclose(fp);
			mostrar(focos, num_focos);
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
	
	free(focos);
	
	return 0;
}

void asignar_memoria(FILE **fp) {
	*fp = fopen("focos.csv", "r");
	if (*fp == NULL) {
		perror("Imposible abrir el archivo");
		exit(EXIT_FAILURE);
	}
}

struct datos* asignar_valores(FILE *fp, int *num_focos) {
	char linea[200];
	int tamano = 10;
	struct datos *focos = malloc(tamano * sizeof(struct datos));
	if (focos == NULL) {
		perror("Error al asignar memoria");
		exit(EXIT_FAILURE);
	}
	
	*num_focos = 0;
	
	fgets(linea, sizeof(linea), fp);
	
	while (fgets(linea, sizeof(linea), fp)) {
		if (*num_focos >= tamano) {
			tamano *= 2;
			struct datos *temp = realloc(focos, tamano * sizeof(struct datos));
			if (temp == NULL) {
				perror("Error al reasignar memoria");
				free(focos);
				exit(EXIT_FAILURE);
			}
			focos = temp;
		}
		sscanf(linea, "%d;%99[^;];%d;%99[^;];%d;%99[^;];%f;%9[^;];%d;%d",
			   &focos[*num_focos].pais_id,
			   focos[*num_focos].pais,
			   &focos[*num_focos].provincia_id,
			   focos[*num_focos].nombre_provincia,
			   &focos[*num_focos].dpto_id,
			   focos[*num_focos].nombre_dpto,
			   &focos[*num_focos].sup_afectadas,
			   focos[*num_focos].unidad_medida,
			   &focos[*num_focos].cant_focos,
			   &focos[*num_focos].anio);
		(*num_focos)++;
	}
	
	return focos;
}


void mostrar(const struct datos *focos, int num_focos) {
	printf("Provincia ID\tNombre Provincia\tSup Afectada\n");
	printf("-----------------------------------------------------\n");
	for (int i = 0; i < num_focos; i++) {
		printf("%-12d|\t%-20s|\t%-12.2f|\n", focos[i].provincia_id, focos[i].nombre_provincia, focos[i].sup_afectadas);
	}
}




