#ifndef FDF_H
# define FDF_H

# include <libgf/gf.h>

typedef struct s_map
{
	t_gf_vec3	*mesh;
	t_gf_point	*mesh_cast;
	double		*mesh_dist;
	int			dx;
	int			dy;
}	t_map;

typedef struct s_list_str
{
	char				*str;
	struct s_list_str	*next;
}	t_list_str;

typedef struct s_data
{
	t_gf_camera	cam;
	t_gf_vec3	cam_center;
	double		cam_dist;
	t_gf_point	frame;
	t_gf_vec3	*line;
	int			line_len;
	t_map		map;
}	t_data;

#endif