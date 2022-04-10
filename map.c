#include <stdlib.h>
#include <limits.h>
#include <libft/libft.h>
#include <libgf/gf.h>
#include "get_next_line.h"
#include "list_str.h"
#include "fdf.h"

static void	map_read_error(char *str, char *str_opt)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(str, 2);
	if (str_opt != 0)
		ft_putstr_fd(str_opt, 2);
	ft_putchar_fd('\n', 2);
	exit(1);
}

static int	read_lines_fd(t_list_str *node, int fd)
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

static void	map_parse_number(t_map *map, int x, int y, char	*str)
{
	int		err;
	char	*np;
	double	v;

	err = 0;
	np = str;
	if (np == 0)
		map_read_error("Unequal line lengths", 0);
	v = ft_strtonum(&np, LLONG_MIN, LLONG_MAX, &err);
	if (err || (*np != '\0' && *np != '\n'))
		map_read_error("Not a valid number: ", str);
	map->mesh[x + y * map->dx] = gf_vec3(FDF_GRID_SEP * x, FDF_GRID_SEP * y, v);
}

static void	map_read_list_str(t_map *map, t_list_str *node, char **row)
{
	int		x;
	int		y;

	y = 0;
	while (node != 0)
	{
		if (row == 0)
			row = ft_split(node->str, ' ');
		x = 0;
		while (x < map->dx)
		{
			map_parse_number(map, x, y, row[x]);
			++x;
		}
		++y;
		node = node->next;
		row = ft_freeparr((void **)row);
	}
}

void	map_read(t_map *map, int fd)
{
	t_list_str	root;
	t_list_str	*node;
	char		**row;

	root.next = 0;
	map->dy = read_lines_fd(&root, fd);
	if (map->dy == 0)
		map_read_error("Empty map", 0);
	node = root.next;
	row = ft_split(node->str, ' ');
	map->dx = 0;
	while (row[map->dx] != 0)
		++map->dx;
	if (map->dx == 0)
		map_read_error("Empty first row", 0);
	map->mesh = ft_calloc(map->dx * map->dy, sizeof(t_gf_vec3));
	map->cast = ft_calloc(map->dx * map->dy, sizeof(t_gf_point));
	map->valid = ft_calloc(map->dx * map->dy, sizeof(int));
	map->dist = ft_calloc(map->dx * map->dy, sizeof(double));
	map_read_list_str(map, node, row);
}
