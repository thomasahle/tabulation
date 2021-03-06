# tabulation
Fast implementation of Tabulation Hashing for strings

# Usage
Tabulation hash comes with a strong random number generator to help seed your hash functions well.
```c
// Make generator
uint64_t seed[SEED_LENGTH] = new uint64_t{/* put 100 64bit numbers from https://www.random.org/ here */}
tab_genrator gen;
init_tab_generator(&gen, seed);

// Make some nearly independent hash functions
tab_hash h1, h2;
init_tab_hash(&h1, gen, 0);
init_tab_hash(&h2, gen, 1);

// Hash some data, streaming fasion
uint8_t bytes = ...
tab_process(&h1, &bytes, len_bytes);
tab_process(&h1, &more_bytes, len_more_bytes);

// Finalize hash value
printf("%llu", tab_finalize(&h1));

// Or just hash a value directly
printf("%llu", tab_hash(&h1, 2314234));
```

# Alternative stream api
That doesn't hide the state inside the hash function
```c
// Hash some data, streaming fasion
uint64_t state = 0;
state = tab_process(&h1, &bytes, len_bytes, state);
state = tab_process(&h1, &more_bytes, len_more_bytes, state);

// Finalize hash value
printf("%llu", tab_finalize(&h1, state));
```
