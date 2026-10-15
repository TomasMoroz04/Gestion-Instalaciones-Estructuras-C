#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ESTRUCTURAS.h"
#include "Funciones.h"

void mostrarMenu(struct LES_Opciones **inicio_les, struct LED_Tareas **inicio_led, struct ABB_Materiales **inicio_ABB,
                 struct LES_Tecnicos *inicio_tecnico, struct LES_Clientes *inicio_clientes,
                 struct Cola_Trabajos **entrada, struct Cola_Trabajos **salida, struct Pila_Tareas_Pendientes **tope);

void limpiarBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(void) {
    // 1. Carga inicial de los 7 archivos CSV en las estructuras dinamicas
    struct LES_Opciones *inicio_les = cargarCSV_opciones("Opciones.csv");
    struct LED_Tareas *inicio_led = cargarCSV_tareas("Tareas.csv");
    struct ABB_Materiales *inicio_ABB = cargarCSV_materiales("Materiales.csv");
    struct LES_Tecnicos *inicio_tecnico = cargarCSV_Tecnicos("Tecnicos.csv");
    struct LES_Clientes *inicio_clientes = cargarCSV_Clientes("Clientes.csv");
    struct Cola_Trabajos *entrada = NULL, *salida = NULL;
    struct Pila_Tareas_Pendientes *tope = cargarCSV_TareasPendientes("TareasPendientes.csv");

    cargarCSV_trabajos(&entrada, &salida, "Trabajos.csv");

    // 2. Ejecucion del menu interactivo
    mostrarMenu(&inicio_les, &inicio_led, &inicio_ABB, inicio_tecnico, inicio_clientes, &entrada, &salida, &tope);

    // 3. Guardado de todas las estructuras actualizadas en los archivos CSV al salir
    escribirCSV_opciones(inicio_les);
    escribir_csv_tareas(inicio_led);
    escribirCSV_tecnicos(inicio_tecnico);
    escribirCSV_Clientes(inicio_clientes);
    escribirCSV_TareasPendientes(&tope);
    escribirCSV_trabajos(&entrada, &salida);
    escribirCSV_arbol(inicio_ABB);

    printf("\nDatos guardados correctamente en los archivos CSV. Programa finalizado.\n");
    return 0;
}

void mostrarMenu(struct LES_Opciones **inicio_les, struct LED_Tareas **inicio_led, struct ABB_Materiales **inicio_ABB,
                 struct LES_Tecnicos *inicio_tecnico, struct LES_Clientes *inicio_clientes,
                 struct Cola_Trabajos **entrada, struct Cola_Trabajos **salida, struct Pila_Tareas_Pendientes **tope) {
    int opcion = -1;
    int op = 0;

    do {
        printf("\n================ MENU PRINCIPAL ================\n");
        printf("1) Listar opciones\n");
        printf("2) Dar de alta una opcion\n");
        printf("3) Dar de alta trabajos\n");
        printf("4) Listar trabajo pendiente de un tecnico en especial\n");
        printf("0) Finalizar y guardar cambios\n");
        printf("================================================\n");
        printf("Ingrese la opcion que desea: ");

        if (scanf("%d", &opcion) != 1) {
            limpiarBufferEntrada();
            printf("\nEntrada invalida. Por favor, ingrese un numero del menu.\n");
            opcion = -1; // Fuerza a que el bucle continue
            continue;
        }
        limpiarBufferEntrada();

        switch (opcion) {
            case 1:
                // Listado de opciones calculando materiales (ABB) y duracion (LED)
                if (*inicio_les != NULL && *inicio_led != NULL) {
                    printf("\n--- LISTADO DE OPCIONES ---\n\n");
                    imprimirLista(*inicio_les, *inicio_ABB, *inicio_led);
                } else {
                    printf("\nNo hay opciones o tareas cargadas para mostrar.\n");
                }
                break;

            case 2:
                // Dar de alta una nueva opcion junto con sus tareas y materiales
                printf("\nQuiere dar de alta una Opcion? Si=1 || No=0: ");
                if (scanf("%d", &op) != 1) {
                    limpiarBufferEntrada();
                    printf("\nEntrada invalida.\n");
                    break;
                }
                limpiarBufferEntrada();

                while (op != 0) {
                    if (op == 1) {
                        *inicio_les = Opciones(inicio_les);
                        *inicio_led = Tareas(inicio_led);
                        *inicio_ABB = Arbol(*inicio_ABB);
                    } else {
                        printf("\nOpcion no valida. Ingrese 1 (Si) o 0 (No).\n");
                    }

                    printf("\nDesea dar de alta otra Opcion? Si=1 || No=0: ");
                    if (scanf("%d", &op) != 1) {
                        limpiarBufferEntrada();
                        printf("\nEntrada invalida.\n");
                        break;
                    }
                    limpiarBufferEntrada();
                }
                break;

            case 3:
                // Dar de alta un nuevo trabajo y apilar sus tareas pendientes
                altaTrabajo(entrada, salida, inicio_clientes, inicio_tecnico, *inicio_led, tope);
                break;

            case 4:
                // Listar trabajos pendientes filtrando por codigo de tecnico
                Trabajo_X_Tecnico(entrada, salida);
                break;

            case 0:
                printf("\nSaliendo del menu y guardando datos...\n");
                break;

            default:
                printf("\nOpcion no valida. Intente de nuevo.\n");
                break;
        }

    } while (opcion != 0);
}