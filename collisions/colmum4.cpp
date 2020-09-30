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
   for (int i = 0; i < 10; i++) {
      uint32_t a1 = rand128() ;
      uint32_t a2 = rand128() ;
      uint32_t a3 = rand128() ;
      uint32_t a4 = rand128() ;
      std::unordered_map<uint64_t, uint64_t> cnts_1;
      std::unordered_map<uint64_t, uint64_t> cnts_2;
      for (int x1 = -(1<<w)+1; x1 < 1<<w; x1++)
      for (int x2 = -(1<<w)+1; x2 < 1<<w; x2++)
      {
         int64_t y1 = (int64_t)a1 * (int64_t)x1 * (1 << (32 - w));
         int64_t y2 = (int64_t)a2 * (int64_t)x2 * (1 << (32 - w));
         int64_t y3 = (int64_t)a3 * (int64_t)x1 * (1 << (32 - w));
         int64_t y4 = (int64_t)a4 * (int64_t)x2 * (1 << (32 - w));
         cnts_1[y1 + y2] += 1;
         cnts_2[y3 + y4] += 1;
      }
      uint64_t zeros = 0;
      for (const auto &pair : cnts_1) {
         uint64_t v1 = pair.second;
         uint64_t v2 = cnts_2[-pair.first];
         zeros += v1*v2;
      }
      printf("w=%d, z=%llu\n", w, zeros);
   }
   return 0;
}
