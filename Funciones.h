#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ESTRUCTURAS.h"

//PROTOTIPO
struct ABB_Materiales* creacionarbol(int opcion, int codigo, int cantidad, char *unidad, float costo_unitario, char nombre_material[30]);

struct ABB_Materiales* Arbol(struct ABB_Materiales *r);

struct ABB_Materiales* insertarABB(struct ABB_Materiales *r, int opcion, int codigo, int cantidad, 
                             char *unidad, float costo_unitario, char *nombre_material);

struct ABB_Materiales* cargarCSV_materiales(char *nombreArchivo);

void imprimirABB(struct ABB_Materiales *raiz);




struct LES_Opciones* cargarCSV_opciones(char *nombreArchivo);

void insertar_opciones(struct LES_Opciones **ini, int id_opcion, char* nombre, float mano_obra);

struct LES_Opciones* crearNodo(char *nombre, int id_opcion,float mano_obra);

void imprimirLista(struct LES_Opciones *ini_les, struct ABB_Materiales *r, struct LED_Tareas *ini_led);

float calcular_monto_materiales(int dato, struct ABB_Materiales *r);

int calcular_duracion(int dato, struct LED_Tareas *ini);





struct LED_Tareas* cargarCSV_tareas(char *nombreArchivo);

void insertar_tareas(struct LED_Tareas **ini, int nro_opcion, int nro_tarea, char *nombre, int orden_tarea, int estimado_tarea);

struct LED_Tareas *crear_nodo_led(char *nombre_Tarea, int nro_Opcion, int nro_Tarea, int orden_Tarea, int estimado_Tarea);

struct LED_Tareas* BuscarAnterior(int opcion, int orden, struct LED_Tareas *ini);

void imprimirListaDoble(struct LED_Tareas *ini);





struct Cola_Trabajos* crear_nodo_cola(int opcion, int id_trabajo, int codTecnico, int codCliente, char *ubicacion, int altura, int duracion, struct Fecha fecha_fin);

void cargarCSV_trabajos(struct Cola_Trabajos **entrada, struct Cola_Trabajos **salida, char *nombreArchivo);

void encolar_ordenes_trabajos(int opcion, int id_trabajo, int codTecnico, int codCliente, char *ubicacion, int altura, int duracion, 
								struct Fecha fecha_fin, struct Cola_Trabajos **entrada, struct Cola_Trabajos **salida);

void desencolar_trabajos(struct Cola_Trabajos **nodo, struct Cola_Trabajos **entrada, struct Cola_Trabajos **salida);

int vacia_cola(struct Cola_Trabajos *salida);

void encolar_cola2(struct Cola_Trabajos **nodo2, struct Cola_Trabajos **entrada2, struct Cola_Trabajos **salida2);

void Trabajo_X_Tecnico(struct Cola_Trabajos **entrada, struct Cola_Trabajos **salida);




struct LES_Tecnicos* crearNodoTecnico(char *nombre, int codTecnico, int dni);

void insertar_Tecnicos(struct LES_Tecnicos **ini, int codTecnico, int dni, char *nombre);

struct LES_Tecnicos* cargarCSV_Tecnicos(char *nombreArchivo);



struct LES_Clientes* crearNodoCliente(char *nombre, int CodCliente, int dni);

void insertar_Clientes(struct LES_Clientes **ini, int CodCliente, int dni, char *nombre);

struct LES_Clientes* cargarCSV_Clientes(char *nombreArchivo);






struct Pila_Tareas_Pendientes* crearNodoTarea(int codTecnico, char *nombreTecnico, int opcion, int tarea, char *nombreTarea, int orden, int tardado);

void insertar_Tarea(struct Pila_Tareas_Pendientes **tope, int codTecnico, char *nombreTecnico, int opcion, int tarea, char *nombreTarea, int orden, int tardado);

struct Pila_Tareas_Pendientes* cargarCSV_TareasPendientes(char *nombreArchivo);

void desapilar_ordenes(struct Pila_Tareas_Pendientes **ds, struct Pila_Tareas_Pendientes **tp);

int vacia_pila(struct Pila_Tareas_Pendientes *tp);


void agregarTareaPila(struct Pila_Tareas_Pendientes **pila, struct Pila_Tareas_Pendientes *nueva_tarea);

void encolarTrabajo(struct Cola_Trabajos **entrada, struct Cola_Trabajos **salida, struct Cola_Trabajos *nuevo_trabajo);

void altaTrabajo(struct Cola_Trabajos **entrada, struct Cola_Trabajos **salida, struct LES_Clientes *clientes, struct LES_Tecnicos *tecnicos, 
					struct LED_Tareas *tareas, struct Pila_Tareas_Pendientes **pila_tareas_pendientes);




void escribirCSV_opciones(struct LES_Opciones *nodo);

void escribir_csv_tareas(struct LED_Tareas *inicio);

void escribirCSV_arbol_recursivo(struct ABB_Materiales *nodo, FILE *archivo);

void escribirCSV_arbol(struct ABB_Materiales *nodo);

void escribirCSV_tecnicos(struct LES_Tecnicos *inicio);

void escribirCSV_Clientes(struct LES_Clientes *nodo);

void escribirCSV_trabajos(struct Cola_Trabajos **entrada, struct Cola_Trabajos **salida);

void escribirCSV_TareasPendientes(struct Pila_Tareas_Pendientes **tope);

