# 🛠️ Sistema de Gestión de Instalaciones y Órdenes de Trabajo en C

Trabajo Práctico Integrador desarrollado en **lenguaje C** para el área de **Algoritmos y Estructuras de Datos** (Ingeniería en Informática).

El sistema administra el ciclo completo de una empresa de instalaciones de seguridad electrónica y perimetral: catálogo de servicios, cálculo dinámico de presupuestos (mano de obra e insumos), asignación de órdenes de trabajo a técnicos y desglose de tareas operativas, sincronizando el estado en memoria dinámica con archivos `.csv`.

---

## 🧠 Estructuras de Datos Implementadas

El proyecto implementa desde cero cinco estructuras dinámicas en memoria RAM (`malloc` / `free`) interconectadas entre sí:

| Estructura | Nombre en Código | Rol en el Sistema |
| :--- | :--- | :--- |
| **Lista Simplemente Enlazada (LES)** | `LES_Opciones`, `LES_Clientes`, `LES_Tecnicos` | Almacena el catálogo de servicios base, la cartera de clientes y el padrón de técnicos mediante inserción al final. |
| **Lista Doblemente Enlazada (LED)** | `LED_Tareas` | Gestiona la secuencia de subtareas de cada servicio (`ant` y `sgte`), manteniendo el orden lógico de ejecución mediante inserción ordenada (`BuscarAnterior`). |
| **Árbol Binario de Búsqueda (ABB)** | `ABB_Materiales` | Indexa los insumos y materiales de instalación ordenados jerárquicamente por código (`izq` menores, `der` mayores) para optimizar su recorrido y costeo. |
| **Cola (FIFO)** | `Cola_Trabajos` | Administra las órdenes de instalación mediante punteros `entrada` y `salida`, diferenciando trabajos finalizados de pendientes. |
| **Pila (LIFO)** | `Pila_Tareas_Pendientes` | Registra mediante manejo de `tope` las tareas operativas pendientes asignadas a cada técnico tras el alta de una orden. |

---

## ⚙️ Funcionalidades Principales

1. **Presupuestación Dinámica Integrada (LES + ABB + LED):**
   * Recorre el catálogo de opciones (`LES_Opciones`), calcula de forma recursiva el costo total de insumos en el árbol binario (`calcular_monto_materiales` sobre `ABB_Materiales`) y suma los tiempos estimados de ejecución en la lista doble (`calcular_duracion` sobre `LED_Tareas`) para informar el costo final y la duración en horas de cada servicio.
2. **Alta de Servicios Configurables:**
   * Permite incorporar nuevas opciones comerciales junto con el desglose de sus subtareas en la lista doblemente enlazada y sus materiales asociados en el árbol binario.
3. **Alta Transaccional de Órdenes de Trabajo:**
   * Valida la integridad referencial verificando la existencia del cliente (`LES_Clientes`) y del técnico (`LES_Tecnicos`).
   * Encola el nuevo trabajo en `Cola_Trabajos` y dispara automáticamente en cascada el apilado de todas las subtareas correspondientes a ese servicio en `Pila_Tareas_Pendientes`.
4. **Consulta de Trabajos Pendientes por Técnico (Filtrado No Destructivo):**
   * Desencola órdenes de `Cola_Trabajos` respetando la disciplina FIFO, filtra aquellas asignadas al técnico consultado que aún no poseen fecha de finalización (`0/0/0`) y utiliza una cola auxiliar (`entrada2`, `salida2`) para reconstruir la estructura original sin pérdida de información.
5. **Persistencia Automática en CSV:**
   * Carga inicial mediante parseo con `fgets` y `sscanf` desde 7 archivos `.csv` y volcado automático de todas las estructuras actualizadas (incluyendo recorrido preorden recursivo para el árbol y vaciado controlado de pilas y colas) al finalizar la sesión.

---

## 📂 Estructura del Proyecto

* `ESTRUCTURAS.h` — Definición de `structs` y nodos de las estructuras de datos.
* `Funciones.h` — Primitivas de listas, pilas, colas y árboles, lógica de negocio y manejo de archivos CSV.
* `Prueba.c` — Programa principal, validación de entradas por consola y ciclo de menú interactivo.
* `*.csv` — Archivos de persistencia (`Opciones.csv`, `Tareas.csv`, `Materiales.csv`, `Tecnicos.csv`, `Clientes.csv`, `Trabajos.csv`, `TareasPendientes.csv`).

---

## 🚀 Cómo compilar y ejecutar

Asegurate de tener los archivos `.csv` en el mismo directorio que el código fuente y ejecutá:

```bash
gcc Prueba.c -o gestion_instalaciones
./gestion_instalaciones
