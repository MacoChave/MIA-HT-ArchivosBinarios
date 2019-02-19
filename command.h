#ifndef COMMAND_H
#define COMMAND_H
#include "lectura.h"

int getIndex (int edad)
{
    if (edad > 0 && edad <= 25)
        return 0;
    else if (edad > 25 && edad <= 50)
        return 26;
    else if (edad > 50 && edad <= 75)
        return 51;
    else
        return 76;    
}

void ver ()
{
    Persona * personas;
    personas = obtenerPersonas();
    
    if (personas == NULL)
        return;

    printf("************************************\n");
    for(int i = 0; i < 100; i++)
    {
        printf("------------------------------------\n");
        if (personas[i].edad > 0)
        {
            printf("* nombre: %s\n", personas[i].nombre);
            printf("* edad: %d\n", personas[i].edad);
        }
        printf("------------------------------------\n");
    }
    printf("************************************\n");
}

/*
 * OBTENER LA PERSONA, SI NO EXISTE SALIR
 * BUSCAR EL INDICE DE LA PERSONA
 * ACTUALIZAR CON LA PERSONA VACÍA
 */
void eliminar ()
{
    char nombre[25];
    int edad = 0;

    memset(nombre, 0, sizeof(nombre));
    printf("* Nombre:\n");
    strcpy(nombre, readline());
    printf("* Edad:\n");
    edad = atoi(readline());

    Persona p;
    memset(p.nombre, 0, sizeof(p.nombre));
    strcpy(p.nombre, nombre);
    p.edad = edad;

    /* DELETE PERSONA */
    int i = getIndex(edad);
    int index = obtenerIndicePersona(p, i);
    
    if (index > 100)
    {
        printf("* ERROR: Persona no existe\n");
        return;
    }
    
    memset(p.nombre, 0, sizeof(p.nombre));
    p.edad = 0;
    actualizarPersona(p, index);
}

/*
 * BUSCAR LA PERSONA A CAMBIAR, SI NO EXISTE SALIR
 * BUSCAR LA NUEVA PERSONA, SI EXISTE SALIR
 * OBTENER EL NÚMERO DE LA SIGUIENTE PERSONA LIBRE CON LOS NUEVOS DATOS
 * ACTUALIZAR LA ANTIGUA POSICIÓN CON UNA PERSONA VACÍA
 * ACTUALIZAR LA NUEVA POSICIÓN CON LA NUEVA PERSONA
 */
void modificar ()
{
    Persona p1;
    Persona p2;

    memset(p1.nombre, 0, sizeof(p1.nombre));
    printf("* Nombre:\n");
    strcpy(p1.nombre, readline());
    printf("* Edad:\n");
    p1.edad = atoi(readline());

    memset(p2.nombre, 0, sizeof(p2.nombre));
    printf("* Nombre:\n");
    strcpy(p2.nombre, readline());
    printf("* Edad:\n");
    p2.edad = atoi(readline());

    /* DELETE PERSONA */
    int i1 = getIndex(p1.edad);
    int index1 = obtenerIndicePersona(p1, i1);
    int index2 = 0;
    
    if (index1 > 100)
    {
        printf("* ERROR: Persona no existe\n");
        return;
    }
    
    int i2 = getIndex(p2.edad);
    
    if (obtenerIndicePersona(p2, i2) < 100)
    {
        printf("* ERROR: Persona ya existe\n");
        return;
    }

    actualizarPersona(p1, index1);
    /* MODIFIY PERSON */
    index2 = obtenerIndiceLibre(i2);
    actualizarPersona(p2, index2);
}

/*
 * BUSCAR LA PERSONA, SI EXISTE SALIR
 * OBTENER EL NÚMERO DE LA SIGUIENTE PERSONA LIBRE
 * ACTUALIZAR LA PERSONA EN EL NÚMERO LIBRE OBTENIDO
 */
void crear ()
{
    char nombre[25];
    int edad = 0;

    memset(nombre, 0, sizeof(nombre));
    printf("* Nombre:\n");
    strcpy(nombre, readline());
    printf("* Edad:\n");
    edad = atoi(readline());

    /* PUSH PERSONA */
    Persona p;
    strcpy(p.nombre, nombre);
    p.edad = edad;
    int i = getIndex(edad);
    
    if (obtenerIndicePersona(p, i) < 100)
    {
        printf("* ERROR: Persona ya existe\n");
        return;
    }

    int index = obtenerIndiceLibre(i);
    actualizarPersona(p, index);
}

void analizeLine (char * comando)
{
    if (strncmp(comando, "crear", sizeof(char) * 5) == 0)
        crear();
    else if (strncmp(comando, "eliminar", sizeof(char) * 8) == 0)
        eliminar();
    else if (strncmp(comando, "modificar", sizeof(char) * 9) == 0)
        modificar();
    else if (strncmp(comando, "ver", sizeof(char) * 3) == 0)
        ver();
}

#endif