//Implementación

struct LES_Opciones* Opciones(struct LES_Opciones **ini_les){

    int band, Opcion;
    float mano_Obra;
    char nombre_opcion[30];
	
	    	printf("\nCarga de La Lista de Opciones:\n");
	        printf("Ingresar los datos en orden:\n");
	        printf("Opcion: ");
	        scanf("%d",&Opcion);
	        fflush(stdin);
	        printf("Nombre de la Tarea: ");
	        gets(nombre_opcion);
	        fflush(stdin);
	        printf("Mano de Obra: ");
	        scanf("%g",&mano_Obra);
	        fflush(stdin);
	        insertar_opciones(&(*ini_les), Opcion,  nombre_opcion, mano_Obra);
	   
	return *ini_les;
}

struct LES_Opciones* cargarCSV_opciones(char *nombreArchivo){
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return NULL;
    }

    char linea[1024];  // Buffer para leer cada línea del archivo
    struct LES_Opciones *ini = NULL;

    // Leer la primera línea de encabezado
    
    // Leer línea por línea el archivo CSV
    int id_opcion;
    char nombre[30];
    float mano_obra;
    while (fgets(linea, 1024, archivo)) {
    	linea[strcspn(linea, "\n")] = '\0';
        sscanf(linea, "%d,%29[^,],%f", &id_opcion, nombre, &mano_obra);
        insertar_opciones(&ini, id_opcion, nombre, mano_obra);
    }

    fclose(archivo);
    return ini;
}

//Funcion para insertar nodos en la LES_Opciones
void insertar_opciones(struct LES_Opciones **ini, int id_opcion, char *nombre, float mano_obra){
    
    struct LES_Opciones *nv = crearNodo(nombre, id_opcion, mano_obra);
    if (*ini == NULL) {
        *ini = nv;
    } else {
    	struct LES_Opciones *aux = *ini;
        while (aux->sgte != NULL) {
            aux = aux->sgte;
        }
        aux->sgte = nv;
    }
    nv=NULL;
}

//Funcion para crear un nodo LES_Opciones
struct LES_Opciones* crearNodo(char *nombre, int id_opcion,float mano_obra) {
    struct LES_Opciones *nuevoNodo = (struct LES_Opciones*)malloc(sizeof(struct LES_Opciones));
    if (nuevoNodo == NULL) {
        perror("Error en la asignación de memoria");
        return NULL;
    }
    nuevoNodo->id_opcion = id_opcion;
    strncpy(nuevoNodo->nombre, nombre, 30);
    nuevoNodo->nombre[29] = '\0'; // Asegura que la cadena esté terminada en nulo
    nuevoNodo->mano_obra = mano_obra;
    nuevoNodo->sgte = NULL;
    return nuevoNodo;
}

void imprimirLista(struct LES_Opciones *ini_les, struct ABB_Materiales *r, struct LED_Tareas *ini_led) {
    struct LES_Opciones *aux = ini_les;
    float materiales, total;
    int duracion;
    
    while (aux != NULL) {
        printf("Opcion: %d\nNombre: %s\nMano de Obra: $%.2f\n", aux->id_opcion, aux->nombre, aux->mano_obra);
        materiales=calcular_monto_materiales(aux->id_opcion, r);
        printf("Costo de Materiales: $%.2f\n", materiales);
        duracion=calcular_duracion(aux->id_opcion, ini_led);
        printf("Duracion: %d hs\n",duracion);
        total=materiales+aux->mano_obra;
        printf("Monto total: $%.2f\n\n",total);
        aux = aux->sgte;
    }
    
}

float calcular_monto_materiales(int dato, struct ABB_Materiales *r) {
    float costo_total = 0;
    if (r != NULL) {
        if (dato == r->opcion) {
            //printf("Coincidencia encontrada: opcion = %d, costo_unitario = %.2f, cantidad = %d\n", r->opcion, r->costo_unitario, r->cantidad);
            costo_total += r->costo_unitario * r->cantidad;
        }
        costo_total += calcular_monto_materiales(dato, r->izq);
        costo_total += calcular_monto_materiales(dato, r->der);
    }
    return costo_total;
}

int calcular_duracion(int dato, struct LED_Tareas *ini){		

	int duracion=0;
	while(ini!=NULL){
		if(dato==ini->opcion){
			duracion=duracion+ini->estimado;
        }
        ini=ini->sgte;
	}
	
	return duracion;
}




struct LED_Tareas* Tareas(struct LED_Tareas **ini_led){

    int band, opcion, tarea, orden, estimado;
    char nombre_tarea[30];
	
	    printf("\nDesea cargar datos a la lista doble? (1):SI || (0):NO\n");
	    scanf("%d",&band);
	    while(band!=0){
	    	if(band ==1){
			
	    	printf("\n Carga de La Lista doble de Tareas:\n");
	        printf("Ingresar los datos en orden:\n");
	        printf("Opcion: ");
	        scanf("%d",&opcion);
	        fflush(stdin);
	        printf("Tarea: ");
	        scanf("%d",&tarea);
	        fflush(stdin);
	        printf("Nombre de la Tarea: ");
	        gets(nombre_tarea);
	        fflush(stdin);
	        printf("Orden: ");
	        fflush(stdin);
	        scanf("%d",&orden);
	        fflush(stdin);
	        printf("Estimado: ");
	        scanf("%d",&estimado);
	        fflush(stdin);
	        insertar_tareas(ini_led, opcion, tarea, nombre_tarea, orden, estimado);
			}
				printf("\nDesea agregar otra tarea a la lista doble? (1):SI || (0):NO\n");
	    		scanf("%d",&band);
	    }
	    
