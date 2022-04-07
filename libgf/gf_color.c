#include <mlx/mlx.h>
#include "gf.h"

int	gf_ctoi(t_gf_color color)
{
	return ((color.r << 16) + (color.g << 8) + color.b);
}

t_gf_color	gf_rgb(int r, int g, int b)
{
	t_gf_color	color;

	color.a = 0;
	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}
