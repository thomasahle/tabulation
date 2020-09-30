#include <stdio.h>
int main() {
   unsigned int x1 = 1;
   unsigned int y1 = 0;
   unsigned int x2 = 0;
   unsigned int y2 = 1;
   for (int w = 1; w <= 10; w++) {
      int res = 0;
      for (unsigned int a1 = 0; a1 < 1<<w; a1++)
      for (unsigned int a2 = 0; a2 < 1<<w; a2++)
      for (unsigned int a3 = 0; a3 < 1<<w; a3++)
      for (unsigned int a4 = 0; a4 < 1<<w; a4++) {
         unsigned int m = (1<<w)-1;
         //if ((a1+x1 & m)*a2 + (a3+x2 & m)*a4 == (a1+y1 & m)*a2 + (a3+y2 & m)*a4)
         if ((a1^x1)*a2 + (a3^x2)*a4 == (a1^y1)*a2 + (a3^y2)*a4)
            res++;
      }
      printf("w=%d, prob=%4.3f * 2^-w\n", w, (double)res/(1<<3*w));
   }
   return 0;
}