	return *ini_led;
}

// Función para crear un nodo LED_Tareas
struct LED_Tareas *crear_nodo_led(char *nombre_Tarea, int nro_Opcion, int nro_Tarea, int orden_Tarea, int estimado_Tarea) {
    struct LED_Tareas *nuevoNodo_tarea = (struct LED_Tareas *)malloc(sizeof(struct LED_Tareas));
    if (nuevoNodo_tarea == NULL) {
        printf("Error al asignar memoria\n");
        return NULL;
    }
    strncpy(nuevoNodo_tarea->nombre, nombre_Tarea, 30);
    nuevoNodo_tarea->nombre[29] = '\0'; // Asegura que la cadena esté terminada en nulo
    nuevoNodo_tarea->opcion = nro_Opcion;
    nuevoNodo_tarea->tarea = nro_Tarea;
    nuevoNodo_tarea->orden = orden_Tarea;
    nuevoNodo_tarea->estimado = estimado_Tarea;
    nuevoNodo_tarea->sgte = NULL;
    nuevoNodo_tarea->ant = NULL;
    return nuevoNodo_tarea;
}

struct LED_Tareas* BuscarAnterior(int opcion, int orden, struct LED_Tareas *ini) {
    struct LED_Tareas *ant = NULL;

    while (ini != NULL) {
        if (ini->opcion > opcion || (ini->opcion == opcion && ini->orden >= orden)) {
            break;
        }
        ant = ini;
        ini = ini->sgte;
    }

    return ant;
}

// Función para insertar nodos en la LED_Tareas
void insertar_tareas(struct LED_Tareas **ini, int nro_opcion, int nro_tarea, char *nombre, int orden_tarea, int estimado_tarea) {
    struct LED_Tareas *nv = crear_nodo_led(nombre, nro_opcion, nro_tarea, orden_tarea, estimado_tarea);
    
	if (nv == NULL) return;

    struct LED_Tareas *ant = BuscarAnterior(nv->opcion, nv->orden, *ini);

    if (*ini != NULL) {
        if (ant != NULL) {
            nv->sgte = ant->sgte;
            nv->ant = ant;
            if (ant->sgte != NULL) {
                ant->sgte->ant = nv;
            }
            ant->sgte = nv;
        } else {
            nv->sgte = *ini;
            (*ini)->ant = nv;
            *ini = nv;
        }
    } else {
        *ini = nv;
    }
    
}

struct LED_Tareas* cargarCSV_tareas(char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return NULL;
    }

    char linea[1024];  // Buffer para leer cada línea del archivo
    struct LED_Tareas *ini = NULL;

    // Leer la primera línea de encabezado
    
    // Leer línea por línea el archivo CSV
    int id_opcion, tarea, orden, estimado;
    char nombre[30];
    while (fgets(linea, 1024, archivo)) {
    	linea[strcspn(linea, "\n")] = '\0';
        sscanf(linea, "%d,%d,%29[^,],%d,%d", &id_opcion, &tarea, nombre, &orden, &estimado);
        insertar_tareas(&ini, id_opcion, tarea, nombre, orden, estimado);
    }

    fclose(archivo);
    return ini;
}

void imprimirListaDoble(struct LED_Tareas *ini) {
    struct LED_Tareas *aux = ini;
    while (aux != NULL) {
        printf("Opcion: %d\nTarea: %d\nNombre: %s\nOrden: %d\nEstimado: %d\n\n", aux->opcion, aux->tarea, aux->nombre, aux->orden, aux->estimado);
        aux = aux->sgte;
    }
}




//Cargado del Arbol
struct ABB_Materiales* creacionarbol(int opcion, int codigo, int cantidad, char *unidad, float costo_unitario, char *nombre_material){
    struct ABB_Materiales* nuevo=(struct ABB_Materiales *)malloc(sizeof(struct ABB_Materiales));
    nuevo->cantidad = cantidad;
    nuevo->codigo = codigo;
    nuevo->costo_unitario = costo_unitario;
    nuevo->opcion = opcion;
    strcpy(nuevo->unidad, unidad);
    strcpy(nuevo->nombre_material, nombre_material);
    nuevo->izq= nuevo->der = NULL;
    return nuevo;
}

struct ABB_Materiales* Arbol(struct ABB_Materiales *r){

	//struct ABB_Materiales
	int band, opcion, codigo, cantidad;
	float costo_unitario;
	char nombre_material[30], unidad[30];
	
	    printf("Desea cargar datos al arbol? (1):SI || (0):NO\n");
	    scanf("%d",&band);
	    while(band!=0){
	    	if(band ==1){
	    
	        printf("Ingresar los datos en orden:\n");
	        printf("Opcion: ");
	        scanf("%d",&opcion);
	        fflush(stdin);
	        printf("Codigo: ");
	        scanf("%d",&codigo);
	        fflush(stdin);
	        printf("Nombre del Material: ");
	        gets(nombre_material);
	        fflush(stdin);
	        printf("Cantidad: ");
	        scanf("%d",&cantidad);
	        fflush(stdin);
	        printf("Unidad: ");
	        gets(unidad);
	        fflush(stdin);
	        printf("Costo Unitario: ");
	        scanf("%g",&costo_unitario);
	        fflush(stdin);
	        r=insertarABB(r, opcion, codigo, cantidad, unidad, costo_unitario, nombre_material);
	    }
	    		printf("\nDesea agregar otro material en el arbol ? (1):SI || (0):NO\n");
	    		scanf("%d",&band);
	}
	
