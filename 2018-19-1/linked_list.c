#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char MyData[65];

struct MyNode;
struct MyNode
{
	MyData  data;
	struct MyNode* next;
};

struct MyNode* create_element(const char* data)
{
  struct MyNode* newElement = malloc(sizeof(struct MyNode));
  
  strncpy(newElement->data, data, 64);
  newElement->data[64] = '\0';
  newElement->next = NULL;
  
  return newElement;
}

void insert_after_element(
  struct MyNode* element,
  const char* data)
{
  struct MyNode* newElement = create_element(data);
  newElement->next = element->next;
  element->next = newElement;
}

void free_element_after(
  struct MyNode* element)
{
  struct MyNode* p = element->next;
  element->next = element->next->next;
  free(p);
}

void free_list(
  struct MyNode* from)
{
  while (from->next != NULL)
  {
    free_element_after(from);
  }
  free(from);
}

int main(void)
{
	struct MyNode* linked_list = create_element("Hello");
	insert_after_element(linked_list, "Whisperity");
	insert_after_element(linked_list->next, "KozsikTomi");
	insert_after_element(linked_list->next->next, "A");
	insert_after_element(linked_list->next->next->next, "B");
	insert_after_element(linked_list->next->next->next->next, "C");
		
	/* tomboknel a bejaras:
	for (int i = 0; i < tombhossz(X); ++i) { valami(X[i]); }
	*/
	
	struct MyNode* p = linked_list;
	while (p != NULL)
	{
	  printf("%s\n", p->data);
	  p = p->next;
    }
    
    free_element_after(linked_list->next->next->next);
    
    p = linked_list;
	while (p != NULL)
	{
	  printf("%s\n", p->data);
	  p = p->next;
    }
    
    free_list(linked_list->next);
    linked_list->next = NULL;
    
    p = linked_list;
	while (p != NULL)
	{
	  printf("%s\n", p->data);
	  p = p->next;
    }
	
	return 0;
}
