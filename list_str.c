#include <stdlib.h>
#include "list_str.h"

void	list_str_del_forw(t_list_str *node)
{
	t_list_str	*next;

	while (node != 0)
	{
		next = node->next;
		free(node->str);
		free(node);
		node = next;
	}
}

t_list_str	*list_str_add(t_list_str *node)
{
	t_list_str	*next;

	next = node->next;
	node->next = malloc(sizeof(t_list_str));
	node->next->next = next;
	return (node->next);
}
