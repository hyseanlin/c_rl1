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
    printf("%s: ", row_name);

    // ��Ū�C�C�Ĥ@�椧�᪺�C�@��
    row_data = strtok(NULL, ",");
    while (row_data != NULL)
    {
        if (row_data[0] == '\"') // �P�_�Ĥ@�Ӧr���O�_�����޸�
        {
            row_data++;
            n = strlen(row_data);
            if (row_data[n-1] == '\"') // �P�_�̫�@�Ӧr���O�_�����޸�
            {
                for (i=0; i<n-1; i++)
                    buff[i] = row_data[i];
            } else if (row_data[n-1] == '\n') //�P�_�̫�@�Ӧr���O�_������r��
            {
                for (i=0; i<n-2; i++)
                    buff[i] = row_data[i];
            } else {
                // �{������즹�B�N��G�@�����޸������Ʀr�O�t�r��
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
