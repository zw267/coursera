#include <stdio.h>

int placeApple(int numOfApple, int numOfPlate); 

int main() {
  int n;
  scanf("%d", &n);

  int i;
  int numOfApple, numOfPlate;
  int res;
  for (i = 0; i < n; i++) {
    scanf(" %d %d", &numOfApple, &numOfPlate);
    res = placeApple(numOfApple, numOfPlate);
    printf("%d\n", res);
  }

  return 0;
}

int placeApple(int numOfApple, int numOfPlate) {
  if (numOfApple == 0 || numOfPlate == 1)
    return 1;
  else if (numOfApple < 0)
    return 0;
  else
    return placeApple(numOfApple, numOfPlate - 1)
      + placeApple(numOfApple - numOfPlate, numOfPlate);
}
