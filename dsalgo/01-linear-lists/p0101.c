/* P0101: Add two polynomials
 * */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_LEN 300
#define DIGIT_LEN 5

/* Should be placed in a speparated header file */
typedef int bool;

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

   scanf("%d\n", &n);
   ListOfPoly inputs = (ListOfPoly) malloc(sizeof(struct Term) * n);
   int line = 0;
   char c;
   int numCount = 0;
   int coefficient;
   int exponent;
   char num[DIGIT_LEN];
   int i = 0;
   Polynomial poly = initPoly();
   PtrToTerm term;
   while ((c = getchar()) != EOF && line < n) {
      if (c == ' ') {
         num[i] = '\0';
         i = 0;
         if (numCount % 2 == 0) {
            coefficient = atoi(num);
            printf("coeff: %d ", coefficient);
         }
         else {
            exponent = atoi(num);
            printf("exp: %d\n", exponent);
            term = createTerm(coefficient, exponent);
            insertTerm(poly, term);
         }
         numCount++;
      }
      else if (c == '\n') {
         num[i] = '\0';
         exponent = atoi(num);
         term = createTerm(coefficient, exponent);
         printf("exp: %d\n", exponent);
         insertTerm(poly, term);
         inputs[line++] = poly;
         // reset env vars
         i = 0;
         numCount = 0;
         poly = initPoly();
      }
      else {
        num[i++] = c;
      }
   }


   int j;
   for (j = 0; j < n; j++) {
      printPoly(inputs[j]);
   }

   ListOfPoly outputs = (ListOfPoly) malloc(sizeof(struct Term) * (n / 2));
   for (j = 0; j < n ; j += 2) {
      outputs[j] = addTwo(inputs[j], inputs[j + 1]);
   }
   
   printResult(outputs, n / 2);

   return 0;
}

void printPoly(Polynomial poly) {
   poly = poly->next;

   while (poly != NULL) {
     printf("[%d %d] ", poly->coefficient, poly->exponent);
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
         printf("[%d %d] ", poly->coefficient, poly->exponent);
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
      poly->coefficient = INT_MIN;
      poly->exponent = INT_MIN;
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
      if (poly->exponent < term->exponent
          && poly->next->exponent > term->exponent)
        break;

      poly = poly->next;
   }

   term->next = poly->next;
   poly->next = term;

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
      if (pa->exponent > pb->exponent) {
         //pb = pb->next;
         coefficient = pb->coefficient;
         exponent = pb->exponent;
         pb = pb->next;
      }
      else if (pa->exponent < pb->exponent) {
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
