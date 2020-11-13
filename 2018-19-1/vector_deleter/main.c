#include <stdio.h> // printf
#include <stdlib.h> // malloc

#include "vector.h"

void my_logging_deleter(Elem_T* element)
{
	printf("Deleting an int array...\n");
	for (size_t i = 0; i < element->length; ++i)
		printf("\t#%llu: %d\n", i, element->data[i]);
	free(element->data);
}

int main(void)
{
	struct int_array arr1, arr2;
	arr1.data = (int*)malloc(2 * sizeof(int));
	arr1.length = 2;
	
	arr2.data = (int*)malloc(4 * sizeof(int));
	arr2.length = 4;
	
	vector_p vp = create_vector();
	push_back(vp, arr1);
	push_back(vp, arr2);
	destroy_vector(vp);
	
	arr1.data[1] = 5;
	
	vp = create_vector_sized(4, &my_logging_deleter);
	push_back(vp, arr1);
	get(vp, 0).data[0] = 42;
	push_back(vp, arr2);
	get(vp, 1).data[1] = 1996;
	destroy_vector(vp);
}
