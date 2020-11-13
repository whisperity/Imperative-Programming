#include <stdio.h>

int main(void)
{
	int ch;
	while ((ch = fgetc(stdin)) != EOF)
	{
		if (ch == '[')
		{
			int from, to;
			from = fgetc(stdin);
			char tmp[3];
			fgets(tmp, sizeof(tmp), stdin); // ..
			to = fgetc(stdin);
			fgetc(stdin); // ]
			
			while (from <= to)
			{
				fprintf(stdout, "%c", from);
				++from;
			}
		}
		else
			fprintf(stdout, "%c", ch);
	}
	
	return 0;
}
