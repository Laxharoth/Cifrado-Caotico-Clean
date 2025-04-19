#include <math.h>
#include <omp.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ConfigStructure.c"
#include "ConfigStructure.h"
#include "bitarray.c"
#include "bitarray.h"
#include "roulete.c"
#include "roulete.h"

void hamming_distance(uint64_t *const a, uint64_t *const b, const uint64_t size,
                      uint64_t *const distance);
double calculateStandardDeviation(int N, double data[]);

/**
 * @brief This experiment generates a random number stream using the Chaotic
 * Roulette PRNG, then compares the Hamming distance with the generated stream
 * using different seeds.
 *
 * @return int
 */
int main() {
    Configuracion config;
    readConfigFile("config.txt", &config);
    uint64_t *const random_buffer = (uint64_t *)malloc(config.file_size);
    uint64_t *const random_buffer2 = (uint64_t *)malloc(config.file_size);
    struct rouleteConfig roulete_config;
    struct rouleteConfig roulete_config2;
    size_t total_checks = config.num_maps * (sizeof(uint64_t) << 3);
    double total_distance = 0;
    double *each_distance = (double *)malloc(total_checks * sizeof(double));
    uint64_t *seed = (uint64_t *)malloc(config.num_maps * sizeof(uint64_t) * 3);
    memset(seed, 0, config.num_maps * sizeof(uint64_t) * 3);
    generate_seed(&config, seed);
    size_t counter = 1;
    initilizale_roulete(&config, &roulete_config, seed);
    roulete_generator(random_buffer, config.file_size, &roulete_config);
    delete_roulete(&roulete_config);

    for (size_t j = 0; j < total_checks; j++, counter++) {
        printf("check %zu | %zu\n", counter, total_checks);
        TOGGLE((char *)seed, j);
        initilizale_roulete(&config, &roulete_config2, seed);
        TOGGLE((char *)seed, j);  // This is used to recover the original seed
                                  // and modify the a single bit per iteration

        roulete_generator(random_buffer2, config.file_size, &roulete_config2);
        uint64_t distance;
        hamming_distance(random_buffer, random_buffer2, config.file_size / 8,
                         &distance);
        total_distance += distance;
        const double double_distance =
            (double)(distance) / (double)(config.file_size * 8);
        each_distance[j] = double_distance;

        delete_roulete(&roulete_config2);
    }

    double avg_distance = (double)(total_distance) /
                          (double)(config.file_size * 8) / total_checks;
    double std_distance = calculateStandardDeviation(counter, each_distance);
    printf("total distance: %f\n", avg_distance);
    printf("distance STD: %f\n", std_distance);

    FILE *f = fopen("hamming.txt", "w");

    for (int i = 0; i < total_checks; i++) fprintf(f, "%f ", each_distance[i]);

    fclose(f);
    free(random_buffer);
    free(random_buffer2);
    free(each_distance);

    return 0;
}

void hamming_distance(uint64_t *const a, uint64_t *const b, const uint64_t size,
                      uint64_t *const distance) {
    uint64_t sum = 0;
    uint64_t i, j;
    // #pragma omp parallel for reduce(+ : sum)
    for (i = 0; i < size; i++) {
        const uint64_t diff = a[i] ^ b[i];
        for (j = 0; j < 64ull; j++) sum += (diff >> j) & 1;
    }
    *distance = sum;
}

double calculateStandardDeviation(int N, double data[]) {
    double sum = 0;
    for (int i = 0; i < N; i++) {
        sum += data[i];
    }
    double mean = sum / N;

    double squared_sum = 0;
    for (int i = 0; i < N; i++) {
        squared_sum += pow(data[i] - mean, 2);
    }

    double variance = squared_sum / N;
    double standardDeviation = sqrt(variance);

    return standardDeviation;
}
