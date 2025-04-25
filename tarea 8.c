#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_JUGADAS 100

typedef struct {
    char nombre[50];
    int numeroJ;
    float dinero;
    int id;
} Jugada;

int numerosGanadores[3];
Jugada jugadas[MAX_JUGADAS];
int totalJugadas = 0;
int idActual = 1;
int loteriaEjecutada = 0;

void guardarJugadaEnArchivo(Jugada j) {
    FILE *archivo = fopen("jugadas.txt", "a");
    if (archivo != NULL) {
        fprintf(archivo, "ID: %d | Nombre: %s | Numero: %d | Dinero: %.2f\n", j.id, j.nombre, j.numeroJ, j.dinero);
        fclose(archivo);
    }
}

void mostrarJugadas() {
    printf("\n--- Lista de Jugadas ---\n");
    for (int i = 0; i < totalJugadas; i++) {
        printf("ID: %d | Nombre: %s | Numero: %d | Dinero: %.2f\n",
               jugadas[i].id, jugadas[i].nombre, jugadas[i].numeroJ, jugadas[i].dinero);
    }
}

void jugar() {
    if (loteriaEjecutada) {
        printf("La lotería ya fue ejecutada. Espere la próxima ronda.\n");
        return;
    }

    if (totalJugadas >= MAX_JUGADAS) {
        printf("No se pueden registrar más jugadas.\n");
        return;
    }

    Jugada nueva;
    printf("Ingrese su nombre: ");
    scanf("%s", nueva.nombre);
    printf("Ingrese el número que quiere jugar (0-99): ");
    scanf("%d", &nueva.numeroJ);
    if (nueva.numeroJ < 0 || nueva.numeroJ > 99) {
        printf("Número fuera de rango.\n");
        return;
    }
    printf("Ingrese cantidad de dinero apostado: ");
    scanf("%f", &nueva.dinero);

    nueva.id = idActual++;
    jugadas[totalJugadas++] = nueva;
    guardarJugadaEnArchivo(nueva);

    printf("Jugada registrada con ID %d.\n", nueva.id);
}

void ejecutarLoteria() {
    if (loteriaEjecutada) {
        printf("La lotería ya fue ejecutada.\n");
        return;
    }

    srand(time(NULL));
    for (int i = 0; i < 3; i++) {
        numerosGanadores[i] = rand() % 100;
    }

    printf("\n--- Números ganadores ---\n");
    printf("1er Premio: %d\n2do Premio: %d\n3er Premio: %d\n",
           numerosGanadores[0], numerosGanadores[1], numerosGanadores[2]);

    printf("\n--- Resultados ---\n");
    for (int i = 0; i < totalJugadas; i++) {
        int multiplicador = 0;
        if (jugadas[i].numeroJ == numerosGanadores[0]) {
            multiplicador = 100;
        } else if (jugadas[i].numeroJ == numerosGanadores[1]) {
            multiplicador = 50;
        } else if (jugadas[i].numeroJ == numerosGanadores[2]) {
            multiplicador = 10;
        }

        if (multiplicador > 0) {
            float ganancia = jugadas[i].dinero * multiplicador;
            printf("Jugador %s ganó %.2f (Multiplicador x%d)\n",
                   jugadas[i].nombre, ganancia, multiplicador);
        } else {
            printf("Jugador %s no ganó.\n", jugadas[i].nombre);
        }
    }

    loteriaEjecutada = 1;
}

void mostrarNumerosGanadores() {
    if (!loteriaEjecutada) {
        printf("Aún no se han generado los números ganadores.\n");
        return;
    }

    printf("\n--- Números ganadores ---\n");
    for (int i = 0; i < 3; i++) {
        printf("Número %d: %d\n", i + 1, numerosGanadores[i]);
    }
}

int main() {
    int opcion;

    do {
        printf("\n=== MENÚ ===\n");
        printf("1. Jugar\n");
        printf("2. Ejecutar Lotería\n");
        printf("3. Mostrar números de lotería\n");
        printf("4. Mostrar jugadas\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                jugar();
                break;
            case 2:
                ejecutarLoteria();
                break;
            case 3:
                mostrarNumerosGanadores();
                break;
            case 4:
                mostrarJugadas();
                break;
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción inválida.\n");
        }

    } while (opcion != 0);

    return 0;
}