	return r;
}

//Funcion para insertar nodos en la ABB_Materiales
struct ABB_Materiales* insertarABB(struct ABB_Materiales *r, int opcion, int codigo, int cantidad, char *unidad, float costo_unitario, char *nombre_material){
    if(r==NULL){
        r=creacionarbol(opcion, codigo, cantidad, unidad, costo_unitario, nombre_material);
    }
    else if (r->codigo>codigo){
        r->izq = insertarABB(r->izq, opcion, codigo, cantidad, unidad, costo_unitario, nombre_material);
    } else if (r->codigo < codigo){
        r->der = insertarABB(r->der,  opcion, codigo, cantidad, unidad, costo_unitario, nombre_material);
    }
    
    return r;
}

struct ABB_Materiales* cargarCSV_materiales(char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return NULL;
    }

    char linea[1024];  // Buffer para leer cada línea del archivo
    struct ABB_Materiales *raiz = NULL;

    // Leer línea por línea el archivo CSV
    
    while (fgets(linea, 1024, archivo)) {
        int opcion, codigo, cantidad;
        float costo_unitario;
        char nombre_material[50], unidad[30];
        sscanf(linea,"%d,%d,%49[^,],%d,%29[^,],%g",&opcion, &codigo, nombre_material , &cantidad, unidad, &costo_unitario);

        // Insertar en el árbol
        raiz = insertarABB(raiz, opcion, codigo, cantidad, unidad, costo_unitario, nombre_material);
    }

    fclose(archivo);
    return raiz;
}

void imprimirABB(struct ABB_Materiales *raiz) {
    if (raiz == NULL) {
        return;
    }

    // Recorrido inorder: izquierda, raíz, derecha
    printf("Opcion: %d\nCodigo: %d\nMaterial: %s\nCantidad: %d\nUnidad: %s\nCosto unitario: %g\n\n",raiz->opcion,raiz->codigo, raiz->nombre_material, raiz->cantidad, raiz->unidad, raiz->costo_unitario);
    imprimirABB(raiz->izq);
    imprimirABB(raiz->der);
}




	
void cargarCSV_trabajos(struct Cola_Trabajos **entrada, struct Cola_Trabajos **salida, char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    char linea[1024];  // Buffer para leer cada línea del archivo
    int opcion, id_trabajo, codTecnico, codCliente, altura, duracion;
    char ubicacion[30], fecha[11];
    struct Fecha fecha_fin;

    while (fgets(linea, sizeof(linea), archivo)) {
        linea[strcspn(linea, "\n")] = '\0';  // Eliminar el carácter de nueva línea

        // Intentar leer con fecha
        int items_read = sscanf(linea, "%d,%d,%d,%d,%29[^,],%d,%d,%10s",
               &opcion, &id_trabajo, &codTecnico, &codCliente, ubicacion,
               &altura, &duracion, fecha);

        if (items_read == 8) {  // Verifica que se hayan leído todos los campos
            // Parsear la fecha
            int parsed = sscanf(fecha, "%d/%d/%d", &fecha_fin.dia, &fecha_fin.mes, &fecha_fin.anio);
            if (parsed == 3) {
                /*printf("Leido del archivo: %d,%d,%d,%d,%s,%d,%d,%s\n",
                       opcion, id_trabajo, codTecnico, codCliente, ubicacion,
                       altura, duracion, fecha);*/
                encolar_ordenes_trabajos(opcion, id_trabajo, codTecnico, codCliente, ubicacion, altura, duracion, fecha_fin, entrada, salida);
            } else {
                printf("Error al parsear la fecha: %s\n", fecha);
            }
        } else {
            // Intentar leer sin fecha
            items_read = sscanf(linea, "%d,%d,%d,%d,%29[^,],%d,%d",
               &opcion, &id_trabajo, &codTecnico, &codCliente, ubicacion,
               &altura, &duracion);

            if (items_read == 7) {  // Verifica que se hayan leído todos los campos excepto la fecha
                // Fecha vacía
                fecha_fin.dia = 0;
                fecha_fin.mes = 0;
                fecha_fin.anio = 0;

                /*printf("Leido del archivo (sin fecha): %d,%d,%d,%d,%s,%d,%d\n",
                       opcion, id_trabajo, codTecnico, codCliente, ubicacion,
                       altura, duracion);*/
                encolar_ordenes_trabajos(opcion, id_trabajo, codTecnico, codCliente, ubicacion, altura, duracion, fecha_fin, entrada, salida);
            } else {
                printf("Error al leer la linea del archivo: %s\n", linea);
            }
        }
    }

    fclose(archivo);
}

