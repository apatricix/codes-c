#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char nombre[50];
    float precio;
    int cantidadVendida;
} Platillo;

typedef struct
{
    char nombre[50];
    int cantidadPlatillos;
    Platillo *menu;
} Sucursal;


Sucursal *buscarMayorIngreso(Sucursal *sucursales, int totalSucursales);


int main()
{
    int totalSucursales;
    int i, j;

    Sucursal *sucursales;
    Sucursal *mayor;

    printf("GESTION DE FRANQUICIAS\n");

    printf("Cuantas sucursales desea registrar: ");
    scanf("%d", &totalSucursales);

    sucursales =
        (Sucursal *)malloc(totalSucursales * sizeof(Sucursal));

    if (sucursales == NULL)
    {
        printf("No se pudo reservar memoria.\n");
        return 1;
    }

    for (i = 0; i < totalSucursales; i++)
    {
        printf("\nSUCURSAL %d\n", i + 1);

        printf("Nombre de la sucursal: ");
        scanf("%s", (sucursales + i)->nombre);

        printf("Cantidad de platillos: ");
        scanf("%d", &(sucursales + i)->cantidadPlatillos);

        (sucursales + i)->menu =
            (Platillo *)malloc(
                (sucursales + i)->cantidadPlatillos *
                sizeof(Platillo)
            );

        if ((sucursales + i)->menu == NULL)
        {
            printf("No se pudo reservar memoria.\n");
            return 1;
        }

        for (j = 0; j < (sucursales + i)->cantidadPlatillos; j++)
        {
            printf("\nPlatillo %d\n", j + 1);

            printf("Nombre: ");
            scanf("%s",
                  ((sucursales + i)->menu + j)->nombre);

            printf("Precio: ");
            scanf("%f",
                  &((sucursales + i)->menu + j)->precio);

            printf("Cantidad vendida: ");
            scanf("%d",
                  &((sucursales + i)->menu + j)->cantidadVendida);
        }
    }

    mayor = buscarMayorIngreso(
        sucursales,
        totalSucursales
    );

    printf("\nRESULTADOS\n");

    if (mayor != NULL)
    {
        printf("\nSucursal con mayor ingreso: %s\n",mayor->nombre);
    }

    for (i = 0; i < totalSucursales; i++)
    {
        float ingreso = 0;

        for (j = 0;j < (sucursales + i)->cantidadPlatillos;j++)
        {
            ingreso = ingreso +((sucursales + i)->menu + j)->precio *((sucursales + i)->menu + j)->cantidadVendida;
        }

        printf("Ingreso de %s: %.2f\n",(sucursales + i)->nombre,ingreso);
    }

    for (i = 0; i < totalSucursales; i++)
    {
        free((sucursales + i)->menu);
    }

    free(sucursales);

    return 0;
}


/* Funcion que busca la sucursal con mayor ingreso */
Sucursal *buscarMayorIngreso(Sucursal *sucursales,int totalSucursales)
{
    Sucursal *mayor = NULL;

    float ingreso;
    float mayorIngreso = -1;

    int i, j;

    for (i = 0; i < totalSucursales; i++)
    {
        ingreso = 0;

        for (j = 0;j < (sucursales + i)->cantidadPlatillos;j++)
        {
            ingreso = ingreso +((sucursales + i)->menu + j)->precio *((sucursales + i)->menu + j)->cantidadVendida;
        }

        if (ingreso > mayorIngreso)
        {
            mayorIngreso = ingreso;

            mayor = sucursales + i;
        }
    }

    return mayor;
}