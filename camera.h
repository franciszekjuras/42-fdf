#include <libgf/gf.h>

void	camera_incr_angle(t_gf_ctx *ctx, double yaw, double pitch, double roll);
void	camera_set_angle(t_gf_ctx *ctx, double yaw, double pitch, double roll);
void	camera_move(t_gf_ctx *ctx, double forward, double left, double up);
void	camera_set_pos(t_gf_ctx *ctx, t_gf_vec3 pos);
