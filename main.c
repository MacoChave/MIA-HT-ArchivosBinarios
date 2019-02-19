#include "lectura.h"
#include "command.h"

int main (int argc, char const *argv[])
{
    crearArchivo();
    char string[25];
    int exit = 0;

    do
    {
        printf("\n******************************\n");
        printf("* [crear]\n* [eliminar]\n* [modificar]\n* [ver]\n* [exit]\n");
        memset(string, 0, 25);
        strcpy(string, readline());

        if (strlen(string) > 0 && isalpha(string[0]))
        {
            if (strncmp(string, "exit", sizeof(char) * 4) == 0)
                break;
            analizeLine(string);
        }
        else
            continue;
        
        printf("\n******************************\n");
    } while (!exit);
    
    return 0;
}