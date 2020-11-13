#include <stdio.h>
#include <stdlib.h>

char* how_are_you()
{
  char* mood = (char*)malloc(sizeof(char) * 1024);
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
  return mood;
}

int main(void)
{
  printf("Karl Jung Psychology!\n");
  char* mood = how_are_you();
  
  printf("You are this how: \n");
  printf("%p\n", mood);
  
  how_are_you(); /* ezt meg nem free-elte senki... */
  
  printf("%s\n", mood);
  
  free(mood);
  
  return 0;
}
