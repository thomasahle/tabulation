#define SEED_LENGTH = 100;
#define BLOCK_LENGTH = 256;

struct tab_generator {
   uint64_t seed[SEED_LENGTH];
}

void init_tab_generator(tab_generator* gen, uint64_t seed[SEED_LENGTH]) {
   for (int i = 0; i < SEED_LENGTH; i++)
      gen->seed[i] = seed[i];
}

uint64_t generate(tab_generator* gen, uint64_t x) {
   // TODO: Compute mod 2^89-1 or something
   uint64_t res = 0;
   for (int i = 0; i < SEED_LENGTH; i++) {
      res = res*x + gen->seed[i];
   }
   return res;
}

struct tab_hash {
   uint64_t utable[BLOCK_LENGTH];
   uint64_t ftable[8][256];
   uint64_t state;
}

void init_tab_hash(tab_hash* sec, tab_generator* gen, uint64_t seed) {
   // TODO: Use FFT to generate values more efficiently
   uint64_t x = seed;
   for (int i = 0; i < BLOCK_LENGTH; i++)
      sec->utable[i] = generate(gen, x++);
   for (int i = 0; i < 8; i++)
      for (int j = 0; j < 256; j++)
         sec->ftable[i][j] = generate(gen, x++);
}

uint64_t tab_process(*tab_secret, uint64_t x) {

}

uint64_t tab_hash(*tab_secret, uint64_t x) {

}
