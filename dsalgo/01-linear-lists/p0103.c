#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMS 100000
#define MAX_OPS  200000

#define FULL_MASK 1
#define MAKE_MASK(i) (1 << i)

int query(int bit, unsigned short *nums, int n);
void add(int inc, unsigned short *nums, int n);
void printRes(unsigned int *res, int n);

int main() {
  int n, m;

  // record the number of integers (n) and that of operations (m)
  scanf("%d %d", &n, &m);

  unsigned short *nums = malloc(sizeof(unsigned short) * n);
  unsigned int *res = malloc(sizeof(unsigned int) * MAX_OPS);
  int i, k;
  for (i = 0; i < n; i++)
    scanf("%d", &nums[i]);

  char op;
  int arg;
  int j;
  int qCount = 0;
  for (j = 0; j < m; j++) {
    scanf(" %c %d", &op, &arg);
    //printf("1:%d ", j);
    if (op == 'Q') {
      res[qCount++] = query(arg, nums, n);
      //printf("2:%d, qCount: %d ", j, qCount);
    }
    else if (op == 'C') {
      add(arg, nums, n);
      //printf("3:%d ", j);
    }
    //printf("4:%d ", j);
  }

  printRes(res, qCount);

  return 0;
}

int query(int bit, unsigned short *nums, int n) {
  int i;
  int count = 0;

  unsigned short mask = MAKE_MASK(bit);
  for (i = 0; i < n; i++) {
    if (nums[i] & mask > 0)
      count++;
  }

  return count;
}

void add(int inc, unsigned short *nums, int n) {
  int i;

  for (i = 0; i < n; i++) {
    nums[i] += inc;
  }
}

void printRes(unsigned int *res, int n) {
  int i;

  for (i = 0; i < n; i++)
    printf("%d\n", res[i]);
}
