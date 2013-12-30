#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
int main() {
  int c, n;
 FILE *fp;
  printf("Ten random numbers in [1,100]\n");
 fp=fopen("rnos.txt","a+");
  for (c = 1; c <= 1000000000; c++) {
    n = rand()%10000 + 1;
    printf("%d\n", n);
	fprintf(fp,"%d",n);
	fprintf(fp,"\n");

  }
  fclose(fp);
 getch();
  return 0;
}
