#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char nombre[50];
    float pesoEquipaje;
} Pasajero;

typedef struct
{
    int identificador;
    int totalPasajeros;
    Pasajero *pasajeros;
} Vuelo;

int *filtrarVuelos(Vuelo *vuelos, int totalVuelos, int *cantidadFiltrados);

int main()
{
    int totalVuelos;
    int i, j;
    int cantidadFiltrados;

    Vuelo *vuelos;
    int *vuelosFiltrados;

    printf("SISTEMA DE EQUIPAJE EN AEROLINEA\n\n");

    printf("Cuantos vuelos desea registrar: ");
    scanf("%d", &totalVuelos);

    vuelos = (Vuelo *)malloc(totalVuelos * sizeof(Vuelo));

    if (vuelos == NULL)
    {
        printf("No se pudo reservar memoria.\n");
        return 1;
    }

    /* Captura de los vuelos */
    for (i = 0; i < totalVuelos; i++)
    {
        printf("\nVUELO %d \n", i + 1);

        printf("Identificador del vuelo: ");
        scanf("%d", &(vuelos + i)->identificador);

        printf("Numero de pasajeros: ");
        scanf("%d", &(vuelos + i)->totalPasajeros);

        (vuelos + i)->pasajeros =
            (Pasajero *)malloc(
                (vuelos + i)->totalPasajeros * sizeof(Pasajero));

        if ((vuelos + i)->pasajeros == NULL)
        {
            printf("No se pudo reservar memoria.\n");
            return 1;
        }

        for (j = 0; j < (vuelos + i)->totalPasajeros; j++)
        {
            printf("\nPasajero %d\n", j + 1);

            printf("Nombre: ");
            scanf("%s", ((vuelos + i)->pasajeros + j)->nombre);

            printf("Peso del equipaje: ");
            scanf("%f",
                  &((vuelos + i)->pasajeros + j)->pesoEquipaje);
        }
    }

    /* Filtrar vuelos */
    vuelosFiltrados =
        filtrarVuelos(vuelos, totalVuelos, &cantidadFiltrados);

    /* Mostrar resultados */
    printf("\nVUELOS QUE EXCEDEN LOS 25 KG\n");

    if (cantidadFiltrados == 0)
    {
        printf("No hay vuelos que excedan los 25 kg.\n");
    }
    else
    {
        for (i = 0; i < cantidadFiltrados; i++)
        {
            printf("Vuelo infractor: %d\n",
                   *(vuelosFiltrados + i));
        }
    }

    free(vuelosFiltrados);

    for (i = 0; i < totalVuelos; i++)
    {
        free((vuelos + i)->pasajeros);
    }

    free(vuelos);

    return 0;
}

int *filtrarVuelos(Vuelo *vuelos, int totalVuelos, int *cantidadFiltrados)
{
    int *filtrados = NULL;
    int *temporal;

    int i, j;
    int infractor;

    *cantidadFiltrados = 0;

    for (i = 0; i < totalVuelos; i++)
    {
        infractor = 0;

        for (j = 0; j < (vuelos + i)->totalPasajeros; j++)
        {
            if (((vuelos + i)->pasajeros + j)->pesoEquipaje > 25)
            {
                infractor = 1;
            }
        }

        if (infractor == 1)
        {
            temporal = (int *)realloc(
                filtrados,
                (*cantidadFiltrados + 1) * sizeof(int));

            if (temporal == NULL)
            {
                free(filtrados);
                return NULL;
            }

            filtrados = temporal;

            *(filtrados + *cantidadFiltrados) =
                (vuelos + i)->identificador;

            *cantidadFiltrados = *cantidadFiltrados + 1;
        }
    }

    return filtrados;
}