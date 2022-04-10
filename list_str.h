#ifndef LIST_STR_H
# define LIST_STR_H

typedef struct s_list_str
{
	char				*str;
	struct s_list_str	*next;
}	t_list_str;

void	list_str_del_forw(t_list_str *node);
t_list_str	*list_str_add(t_list_str *node);

#endif
