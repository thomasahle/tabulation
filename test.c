#include <tab.h>
#include <stdio.h>

int main() {
   TAB_generator gen;
   TAB_init_generator(&gen, TAB_DEFAULT_SEED);

   TAB_hash hash;
   TAB_init_hash(&hash, &gen, 0);
   uint8_t data[8] = {1, 2, 4, 5, 6, 7, 9};
   uint64_t state = TAB_process(&hash, data, 8, 0);
   state = TAB_process(&hash, data, 8, state);
   printf("%llu\n", TAB_finalize(&hash, state));

   TAB_hash_64 hash64;
   TAB_init_hash_64(&hash64, &gen, 0);
   state = TAB_process_64(&hash64, data, 8, 0);
   printf("%llu\n", TAB_finalize_64(&hash64, state));
}
