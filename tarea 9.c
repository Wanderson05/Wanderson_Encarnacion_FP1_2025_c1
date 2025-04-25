#include <stdio.h>
#include <ctype.h>

int main() {
    FILE *archivo;
    char nombreArchivo[100];
    char c;
    int letras[26] = {0}; // Contador de A-Z
    int palabras = 0;
    int dentroPalabra = 0;

    printf("Ingrese el nombre del archivo (ej. texto.txt): ");
    scanf("%s", nombreArchivo);

    archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    while ((c = fgetc(archivo)) != EOF) {
        // Contar letras
        if (isalpha(c)) {
            c = tolower(c);
            letras[c - 'a']++;
        }

        // Contar palabras
        if (isspace(c) || ispunct(c)) {
            dentroPalabra = 0;
        } else if (!dentroPalabra) {
            dentroPalabra = 1;
            palabras++;
        }
    }

    fclose(archivo);

    printf("\nCantidad de palabras: %d\n", palabras);
    printf("Frecuencia de letras:\n");
    for (int i = 0; i < 26; i++) {
        printf("%c: %d\n", 'a' + i, letras[i]);
    }

    return 0;
}

