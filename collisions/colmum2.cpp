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
   for (int w = 1; w < 6; w++)
   for (int i = 0; i < 10; i++) {
      uint64_t a1 = rand128() ;
      uint64_t a2 = rand128() ;
      uint64_t a3 = rand128() ;
      uint64_t a4 = rand128() ;
      uint64_t a5 = rand128() ;
      uint64_t a6 = rand128() ;
      uint64_t a7 = rand128() ;
      uint64_t a8 = rand128() ;
      uint64_t a11 = rand128();
      uint64_t a12 = rand128();
      uint64_t a13 = rand128();
      uint64_t a14 = rand128();
      uint64_t a15 = rand128();
      uint64_t a16 = rand128();
      uint64_t a17 = rand128();
      uint64_t a18 = rand128();
      //printf("%llu", a1);
      std::unordered_map<uint64_t, uint64_t> cnts_1;
      std::unordered_map<uint64_t, uint64_t> cnts_2;
      for (int x1 = -(1<<w)+1; x1 < 1<<w; x1++)
      for (int x2 = -(1<<w)+1; x2 < 1<<w; x2++)
      for (int x3 = -(1<<w)+1; x3 < 1<<w; x3++)
      for (int x4 = -(1<<w)+1; x4 < 1<<w; x4++)
      for (int x5 = -(1<<w)+1; x5 < 1<<w; x5++)
      for (int x6 = -(1<<w)+1; x6 < 1<<w; x6++)
      for (int x7 = -(1<<w)+1; x7 < 1<<w; x7++)
      for (int x8 = -(1<<w)+1; x8 < 1<<w; x8++)
      {
         int64_t y1 = a1 * (int64_t)x1 * (1 << (32 - w));
         int64_t y2 = a2 * (int64_t)x2 * (1 << (32 - w));
         int64_t y3 = a3 * (int64_t)x3 * (1 << (32 - w));
         int64_t y4 = a4 * (int64_t)x4 * (1 << (32 - w));
         int64_t y5 = a5 * (int64_t)x5 * (1 << (32 - w));
         int64_t y6 = a6 * (int64_t)x6 * (1 << (32 - w));
         int64_t y7 = a7 * (int64_t)x7 * (1 << (32 - w));
         int64_t y8 = a8 * (int64_t)x8 * (1 << (32 - w));
         int64_t y11 = a11 * (int64_t)x1 * (1 << (32 - w));
         int64_t y12 = a12 * (int64_t)x2 * (1 << (32 - w));
         int64_t y13 = a13 * (int64_t)x3 * (1 << (32 - w));
         int64_t y14 = a14 * (int64_t)x4 * (1 << (32 - w));
         int64_t y15 = a15 * (int64_t)x5 * (1 << (32 - w));
         int64_t y16 = a16 * (int64_t)x6 * (1 << (32 - w));
         int64_t y17 = a17 * (int64_t)x7 * (1 << (32 - w));
         int64_t y18 = a18 * (int64_t)x8 * (1 << (32 - w));
         cnts_1[y1 + y2 + y3 + y4 + y5 + y6 + y7 + y8] += 1;
         cnts_2[y11 + y12 + y13 + y14 + y15 + y16 + y17 + y18] += 1;
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
