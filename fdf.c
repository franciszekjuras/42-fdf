#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <X11/X.h>
#include <mlx/mlx.h>
#include <libft/libft.h>
#include <libgf/gf.h>
#include <libgf/gf_keys.h>
#include "camera.h"
#include "map.h"
#include "fdf.h"

int	render(t_gf_ctx *ctx);

	// mlx_destroy_window(ctx->mlx, ctx->win);
	// mlx_destroy_display(ctx->mlx);
int	close_app(t_gf_ctx *ctx)
{
	(void) ctx;
	exit(0);
	return (0);
}

	// fprintf(stderr, "Key: %#X\n", keycode);
	// t_data		*data;
	// t_gf_camera	*cam;
	// data = ctx->data;
	// cam = &data->cam;
int	handle_key(int keycode, t_gf_ctx *ctx)
{
	if (GF_K_ESC == keycode)
		close_app(ctx);
	else if (GF_K_HOME == keycode)
		camera_init(ctx);
	else if (GF_K_LEFT == keycode)
		camera_move(ctx, 0., 0.1, 0.);
	else if (GF_K_RIGHT == keycode)
		camera_move(ctx, 0., -0.1, 0.);
	else if (GF_K_UP == keycode)
		camera_move(ctx, 0.1, 0., 0.);
	else if (GF_K_DONW == keycode)
		camera_move(ctx, -0.1, 0., 0.);
	else if (GF_K_PGUP == keycode)
		camera_move(ctx, 0.0, 0., 0.1);
	else if (GF_K_PGDN == keycode)
		camera_move(ctx, 0.0, 0., -0.1);
	else if ('a' == keycode)
		camera_incr_angle(ctx, 1. * GF_DEG, 0., 0.);
	else if ('d' == keycode)
		camera_incr_angle(ctx, -1. * GF_DEG, 0., 0.);
	else if ('w' == keycode)
		camera_incr_angle(ctx, 0., 1. * GF_DEG, 0.);
	else if ('s' == keycode)
		camera_incr_angle(ctx, 0., -1. * GF_DEG, 0.);
	render(ctx);
	return (0);
}

	// i = 0;
	// while (i < data->line_len - 1)
	// {
	// 	if (data->cam.project(&data->cam, &pts[0], data->line[i])
	// 		&& data->cam.project(&data->cam, &pts[1], data->line[i + 1]))
	// 		gf_line_put(ctx, pts[0], pts[1], color);
	// 	++i;
	// }

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

	color = gf_rgb(255, 200, 200);	
	gf_line_put(ctx, map->cast[i], map->cast[j], color);
}

static void	render_map_draw(t_gf_ctx *ctx, t_map *map)
{
	int			x;
	int			y;
	int			i;

	y = 0;
	while (y < map->dy)
	{
		x = 0;
		while (x < map->dx)
		{
			i = x + y * map->dx;
			if (map->valid[i])
			{
				if (map->valid[i + 1] && x + 1 < map->dx)
					render_map_line_put(ctx, map, i, i + 1);
				if (map->valid[i + map->dx] && y + 1 < map->dy)
					render_map_line_put(ctx, map, i, i + map->dx);
			}
			++x;
		}
		++y;
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

	// data->frame = gf_point(0, ctx->h / 2);
	// data->frame = gf_point(ctx->w / 2, ctx->h / 2);
	// data->line_len = 10;
	// data->line = ft_calloc(data->line_len, sizeof(t_gf_vec3));
	// data->line[0] = gf_vec3(0.5, 0.5, 0.);
	// data->line[1] = gf_vec3(-0.5, 0.5, 0.);
	// data->line[2] = gf_vec3(0., 0., 1.);
	// data->line[3] = gf_vec3(0.5, -0.5, 0.);
	// data->line[4] = gf_vec3(-0.5, -0.5, 0.);
	// data->line[5] = gf_vec3(0., 0., 1.);
	// data->line[6] = gf_vec3(0.5, 0.5, 0.);
	// data->line[7] = gf_vec3(0.5, -0.5, 0.);
	// data->line[8] = gf_vec3(-0.5, -0.5, 0.);
	// data->line[9] = gf_vec3(-0.5, 0.5, 0.);
void	ctx_data_init(t_gf_ctx *ctx, t_data *data, int fd)
{
	ctx->data = data;
	map_read(&data->map, fd);
	camera_init(ctx);
}

void	context_init(t_gf_ctx *ctx)
{
	ctx->do_repaint = 1;
	fprintf(stderr, "init mlx...\n");
	ctx->mlx = mlx_init();
	fprintf(stderr, "mlx_init(): %p\n", ctx->mlx);
	ctx->w = 1200;
	ctx->h = 800;
	ctx->win = mlx_new_window(ctx->mlx, ctx->w, ctx->h, "Hello there");
	ctx->img = gf_img(ctx->mlx, ctx->w, ctx->h);
	ctx->do_repaint = 1;
	mlx_do_key_autorepeaton(ctx->mlx);
}

int	main(int argc, char **argv)
{
	t_gf_ctx	ctx;
	t_data		data;
	int			fd;

	if (argc != 2)
	{
		ft_putstr_fd("Help placeholder\n", 2);
		return(0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Cannot open file: ", 2);
		ft_putendl_fd(argv[1], 2);
		return (0);
	}
	context_init(&ctx);
	ctx_data_init(&ctx, &data, fd);
	close(fd);
	mlx_hook(ctx.win, DestroyNotify, 0, &close_app, &ctx);
	mlx_hook(ctx.win, KeyPress, KeyPressMask, &handle_key, &ctx);
	render(&ctx);
	mlx_loop(ctx.mlx);
}
