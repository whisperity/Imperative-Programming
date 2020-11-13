#include <stdio.h>

int main(void)
{
	FILE* fptr = fopen("input.txt", "r");
	if (!fptr || ferror(fptr))
	{
		printf("Error: the file could not be opened!\n");
		return 1;
	}
	int sum = 0, cnt = 0;
	int num;
	while (fscanf(fptr, "%d", &num) != EOF && !feof(fptr))
	{
		printf("%d\n", num + 1);
		sum += num;
		++cnt;
	}
	
	fclose(fptr);
	
	printf("Avg: %f\n", num / sum);
	
	return 0;
}
