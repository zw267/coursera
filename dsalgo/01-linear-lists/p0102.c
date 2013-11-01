/* P0102: Insert a substr to a sub right after the char
 * of the greatest ACSII code.
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 10
#define MAX_SUB_STR_LEN 3

typedef char *String;

String insert(String str, String substr);
int getInsPos(String str);

int main() {
  String str, substr;
  String res;

  str = (String) malloc(sizeof(char) * MAX_STR_LEN);
  substr = (String) malloc(sizeof(char) * MAX_SUB_STR_LEN);

  while (scanf("%s %s", str, substr) == 2) {
    res = insert(str, substr);
    printf("%s\n", res);
  }
}

String insert(String str, String substr) {
  int strLen = strlen(str);
  int substrLen = strlen(substr);
  int resLen = strLen + substrLen;

  int insPos = getInsPos(str);

  String res = (String) malloc(sizeof(char) * (resLen));

  int i;
  for (i = 0; i < resLen; i++) {
    if (i <= insPos)
      res[i] = str[i];
    if (i > insPos && i <= insPos + substrLen)
      res[i] = substr[i - insPos - 1];
    if (i > insPos + substrLen)
      res[i] = str[i - substrLen];
  }

  return res;
}

int getInsPos(String str) {
  int strLen = strlen(str);

  int pos, i;
  for (i = 1, pos = 0; i < strLen; i++) {
    if (str[i] > str[pos]) pos = i;
    if (str[i] <= str[pos]) continue;
  }

  return pos;
}
