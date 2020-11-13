#include <stdio.h>

int main(void)
{
	int i = 3;
	i += 5;
	i /= 2;
	
	/* i == 4 */
	
	if (i) {
		printf("De jo az integer osztas!\n");
	} else if (i == 4) {
		printf("Basszus!\n");
	} else {
		printf("Na jo van ma'\n");
	}
	
	switch (i) {
		case 4:
			/* int k = 4; */
			printf("negy\n");
			break;
		case 5:
			/* float j = 9.5; */
			printf("ot\n");
			break;
		default:
			printf("barmi mas\n");
			break;
	}
	
	/*if (i) {
		if (k) {
			printf(); }
	else
		if (j) {
			printf(); }
		else {
			printf(); }
	}*/
	
	/* A; if (B) { D; C }; if (B) { D; C } ... */
	
	for (i = 4; i < 10; ++i) {
		printf("%d, ", i);
	}
	printf("\n");
	printf("@end: %d\n", i);
	
	i = 4;
	while (i < 10) {
		printf("%d, ", i);
		++i;
	}
	printf("\n");
	printf("@end: %d\n", i);
	
	return 0;
}

/*
int ++i(int i)
{
	i = i + 1;
	return i;
}

int i++(int i)
{
	int j = i;
	i = i + 1;
	return j;
}

int i = 4;
printf("%d", i++);
printf("%d", i);
*/
