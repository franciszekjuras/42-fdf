#ifndef FDF_H
# define FDF_H

# include <libgf/gf.h>

typedef struct s_data
{
	t_gf_camera	cam;
	t_gf_vec3	cam_center;
	double		cam_dist;
	t_gf_point	frame;
	t_gf_vec3	*line;
	int			line_len;
}	t_data;

#endif