#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unordered_map>


static __uint128_t rand128() {
   // we don't know how many bits we get from rand(),
   // but it is at least 16, so we concattenate a couple.
   __uint128_t r = 0;
   for (int i = 0; i < 8; i++) {
      r <<= 16;
      r ^= rand();
   }
   return r;
}
int main() {
   srand(123);
   for (int w = 1; w <= 16; w++)
   for (int i = 0; i < 3; i++) {
      uint64_t a1 = rand128();
      uint64_t a2 = rand128();
      uint64_t a3 = rand128();
      uint64_t a4 = rand128();
      std::unordered_map<uint64_t, uint64_t> cnts_1;
      std::unordered_map<uint64_t, uint64_t> cnts_2;
      for (int64_t x1 = -(1<<w)+1; x1 < 1<<w; x1++)
      for (int64_t x2 = -(1<<w)+1; x2 < 1<<w; x2++)
      {
         cnts_1[(a1*x1 + a2*x2) % (1 << 2*w)] += 1;
         cnts_2[(a3*x1 + a4*x2) % (1 << 2*w)] += 1;
      }
      uint64_t zeros = 0;
      for (const auto &pair : cnts_1) {
         uint64_t v1 = pair.second;
         uint64_t v2 = cnts_2[(1<<2*w)-pair.first];
         zeros += v1*v2;
      }
      printf("w=%d, z=%llu (+%lld)\n", w, zeros, (int64_t)zeros-(1ll<<(2*w+2)));
   }
   return 0;
}
