#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>
#include <time.h>
#include <mlx/mlx.h>
#include <libft/libft.h>
#include <libgf/gf.h>
#include <libgf/gf_keys.h>
#include "fdf.h"
#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC 0
#endif

int	render(t_gf_ctx *ctx);

int close_app(t_gf_ctx* ctx)
{
	mlx_destroy_window(ctx->mlx, ctx->win);
	// mlx_destroy_display(ctx->mlx);
	exit(0);
	return (0);
}

int	handle_key(int keycode, t_gf_ctx* ctx)
{
	t_data	*data;

	data = ctx->data;
	// fprintf(stderr, "Key: %#X\n", keycode);
	if (GF_K_ESC == keycode)
		close_app(ctx);
	else if (GF_K_HOME == keycode)
		data->frame = gf_point(0, 0);
	else if (GF_K_LEFT == keycode)
		data->frame.x -= 10;
	else if (GF_K_RIGHT == keycode)
		data->frame.x += 10;
	else if (GF_K_UP == keycode)
		data->frame.y -= 10;
	else if (GF_K_DONW == keycode)
		data->frame.y += 10;
	ctx->do_repaint = 1;
	render(ctx);
	return (0);
}

int	render(t_gf_ctx *ctx)
{
	t_gf_point	tl;
	t_gf_point	br;
	t_gf_color	clr;
	t_data		*data;
	int			i;
	struct timespec time_crr;
	struct timespec time_prev;
	long			nanos;

	data = ctx->data;
	if (!ctx->do_repaint)
		return (0);
	// mlx_clear_window(ctx->mlx, ctx->win);
	clock_gettime(CLOCK_MONOTONIC, &time_prev);
	ft_bzero(ctx->img.adr, ctx->img.lnlen * ctx->img.h);
	i = 0;
	while (i < 1000){
		tl = data->frame;
		br = tl;
		br.y += rand() % 500 - 250;
		br.x += rand() % 500 - 250;
		clr = gf_rgb(rand() % 255, rand() % 255, rand() % 255);
		gf_line_put(ctx, tl, br, clr);
		++i;
	}
	clock_gettime(CLOCK_MONOTONIC, &time_crr);
	nanos = (1000000000l * (time_crr.tv_sec - time_prev.tv_sec)
		+ (time_crr.tv_nsec - time_prev.tv_nsec));
	fprintf(stderr, "%ld\n", nanos/1000);
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->img.img, 0, 0);
	ctx->do_repaint = 0;
	return (0);
}

t_data	*data_init_p(t_gf_ctx *ctx, t_data* data)
{
	// data->frame = gf_point(0, ctx->h / 2);
	data->frame = gf_point(ctx->w / 2, ctx->h / 2);
	return (data);
}

t_gf_ctx	context_init()
{
	t_gf_ctx	ctx;

	ctx.do_repaint = 1;
	ctx.mlx = mlx_init();
	ctx.w = 1200;
	ctx.h = 800;
	ctx.win = mlx_new_window(ctx.mlx, ctx.w, ctx.h, "Hello there");
	ctx.img = gf_img(ctx.mlx, ctx.w, ctx.h);
	// mlx_put_image_to_window(ctx.mlx, ctx.win, ctx.img.img, 0, 0);
	ctx.do_repaint = 1;
	mlx_do_key_autorepeaton(ctx.mlx);
	return (ctx);
}

int	main(void)
{
	t_gf_ctx	ctx;
	t_data		data;

	ctx = context_init();
	ctx.data = data_init_p(&ctx, &data);
	mlx_hook(ctx.win, DestroyNotify, 0, &close_app, &ctx);
	mlx_hook(ctx.win, KeyPress, KeyPressMask, &handle_key, &ctx);
	render(&ctx);
	mlx_loop(ctx.mlx);
}
