/* P0101: Add two polynomials
 * */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_LEN 300

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
   if (n < 2 || n > 99) {
      printf("n should be within (1, 100)\n");
      return 1;
   }

   ListOfPoly inputs = (ListOfPoly) malloc(sizeof(struct Term) * (n * 2));
   int line = 0;
   char c;
   int charCount = -1;
   int numCount = 0;
   int coefficient;
   int exponent;
   char *num = (char *) malloc(sizeof(char) * MAX_LEN);
   // char num[MAX_LEN];
   int i = 0;
   Polynomial poly = initPoly();
   PtrToTerm term;
   while (1) {
      c = getchar();
      if (++charCount > MAX_LEN) {
         printf("The length of each line should be less than 300.\n");
         return 1;
      }
      if (c == ' ') {
         num[i] = '\0';
         i = 0;
         if (numCount % 2 == 0) {
            coefficient = atoi(num);
            //printf("coeff: %d ", coefficient);
         }
         else {
            exponent = atoi(num);
            //printf("exp: %d\n", exponent);
            term = createTerm(coefficient, exponent);
            insertTerm(poly, term);
         }
         numCount++;
      }
      else if (c == '\n' && numCount > 0) {
         //num[i] = '\0';
         //exponent = atoi(num);
         //term = createTerm(coefficient, exponent);
         //printf("exp: %d\n", exponent);
         //insertTerm(poly, term);
         inputs[line++] = poly;
         
         if (line == n * 2) break;
         // reset env vars
         charCount = 0;
         i = 0;
         numCount = 0;
         poly = initPoly();
      }
      else if (c == '-' || c == '+' || (c >= '0' && c <= '9')) {
         num[i++] = c;
      }
      else if (c == '\0' || c == EOF) {
         if (line == n * 2 - 1) {
            inputs[line] = poly;
            break;
         }
         else
            continue;
      }
   }

   //if (line < n * 2 - 1) return 0;


   //int j;
   //for (j = 0; j < n; j++) {
   //   printPoly(inputs[j]);
   //}

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
