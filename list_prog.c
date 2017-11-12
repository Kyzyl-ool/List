#include <stdio.h>
#include "list.h"

int main()
{
	list* l = list_Construct();
	
	
	for (int i = 0; i < 10; i++)
	{
		list_Push_Head(l, i);
	}
	
	
	list_Print_Dump(l, "LIST_DUMP.DMP");
	list_Destroy(l);
	return 0;
}
