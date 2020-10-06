#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <algorithm>

static uint32_t murmur32(uint32_t k) {
    k ^= k >> 17;
    k *= 0xcc9e2d51;
    k ^= k >> 17;
    k *= 0x1b873593;
    k ^= k >> 17;
    return k;
}
static uint32_t murmur32_rot(uint32_t k) {
    k *= 0xcc9e2d51;
    k = (k << 15) | (k >> 17);
    k *= 0x1b873593;
    return k;
}
// H  H [x1]
// H -H [x2]
// = [H x1 + H x2]
//   [H x1 - H x2]
static void hadamard(int64_t* pt, uint64_t len) {
   // assert len is a power of 2
   if (len == 1)
      return;
   hadamard(pt, len/2);
   hadamard(pt+len/2, len/2);
   for (uint32_t i = 0; i < len/2; i++) {
      int64_t Hx1 = pt[i];
      int64_t Hx2 = pt[i+len/2];
      pt[i] = Hx1 + Hx2;
      pt[i+len/2] = Hx1 - Hx2;
   }
}
#define ibits 26
static int64_t f[1ull<<ibits]; // Too bit to be on stack
static int64_t fr[1ull<<ibits]; // Too bit to be on stack
int main() {
   for (int obit = 0; obit < 32; obit++) {
      memset(f, 0, 1ull<<ibits);
      printf("Testing bit %d\n", obit);
      for (uint64_t x = 0; x < 1ull<<ibits; x++) {
         f[x] = (int64_t)((murmur32((uint32_t)x) >> obit) & 1) * 2 - 1;
         fr[x] = (rand() & 1) * 2 - 1;
      }
      printf("Transforming\n");
      hadamard(f, 1ull<<ibits);
      hadamard(fr, 1ull<<ibits);
      //printf("%lld  %lld\n", f[0], fr[0]);
      // Now entry Hf[i] contains
      // H_i f,
      // S -> X_S(x) er vektoren prod_{i\in S} x_i = (-1)^(S dot i)
      // Så X_{1} = (x_1, x'_1, x''_1, ...)
      // Den xte række er jo  (-1)^(x dot i)  (i kolonne i)
      // Så ok, X_S er bare Hf[bin(S)]
      double ls[ibits+1];
      double lsr[ibits+1];
      std::fill(ls, ls+ibits+1, 0);
      std::fill(lsr, lsr+ibits+1, 0);
      for (uint64_t x = 0; x < 1ull<<ibits; x++) {
         int s = __builtin_popcount(x);
         ls[s] += (double)f[x]*(double)f[x];
         lsr[s] += (double)fr[x]*(double)fr[x];
      }
      //for (int i = 0; i <= ibits; i++) {
      for (int i = ibits; i <= ibits; i++) {
         printf("Level %d: %3.3f%% (%f, %f)\n", i,
               (ls[i]/(double)lsr[i]-1)*100, ls[i], lsr[i]);
      }
   }
}
