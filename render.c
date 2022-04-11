#include <mlx/mlx.h>
#include <libgf/gf.h>
#include "fdf.h"

static void	render_map_cast(t_map *map, t_gf_camera *cam)
{
	int		x;
	int		y;
	int		i;
	y = 0;
	while (y < map->dy)
	{
		x = 0;
		while (x < map->dx)
		{
			i = x + y * map->dx;
			map->valid[i] = cam->project(cam, &map->cast[i], map->mesh[i]);
			++x;
		}
		++y;
	}
}

static void	render_map_line_put(t_gf_ctx *ctx, t_map *map, int i, int j)
{
	t_gf_color	color;
	t_data		*data;
	double		meanz;

	data = ctx->data;
	meanz = (map->mesh[i].z + map->mesh[j].z) * 0.5;
	if (meanz >= 0.)
		color = gf_color_grad(meanz, &data->grad_pos);
	else
		color = gf_color_grad(meanz, &data->grad_neg);
	gf_line_put(ctx, map->cast[i], map->cast[j], color);
}

static void	render_map_draw(t_gf_ctx *ctx, t_map *map)
{
	int			x;
	int			y;
	int			i;

	x = 0;
	while (x < map->dx)
	{
		y = 0;
		while (y < map->dy)
		{
			i = y + x * map->dy;
			if (map->valid[i])
			{
				if (y + 1 < map->dy && map->valid[i + 1])
					render_map_line_put(ctx, map, i, i + 1);
				if (x + 1 < map->dx && map->valid[i + map->dy])
					render_map_line_put(ctx, map, i, i + map->dy);
			}
			++y;
		}
		++x;
	}
}

int	render(t_gf_ctx *ctx)
{
	t_data	*data;

	gf_img_clear(&ctx->img);
	data = ctx->data;
	render_map_cast(&data->map, &data->cam);
	render_map_draw(ctx, &data->map);
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->img.img, 0, 0);
	return (0);
}