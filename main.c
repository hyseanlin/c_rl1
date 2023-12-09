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

    sum = 0;
    // 解讀每列第一欄之後的每一欄
    row_data = strtok(NULL, ",");
    while (row_data != NULL)
    {
        if (row_data[strlen(row_data)-1]=='\n')
            row_data[strlen(row_data)-1] = '\0';

        memset(buff, '\0', 1024);

        if (row_data[0]=='\"' && row_data[strlen(row_data)-1]=='\"')
        {
            row_data++;
            row_data[strlen(row_data)-1] = '\0';
            for (i=0; i<strlen(row_data); i++)
                buff[i] = row_data[i];
        } else if (row_data[0]=='\"' && row_data[strlen(row_data)-1]!='\"') {
            row_data++;
            j = 0;
            do
            {
                for (i=0; i<strlen(row_data); i++, j++)
                    buff[j] = row_data[i];

                row_data = strtok(NULL, ",");
                if (row_data[strlen(row_data)-1]=='\n')
                    row_data[strlen(row_data)-1] = '\0';
            } while (row_data[strlen(row_data)-1]!='\"');
            row_data[strlen(row_data)-1] = '\0';
            for (i=0; i<strlen(row_data); i++, j++)
                buff[j] = row_data[i];
        } else {
            for (i=0; i<strlen(row_data); i++)
                buff[i] = row_data[i];
        }
        value = atoi(buff);
        sum += value;
        printf("%d,", value);

        row_data = strtok(NULL, ",");
    }
    printf(" sum = %d", sum);
    printf("\n");
  }

  fclose(fp);

  return 0;
}
