#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h> // for DBL_MAX and DBL_MIN

#define NUM_DAYS 28

int main() {
  FILE* fp = fopen("test.csv", "r");

  if (fp == NULL) {
    printf("�}���ɮ׿��~\n");
    return 1;
  }

  char line[1024], buff[1024];

  // �q�ɮ�Ū���Ĥ@��æC�L�X��
  char *row_name, *row_data;
  int i=0, j=0, n=0;
  int sum=0, value=0;

  // Ū���óB�z�ɮפ�����l��
  while (fgets(line, 1024, fp)) {
    // ��Ū�C�@�C���Ĥ@��
    row_name = strtok(line, ",");
    printf("%s:\n ", row_name);

    sum = 0;
    // ��Ū�C�C�Ĥ@�椧�᪺�C�@��
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
