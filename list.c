#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "list.h"
#include <assert.h>

list* 	list_Construct()
{
	list* l = (list* )calloc(1, sizeof(list));
	l->head = NULL;
	l->tail = NULL;
	l->amount = 0;
	return l;
}

int		list_Destroy(list* l)
{
	assert(l);
	list_elem* i = l->head;
	while (i != NULL)
	{
		list_elem* tmp = i->next;
		free(i);
		i = tmp;
	}
	
	free(l);
	return 0;
}

int		list_Push_Tail(list* l, list_elem_t value)
{
	assert(l); assert(isfinite(value));
	if (l->amount == 0)
	{
		list_Push_Head(l, value);
	}
	else
	{
		list_elem* new = (list_elem* )calloc(1, sizeof(list_elem));
		new->value = value;
		new->next = NULL;
		new->pred = l->tail;
		l->tail->next = new;
		l->tail = new;
		l->amount++;
	}
	return list_Check(l);
}

int		list_Push_Head(list* l, list_elem_t value)
{
	assert(l); assert(isfinite(value));
	list_elem* new = (list_elem* )calloc(1, sizeof(list_elem));
	new->value = value;
	if (l->amount == 0)
	{
		l->head = new;
		l->tail = new;
		new->pred = NULL;
		new->next = NULL;
	}
	else
	{
		new->next = l->head;
		new->pred = NULL;
		l->head->pred = new;
		l->head = new;
		
	}
	l->amount++;
	return list_Check(l);
}

list_elem_t list_Pop_by_number(list* l, int n)
{
	assert(l);
	assert(isfinite(n));
	list_elem_t val = list_Find(l, n)->value;
	list_Delete(l, list_Find(l, n));
	return val;
}
int		list_Push_by_number(list*l, list_elem_t value, int n)
{
	assert(l); assert(isfinite(value)); assert(isfinite(n));
	if (n == 0)
	{
		list_Push_Head(l, value);
	}
	else if (n == l->amount - 1)
	{
		list_Push_Tail(l, value);
	}
	else
	{
		list_elem* i = l->head;
		for (int j = 0; j < n; j++)
		{
			i = i->next;
		}
		list_elem* new = (list_elem* )calloc(1, sizeof(list_elem));
		i->next->pred = new;
		new->next = i->next;
		new->pred = i;
		i->next = new;
		l->amount++;
	}
	return list_Check(l);
}

void			list_Dump(list* l)
{
	assert(l);
	printf(
	"List dump (%s).\n\n"
	"Address: [%p]\n"
	"Head: [%p]\n"
	"Tail: [%p]\n"
	"Amount: %d\n\n", list_error_message(list_Check(l)), l, l->head, l->tail, l->amount);
	
	printf("Elements:\n");
	list_elem* i = l->head;
	for (int j = 1; j <= l->amount; j++)
	{
		printf("%d: %lg\n", j, i->value);
		i = i->next;
		
	}
}

void			list_Print_Dump(list* l, const char* dump_name)
{
	assert(l);
	FILE* fo = fopen(dump_name, "w");
	fprintf(fo,
	"List dump (%s).\n\n"
	"Address: [%p]\n"
	"Head: [%p]\n"
	"Tail: [%p]\n"
	"Amount: %d\n\n", list_error_message(list_Check(l)), l, l->head, l->tail, l->amount);
	
	if (l->amount > 0)
	{
		fprintf(fo, "Elements:\n");
		list_elem* i = l->head;
		for (int j = 1; j <= l->amount; j++)
		{
			fprintf(fo, "%d: %lg\n", j, i->value);
			i = i->next;
			
		}
	}
	fclose(fo);
}


