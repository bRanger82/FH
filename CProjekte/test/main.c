/* malloc2.c */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
   int *p = malloc(2 * sizeof(int));

   if(p != NULL) {
      *p=99;         /* alternativ auch p[0] = 99  */
      *(p+1) = 100;  /* alternativ auch p[1] = 100 */
      printf("Allokation erfolgreich ... \n");
   }
   else {
      printf("Kein virtueller RAM mehr verfügbar ...\n");
      return EXIT_FAILURE;
   }
   printf("%d %d\n", p[0], p[1]);
   /* Sie können die Werte auch so ausgeben lassen. */
   printf("%d %d\n", *p, *(p+1));
   return EXIT_SUCCESS;
}
