#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h> // for DBL_MAX and DBL_MIN

#define NUM_DAYS 28

int main() {
  FILE* fp = fopen("test.csv", "r");

  if (fp == NULL) {
    printf("開啟檔案錯誤\n");
    return 1;
  }

  char line[1024], buff[1024];

  // 從檔案讀取第一行並列印出來
  char *row_name, *row_data;
  int i=0, j=0, n=0;
  int sum=0, value=0;

  // 讀取並處理檔案中的其餘行
  while (fgets(line, 1024, fp)) {
    // 解讀每一列的第一欄
    row_name = strtok(line, ",");
    printf("%s:\n ", row_name);

    // 解讀每列第一欄之後的每一欄
    row_data = strtok(NULL, ",");
    while (row_data != NULL)
    {
        printf("\t%s\n", row_data);
        row_data = strtok(NULL, ",");
    }
  }

  fclose(fp);

  return 0;
}
