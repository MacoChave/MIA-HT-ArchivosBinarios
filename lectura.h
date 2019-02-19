#ifndef LECTURA_H
#define LECTURA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FILENAME "/home/marco/hoja_trabajo1.bin"

typedef struct Persona Persona;
struct Persona
{
    char nombre[25];
    int edad;
};

/*
 * CREAR EL ARCHIVO BINARIO CON 100 PERSONAS VACÍAS
 */
void crearArchivo ()
{
    FILE * file;
    Persona persona;
    memset(persona.nombre, 0, sizeof(persona.nombre));
    persona.edad = 0;

    if ((file = fopen(FILENAME, "wb")) == NULL)
        return;
    
    for(int i = 0; i < 100; i++)
        fwrite(&persona, sizeof(Persona), 1, file);
    

    fclose(file);
}

/*
 * ACTUALIZAR la 'Persona' n INDICADO POR 'index'
 * 
 */
void actualizarPersona (Persona persona, int index)
{
    FILE * file;

    if ((file = fopen(FILENAME, "rb+")) == NULL)
        return;

    /* AVANZAR 'index' Personas */ 
    fseek(file, index * sizeof(Persona), SEEK_SET);

    fwrite(&persona, sizeof(Persona), 1, file);
    
    fclose(file);
}

/* 
 * OBTENER LA PERSONA VACÍA
 * A PARTIR DEL CUADRANTE INDICADO POR 'index'
 */
int obtenerIndiceLibre (int index)
{
    FILE * file;
    Persona p;

    if ((file = fopen(FILENAME, "rb")) == NULL)
        return 200;

    /* AVANZAR 'index' PERSONAS */   
    fseek(file, index * sizeof(Persona), SEEK_SET);
    int i = index;
    for(i; i < 100; i++)
    {
        fread(&p, sizeof(Persona), 1, file);
        if (p.edad == 0)
            break;
    }
    
    fclose(file);
    return i;
}

/* 
 * BUSCAR LA PERSONA
 * A PARTIR DEL CUADRANTE INDICADO POR 'index'
 */
int obtenerIndicePersona (Persona persona, int index)
{
    FILE * file;
    Persona p;

    if ((file = fopen(FILENAME, "rb")) == NULL)
        return 200;
    
    fseek(file, index * sizeof(Persona), SEEK_SET);
    int i = index;
    for(i; i < 100; i++)
    {
        fread(&p, sizeof(Persona), 1, file);
        if (strcmp(p.nombre, persona.nombre) == 0 && p.edad == persona.edad)
            break;
    }
    
    fclose(file);
    return i;
}

/*
 * OBTENER LAS PERSONAS
 */
Persona * obtenerPersonas ()
{
    FILE * file;
    Persona * personas = (Persona *)malloc(sizeof(Persona) * 100);

    if ((file = fopen(FILENAME, "rb")) == NULL)
        return NULL;

    fread(personas, sizeof(Persona), 100, file);

    fclose(file);
    return personas;
}

/*****************************************
 * METODO LECTURA DE LÍNEA DE COMANDO
 *****************************************/
char * readline ()
{
    char * line = (char *)malloc(sizeof(char) * 25);
    char * linep = line;
    size_t lenmax = 25, len = lenmax;

    int c;

    if (line == NULL)
        return NULL;
    
    while (1)
    {
        c = fgetc(stdin);

        /* SALIR SI SE LLEGA AL FINAL DE LECTURA */
        if (c == EOF)
            break;
        
        if (--len == 0)
        {
            len = lenmax;
            char * linen = realloc(linep, lenmax *= 2);

            if (linen == NULL)
            {
                free(linep);
                return NULL;
            }

            line = line + (line - linep);
            line = linen;
        }

        if ((*line++ = c) == '\n')
            break;
    }

    *line = '\0';
    return linep;
}

#endif