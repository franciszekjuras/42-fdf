#include <stdlib.h>
#include <libft/libft.h>
#include "get_next_line.h"
#include "fdf.h"

void list_str_del_forw(t_list_str* node)
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

t_list_str	*list_str_add(t_list_str* node)
{
	t_list_str	*next;

	next = node->next;
	node->next = malloc(sizeof(t_list_str));
	node->next->next = next;
	return (node->next);
}

void	map_read_error(char *str)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(str, 2)
	exit(1);
}

int	read_lines_fd(t_list_str *node, int fd)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (line != 0)
	{
		node = list_str_add(node);
		node->str = line;
		line = get_next_line(fd);
		++i;
	}
	return (i);
}

void	map_read(t_map *map, int fd)
{
	t_list_str	root;
	t_list_str	*node;
	char		**row;

	map->dy = read_lines_fd(&root, fd);
	if (map->dy == 0)
		map_read_error("Empty map");
	node = root.next;
	row = ft_split(node->str, ' ');
	map->dx = 0;
	while (row[map->dx] != 0)
		++map->dx;	
	if (map->dx == 0)
		map_read_error("Empty first row");
	while (node->str != 0)
	{
		if (row == 0)
			row = ft_split(node->str);
		//processing
		node = node->next;
		row = ft_freeparr(row);
	}
}
