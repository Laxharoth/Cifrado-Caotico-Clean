#ifndef __CONFIGSTRUCTURE_H__
#define __CONFIGSTRUCTURE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

/**
 * @brief Estructura para cargar una configuracion para el generador de
 * numeros aleatorios. Esta configuración se carga desde un archivo de texto y
 * solo debería ser usada durante la fase de pruebas.
 *
 */
typedef struct {
    // parametros de renyi
    unsigned long long beta;
    unsigned long long lambda;
    unsigned long long n;
    // semilla aleatoria
    unsigned long long seed;
    // numero de bytes a escribir
    unsigned long long file_size;
    unsigned long long bulk_size;
    unsigned long long num_maps;
} Configuracion;

void readConfigFile(const char *filename, Configuracion *const config);

#endif