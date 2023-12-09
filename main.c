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
    printf("%s: ", row_name);

    // 解讀每列第一欄之後的每一欄
    row_data = strtok(NULL, ",");
    while (row_data != NULL)
    {
        if (row_data[0] == '\"') // 判斷第一個字元是否為雙引號
        {
            row_data++;
            n = strlen(row_data);
            if (row_data[n-1] == '\"') // 判斷最後一個字元是否為雙引號
            {
                for (i=0; i<n-1; i++)
                    buff[i] = row_data[i];
            } else if (row_data[n-1] == '\n') //判斷最後一個字元是否為換行字元
            {
                for (i=0; i<n-2; i++)
                    buff[i] = row_data[i];
            } else {
                // 程式執行到此處代表：一對雙引號中的數字是含逗號
                for (i=0; i<n; i++)
                    buff[i]=row_data[i];

                row_data = strtok(NULL, ",");
                n = strlen(row_data);
                if (row_data[n-1] == '\n')
                    n--;
                for (j=0; j<n-1; j++)
                    buff[i++] = row_data[j];
            }
            buff[i] = '\0';

            value = atoi(buff);
        } else {
            value = atoi(row_data);
        }

        sum += value;
        printf("%10d, ", value);

        row_data = strtok(NULL, ",");
    }
    printf("sum = %d\n", sum);
  }

  fclose(fp);

  return 0;
}
