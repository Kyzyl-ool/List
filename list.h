#define POISON 999999.999999

typedef double list_elem_t;
typedef struct list_elem
{
	list_elem_t value;
	struct list_elem* next;
	struct list_elem* pred;
}list_elem;

typedef struct list
{
	list_elem* head;
	list_elem* tail;
	int amount;
}list;

enum list_error_codes
{
	LIST_UNKNOWN_ERROR = -1,
	LIST_OK,
	LIST_DELETE_FROM_EMPTY_LIST,
	LIST_DELETE_INVALID_ELEM_ADDRESS,
	LIST_HEAD_WITH_NULL_PRED_AND_NEXT_BUT_LIST_AMOUNT_IS_NOT_ONE,
	LIST_HEAD_WITH_NULL_NEXT_BUT_LIST_AMOUNT_IS_NOT_ONE,
	LIST_HEAD_PRED_IS_NOT_NULL,
	LIST_TAIL_NEXT_IS_NOT_NULL,
	LIST_TAIL_PRED_IS_NULL_BUT_LIST_AMOUNT_IS_NOT_ONE,
	LIST_TAIL_PRED_AND_NEXT_IS_NULL_BUT_LIST_AMOUNT_IS_NOT_ONE,
	LIST_IS_BROKEN,
	LIST_POP_FROM_INVALID_INDEX,
	
	LIST_ELEM_FIASKO,
	LIST_ELEM_VALUE_IS_NOT_FINITE,
	LIST_ELEM_PRED_BROKEN,
	LIST_ELEM_NEXT_BROKEN,
	LIST_ELEM_PRED_NEXT_BROKEN,
	LIST_ELEM_OK,
	LIST_ELEM_OK_PRED_NULL,
	LIST_ELEM_OK_NEXT_NULL,
	LIST_ELEM_OK_PRED_NEXT_NULL,
};
typedef enum list_error_codes list_error_code;

list* 			list_Construct();
int				list_Destroy(list* l);

int				list_Push_Tail(list* l, list_elem_t value);
int				list_Push_Head(list* l, list_elem_t value);
int				list_Push_by_number(list*l, list_elem_t value, int n);
int				list_Push(list* l, list_elem_t val, list_elem* elem);

list_elem_t 	list_Pop_by_number(list* l, int n);
int				list_Delete_by_value(list* l, list_elem_t val);
int				list_Delete(list* l, list_elem* elem);

list_elem*		list_Find(list* l, int n);

void			list_Dump(list* l);
void			list_Print_Dump(list* l, const char* dump_name);
int				list_Check(const list* l);
void			list_help(list_error_code error_code);
char*			list_error_message(list_error_code error_code);
int				list_elem_check(list_elem* elem);
