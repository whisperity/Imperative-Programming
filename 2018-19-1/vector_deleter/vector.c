#include <stdlib.h> // malloc, exit
#include <stdio.h>  // fprintf (hibauzenetek)
#include <string.h> // memcpy

#include "vector.h"

void _double_capacity(vector_p vp)
{
	printf("ALLOCATING BIGGER THING...\n");
	Elem_T* old_data = vp->data;
	
	/*printf("OLD DATA AT %p\n", old_data);*/
	
	vp->capacity = vp->capacity << 1;
	vp->data = (Elem_T*)malloc(vp->capacity * sizeof(Elem_T));
	
	/* for (size_t i = 0; i < size(vp); ++i)
		memcpy(vp->data + i, old_data + i, sizeof(Elem_T)); */
	memcpy(vp->data, old_data, size(vp) * sizeof(Elem_T));
	
	/* free ELEMENTS behind old?! */
	free(old_data);
}

vector_p create_vector(void)
{
	return create_vector_sized(2, NULL);
}

vector_p create_vector_sized(size_t capacity,
                             vector_elem_delete_fun_ptr deleter_ptr)
{
	if (capacity < 2)
		capacity = 2;

	vector_p vp = (vector_p)malloc(sizeof(struct vector));
	vp->size = 0;
	vp->capacity = capacity;
	vp->data = (Elem_T*)malloc(vp->capacity * sizeof(Elem_T));
	vp->deleter_ptr = deleter_ptr;
	return vp;
}

void destroy_vector(vector_p vp)
{
	if (vp->deleter_ptr)
		for (size_t i = 0; i < vp->size; ++i)
			vp->deleter_ptr(vp->data + i);
	
	free(vp->data);
	free(vp);
}

size_t size(vector_p vp) { return vp->size; }
size_t capacity(vector_p vp) { return vp->capacity; }

Elem_T get(vector_p vp, size_t idx)
{
	if (idx >= size(vp))
		exit(1);
	
	return *(vp->data + idx);
}

void push_back(vector_p vp, Elem_T e)
{
	/*printf("%lu, %lu\n", size(vp), capacity(vp));*/
	if (size(vp) >= capacity(vp))
	{
		/*printf("NEED TO INCREASE!\n");*/
		_double_capacity(vp);
	}
	
	/*printf("SIZE BEFORE: %lu\n", vp->size);*/
	++vp->size;
	set(vp, vp->size - 1, e);
	/*printf("SIZE AFTER: %lu\n", vp->size);*/
}

void set(vector_p vp, size_t idx, Elem_T e)
{
	if (idx >= size(vp))
		exit(1);
	
	/*printf("ADDR: %p\n", vp->data + idx);*/
	memcpy(vp->data + idx, &e, sizeof(Elem_T));
}

void pop_back(vector_p vp)
{
	remove_idx(vp, size(vp) - 1);
}

void remove_idx(vector_p vp, size_t idx)
{
	if (idx < size(vp) - 1)
	{
		for (size_t i = idx; i < size(vp) - 1; ++i)
		{
			Elem_T e = get(vp, i + 1);
			set(vp, i, e);
		}
		
		/* delete last element if pointer?! */
	}
	
	--vp->size;
}
