#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stddef.h> // size_t

struct int_array
{
	int* data;
	size_t length;
};

typedef struct int_array Elem_T;

typedef void(*vector_elem_delete_fun_ptr)(Elem_T*);

struct vector
{
	size_t capacity;
	size_t size;
	Elem_T* data;
	vector_elem_delete_fun_ptr deleter_ptr;
};

typedef struct vector* vector_p;

void _double_capacity(vector_p vp);

vector_p create_vector(void);
vector_p create_vector_sized(size_t capacity,
                             vector_elem_delete_fun_ptr deleter_ptr);

void destroy_vector(vector_p vp);

size_t size(vector_p vp);
size_t capacity(vector_p vp);

Elem_T get(vector_p vp, size_t idx); // idx < vp->size

void push_back(vector_p vp, Elem_T e);

void set(vector_p vp, size_t idx, Elem_T e); // idx < vp->size

void pop_back(vector_p vp);
void remove_idx(vector_p vp, size_t idx); // idx < vp->size

#endif // _VECTOR_H_
