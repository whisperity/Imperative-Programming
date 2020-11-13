#include <stdio.h> // printf

#include "vector.h"

int main(void)
{
	vector_p vec = create_vector();
	printf("%p\n", vec);
	printf("%lu %lu\n", size(vec), capacity(vec));
	destroy_vector(vec);
	
	/* vector_p */ vec = create_vector_sized(4);
	printf("%p\n", vec);
	printf("%lu %lu\n", size(vec), capacity(vec));
	
	printf("VECTOR'S CAPACITY AT %p\n", &vec->capacity);
	printf("VECTOR'S ARRAY PTR AT %p\n", &vec->data);
	printf("VECTOR'S ARRAY BEGINS AT %p\n", vec->data);
	
	push_back(vec, 42);
	printf("0: %d\n", get(vec, 0));
	push_back(vec, 69);
	printf("1: %d\n", get(vec, 1));
	push_back(vec, 420);
	printf("2: %d\n", get(vec, 2));
	push_back(vec, 1337);
	printf("3: %d\n", get(vec, 3));
	printf("SIZE CHECK: %lu %lu\n", size(vec), capacity(vec));
	push_back(vec, 9001);
	printf("4: %d\n", get(vec, 4));
	push_back(vec, 65536);
	printf("5: %d\n", get(vec, 5));
	push_back(vec, 80085);
	printf("6: %d\n", get(vec, 6));
	push_back(vec, 16666);
	printf("7: %d\n", get(vec, 7));
	
	printf("END?\n");
	printf("SIZE CHECK: %lu %lu\n", size(vec), capacity(vec));
	
	/*printf("Tempt the devil...\n");*/
	
	push_back(vec, 19960110);
	printf("0: %d\n", get(vec, 0));
	printf("1: %d\n", get(vec, 1));
	printf("2: %d\n", get(vec, 2));
	printf("3: %d\n", get(vec, 3));
	printf("4: %d\n", get(vec, 4));
	printf("5: %d\n", get(vec, 5));
	printf("6: %d\n", get(vec, 6));
	printf("7: %d\n", get(vec, 7));
	printf("8: %d\n", get(vec, 8));
	printf("SIZE CHECK: %lu %lu\n", size(vec), capacity(vec));
	
	pop_back(vec);
	printf("SIZE CHECK: %lu %lu\n", size(vec), capacity(vec));
	printf("last: %d\n", get(vec, size(vec) - 1));
	
	set(vec, 0, 19960110);
	printf("0: %d\n", get(vec, 0));
	printf("SIZE CHECK: %lu %lu\n", size(vec), capacity(vec));
	
	remove_idx(vec, 0);
	printf("0: %d\n", get(vec, 0));
	printf("1: %d\n", get(vec, 1));
	printf("2: %d\n", get(vec, 2));
	printf("3: %d\n", get(vec, 3));
	printf("4: %d\n", get(vec, 4));
	printf("5: %d\n", get(vec, 5));
	printf("6: %d\n", get(vec, 6));
	printf("SIZE CHECK: %lu %lu\n", size(vec), capacity(vec));
}
