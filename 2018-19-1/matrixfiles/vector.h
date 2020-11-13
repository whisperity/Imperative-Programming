#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stddef.h> // size_t

typedef int* Elem_T;

struct vector
{
	size_t capacity;
	size_t size;
	Elem_T* data;
};

typedef struct vector* vector_p;

void _double_capacity(vector_p vp);

vector_p create_vector(void);
vector_p create_vector_sized(size_t capacity);

void destroy_vector(vector_p vp);

size_t size(vector_p vp);
size_t capacity(vector_p vp);

Elem_T get(vector_p vp, size_t idx); // idx < vp->size

void push_back(vector_p vp, Elem_T e);

void set(vector_p vp, size_t idx, Elem_T e); // idx < vp->size

void pop_back(vector_p vp);
void remove_idx(vector_p vp, size_t idx); // idx < vp->size

#endif // _VECTOR_H_