void encolar_ordenes_trabajos(int opcion, int id_trabajo, int codTecnico, int codCliente, char *ubicacion, int altura, int duracion, struct Fecha fecha_fin, 
                              struct Cola_Trabajos **entrada, struct Cola_Trabajos **salida) {
    struct Cola_Trabajos *nv = crear_nodo_cola(opcion, id_trabajo, codTecnico, codCliente, ubicacion, altura, duracion, fecha_fin);
    if (nv == NULL) {
        printf("Error al crear el nodo de la cola.\n");
        return;
    }

    if (*salida == NULL) {
        // Si la cola está vacía, el nuevo nodo será tanto el inicio como el final de la cola
        *entrada = *salida = nv;
    } else {
        // Si la cola no está vacía, el nuevo nodo se añade al final de la cola
        (*entrada)->sgte = nv;
        *entrada = nv;
    }
    /*printf("Nodo encolado: %d,%d,%d,%d,%s,%d,%d,%d,%d,%d\n",
           opcion, id_trabajo, codTecnico, codCliente, ubicacion,
           altura, duracion, fecha_fin.dia, fecha_fin.mes, fecha_fin.anio);*/
}



struct Cola_Trabajos* crear_nodo_cola(int opcion, int id_trabajo, int codTecnico, int codCliente, char *ubicacion, int altura, int duracion, struct Fecha fecha_fin) {
    struct Cola_Trabajos *nuevo = (struct Cola_Trabajos *)malloc(sizeof(struct Cola_Trabajos));
    if (nuevo == NULL) {
        perror("Error en la asignacion de memoria");
        return NULL;
    }
    nuevo->opcion = opcion;
    nuevo->id_trabajo = id_trabajo;
    nuevo->codTecnico = codTecnico;
    nuevo->codCliente = codCliente;
    strncpy(nuevo->ubicacion, ubicacion, sizeof(nuevo->ubicacion) - 1);
    nuevo->ubicacion[sizeof(nuevo->ubicacion) - 1] = '\0'; // Asegura que la cadena esté terminada en nulo
    nuevo->altura = altura;
    nuevo->duracion = duracion;
    nuevo->fecha_fin = fecha_fin;
    nuevo->sgte = NULL;

    return nuevo;
}

int vacia_cola(struct Cola_Trabajos *cola) {
    return (cola == NULL);
}

void desencolar_trabajos(struct Cola_Trabajos **nodo, struct Cola_Trabajos **entrada, struct Cola_Trabajos **salida) {
    if (*salida == NULL) {
        *nodo = NULL;
        return;
    }
    *nodo = *salida;
    *salida = (*salida)->sgte;
    if (*salida == NULL) {
        *entrada = NULL;
    }
}

void encolar_cola2(struct Cola_Trabajos **nodo2, struct Cola_Trabajos **entrada2, struct Cola_Trabajos **salida2) {
    if (*entrada2 == NULL) {
        *salida2 = *nodo2;
    } else {
        (*entrada2)->sgte = *nodo2;
    }
    *entrada2 = *nodo2;
    *nodo2 = NULL;
}

void Trabajo_X_Tecnico(struct Cola_Trabajos **entrada, struct Cola_Trabajos **salida) {
    int cod;
    struct Cola_Trabajos *nodo, *entrada2 = NULL, *salida2 = NULL;
    printf("Ingrese el codigo del tecnico que desee: ");
    scanf("%d", &cod);
    int trabajos_encontrados = 0; // Variable para contabilizar trabajos encontrados
    
    while (!vacia_cola(*salida)) {
        desencolar_trabajos(&nodo, entrada, salida);
        if (nodo->codTecnico == cod && (nodo->fecha_fin.dia == 0 && nodo->fecha_fin.mes == 0 && nodo->fecha_fin.anio == 0)) {
            trabajos_encontrados++; // Incrementa el contador de trabajos encontrados
            printf("Debes realizar el siguiente trabajo:\n");
            printf("Opcion: %d\n", nodo->opcion);
            printf("Nro Trabajo: %d\n", nodo->id_trabajo);
            printf("Codigo Tecnico: %d\n", nodo->codTecnico);
            printf("Codigo Cliente: %d\n", nodo->codCliente);
            printf("Ubicacion: %s\n", nodo->ubicacion);
            printf("Altura: %d\n", nodo->altura);
            printf("Duracion: %d\n", nodo->duracion);
        } else {
            encolar_cola2(&nodo, &entrada2, &salida2);
        }
    }

    if (trabajos_encontrados == 0) {
        printf("El codigo de tecnico ingresado no tiene trabajos pendientes.\n");
    }

    while (!vacia_cola(salida2)) {
        desencolar_trabajos(&nodo, &entrada2, &salida2);
        encolar_cola2(&nodo, &(*entrada), &(*salida));
    }
}









struct LES_Tecnicos* crearNodoTecnico(char *nombre, int codTecnico, int dni) {
    
	struct LES_Tecnicos *nuevoNodo = (struct LES_Tecnicos*)malloc(sizeof(struct LES_Tecnicos));
    if (nuevoNodo == NULL) {
        perror("Error en la asignación de memoria");
        return NULL;
    }
    nuevoNodo->codTecnico = codTecnico;
    strncpy(nuevoNodo->nombre, nombre, 30);
    nuevoNodo->nombre[29] = '\0'; // Asegura que la cadena esté terminada en nulo
    nuevoNodo->dni = dni;
    nuevoNodo->sgte = NULL;
    return nuevoNodo;
}

void insertar_Tecnicos(struct LES_Tecnicos **ini, int codTecnico, int dni, char *nombre) {
    
	struct LES_Tecnicos *nv = crearNodoTecnico(nombre, codTecnico, dni);
    if (*ini == NULL) {
        *ini = nv;
    } else {
        struct LES_Tecnicos *aux = *ini;
        while (aux->sgte != NULL) {
            aux = aux->sgte;
        }
        aux->sgte = nv;
    }
}

