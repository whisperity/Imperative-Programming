#include <stdio.h>

char change_(char in);
char change(char c);
char change__(char ch);
char change___(char ch); /* CONTAINS UB */

int main(void)
{
	int ch;
	printf("%d", 'a');

	while ((ch = getchar()) != EOF)
	{
		if (change(ch) == change_(ch) && change(ch) == change__(ch))
			/* ha valamit elszurunk a 3 kulonbozo implementacioban, akkor
			 * ? jon ki a betu helyett */
			putchar(change___(ch));
		else
			putchar('?');
	}
	
	return 0;
}

char change_(char in)
{
	switch (in) {
		case 'a':
			return 'e';
		case 'e':
			return 'i';
		case 'i':
			return 'o';
		case 'o':
			return 'u';
		case 'u':
			return 'a';
		default:
			return in;
	}
	/* ----------------- */
	/*if (in == 'a')
		return 'e';
	if (in == 'e')
		return 'i';
	if (in == 'i')
		return 'o';
	if (in == 'o')
		return 'u';
	if (in == 'u')
		return 'a';

	return in;*/
}

char change(const char c)
{
	const char input[]  = {'a', 'e', 'i', 'o', 'u'};
	const char output[] = {'e', 'i', 'o', 'u', 'a'};
	
	for (int i = 0; i < sizeof(input) / sizeof(input[0]); ++i)
	{
		if (c == input[i])
		{
			return output[i];
		}
	}
	
	return c;
}

char change___(char ch)
{
	const char input[]  = {'a', 'e', 'i', 'o', 'u'/* ... */};
	/*const char output[] =    {'e', 'i', 'o', 'u', 'y', 'a'};*/
	
	char output[sizeof(input) / sizeof(input[0])];
	for (int i = 0; i < sizeof(input) / sizeof(input[0]); ++i)
	{
		output[i] = input[i + 1]; /* UNDEFINED BEHAVIOUR if i == 4 (i + 1 == 5, input length is 4) */
	}
	output[(sizeof(output) / sizeof(output[0])) - 1] = input[0];
	
	for (int i = 0; i < sizeof(input) / sizeof(input[0]); ++i)
	{
		if (ch == input[i])
		{
			return output[i];
		}
	}
	
	return ch;
}

char change__(char ch)
{
	const char input[]  = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
	
	char output[sizeof(input) / sizeof(input[0])];
	for (int i = 0; i < sizeof(output) / sizeof(output[0]) - 1; ++i)
	{
		output[i] = input[i + 1];
	}
	output[(sizeof(output) / sizeof(output[0])) - 1] = input[0];
	
	for (int i = 0; i < sizeof(input) / sizeof(input[0]); ++i)
	{
		if (ch == input[i])
		{
			return output[i];
		}
	}
	
	return ch;
}

/* HF: felvenni 256 (0tol 255ig) tombot minden betuhoz, es kezzel
 * lehessen beallitani KULON KULON az egyes betukhoz, hogy mire
 * irodjanak at. */
