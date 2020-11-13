#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

/* HF: mx determinansa es a std outputra kiirni */

int main(void)
{
    FILE* fp = fopen("rossz.txt", "r");
    if (!fp)
    {
        perror("File opening failed");
        return 1;
    }

	printf("%ld\n", ftell(fp));
	unsigned long columns = 0;
	int c = 0;
	while (c != '\n')
	{
	  fscanf(fp, "%d", &c);
	  printf("read: %d\n", c);
	  ++columns;
	  c = fgetc(fp);
	}
	printf("%ld\n", ftell(fp));
	printf("Column # is: %lu\n", columns);
	
	fseek(fp, 0, SEEK_SET);
	printf("%ld\n", ftell(fp));
	
	vector_p row_vector = create_vector();
	
	c = 0;
	while (c != EOF && !feof(fp)) /* while (!(c == EOF || feof(fp))) */
	{
	  c = 0;

	  printf("----- BEGIN NEW ROW ------\n");

	  int* current_row = (int*)malloc(sizeof(int) * columns);
	  push_back(row_vector, current_row);
	  
	  unsigned long columns = 0;
	  while (c != '\n' && c != EOF && !feof(fp))
	  { 
	    c = fscanf(fp, "%d", current_row + columns);
	    if (feof(fp) || c == EOF)
	    {
			pop_back(row_vector); /* itt memory leak... */
			break;
		}
	    
	    printf("Read: %d\n", *(current_row + columns));
	    ++columns;
	    c = fgetc(fp);
	  }
	  printf("#### NEWLINE REACHED ####\n");
	  
	  /* free(current_row); <- NEM SZABAD MOST MEG!!! */
	}
	
	if (ferror(fp))
        printf("I/O error when reading\n");
    else if (feof(fp))
        printf("End of file reached successfully\n");
	fclose(fp);
	
	for (size_t i = 0; i < size(row_vector); ++i)
	{
		for (size_t j = 0; j < columns; ++j)
		{
			/*printf("(%llu, %llu): %d\n", i, j, *(get(row_vector, i) + j));*/
			printf("%d ", *(get(row_vector, i) + j));
		}
		printf("\n");
	}
	
	printf("---------------------------------------------------\n");
	
	for (size_t i = 0; i < size(row_vector); ++i)
	{
		for (size_t j = 0; j < columns; ++j)
		{
			++(*(get(row_vector, i) + j));
		}
	}
	
	printf("Ellenorzes...\n");
	
	for (size_t i = 0; i < size(row_vector); ++i)
	{
		for (size_t j = 0; j < columns; ++j)
		{
			/*printf("(%llu, %llu): %d\n", i, j, *(get(row_vector, i) + j));*/
			printf("%d ", *(get(row_vector, i) + j));
		}
		printf("\n");
	}
	
	fp = fopen("output1.txt", "w");
    if (!fp)
    {
        perror("File opening failed");
        return 1;
    }
    
    for (size_t i = 0; i < size(row_vector); ++i)
	{
		for (size_t j = 0; j < columns; ++j)
		{
			fprintf(fp, "%d ", *(get(row_vector, i) + j));
		}
		fputc('\n', fp);
	}
	
	fclose(fp);

	/* vektor elemei memory leak-elni fognak! */
	
	destroy_vector(row_vector);
	row_vector = NULL;
}
