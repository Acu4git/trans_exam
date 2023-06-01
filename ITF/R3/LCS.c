#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LENGTH 1024

unsigned int mat[MAX_NAME_LENGTH + 1][MAX_NAME_LENGTH + 1];
char res1[MAX_NAME_LENGTH + 1], res2[MAX_NAME_LENGTH + 1];

unsigned int max(unsigned int a, unsigned int b) { return a > b ? a : b; }

unsigned int lcs(char *str1, char *str2) {
  unsigned int i, j;
  unsigned int len1 = strlen(str1);
  unsigned int len2 = strlen(str2);
  for (i = 0; i <= len1; i++) {
    mat[i][0] = 0;
  }
  for (j = 0; j <= len2; j++) {
    mat[0][j] = 0;
  }
  for (i = 1; i <= len1; i++) {
    for (j = 1; j <= len2; j++) {
      char nextchar1 = str1[i - 1];
      char nextchar2 = str2[j - 1];
      if (nextchar1 == nextchar2) {
        mat[i][j] = mat[i - 1][j - 1] + 1;
      } else {
        mat[i][j] = max(mat[i - 1][j], mat[i][j - 1]);
      }
    }
  }
  printf("%u\n", mat[len1][len2]); /*最長共通部分列の長さ*/

  unsigned int row = len1, col = len2;
  res1[row] = '\0';
  res2[col] = '\0';
  int k;  // unsigned int k:と宣言すると失敗する。
          // ⇒k=0のときにk--;とするとkがunsigned intの最大値4294967295になる。
  while (1) {
    if (col == 0) {
      for (k = row - 1; k >= 0; k--) {
        res1[k] = '-';
      }
      break;
    }
    if (row == 0) {
      for (k = col - 1; k >= 0; k--) {
        res2[k] = '-';
      }
      break;
    }
    if (mat[row][col] == mat[row - 1][col]) {
      row--;
      res1[row] = '-';
    } else if (mat[row][col] == mat[row][col - 1]) {
      col--;
      res2[col] = '-';
    } else if (mat[row][col] == mat[row - 1][col - 1] + 1) {
      row--;
      col--;
      res1[row] = str1[row];
      res2[col] = str2[col];
    }
  }
  printf("Selected characters 1: %s\n", res1);
  printf("Selected characters 2: %s\n", res2);
}

int main() {
  char s1[MAX_NAME_LENGTH + 1], s2[MAX_NAME_LENGTH + 1];
  scanf("%s%s", s1, s2);
  lcs(s1, s2);
  return 0;
}