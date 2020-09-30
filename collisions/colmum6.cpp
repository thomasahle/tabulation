#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unordered_map>
#include <algorithm>
#include <vector>


static uint64_t rand64() {
   // we don't know how many bits we get from rand(),
   // but it is at least 16, so we concattenate a couple.
   uint64_t r = 0;
   for (int i = 0; i <= 4; i++) {
      r <<= 16;
      r ^= rand();
   }
   return r;
}

uint64_t SquaredCollisions (std::vector<uint64_t> & hashes) {
   std::sort(hashes.begin(),hashes.end());

   uint64_t res = 0;
   uint64_t start = hashes[0];
   uint64_t runlength = 1;
   for (size_t hnb = 1; hnb < hashes.size(); hnb++) {
      if (hashes[hnb] == start) {
         runlength++;
      } else {
         res += runlength*(runlength-1)/2;
         start = hashes[hnb];
         runlength = 1;
      }
   }
   res += runlength*(runlength-1)/2;
   return res;
}

int main() {
   srand(123);
   for (int b = 1; b <= 16; b++)
   for (int i = 0; i < 3; i++) {
      uint32_t a1 = rand64();
      uint32_t a2 = rand64();
      uint32_t a3 = rand64();
      uint32_t a4 = rand64();
      std::vector<uint64_t> keys;
      for (int rep = 0; rep < 1<<20; rep++) {
         uint64_t key = rand64() % (1ull<<4*b);
         keys.push_back(key);
      }
      std::sort(keys.begin(), keys.end());
      //printf("Made %lu (nnd) keys\n", keys.size());
      std::vector<uint64_t> hashes;
      int distinct = 0;
      uint64_t last = 0;
      for (const auto &key : keys) {
         if (key == last)
            continue;
         last = key;
         distinct++;
         uint64_t kkey = key;
         uint32_t x1 = (kkey % (1<<b)) << (32-b);
         kkey >>= b;
         uint32_t x2 = (kkey % (1<<b)) << (32-b);
         kkey >>= b;
         uint32_t x3 = (kkey % (1<<b)) << (32-b);
         kkey >>= b;
         uint32_t x4 = (kkey % (1<<b)) << (32-b);
         kkey >>= b;
         uint64_t val = (uint64_t)a1*x1 + (uint64_t)a2*x2 + (uint64_t)a3*x3 + (uint64_t)a4*x4;
         //uint64_t val = (uint64_t)(a1+x1)*(a2+x2) + (uint64_t)(a3+x3)*(a4+x4);
         //uint64_t val = (uint64_t)(a1^x1)*(a2^x2) + (uint64_t)(a3^x3)*(a4^x4);
         hashes.push_back(val);
      }
      uint64_t colls = SquaredCollisions(hashes);
      printf("b=%d, keys=%d, c=%llu\n", b, distinct, colls);
   }
   return 0;
}