int				list_Check(const list* l)
{
	assert(l);
	if (l->amount > 0)
	{
		list_error_code code = list_elem_check(l->head);
		switch (code)
		{
			case LIST_ELEM_OK_PRED_NEXT_NULL:
			{
				if (l->amount != 1)
				{
					return LIST_HEAD_WITH_NULL_PRED_AND_NEXT_BUT_LIST_AMOUNT_IS_NOT_ONE;
				}
				break;
			}
			case LIST_ELEM_OK_NEXT_NULL:
			{
				if (l->amount != 1)
				{
					return LIST_HEAD_WITH_NULL_NEXT_BUT_LIST_AMOUNT_IS_NOT_ONE;
				}
				break;
			}
			case LIST_ELEM_OK:
			{
				return LIST_HEAD_PRED_IS_NOT_NULL;
				break;
			}
			case LIST_ELEM_OK_PRED_NULL:
			{
				break;
			}
			default:
			{
				return code;
			}
		}
		
		code = list_elem_check(l->tail);
		switch (code)
		{
			case LIST_ELEM_OK:
			{
				return LIST_TAIL_NEXT_IS_NOT_NULL;
			}
			case LIST_ELEM_OK_PRED_NULL:
			{
				if (l->amount != 1)
				{
					return LIST_TAIL_PRED_IS_NULL_BUT_LIST_AMOUNT_IS_NOT_ONE;
				}
				break;
			}
			case LIST_ELEM_OK_PRED_NEXT_NULL:
			{
				if (l->amount != 1)
				{
					return LIST_TAIL_PRED_AND_NEXT_IS_NULL_BUT_LIST_AMOUNT_IS_NOT_ONE;
				}
				break;
			}
			case LIST_ELEM_OK_NEXT_NULL:
			{
				break;
			}
			default:
			{
				return code;
			}
		}
	}
	
	if (l->amount > 2)
	{
		list_elem* i = l->head->next;
		while (i->next->next != NULL)
		{
			if (list_elem_check(i) != LIST_ELEM_OK)
			{
				return LIST_IS_BROKEN;
			}
			i = i->next;
		}
	}
	
	return LIST_OK;
}

int				list_Delete_by_value(list* l, list_elem_t val)
{
	assert(l);
	assert(isfinite(val));
	list_elem* i = l->head;
	while (i->value != val && i->next != NULL)
	{
		i = i->next;
	}
	if (i->value == val) list_Delete(l, i);
		
	return list_Check(l);
}

list_elem*		list_Find(list* l, int n)
{
	assert(l);
	assert(isfinite(n));
	int i = 0;
	list_elem* current = l->head;
	while (i < n && current->next != NULL)
	{
		current = current->next;
		i++;
	}
	if (i == n)
		return current;
	else
		return NULL;
}

void			list_help(list_error_code error_code)
{
	printf("%s\n", list_error_message(error_code));
}

char*			list_error_message(list_error_code error_code)
{
	switch (error_code)
	{
		#define RET_CODE_(code) case code: return #code;
		
		RET_CODE_ (LIST_OK)
		RET_CODE_ (LIST_DELETE_FROM_EMPTY_LIST)
		RET_CODE_ (LIST_DELETE_INVALID_ELEM_ADDRESS)
		RET_CODE_ (LIST_HEAD_WITH_NULL_PRED_AND_NEXT_BUT_LIST_AMOUNT_IS_NOT_ONE)
		RET_CODE_ (LIST_HEAD_WITH_NULL_NEXT_BUT_LIST_AMOUNT_IS_NOT_ONE)
		RET_CODE_ (LIST_HEAD_PRED_IS_NOT_NULL)
		RET_CODE_ (LIST_TAIL_NEXT_IS_NOT_NULL)
		RET_CODE_ (LIST_TAIL_PRED_IS_NULL_BUT_LIST_AMOUNT_IS_NOT_ONE)
		RET_CODE_ (LIST_TAIL_PRED_AND_NEXT_IS_NULL_BUT_LIST_AMOUNT_IS_NOT_ONE)
		RET_CODE_ (LIST_IS_BROKEN)
		RET_CODE_ (LIST_POP_FROM_INVALID_INDEX)
		 
		RET_CODE_ (LIST_ELEM_FIASKO)
		RET_CODE_ (LIST_ELEM_VALUE_IS_NOT_FINITE)
		RET_CODE_ (LIST_ELEM_PRED_BROKEN)
		RET_CODE_ (LIST_ELEM_NEXT_BROKEN)
		RET_CODE_ (LIST_ELEM_PRED_NEXT_BROKEN)
		RET_CODE_ (LIST_ELEM_OK)
		RET_CODE_ (LIST_ELEM_OK_PRED_NULL)
		RET_CODE_ (LIST_ELEM_OK_NEXT_NULL)
		RET_CODE_ (LIST_ELEM_OK_PRED_NEXT_NULL)
		
		default: return "LIST_UNKNOWN_ERROR";
		#undef RET_CODE_
	}
}

