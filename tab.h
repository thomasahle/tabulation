#include <stdint.h>
#include <stddef.h>  /* size_t */
#include <string.h>  /* memcpy() */

#define TAB_SEED_LENGTH 100
#define TAB_BLOCK_LENGTH 256

static uint64_t TAB_DEFAULT_SEED[TAB_SEED_LENGTH] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100};

struct TAB_generator {
   // TODO: We could also let the user decide how many words they want to add.
   // Then we just store a pointer and a length and run the polynomial as deep
   // as needed.
   // Remember: If we store pointers in structs, we need to provide a free_generator
   // function to allow releasing the data.
   uint64_t seed[TAB_SEED_LENGTH];
};
typedef struct TAB_generator TAB_generator;

/*
 * Instantiate the random generator.
 */
void TAB_init_generator(TAB_generator* gen, uint64_t seed[TAB_SEED_LENGTH]);

// TODO: Would
// tab_generator* tab_new_generator(seed);
// Be a better API?

/*
 * Produce a single random value using the generator.
 * Can also be used as a single (strong) hash function h(x).
 */
uint64_t TAB_generate(TAB_generator* gen, uint64_t x);

struct TAB_hash {
   uint64_t nh_table[TAB_BLOCK_LENGTH];
   uint64_t tab_table[8][256];
   __uint128_t ms_table[TAB_BLOCK_LENGTH];
   uint64_t alpha;
   __uint128_t ms_extra;
};
typedef struct TAB_hash TAB_hash;

// More randomness for more security
struct TAB_hash_64 {
   uint64_t utable[TAB_BLOCK_LENGTH];
   uint64_t ftable[8][256];
};

struct TAB_hash_128 {
   uint64_t utable[TAB_BLOCK_LENGTH];
   uint64_t ftable[8][256];
};

/*
 * Initialize hash function using a generator and a seed.
 * The hash functions will be 100-independent, which is enough for nearly
 * anything - Jakob can you add something here?
 */
void TAB_init_hash(TAB_hash* hash, TAB_generator* gen, uint64_t seed);

/*
 * Process `len` bytes and return a state for further processing.
 * Can be called with `state = 0` when run the first time.
 * TODO: Is a single 64bit number enough state? Maybe we need to keep the length
 * to prevent extension attacks? Or can we just add the given individual lengths
 * as separate characters? That sounds fine to me. It's also nice that the partial
 * state is always a universal hash of what we've seen so far.
 */
uint64_t TAB_process(TAB_hash* hash, const uint8_t* const bytes, size_t len_bytes, uint64_t state);

/*
 * Apply a strong hash to the state.
 */
uint64_t TAB_finalize(TAB_hash* hash, uint64_t state);

/*
 * Convenience function for hashing a single value.
 * TODO: Is this actually different from calling tab_finalize(x)?
 */
static uint64_t TAB_hash_single(TAB_hash* hash, uint64_t x) {
   uint8_t bytes[8];
   memcpy(bytes, &x, sizeof(x));
   uint64_t state = TAB_process(hash, bytes, 8, 0);
   return TAB_finalize(hash, state);
}
