<h1 align="center">🛠️ Gestión de Instalaciones y Órdenes de Trabajo</h1>
<h3 align="center">Sistema de gestión desarrollado en C</h3>

<p align="center">
  <img src="https://img.shields.io/badge/Lenguaje-C-A8B9CC?style=for-the-badge&logo=c&logoColor=white" alt="Lenguaje C">
  <img src="https://img.shields.io/badge/Compilador-GCC-5C6E8C?style=for-the-badge&logo=gnu&logoColor=white" alt="GCC">
  <img src="https://img.shields.io/badge/Estructuras-Listas%20%7C%20Pilas%20%7C%20Colas-0A7EA4?style=for-the-badge" alt="Estructuras de datos">
  <img src="https://img.shields.io/badge/Persistencia-CSV-239120?style=for-the-badge" alt="Archivos CSV">
</p>

Trabajo Práctico Integrador desarrollado en **lenguaje C** para el área de **Algoritmos y Estructuras de Datos** (2.° año de Ingeniería en Informática, UGD).

El sistema administra el ciclo completo de una empresa de instalaciones de seguridad electrónica y perimetral: catálogo de servicios, presupuestos dinámicos de mano de obra e insumos, asignación de órdenes de trabajo a técnicos y desglose de tareas operativas. La información se mantiene en estructuras dinámicas en memoria y se sincroniza con archivos `.csv`.

---

## 📑 Índice

- [Contexto y créditos](#-contexto-del-proyecto-y-créditos)
- [Estructuras de datos](#-estructuras-de-datos-implementadas)
- [Funcionalidades](#-funcionalidades-principales)
- [Estructura del proyecto](#-estructura-del-proyecto)
- [Compilación y ejecución](#-cómo-compilar-y-ejecutar)

---

## 👥 Contexto del proyecto y créditos

Este trabajo refleja el **esfuerzo colaborativo de cuatro estudiantes**, desarrollado durante nuestro segundo año de carrera. La versión publicada contiene el código fuente del proyecto final entregado y defendido para la aprobación de la materia, demostrando el manejo manual de memoria y el dominio de estructuras de datos complejas.

**Equipo de desarrolladores:**

- G. Casale
- E. Centurion
- M. Landro
- **Tomás Moroz** — curador de este repositorio

---

## 🧠 Estructuras de datos implementadas

El proyecto implementa desde cero cinco estructuras dinámicas en RAM mediante `malloc` y `free`, interconectadas para resolver las operaciones del sistema.

| Estructura | Nombre en código | Función dentro del sistema |
|---|---|---|
| **Lista simplemente enlazada (LES)** | `LES_Opciones`, `LES_Clientes`, `LES_Tecnicos` | Almacena el catálogo de servicios, la cartera de clientes y el padrón de técnicos, con inserción al final. |
| **Lista doblemente enlazada (LED)** | `LED_Tareas` | Gestiona las subtareas de cada servicio mediante los enlaces `ant` y `sgte`, manteniendo el orden mediante `BuscarAnterior`. |
| **Árbol binario de búsqueda (ABB)** | `ABB_Materiales` | Indexa materiales por código, ubicando los menores a la izquierda (`izq`) y los mayores a la derecha (`der`). |
| **Cola FIFO** | `Cola_Trabajos` | Administra las órdenes de instalación mediante los punteros `entrada` y `salida`, diferenciando trabajos pendientes y finalizados. |
| **Pila LIFO** | `Pila_Tareas_Pendientes` | Registra las tareas pendientes asignadas a cada técnico mediante el puntero `tope`. |

---

## ⚙️ Funcionalidades principales

### 1. 💰 Presupuestación dinámica integrada

Combina tres estructuras de datos para calcular presupuestos:

- Recorre el catálogo de servicios en `LES_Opciones`.
- Calcula recursivamente el costo de los insumos del árbol `ABB_Materiales` mediante `calcular_monto_materiales`.
- Suma los tiempos de ejecución de `LED_Tareas` mediante `calcular_duracion`.
- Informa el costo final y la duración estimada en horas de cada servicio.

### 2. 🧩 Alta de servicios configurables

Permite incorporar opciones comerciales y asociarles subtareas en la lista doblemente enlazada y materiales en el árbol binario.

### 3. 🧾 Alta transaccional de órdenes de trabajo

- Verifica la existencia del cliente en `LES_Clientes` y del técnico en `LES_Tecnicos`.
- Encola el nuevo trabajo en `Cola_Trabajos`.
- Apila las subtareas correspondientes al servicio en `Pila_Tareas_Pendientes`.

### 4. 🔎 Consulta de trabajos pendientes por técnico

Desencola órdenes respetando FIFO, filtra las asignadas al técnico consultado que todavía no tienen fecha de finalización (`0/0/0`) y utiliza una cola auxiliar (`entrada2`, `salida2`) para reconstruir la estructura original sin perder información.

### 5. 💾 Persistencia automática en CSV

- Carga inicial de siete archivos `.csv` mediante `fgets` y `sscanf`.
- Guarda las estructuras actualizadas al finalizar la sesión.
- Incluye recorrido preorden recursivo para el árbol y vaciado controlado de pilas y colas.

---

## 📂 Estructura del proyecto

| Archivo | Descripción |
|---|---|
| `ESTRUCTURAS.h` | Definición de `structs` y nodos de las estructuras de datos. |
| `Funciones.h` | Primitivas de listas, pilas, colas y árboles; lógica de negocio y manejo de CSV. |
| `Prueba.c` | Programa principal, validación de entradas por consola y menú interactivo. |
| `Opciones.csv` | Catálogo de opciones o servicios. |
| `Tareas.csv` | Tareas vinculadas a los servicios. |
| `Materiales.csv` | Materiales e insumos de instalación. |
| `Tecnicos.csv` | Padrón de técnicos. |
| `Clientes.csv` | Padrón de clientes. |
| `Trabajos.csv` | Órdenes de trabajo. |
| `TareasPendientes.csv` | Tareas pendientes por técnico. |

---

## 🚀 Cómo compilar y ejecutar

Asegurate de tener los archivos `.csv` en el mismo directorio de trabajo que el ejecutable y el código fuente.

```bash
gcc Prueba.c -o gestion_instalaciones
./gestion_instalaciones
```

> **Importante:** la aplicación necesita los archivos CSV para cargar los datos existentes y guardar los cambios. Conservá sus nombres y ubicaciones esperados por el programa.

---

<p align="center"><b>Algoritmos y Estructuras de Datos · C · Memoria dinámica · Persistencia CSV</b></p>