int				list_Delete(list* l, list_elem* elem)
{
	assert(l);
	assert(elem);
	list_error_code code = list_elem_check(elem);
	switch (code)
	{
		case LIST_ELEM_OK:
		{
			elem->pred->next = elem->next;
			elem->next->pred = elem->pred;
			free(elem);
			l->amount--;
			break;
		}
		case LIST_ELEM_OK_NEXT_NULL:
		{
			elem->pred->next = NULL;
			l->tail = elem->pred;
			free(elem);
			l->amount--;
			break;
		}
		case LIST_ELEM_OK_PRED_NEXT_NULL:
		{
			free(elem);
			l->head = NULL;
			l->tail = NULL;
			l->amount--;
			break;
		}
		case LIST_ELEM_OK_PRED_NULL:
		{
			elem->next->pred = NULL;
			l->head = elem->next;
			free(elem);
			l->amount--;
			break;
		}
		default:
		{
			list_help(code);
			return code;
		}
	}
	return list_Check(l);
}
int				list_Push(list* l, list_elem_t val, list_elem* elem)
{
	assert(l);	
	if (elem == NULL)
	{
		list_elem* new_elem = (list_elem* )calloc(1, sizeof(list_elem));
		new_elem->value = val;
		new_elem->pred = NULL;
		new_elem->next = l->head;
		l->head->pred = new_elem;
		l->head = new_elem;
		l->amount++;
	}
	else
	{
		int code = list_elem_check(elem);
		switch (code)
		{
			case LIST_ELEM_OK:
			{
				list_elem* new_elem = (list_elem* )calloc(1, sizeof(list_elem));
				new_elem->value = val;
				new_elem->pred = elem;
				new_elem->next = elem->next;
				elem->next->pred = new_elem;
				elem->next = new_elem;
				l->amount++;
				break;
			}
			case LIST_ELEM_OK_PRED_NULL:
			{
				list_elem* new_elem = (list_elem* )calloc(1, sizeof(list_elem));
				new_elem->value = val;
				new_elem->pred = l->head;
				new_elem->next = l->head->next;
				l->head->next->pred = new_elem;
				l->head->next = new_elem;
				l->amount++;
				break;
			}
			case LIST_ELEM_OK_PRED_NEXT_NULL:
			{
				list_elem* new_elem = (list_elem* )calloc(1, sizeof(list_elem));
				new_elem->value = val;
				new_elem->pred = l->head;
				new_elem->next = NULL;
				l->head->next = new_elem;
				l->amount++;
				break;
			}
			case LIST_ELEM_OK_NEXT_NULL:
			{
				list_elem* new_elem = (list_elem* )calloc(1, sizeof(list_elem));
				new_elem->value = val;
				new_elem->next = NULL;
				new_elem->pred = l->tail;
				l->tail->next = new_elem;
				l->tail = new_elem;
				l->amount++;
				break;
			}
			default:
			{
				list_help(code);
				return code;
			}
		}
	}
	return LIST_ELEM_FIASKO;
}

int				list_elem_check(list_elem* elem)
{
	int ok = 0;
	int error = 0;
	if (isfinite(elem->value))
	{
		if (elem->pred)
		{
			if (elem->pred->next == elem)
			{
				//left is ok
				ok += 2;
			}
			else
			{
				//left is not ok
				error += 2;
			}
		}
		else
		{
			//left is null
		}
		if (elem->next)
		{
			if (elem->next->pred == elem)
			{
				//right is ok
				ok += 1;
			}
			else
			{
				//right is not ok
				error += 1;
			}
		}
		else
		{
			//right is null
		}
	}
	else
	{
		return LIST_ELEM_VALUE_IS_NOT_FINITE;
	}
	if (error == 0)
	{
		switch (ok)
		{
			case 0: return LIST_ELEM_OK_PRED_NEXT_NULL;
			case 1: return LIST_ELEM_OK_PRED_NULL;
			case 2: return LIST_ELEM_OK_NEXT_NULL;
			case 3: return LIST_ELEM_OK;
			default: return LIST_ELEM_FIASKO;
		}
	}
	else
	{
		switch (error)
		{
			case 1: return LIST_ELEM_NEXT_BROKEN;
			case 2:
			{
				printf("elem value: [%p]", elem);
				return  LIST_ELEM_PRED_BROKEN;
			}
			case 3: return LIST_ELEM_PRED_NEXT_BROKEN;
			default: return LIST_ELEM_FIASKO;
		}
	}
	return LIST_ELEM_FIASKO;
}
