#ifndef MAP_H
# define MAP_H

# include <libgf/gf.h>

# define FDF_GRID_SEP 100

typedef struct s_map
{
	t_gf_vec3	*mesh;
	t_gf_point	*cast;
	int			*valid;
	int			dy;
	int			dx;
	double		max;
	double		min;
}	t_map;

void	map_read(t_map *map, int fd);

#endif
