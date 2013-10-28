/* P0101: Add two polynomials
 * */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_LEN 300
#define TRUE    1
#define FALSE   0

/* Should be placed in a speparated header file */
typedef int bool;

struct Term;
typedef struct Term *Position;
typedef Position Polynomial;

Position createTerm(int coefficient, int exponent);
Polynomial initPoly();
Polynomial addTwo(Polynomial a, Polynomial b);
void destroyPoly(Polynomial poly);
Polynomial resetPoly(Polynomial poly);

/* The implementation begins here */
struct Term {
   int coefficient;   // the coefficient of the term
   int exponent;      // the exponent of the term
   Position next;
};

int main() {
   int n = 0;

   Polynomial a = initPoly();
   Polynomial b = initPoly();

   if (a == NULL || b == NULL) {
      printf("Fail to initialize polynomials.\n");
      return 1;
   }


}

Position createTerm(int coefficient, int exponent) {
   Position pos = malloc(sizeof(struct Term));
   pos->coefficient = coefficient;
   pos->exponent = exponent;
   pos->next = NULL;

   return pos;
}

Polynomial initPoly() {
   Polynomial poly = malloc(sizeof(struct Term));
   if (poly == NULL) {
      printf("Fatal error: out of space!\n");
   }
   else {
      poly->coefficient = INT_MIN;
      poly->exponent = INT_MIN;
   }
   return poly;
}

Polynomial resetPoly(Polynomial poly) {
   Position pos = poly->next;
   poly->next = NULL;

   destroyPoly(pos);

   return poly;
}

void destroyPoly(Polynomial poly) {
   Position cursor = poly;

   while (cursor != NULL) {
      Position tmp = cursor;
      cursor = cursor->next;
      free(tmp);
   }
}

/* both polynomials are orderd by exponents increasingly */
Polynomial addTwo(Polynomial a, Polynomial b) {
   Position pa = a->next;
   Position pb = b->next;

   while (pa != NULL && pb != NULL) {
      if (pa->exponent > pb->exponent) {
         pb = pb->next;
      }
      else if (pa->exponent < pb->exponent) {
         pa = pa->next;
      }
      else {
         pa->coefficient += pb->coefficient;
         pa = pa->next;
         pb = pb->next;
      }
   }

   if (pa == NULL)
      pa->next = pb;

   return pa;
}
