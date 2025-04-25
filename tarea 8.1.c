#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_JUGADAS 100

typedef struct {
    int id;
    char nombre[50];
    int numeroJugado;
    float dinero;
} Jugada;

Jugada jugadas[MAX_JUGADAS];
int totalJugadas = 0;
int idActual = 1;
int numerosGanadores[3];
int loteriaEjecutada = 0;

void guardarJugadaEnArchivo(Jugada j) {
    FILE *archivo = fopen("jugadas.txt", "a");
    if (archivo != NULL) {
        fprintf(archivo, "ID: %d | Nombre: %s | Número: %d | Dinero: %.2f\n",
                j.id, j.nombre, j.numeroJugado, j.dinero);
        fclose(archivo);
    } else {
        printf("No se pudo abrir el archivo para guardar la jugada.\n");
    }
}

void registrarJugador() {
    if (loteriaEjecutada) {
        printf("La lotería ya fue ejecutada. No se pueden registrar más jugadores ahora.\n");
        return;
    }

    if (totalJugadas >= MAX_JUGADAS) {
        printf("Se alcanzó el máximo de jugadas.\n");
        return;
    }

    Jugada nueva;
    nueva.id = idActual++;
    printf("Ingrese su nombre: ");
    scanf("%s", nueva.nombre);
    printf("Ingrese un número entre 0 y 99: ");
    scanf("%d", &nueva.numeroJugado);

    if (nueva.numeroJugado < 0 || nueva.numeroJugado > 99) {
        printf("Número fuera de rango.\n");
        return;
    }

    printf("Ingrese la cantidad de dinero a apostar: ");
    scanf("%f", &nueva.dinero);

    jugadas[totalJugadas++] = nueva;
    guardarJugadaEnArchivo(nueva);

    printf("Jugada registrada con ID: %d\n", nueva.id);
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

    printf("\n--- NÚMEROS GANADORES ---\n");
    printf("1er Premio: %d\n", numerosGanadores[0]);
    printf("2do Premio: %d\n", numerosGanadores[1]);
    printf("3er Premio: %d\n", numerosGanadores[2]);

    printf("\n--- RESULTADOS DE LOS JUGADORES ---\n");
    for (int i = 0; i < totalJugadas; i++) {
        int premio = 0;
        if (jugadas[i].numeroJugado == numerosGanadores[0])
            premio = 100;
        else if (jugadas[i].numeroJugado == numerosGanadores[1])
            premio = 50;
        else if (jugadas[i].numeroJugado == numerosGanadores[2])
            premio = 10;

        if (premio > 0) {
            float ganancia = jugadas[i].dinero * premio;
            printf("Jugador %s ganó %.2f (x%d)\n", jugadas[i].nombre, ganancia, premio);
        } else {
            printf("Jugador %s no ganó.\n", jugadas[i].nombre);
        }
    }

    loteriaEjecutada = 1;
}

void mostrarNumerosGanadores() {
    if (!loteriaEjecutada) {
        printf("Aún no se ha ejecutado la lotería.\n");
        return;
    }

    printf("\n--- NÚMEROS GANADORES ---\n");
    for (int i = 0; i < 3; i++) {
        printf("Premio %d: %d\n", i + 1, numerosGanadores[i]);
    }
}

void mostrarJugadas() {
    printf("\n--- LISTA DE JUGADAS ---\n");
    for (int i = 0; i < totalJugadas; i++) {
        printf("ID: %d | Nombre: %s | Número: %d | Dinero: %.2f\n",
               jugadas[i].id, jugadas[i].nombre, jugadas[i].numeroJugado, jugadas[i].dinero);
    }
}

int main() {
    int opcion;

    do {
        printf("\n===== MENÚ =====\n");
        printf("1. Registrar jugador\n");
        printf("2. Ejecutar lotería\n");
        printf("3. Mostrar números ganadores\n");
        printf("4. Mostrar jugadas\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: registrarJugador(); break;
            case 2: ejecutarLoteria(); break;
            case 3: mostrarNumerosGanadores(); break;
            case 4: mostrarJugadas(); break;
            case 0: printf("¡Hasta luego!\n"); break;
            default: printf("Opción inválida.\n");
        }

    } while (opcion != 0);

    return 0;
}
