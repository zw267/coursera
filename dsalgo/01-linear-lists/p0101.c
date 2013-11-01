/* P0101: Add two polynomials
 * */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_LEN 300
#define DIGIT_LEN 10

/* Should be placed in a speparated header file */
struct Term;
typedef struct Term *PtrToTerm;
typedef PtrToTerm Polynomial;
typedef Polynomial *ListOfPoly;

PtrToTerm createTerm(int coefficient, int exponent);
Polynomial initPoly();
void insertTerm(Polynomial poly, PtrToTerm term);
Polynomial addTwo(Polynomial a, Polynomial b);
void destroyPoly(Polynomial poly);
Polynomial resetPoly(Polynomial poly);
void printPoly(Polynomial poly);
void printResult(ListOfPoly list, int n);

/* The implementation begins here */
struct Term {
   int coefficient;   // the coefficient of the term
   int exponent;      // the exponent of the term
   PtrToTerm next;
};

int main() {
   int n = 0;

   scanf("%d", &n);
   if (n < 1 || n > 99) {
      printf("n should be within (1, 100)\n");
      return 1;
   }

   ListOfPoly inputs = (ListOfPoly) malloc(sizeof(struct Term) * (n * 2));
   int lineCount = 0;
   int numCount = 0;
   int coefficient;
   int exponent;
   int k;
   Polynomial poly = initPoly();
   PtrToTerm term;

   for (lineCount = 0; lineCount < 2 * n; lineCount++) {
      while (1) {
         scanf("%d", &k);
         if (numCount % 2 == 0) {
            coefficient = k;
            numCount++;
         }
         else {
            if (k >= 0) {
               exponent = k;
               numCount++;
               term = createTerm(coefficient, exponent);
               insertTerm(poly, term);
            }
            else 
               break;
         }
      }

      numCount = 0;
      coefficient = 0;
      inputs[lineCount] = poly;
      //destroyPoly(poly);

      if (lineCount < 2 * n - 1)
         poly = initPoly();

   }

   int j;
   ListOfPoly outputs = (ListOfPoly) malloc(sizeof(struct Term) * n);
   for (j = 0; j < n; j++) {
      outputs[j] = addTwo(inputs[2 * j], inputs[2 * j + 1]);
   }
   
   printResult(outputs, n);

   return 0;
}


void printPoly(Polynomial poly) {
   poly = poly->next;

   while (poly != NULL) {
     if (poly->exponent > 0) {
        if (poly->next == NULL)
           printf("[ %d %d ]", poly->coefficient, poly->exponent);
        else
           printf("[ %d %d ] ", poly->coefficient, poly->exponent);
     }
     poly = poly->next;
   }

   printf("\n");
}

void printResult(ListOfPoly list, int n) {
   int i = 0;
   Polynomial poly;

   for (i = 0; i < n; i++) {
      poly = list[i];
      poly = poly->next;
      while (poly != NULL) {
        if (poly->exponent >= 0 && poly->coefficient != 0) {
           if (poly->next == NULL)
              printf("[ %d %d ]", poly->coefficient, poly->exponent);
           else
              printf("[ %d %d ] ", poly->coefficient, poly->exponent);
        }
        poly = poly->next;
      }
      printf("\n");
   }
}

PtrToTerm createTerm(int coefficient, int exponent) {
   PtrToTerm pos = malloc(sizeof(struct Term));
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
      poly->coefficient = INT_MAX;
      poly->exponent = INT_MAX;
      poly->next = NULL;
   }
   return poly;
}

Polynomial resetPoly(Polynomial poly) {
   PtrToTerm pos = poly->next;
   poly->next = NULL;

   destroyPoly(pos);

   return poly;
}

void destroyPoly(Polynomial poly) {
   PtrToTerm cursor = poly;

   while (cursor != NULL) {
      PtrToTerm tmp = cursor;
      cursor = cursor->next;
      free(tmp);
   }
}

/* insert a term to a given polynomial sorted by exponents increasingly */
void insertTerm(Polynomial poly, PtrToTerm term) {
   if (poly == NULL || term == NULL) {
      printf("Invalid input: NULL polynomial or term.");
      return;
   }

   if (poly->next == NULL) {
      poly->next = term;
      return;
   }

   // skip the head of the polynomial
   //poly = poly->next;
   while (poly->next != NULL) {
      if (poly->exponent >= term->exponent
          && poly->next->exponent < term->exponent)
        break;

      poly = poly->next;
   }

   if (poly->exponent == term->exponent)
      poly->coefficient += term->coefficient;
   else {
      term->next = poly->next;
      poly->next = term;
   }


   /*
   if (poly->next == NULL) poly->next = term;
   else {
   term->next = poly->next;
   poly->next = term;
   }
   */
   return;
}

/* both polynomials are orderd by exponents increasingly */
Polynomial addTwo(Polynomial a, Polynomial b) {
   PtrToTerm pa = a->next;
   PtrToTerm pb = b->next;

   Polynomial result = initPoly();
   PtrToTerm tmp = result;

   int coefficient, exponent;
   while (pa != NULL && pb != NULL) {
      if (pa->exponent < pb->exponent) {
         //pb = pb->next;
         coefficient = pb->coefficient;
         exponent = pb->exponent;
         pb = pb->next;
      }
      else if (pa->exponent > pb->exponent) {
         coefficient = pa->coefficient;
         exponent = pa->exponent;
         pa = pa->next;
      }
      else {
         coefficient = pa->coefficient + pb->coefficient;
         exponent = pa->exponent;
         pa = pa->next;
         pb = pb->next;
      }

      PtrToTerm term = createTerm(coefficient, exponent);
      tmp->next = term;
      tmp = tmp->next;
   }

   if (pa == NULL)
      tmp->next = pb;
   else if (pb == NULL)
      tmp->next = pa;

   return result;
}