struct LES_Tecnicos* cargarCSV_Tecnicos(char *nombreArchivo) {
    
	FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return NULL;
    }

    char linea[1024];  // Buffer para leer cada línea del archivo
    struct LES_Tecnicos *ini = NULL;

    // Leer línea por línea el archivo CSV
    char nombre[30];
    int codTecnico;
    int dni;
    while (fgets(linea, 1024, archivo)) {
    	linea[strcspn(linea, "\n")] = '\0';
        sscanf(linea, "%d,%d,%29[^,]", &codTecnico, &dni, nombre);
        insertar_Tecnicos(&ini, codTecnico, dni, nombre);
    }

    fclose(archivo);
    return ini;
}







struct LES_Clientes* crearNodoCliente(char *nombre, int CodCliente, int dni) {
    struct LES_Clientes *nuevoNodo = (struct LES_Clientes*)malloc(sizeof(struct LES_Clientes));
    if (nuevoNodo == NULL) {
        perror("Error en la asignación de memoria");
        return NULL;
    }
    nuevoNodo->CodCliente = CodCliente;
    nuevoNodo->dni = dni;
    strncpy(nuevoNodo->nombre, nombre, 30);
    nuevoNodo->nombre[29] = '\0'; // Asegura que la cadena esté terminada en nulo
    nuevoNodo->sgte = NULL;
    return nuevoNodo;
}

void insertar_Clientes(struct LES_Clientes **ini, int CodCliente, int dni, char *nombre) {
    struct LES_Clientes *nv = crearNodoCliente(nombre, CodCliente, dni);
    if (*ini == NULL) {
        *ini = nv;
    } else {
        struct LES_Clientes *aux = *ini;
        while (aux->sgte != NULL) {
            aux = aux->sgte;
        }
        aux->sgte = nv;
    }
}

struct LES_Clientes* cargarCSV_Clientes(char *nombreArchivo) {
    
    
	FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return NULL;
    }
    char linea[1024];  // Buffer para leer cada línea del archivo
    struct LES_Clientes *ini = NULL;

    // Leer línea por línea el archivo CSV
    char nombre[30];
    int CodCliente;
    int dni;
    while (fgets(linea, 1024, archivo)) {
    	linea[strcspn(linea, "\n")] = '\0';
        sscanf(linea, "%d,%d,%29[^,]", &CodCliente, &dni, nombre);
        insertar_Clientes(&ini, CodCliente, dni, nombre);
        
    }
    fclose(archivo);
    return ini;
}





struct Pila_Tareas_Pendientes* crearNodoTarea(int codTecnico, char *nombreTecnico, int opcion, int tarea, char *nombreTarea, int orden, int tardado) {
    struct Pila_Tareas_Pendientes *nuevoNodo = (struct Pila_Tareas_Pendientes*)malloc(sizeof(struct Pila_Tareas_Pendientes));
    if (nuevoNodo == NULL) {
        perror("Error en la asignación de memoria");
        return NULL;
    }
    nuevoNodo->codTecnico = codTecnico;
    strncpy(nuevoNodo->nombreTecnico, nombreTecnico, 49);
    nuevoNodo->nombreTecnico[49] = '\0'; // Asegura que la cadena esté terminada en nulo
    nuevoNodo->opcion = opcion;
    nuevoNodo->tarea = tarea;
    strncpy(nuevoNodo->nombreTarea, nombreTarea, 49);
    nuevoNodo->nombreTarea[49] = '\0'; // Asegura que la cadena esté terminada en nulo
    nuevoNodo->orden = orden;
    nuevoNodo->tardado = tardado;
    nuevoNodo->sgte = NULL;
    return nuevoNodo;
}

void insertar_Tarea(struct Pila_Tareas_Pendientes **tope, int codTecnico, char *nombreTecnico, int opcion, int tarea, char *nombreTarea, int orden, int tardado) {
    struct Pila_Tareas_Pendientes *nv = crearNodoTarea(codTecnico, nombreTecnico, opcion, tarea, nombreTarea, orden, tardado);
    
    nv->sgte = *tope;
    *tope = nv;
    
}

struct Pila_Tareas_Pendientes* cargarCSV_TareasPendientes(char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return NULL;
    }

    char linea[1024];  // Buffer para leer cada línea del archivo
    struct Pila_Tareas_Pendientes *tope = NULL;

    
    int codTecnico, opcion, tarea, orden, tardado;
    char nombreTecnico[50];
    char nombreTarea[50];

    while (fgets(linea, 1024, archivo)) {
        sscanf(linea, "%d,%49[^,],%d,%d,%49[^,],%d,%d", &codTecnico, nombreTecnico, &opcion, &tarea, nombreTarea, &orden, &tardado);
        insertar_Tarea(&tope, codTecnico, nombreTecnico, opcion, tarea, nombreTarea, orden, tardado);
    }

    fclose(archivo);
    return tope;
}

void desapilar_ordenes(struct Pila_Tareas_Pendientes **ds, struct Pila_Tareas_Pendientes **tp) {
    
	if (*tp == NULL) {
        *ds = NULL;
    } else {
        *ds = *tp;
        *tp = (*tp)->sgte;
        (*ds)->sgte = NULL;
    }
}

