#include <stdio.h>

#ifndef FUNCIONES_H
#define FUNCIONES_H

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
struct datos* asignar_valores(int *num_focos);
void mostrar(const struct datos *focos, int num_focos);
void mostrar_focos_por_provincia(const struct datos *focos, int num_focos);
void top3_incendios_por_hectareas(const struct datos *focos, int num_focos);


#endif

void asignar_memoria(FILE **fp) {
	*fp = fopen("focos.csv", "r");
	if (*fp == NULL) {
		perror("Imposible abrir el archivo");
		exit(EXIT_FAILURE);
	}
}

struct datos* asignar_valores(int *num_focos) {
	FILE *fp = NULL;
	
	asignar_memoria(&fp);
	
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
	
	fclose(fp);
	
	return focos;
}

void mostrar(const struct datos *focos, int num_focos) {
	printf("Provincia ID\tNombre Provincia\tSup Afectada\n");
	printf("--------------------------------------------------------\n");
	for (int i = 0; i < num_focos; i++) {
		printf("%-12d|\t%-20s|\t%-12.2f|\n", focos[i].provincia_id, focos[i].nombre_provincia, focos[i].sup_afectadas);
	}
}

void mostrar_focos_por_provincia(const struct datos *focos, int num_focos) {
	printf("Provincia ID\tNombre Provincia\tCantidad de Focos\n");
	printf("--------------------------------------------------------\n");
	for (int i = 0; i < num_focos; i++) {
		printf("%-12d|\t%-20s|\t%-12d|\n", focos[i].provincia_id, focos[i].nombre_provincia, focos[i].cant_focos);
	}
}

void top3_incendios_por_hectareas(const struct datos *focos, int num_focos) {
	struct datos focos_copia[num_focos];
	for (int i = 0; i < num_focos; i++) {
		focos_copia[i] = focos[i];
	}
	
	for (int i = 0; i < num_focos - 1; i++) {
		for (int j = 0; j < num_focos - i - 1; j++) {
			if (focos_copia[j].sup_afectadas < focos_copia[j + 1].sup_afectadas) {
				struct datos temp = focos_copia[j];
				focos_copia[j] = focos_copia[j + 1];
				focos_copia[j + 1] = temp;
			}
		}
	}
	
	printf("Provincia ID\tNombre Provincia\tSuperficie Afectada\n");
	printf("--------------------------------------------------------\n");
	for (int i = 0; i < 3 && i < num_focos; i++) {
		printf("%-12d|\t%-20s|\t%-12.2f|\n", 
			   focos_copia[i].provincia_id, 
			   focos_copia[i].nombre_provincia, 
			   focos_copia[i].sup_afectadas);
	}
}
