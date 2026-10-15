#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct Fecha{
    int dia, mes, anio;
};

struct LES_Clientes{
    int CodCliente, dni;
    char nombre[30];
    struct LES_Clientes *sgte;
};

struct LES_Tecnicos{
    int  disponible, codTecnico, dni;
    char nombre[30];
    struct LES_Tecnicos *sgte;
};

struct LES_Opciones {   //OPCIONES
    int id_opcion;
    char nombre[30];
    float mano_obra;
    struct LES_Opciones *sgte;
};

struct Cola_Trabajos{  //TRABAJOS
    int opcion, id_trabajo, codTecnico, altura, codCliente, duracion;
    char ubicacion[30];
    struct Fecha fecha_fin;
    struct Cola_Trabajos *sgte;
};
 
struct Pila_Tareas_Pendientes {
    int codTecnico, opcion, tarea, orden, tardado;
    char nombreTecnico[50], nombreTarea[50];
    struct Pila_Tareas_Pendientes *sgte;
};

struct LED_Tareas{
    int opcion, tarea, orden, estimado;
    char nombre[30];
    struct LED_Tareas *ant, *sgte;
};

struct ABB_Materiales{ 
    int opcion, codigo, cantidad;
    float costo_unitario;
    char nombre_material[50], unidad[30];
    struct ABB_Materiales *izq, *der;
};


#endif