int vacia_pila(struct Pila_Tareas_Pendientes *tp){
    int vac;
    if (tp == NULL){
        vac=1;
    }else{
        vac=0;
    }
    return vac;
}

// Función para agregar una tarea pendiente a la pila
void agregarTareaPila(struct Pila_Tareas_Pendientes **pila_tareas_pendientes, struct Pila_Tareas_Pendientes *nueva_tarea) {
    nueva_tarea->sgte = *pila_tareas_pendientes;
    *pila_tareas_pendientes = nueva_tarea;
}

// Función para encolar un trabajo
void encolarTrabajo(struct Cola_Trabajos **entrada, struct Cola_Trabajos **salida, struct Cola_Trabajos *nuevo_trabajo) {
    if (*entrada == NULL) {
        *entrada = nuevo_trabajo;
        *salida = nuevo_trabajo;
    } else {
        (*entrada)->sgte = nuevo_trabajo;
        *entrada = nuevo_trabajo;
    }
}

// Función principal para dar de alta un nuevo trabajo
void altaTrabajo(struct Cola_Trabajos **entrada, struct Cola_Trabajos **salida, struct LES_Clientes *clientes, struct LES_Tecnicos *tecnicos, struct LED_Tareas *tareas, struct Pila_Tareas_Pendientes **pila_tareas_pendientes) {
    // Crear nuevo trabajo
    struct Cola_Trabajos *nuevo_trabajo = (struct Cola_Trabajos *) malloc(sizeof(struct Cola_Trabajos));
    if (nuevo_trabajo == NULL) {
        printf("Error: No se pudo asignar memoria para el nuevo trabajo.\n");
        return;
    }

    printf("Ingrese los datos del nuevo trabajo:\n");
    printf("Ingrese la Opcion: ");
    scanf("%d", &nuevo_trabajo->opcion);
    fflush(stdin);
    printf("ID de trabajo: ");
    scanf("%d", &nuevo_trabajo->id_trabajo);
    fflush(stdin);
	printf("Codigo de tecnico: ");
    scanf("%d", &nuevo_trabajo->codTecnico);
    fflush(stdin);
    printf("Codigo de cliente: ");
    scanf("%d", &nuevo_trabajo->codCliente);
    fflush(stdin);
    printf("Ubicacion: ");
    scanf("%s", nuevo_trabajo->ubicacion);
    fflush(stdin);
    printf("Altura: ");
    scanf("%d", &nuevo_trabajo->altura);
    fflush(stdin);
    printf("Duracion: ");
    scanf("%d", &nuevo_trabajo->duracion);
    fflush(stdin);
    printf("Ingrese la fecha: (dd/mm/aaaa): ");
    printf("Dia: ");
    scanf("%d",&nuevo_trabajo->fecha_fin.dia);
    fflush(stdin);
    printf("Mes: ");
    scanf("%d",&nuevo_trabajo->fecha_fin.mes);
    fflush(stdin);
    printf("Anio: ");
    scanf("%d",&nuevo_trabajo->fecha_fin.anio);
    fflush(stdin);

    // Verificar que el cliente y el técnico existan
    struct LES_Clientes *cliente_actual = clientes;
    while (cliente_actual != NULL) {
        if (cliente_actual->CodCliente == nuevo_trabajo->codCliente) {
            break;
        }
        cliente_actual = cliente_actual->sgte;
    }
    if (cliente_actual == NULL) {
        printf("Error: El cliente no existe.\n");
        free(nuevo_trabajo);
        return;
    }

    struct LES_Tecnicos *tecnico_actual = tecnicos;
    while (tecnico_actual != NULL) {
        if (tecnico_actual->codTecnico == nuevo_trabajo->codTecnico) {
            break;
        }
        tecnico_actual = tecnico_actual->sgte;
    }
    if (tecnico_actual == NULL) {
        printf("Error: El técnico no existe.\n");
        free(nuevo_trabajo);
        return;
    }

    // Encolar el nuevo trabajo
    nuevo_trabajo->sgte = NULL;
    encolarTrabajo(entrada, salida, nuevo_trabajo);

    // Cargar tareas correspondientes a la pila de tareas pendientes
    struct LED_Tareas *tarea_actual = tareas;
    while (tarea_actual != NULL) {
        if (tarea_actual->opcion == nuevo_trabajo->opcion) {
            struct Pila_Tareas_Pendientes *nueva_tarea = (struct Pila_Tareas_Pendientes *) malloc(sizeof(struct Pila_Tareas_Pendientes));
            if (nueva_tarea == NULL) {
                printf("Error: No se pudo asignar memoria para la nueva tarea pendiente.\n");
                // Liberar memoria asignada a nuevo_trabajo
                free(nuevo_trabajo);
                return;
            }
            nueva_tarea->codTecnico = nuevo_trabajo->codTecnico;
            nueva_tarea->opcion = nuevo_trabajo->opcion;
            nueva_tarea->tarea = tarea_actual->tarea;
            nueva_tarea->orden = tarea_actual->orden;
            nueva_tarea->tardado = tarea_actual->estimado;
            strcpy(nueva_tarea->nombreTecnico, tecnico_actual->nombre);
            strcpy(nueva_tarea->nombreTarea, tarea_actual->nombre);
            nueva_tarea->sgte = NULL;
            agregarTareaPila(pila_tareas_pendientes, nueva_tarea);

        }
        tarea_actual = tarea_actual->sgte;
    }
}


