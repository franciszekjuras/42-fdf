#include <math.h>
#include <libgf/gf.h>
#include <libft/libft.h>
#include "fdf.h"
#include "map.h"

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

void	camera_init(t_gf_ctx *ctx)
{
	t_data		*data;
	t_map		*map;
	t_gf_camera	*cam;
	t_gf_vec3	vec;

	data = ctx->data;
	cam = &data->cam;
	map = &data->map;
	cam->yaw = 225. * GF_DEG;
	cam->pitch = 25. * GF_DEG;
	cam->roll = 0.;
	gf_camera_angle_changed(cam);
	vec = gf_vec3_sub(map->mesh[map->dx * map->dy - 1], map->mesh[0]);
	cam->pos = gf_vec3_mult(cam->z, -2. * gf_vec3_len(vec));
	vec = gf_vec3_add(map->mesh[map->dx * map->dy - 1], map->mesh[0]);
	gf_vec3_iadd(&cam->pos, gf_vec3_mult(vec, 0.5));
	cam->center = gf_point(ctx->w / 2, ctx->h / 2);
	cam->fov = 0.5;
	cam->iso_dist = 5.;
	cam->scale = ctx->w;
	cam->project = gf_project_rectilinear;
}
