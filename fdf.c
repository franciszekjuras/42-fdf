#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>
#include <mlx/mlx.h>
#include <libft/libft.h>
#include <libgf/gf.h>
#include <libgf/gf_keys.h>
#include "fdf.h"
#include "camera.h"

int	render(t_gf_ctx *ctx);

	// mlx_destroy_window(ctx->mlx, ctx->win);
	// mlx_destroy_display(ctx->mlx);
int	close_app(t_gf_ctx *ctx)
{
	(void) ctx;
	exit(0);
	return (0);
}

void	ctx_camera_init(t_gf_ctx *ctx, t_gf_camera *cam)
{
	cam->yaw = 0.;
	cam->pitch = 25. * GF_DEG;
	cam->roll = 0.;
	gf_camera_angle_changed(cam);
	cam->pos = gf_vec3_mult(cam->z, -10.);
	cam->center = gf_point(ctx->w / 2, ctx->h / 2);
	cam->fov = 0.5;
	cam->iso_dist = 5.;
	cam->scale = ctx->w;
	cam->project = gf_project_rectilinear;
}

	// fprintf(stderr, "Key: %#X\n", keycode);
int	handle_key(int keycode, t_gf_ctx *ctx)
{
	t_data		*data;
	t_gf_camera	*cam;

	data = ctx->data;
	cam = &data->cam;
	if (GF_K_ESC == keycode)
		close_app(ctx);
	else if (GF_K_HOME == keycode)
		ctx_camera_init(ctx, cam);
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

int	render(t_gf_ctx *ctx)
{
	t_data		*data;
	int			i;
	t_gf_color	color;
	t_gf_point	pts[2];

	gf_img_clear(&ctx->img);
	data = ctx->data;
	color = gf_rgb(255, 200, 200);
	i = 0;
	while (i < data->line_len - 1)
	{
		if (data->cam.project(&data->cam, &pts[0], data->line[i])
			&& data->cam.project(&data->cam, &pts[1], data->line[i + 1]))
			gf_line_put(ctx, pts[0], pts[1], color);
		++i;
	}
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->img.img, 0, 0);
	return (0);
}

	// data->frame = gf_point(0, ctx->h / 2);
	// data->frame = gf_point(ctx->w / 2, ctx->h / 2);
t_data	*ctx_data_init(t_gf_ctx *ctx, t_data *data)
{
	ctx_camera_init(ctx, &data->cam);
	data->line_len = 10;
	data->line = ft_calloc(data->line_len, sizeof(t_gf_vec3));
	data->line[0] = gf_vec3(0.5, 0.5, 0.);
	data->line[1] = gf_vec3(-0.5, 0.5, 0.);
	data->line[2] = gf_vec3(0., 0., 1.);
	data->line[3] = gf_vec3(0.5, -0.5, 0.);
	data->line[4] = gf_vec3(-0.5, -0.5, 0.);
	data->line[5] = gf_vec3(0., 0., 1.);
	data->line[6] = gf_vec3(0.5, 0.5, 0.);
	data->line[7] = gf_vec3(0.5, -0.5, 0.);
	data->line[8] = gf_vec3(-0.5, -0.5, 0.);
	data->line[9] = gf_vec3(-0.5, 0.5, 0.);
	return (data);
}

t_gf_ctx	context_init(void)
{
	t_gf_ctx	ctx;

	ctx.do_repaint = 1;
	fprintf(stderr, "init mlx...\n");
	ctx.mlx = mlx_init();
	fprintf(stderr, "mlx_init(): %p\n", ctx.mlx);
	ctx.w = 1200;
	ctx.h = 800;
	ctx.win = mlx_new_window(ctx.mlx, ctx.w, ctx.h, "Hello there");
	ctx.img = gf_img(ctx.mlx, ctx.w, ctx.h);
	ctx.do_repaint = 1;
	mlx_do_key_autorepeaton(ctx.mlx);
	return (ctx);
}

int	main(void)
{
	t_gf_ctx	ctx;
	t_data		data;

	ctx = context_init();
	ctx.data = ctx_data_init(&ctx, &data);
	mlx_hook(ctx.win, DestroyNotify, 0, &close_app, &ctx);
	mlx_hook(ctx.win, KeyPress, KeyPressMask, &handle_key, &ctx);
	render(&ctx);
	mlx_loop(ctx.mlx);
}
