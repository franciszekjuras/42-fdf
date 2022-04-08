#include <math.h>
#include <libgf/gf.h>
#include "fdf.h"

void	camera_incr_angle(t_gf_ctx *ctx, double yaw, double pitch, double roll)
{
	t_data		*data;
	t_gf_camera	*cam;

	data = ctx->data;
	cam = &data->cam;
	cam->yaw += yaw;
	cam->pitch += pitch;
	cam->roll += roll;
	gf_camera_angle_changed(cam);
}

void	camera_set_angle(t_gf_ctx *ctx, double yaw, double pitch, double roll)
{
	t_data		*data;
	t_gf_camera	*cam;

	data = ctx->data;
	cam = &data->cam;
	cam->yaw = yaw;
	cam->pitch = pitch;
	cam->roll = roll;
	gf_camera_angle_changed(cam);
}

	// if (forward != 0.)
	// 	gf_vec3_iadd(&cam->pos, gf_vec3_mult(cam->z, forward));
void	camera_move(t_gf_ctx *ctx, double forward, double left, double up)
{
	t_data		*data;
	t_gf_camera	*cam;

	data = ctx->data;
	cam = &data->cam;
	if (left != 0.)
	{
		cam->pos.x += -sin(cam->yaw) * left;
		cam->pos.y += cos(cam->yaw) * left;
	}
	if (forward != 0.)
	{
		cam->pos.x += cos(cam->yaw) * forward;
		cam->pos.y += sin(cam->yaw) * forward;
	}
	cam->pos.z += up;
}

void	camera_set_pos(t_gf_ctx *ctx, t_gf_vec3 pos)
{
	t_data		*data;
	t_gf_camera	*cam;

	data = ctx->data;
	cam = &data->cam;
	cam->pos = pos;
}
