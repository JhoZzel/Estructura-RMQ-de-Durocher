# Proyecto: Estructura RMQ de Durocher (sin método de los Cuatro Rusos)

## Descripción

Este proyecto implementa y compara dos estructuras para resolver el problema de Range Minimum Query (RMQ):

- **Sparse Table** clásica (O(n log n) preprocesamiento, O(1) por consulta)
- **Durocher RMQ**, una estructura avanzada que logra **O(n)** de preprocesamiento y **O(1)** por consulta sin utilizar el método de los Cuatro Rusos.

El objetivo es validar la eficiencia teórica de la estructura de Durocher mediante pruebas unitarias y benchmarks reales, enfocándose en su uso práctico frente a la sparse table tradicional.

---

## Archivos principales

- `Durocher.ipynb`: Notebook con visualizaciones o análisis.
- `Durocher_RMQ.h`: Implementación de la estructura Durocher.
- `SparseTable.h`: Implementación clásica de sparse table.
- `CartesianTree.h`: Árbol cartesiano usado como base auxiliar.
- `benchmark.cpp`: Comparación de tiempos entre Durocher y Sparse Table.
- `test.h`, `unit_tests_dur.cpp`, `unit_tests_st.cpp`: Pruebas unitarias.
- `generating_tests_*.cpp`: Generación de datos de prueba.
- `img/`: Carpeta opcional para imágenes o diagramas.
- `random.h`: Utilidades para datos aleatorios.

---

## Detalles de implementación

**Durocher RMQ** trabaja dividiendo el arreglo original en bloques pequeños de tamaño \( k = \frac{\log n}{2} \). Luego:
- Se construye una sparse table sobre los mínimos de cada bloque.
- Se codifican todos los posibles "tipos" de bloques pequeños y se precomputan sus respuestas.
- La consulta final se resuelve combinando ambas partes en **O(1)**.

Esta técnica evita el método de los Cuatro Rusos y logra complejidad óptima teórica sin comprometer claridad de implementación.

---

## Objetivos alcanzados

- [x] Implementación completa de Durocher RMQ y Sparse Table.
- [x] Función `query(i, j)` en O(1) para ambas estructuras.
- [x] Preprocesamiento O(n) para Durocher.
- [x] Comparación empírica de tiempo y uso de memoria.
- [x] Verificación con búsqueda lineal para garantizar correctitud.

---