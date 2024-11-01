#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef PRUEBA_H
#define PRUEBA_H

struct datos
{
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

struct provincia
{
	int provincia_id;
	char nombre_provincia[100];
	float total_sup_afectadas;
	int total_focos;
};

void asignar_memoria(FILE **fp);
struct datos *asignar_valores(int *cant_cargas);
struct provincia *agrupar_por_provincia(struct datos *carga, int cant_cargas, int *cant_provincias);
void cant_supAfectada_por_provincia(struct provincia *provincias, int cant_provincias);
void cant_focos_por_provincia(struct provincia *provincias, int cant_provincias);
void top3_prov_mas_afectadas_por_cant_ha(struct provincia *provincias, int cant_provincias);
void intercambiar(struct provincia *a, struct provincia *b);
void ordenar_por_hectareas(struct provincia *provincias, int cant_provincias);
void ordenar_por_focos(struct provincia *provincias, int cant_provincias);
void top_3_hectareas(struct provincia *provincias, int cant_provincias);
void top_3_focos(struct provincia *provincias, int cant_provincias);

#endif

void asignar_memoria(FILE **fp)
{
	*fp = fopen("focos.csv", "r");
	if (*fp == NULL)
	{
		perror("Imposible abrir el archivo");
		exit(EXIT_FAILURE);
	}
}

struct datos *asignar_valores(int *cant_cargas)
{
	FILE *fp = NULL;
	asignar_memoria(&fp);
	
	char linea[200];
	*cant_cargas = 0;
	
	// Contar cuántas líneas (datos) hay en el archivo
	while (fgets(linea, sizeof(linea), fp))
	{
		(*cant_cargas)++;
	}
	
	// Asignar la memoria exacta
	struct datos *carga = malloc((*cant_cargas) * sizeof(struct datos));
	if (carga == NULL)
	{
		perror("Error al asignar memoria");
		exit(EXIT_FAILURE);
	}
	
	// Volver al inicio del archivo para leer los datos
	rewind(fp);
	
	int index = 0;
	while (fgets(linea, sizeof(linea), fp))
	{
		// Reemplazar coma por punto para decimales
		for (int i = 0; linea[i] != '\0'; i++)
		{
			if (linea[i] == ',')
			{
				linea[i] = '.';
			}
		}
		sscanf(linea, "%d;%99[^;];%d;%99[^;];%d;%99[^;];%f;%9[^;];%d;%d",
			   &carga[index].pais_id,
			   carga[index].pais,
			   &carga[index].provincia_id,
			   carga[index].nombre_provincia,
			   &carga[index].dpto_id,
			   carga[index].nombre_dpto,
			   &carga[index].sup_afectadas,
			   carga[index].unidad_medida,
			   &carga[index].cant_focos,
			   &carga[index].anio);
		index++;
	}
	
	fclose(fp);
	return carga;
}

struct provincia *agrupar_por_provincia(struct datos *carga, int cant_cargas, int *cant_provincias)
{
	struct provincia *provincias = malloc(cant_cargas * sizeof(struct provincia)); // Ajuste: esto podría optimizarse más adelante
	if (provincias == NULL)
	{
		perror("Error al asignar memoria para provincias");
		exit(EXIT_FAILURE);
	}
	
	*cant_provincias = 0;
	for (int i = 0; i < cant_cargas; i++)
	{
		int encontrado = 0;
		for (int j = 0; j < *cant_provincias; j++)
		{
			if (provincias[j].provincia_id == carga[i].provincia_id)
			{
				provincias[j].total_sup_afectadas += carga[i].sup_afectadas;
				provincias[j].total_focos += carga[i].cant_focos;
				encontrado = 1;
				break;
			}
		}
		if (!encontrado)
		{
			provincias[*cant_provincias].provincia_id = carga[i].provincia_id;
			strcpy(provincias[*cant_provincias].nombre_provincia, carga[i].nombre_provincia);
			provincias[*cant_provincias].total_sup_afectadas = carga[i].sup_afectadas;
			provincias[*cant_provincias].total_focos = carga[i].cant_focos;
			(*cant_provincias)++;
		}
	}
	return provincias;
}

void cant_supAfectada_por_provincia(struct provincia *provincias, int cant_provincias)
{
	printf("\nCantidad de superficie afectada por provincia:\n");
	for (int i = 0; i < cant_provincias; i++)
	{
		printf("Provincia: %s, Superficie afectada: %.2f ha\n",
			   provincias[i].nombre_provincia,
			   provincias[i].total_sup_afectadas);
	}
}

void cant_focos_por_provincia(struct provincia *provincias, int cant_provincias)
{
	printf("\nCantidad de focos por provincia:\n");
	for (int i = 0; i < cant_provincias; i++)
	{
		printf("Provincia: %s, Cantidad de focos: %d\n",
			   provincias[i].nombre_provincia,
			   provincias[i].total_focos);
	}
}

// Función para intercambiar dos provincias
void intercambiar(struct provincia *a, struct provincia *b)
{
	struct provincia temp = *a;
	*a = *b;
	*b = temp;
}

// Función para ordenar las provincias por cantidad de hectáreas afectadas
void ordenar_por_hectareas(struct provincia *provincias, int cant_provincias)
{
	for (int i = 0; i < cant_provincias - 1; i++)
	{
		for (int j = 0; j < cant_provincias - i - 1; j++)
		{
			if (provincias[j].total_sup_afectadas < provincias[j + 1].total_sup_afectadas)
			{
				intercambiar(&provincias[j], &provincias[j + 1]);
			}
		}
	}
}

// Funcián para ordenar las provincias por cantidad de focos
void ordenar_por_focos(struct provincia *provincias, int cant_provincias)
{
	for (int i = 0; i < cant_provincias - 1; i++)
	{
		for (int j = 0; j < cant_provincias - i - 1; j++)
		{
			if (provincias[j].total_focos < provincias[j + 1].total_focos)
			{
				intercambiar(&provincias[j], &provincias[j + 1]);
			}
		}
	}
}

// Función para mostrar las 3 provincias más afectadas por cantidad de hectáreas
void top_3_hectareas(struct provincia *provincias, int cant_provincias)
{
	if (cant_provincias < 3)
	{
		printf("\nNo hay suficientes provincias para mostrar el top 3.\n");
		return;
	}
	
	ordenar_por_hectareas(provincias, cant_provincias);
	
	printf("\nLas 3 provincias más afectadas por cantidad de hectáreas afectadas:\n");
	for (int i = 0; i < 3; i++)
	{
		printf("Provincia: %s, Superficie afectada: %.2f ha\n",
			   provincias[i].nombre_provincia,
			   provincias[i].total_sup_afectadas);
	}
}

// Función para mostrar las 3 provincias más afectadas por cantidad de focos de incendio
void top_3_focos(struct provincia *provincias, int cant_provincias)
{
	if (cant_provincias < 3)
	{
		printf("\nNo hay suficientes provincias para mostrar el top 3.\n");
		return;
	}
	
	ordenar_por_focos(provincias, cant_provincias);
	
	printf("\nLas 3 provincias más afectadas por cantidad de focos de incendio:\n");
	for (int i = 0; i < 3; i++)
	{
		printf("Provincia: %s, Focos de incendio: %d\n",
			   provincias[i].nombre_provincia,
			   provincias[i].total_focos);
	}
}
