#include <math.h>
#include "gf.h"

double	gf_vec3_dot(t_gf_vec3 v1, t_gf_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_gf_vec3	gf_vec3_cross(t_gf_vec3 v1, t_gf_vec3 v2)
{	
	t_gf_vec3	v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}

t_gf_vec3	gf_vec3_norm(t_gf_vec3 v)
{
	t_gf_vec3	r;
	double		srt;

	srt = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	r.x = v.x / srt;
	r.y = v.y / srt;
	r.z = v.z / srt;
	return (r);
}
