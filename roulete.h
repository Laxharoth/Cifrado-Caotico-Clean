#ifndef __ROULETE_H__
#define __ROULETE_H__

#include <stdint.h>
#include <stdlib.h>

#include "ConfigStructure.h"
#include "chaotic_map.h"

const static uint64_t epsilon = 65535;
/**
 * @brief A structure to store the lookup table for the chaotic map and its
 * state.
 *
 */
struct chaotic_lookup_table {
    uint64_t *lookup_table;
    uint64_t parameter_r;
    uint64_t parameter_l;
    uint64_t last_generated;
};

/**
 * @brief A structure to store the configuration of the roulete generator.
 *
 */
struct rouleteConfig {
    struct chaotic_lookup_table *roulete;
    struct chaotic_lookup_table **roulete_cycle;
    uint8_t *raw;
    uint64_t lu_table_mask;
    uint64_t lu_raw_mask;
    uint64_t epsilon;
    uint8_t roulette_selector;
    uint64_t lu_table_position;
    uint64_t H;
    uint64_t renyi_beta;
    uint64_t renyi_lambda;
};
/**
 * @brief Function to generate a seed for the random number generator. (Should
 * only be used for testing)
 *
 * @param config Configuration to obtain the required size for the seed of the
 * roulette.
 * @param seed A seed to feed srand. and make the generator consistent for the
 * sake of testing.
 */
void generate_seed(const Configuracion *const config, uint64_t *const seed);
/**
 * @brief
 *
 * @param config Configuration to set number of maps and the size of the lookup
 * table.
 * @param roulete_config structure to store the lookup table and its state.
 * @param seed seed to initialize the roulette random number generator.
 */
void initilizale_roulete(const Configuracion *const config,
                         struct rouleteConfig *roulete_config,
                         const uint64_t *const seed);
/**
 * @brief Function to clear memory used to store roulette.
 *
 * @param config Configuration containing the roulette.
 */
void delete_roulete(struct rouleteConfig *config);
uint64_t random_select_coupled_chaotic_map_lookuptable(
    struct rouleteConfig *roulete_config);
void roulete_generator(uint64_t *const buffer, const uint64_t bytes_2_generate,
                       struct rouleteConfig *rouleteConfig);

#endif  //__ROULETE_H__