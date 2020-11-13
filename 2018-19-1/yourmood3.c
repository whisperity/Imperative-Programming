#include <stdio.h>
#include <stdlib.h>

void how_are_you(char* mood)
{
  printf("How are you?\n");
  char* p = gets(mood);
  
  if (p == mood)
  {
    printf("Read really success!\n");
  }
  else if (p == NULL)
  {
	fprintf(stderr, "Nem sikerult olvasni.\n");
	exit(1);
  }
  
  printf("Read success to %p \n", mood);
}

int main(void)
{
  printf("Karl Jung Psychology!\n");
  char* mood = (char*)malloc(sizeof(char) * 1024);
  how_are_you(mood);
  
  printf("You are this how: \n");
  printf("%p\n", mood);
  
  printf("%s\n", mood);
  
  printf("Oh really?\n");
  how_are_you(mood);
  printf("Ye really: %s\n", mood);
  
  free(mood);
  
  return 0;
}
