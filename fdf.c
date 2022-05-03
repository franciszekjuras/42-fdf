#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <X11/X.h>
#include <mlx/mlx.h>
#include <libft/libft.h>
#include <libgf/gf.h>
#include <libgf/gf_keys.h>
#include "render.h"
#include "camera.h"
#include "map.h"
#include "fdf.h"

int	close_app(t_gf_ctx *ctx)
{
	(void) ctx;
	exit(0);
	return (0);
}

int	handle_key(int keycode, t_gf_ctx *ctx)
{
	double	step;

	step = 0.5 * FDF_GRID_SEP;
	if (GF_K_ESC == keycode)
		close_app(ctx);
	else if (GF_K_HOME == keycode)
		camera_init(ctx);
	else if (GF_K_LEFT == keycode)
		camera_move(ctx, 0., step, 0.);
	else if (GF_K_RIGHT == keycode)
		camera_move(ctx, 0., -step, 0.);
	else if (GF_K_UP == keycode)
		camera_move(ctx, step, 0., 0.);
	else if (GF_K_DONW == keycode)
		camera_move(ctx, -step, 0., 0.);
	else if (GF_K_PGUP == keycode)
		camera_move(ctx, 0.0, 0., step);
	else if (GF_K_PGDN == keycode)
		camera_move(ctx, 0.0, 0., -step);
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

void	ctx_data_init(t_gf_ctx *ctx, t_data *data, int fd)
{
	t_gf_color	col_ntrl;
	t_gf_color	col_pos;
	t_gf_color	col_neg;

	col_ntrl = gf_rgb(255, 255, 255);
	col_pos = gf_rgb(255, 30, 30);
	col_neg = gf_rgb(30, 40, 200);
	ctx->data = data;
	map_read(&data->map, fd);
	data->grad_pos = gf_grad(col_ntrl, col_pos, 0, data->map.max);
	data->grad_neg = gf_grad(col_neg, col_ntrl, data->map.min, 0);
	camera_init(ctx);
}

void	context_init(t_gf_ctx *ctx)
{
	ctx->mlx = mlx_init();
	ctx->w = 1600;
	ctx->h = 900;
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
