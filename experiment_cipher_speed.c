#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "ConfigStructure.c"
#include "ConfigStructure.h"
#include "cipher.c"
#include "cipher.h"
#include "minmax.h"
#include "roulete.c"
#include "roulete.h"

// Set Sample size for time measurement
#define SAMPLE_SIZE 1000
#include "time_measure.h"

/**
 * @brief This experiment is used to measure the speed of the cipher.
 *
 * @return int
 */

int main() {
    // inicializar constantes
    const size_t block_size = 1024;
    const size_t block_size_as_u64 = block_size / sizeof(uint64_t);
    const size_t required_random_numbers = block_size_as_u64 * 2 + 1;
    const size_t stream_size = 1048576;  // 1 MB
    uint8_t hash = 0;

    uint8_t *const stream_start = (uint8_t *)malloc(stream_size);
    uint8_t *const block = (uint8_t *)malloc(block_size);

    // Cargar generador de números aleatorios
    Configuracion config;
    readConfigFile("config.txt", &config);
    // sobreescribir el tamaño del archivo por el numero deseado de números
    // aleatorios
    uint64_t *const random_buffer =
        (uint64_t *)malloc(required_random_numbers * sizeof(uint64_t));
    struct rouleteConfig roulete_config;
    uint64_t *seed =
        (uint64_t *)malloc(config.num_maps * sizeof(uint64_t) * 3 + 2);
    memset(seed, 0, config.num_maps * sizeof(uint64_t) * 3 + 2);
    generate_seed(&config, seed);
    initilizale_roulete(&config, &roulete_config, seed);

    double time_secs = time_exec(        // comienza ejecucion de cifrado
        size_t remaining = stream_size;  // inicializa el tamaño de cifrado
        uint8_t *stream = stream_start;  // inicializa el puntero de cifrado
        while (remaining) {
            roulete_generator(random_buffer,
                              required_random_numbers * sizeof(uint64_t),
                              &roulete_config);

            const size_t ciphered_size = min(block_size, remaining);
            if (memcpy((char *)block, stream, block_size) == NULL) {
                perror("Error while reading");
                exit(EXIT_FAILURE);
            }
            // padding for the last block
            if (ciphered_size < block_size) {
                memset(block + ciphered_size, 0, block_size - ciphered_size);
            }

            cipher((uint64_t *)block, random_buffer, block_size_as_u64,
                   required_random_numbers, 0, &hash, roulete_config.renyi_beta,
                   roulete_config.renyi_lambda);

            stream += ciphered_size;
            remaining -= ciphered_size;
        });
    printf("Velocidad de cifrado: %0.4f Gbps\n",
           stream_size * 8 / time_secs / 1e9);

    delete_roulete(&roulete_config);  // libera la memoria de la ruleta
    free(random_buffer);
    free(stream_start);

    return 0;
}