// Función para escribir los datos de la LES en un archivo CSV
void escribirCSV_opciones(struct LES_Opciones *nodo) {
    
    FILE *archivo_opciones=fopen("Opciones.csv","w");
    if (archivo_opciones == NULL) {
        printf("Error al abrir el archivo\n");
        return;
    }
    
    while (nodo != NULL) {
        fprintf(archivo_opciones, "%d,%s,%.2f\n", nodo->id_opcion, nodo->nombre, nodo->mano_obra);
        nodo = nodo->sgte;
    }

    fclose(archivo_opciones);
}

// Función para escribir los datos de la LED en un archivo CSV
void escribir_csv_tareas(struct LED_Tareas *inicio) {
    FILE *archivo_tareas = fopen("Tareas.csv", "w");
    if (archivo_tareas == NULL) {
        printf("Error al abrir el archivo para escritura.\n");
        return;
    }
    struct LED_Tareas *actual = inicio;
    while (actual != NULL) {
        fprintf(archivo_tareas, "%d,%d,%s,%d,%d\n", actual->opcion, actual->tarea, actual->nombre, actual->orden, actual->estimado);
        actual = actual->sgte;
    }
    fclose(archivo_tareas); // <-- Agregado
}

//Cargado de los archivos CSV


void escribirCSV_arbol_recursivo(struct ABB_Materiales *nodo, FILE *archivo) {
    if (nodo != NULL) {
        fprintf(archivo, "%d,%d,%s,%d,%s,%.2f\n", nodo->opcion, nodo->codigo, nodo->nombre_material, nodo->cantidad, nodo->unidad, nodo->costo_unitario);
        escribirCSV_arbol_recursivo(nodo->izq, archivo);
        escribirCSV_arbol_recursivo(nodo->der, archivo);
    }
}

void escribirCSV_arbol(struct ABB_Materiales *nodo) {
    FILE *archivo = fopen("Materiales.csv", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para escritura.\n");
        return;
    }

    //printf("Archivo abierto para escritura.\n");

    escribirCSV_arbol_recursivo(nodo, archivo);

    fclose(archivo);
    //printf("Archivo cerrado.\n");
}

void escribirCSV_tecnicos(struct LES_Tecnicos *nodo) {
    FILE *archivo = fopen("Tecnicos.csv", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para escritura.\n");
        return;
    }
    while (nodo != NULL) {
        fprintf(archivo, "%d,%d,%s\n", nodo->codTecnico, nodo->dni, nodo->nombre);
        nodo = nodo->sgte;
    }
    fclose(archivo); // <-- Agregado
}

void escribirCSV_Clientes(struct LES_Clientes *nodo) {
    FILE *archivo = fopen("Clientes.csv", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para escritura.\n");
        return;
    }
    while (nodo != NULL) {
        fprintf(archivo, "%d,%d,%s\n", nodo->CodCliente, nodo->dni, nodo->nombre);
        nodo = nodo->sgte;
    }
    fclose(archivo); // <-- Agregado
}

void escribirCSV_trabajos(struct Cola_Trabajos **entrada, struct Cola_Trabajos **salida) {
    FILE *archivo = fopen("Trabajos.csv", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para escritura.\n");
        return;
    }

    struct Cola_Trabajos *nodo;
    while (!vacia_cola(*salida)) {
        desencolar_trabajos(&nodo, entrada, salida);
        if (nodo != NULL) {
            /*printf("Escribiendo nodo: %d,%d,%d,%d,%s,%d,%d,%d,%d,%d\n",
                   nodo->opcion, nodo->id_trabajo, nodo->codTecnico,
                   nodo->codCliente, nodo->ubicacion, nodo->altura,
                   nodo->duracion, nodo->fecha_fin.dia, nodo->fecha_fin.mes, nodo->fecha_fin.anio);*/
            fprintf(archivo, "%d,%d,%d,%d,%s,%d,%d", nodo->opcion, nodo->id_trabajo, nodo->codTecnico, nodo->codCliente, nodo->ubicacion, nodo->altura, nodo->duracion);
            if (nodo->fecha_fin.dia != 0) {
                fprintf(archivo, ",%d/%d/%d", nodo->fecha_fin.dia, nodo->fecha_fin.mes, nodo->fecha_fin.anio);
            }
            fprintf(archivo, "\n");
        } else {
            printf("Nodo nulo encontrado.\n");
        }
    }

    fclose(archivo);
    //printf("Escritura de archivo completada.\n");
}

void escribirCSV_TareasPendientes(struct Pila_Tareas_Pendientes **tope) {
    FILE *archivo = fopen("TareasPendientes.csv", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para escritura.\n");
        return;
    }
    
    struct Pila_Tareas_Pendientes *nodo = NULL;
    while (!vacia_pila(*tope)) { // Usa *tope en vez de nodo
        desapilar_ordenes(&nodo, tope);
        if (nodo != NULL) { // Verifica que nodo no sea NULL
            //puts(nodo->nombreTarea);
            fprintf(archivo, "%d,%s,%d,%d,%s,%d,%d\n", nodo->codTecnico, nodo->nombreTecnico, nodo->opcion, nodo->tarea, nodo->nombreTarea, nodo->orden, nodo->tardado);
            free(nodo); // Libera la memoria del nodo desapilado
        }
    }

    fclose(archivo);
}