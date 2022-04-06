#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mlx/mlx.h>
#include <libft/libft.h>
#include "gf.h"

// static void	gf_line_put_x(
// 	t_gf_ctx* ctx, t_gf_point beg, t_gf_point end, int good_color)
// {
// 	t_gf_point	d;
// 	int			D;
// 	int			yi;

// 	d.x = end.x - beg.x;
// 	d.y = end.y - beg.y;
// 	yi = 1;
//     if (d.y < 0)
// 	{
//         yi = -1;
//         d.y = -d.y;
// 	}
// 	D = 2 * d.y - d.x;
// 	while (beg.x < end.x)
// 	{
// 		gf_point_put_gc(ctx, beg, good_color);
// 		if (D > 0)
// 		{
// 			beg.y += yi;
// 			D += 2 * d.y - 2 * d.x;
// 		}
// 		else
// 			D += 2 * d.y;
// 		beg.x += 1;
// 	}
// }

// static void	gf_line_put_y(
// 	t_gf_ctx* ctx, t_gf_point beg, t_gf_point end, int good_color)
// {
// 	t_gf_point	d;
// 	int			D;
// 	int			xi;

// 	d.x = end.x - beg.x;
// 	d.y = end.y - beg.y;
// 	xi = 1;
//     if (d.x < 0)
// 	{
//         xi = -1;
//         d.x = -d.x;
// 	}
// 	D = 2 * d.x - d.y;
// 	while (beg.y < end.y)
// 	{
// 		gf_point_put_gc(ctx, beg, good_color);
// 		if (D > 0)
// 		{
// 			beg.x += xi;
// 			D += 2 * d.x - 2 * d.y;
// 		}
// 		else
// 			D += 2 * d.x;
// 		beg.y += 1;
// 	}
// }

// void	gf_line_put(
// 	t_gf_ctx* ctx, t_gf_point p1, t_gf_point p2, t_gf_color color)
// {
// 	int	good_color;
	
// 	good_color = mlx_get_color_value(ctx->mlx, gf_ctoi(color));
// 	if (ft_abs(p2.x - p1.x) > ft_abs(p2.y - p1.y))
// 		if (p2.x > p1.x)
// 			gf_line_put_x(ctx, p1, p2, good_color);
// 		else
// 			gf_line_put_x(ctx, p2, p1, good_color);
// 	else		
// 		if (p2.y > p1.y)
// 			gf_line_put_y(ctx, p1, p2, good_color);
// 		else
// 			gf_line_put_y(ctx, p2, p1, good_color);
// }

void	gf_line_put(
	t_gf_ctx* ctx, t_gf_point beg, t_gf_point end, t_gf_color color)
{
	t_gf_point	d;
	int			D2;
	int			D;
	int			good_color;
	t_gf_point	s;

    d.x = abs(end.x - beg.x);
    s.x = beg.x < end.x ? 1 : -1;
    d.y = -abs(end.y - beg.y);
    s.y = beg.y < end.y ? 1 : -1;
    D = 2 * (d.x + d.y);
	good_color = mlx_get_color_value(ctx->mlx, gf_ctoi(color));
    while (1)
	{       
		gf_point_put_gc(ctx, beg, good_color);
        if (beg.x == end.x && beg.y == end.y)
			break;
		D2 = 2 * D;
        if (D2 >= d.y)
		{
            if (beg.x == end.x)
				break;
            D += d.y;
            beg.x += s.x;
		}
        else if (D2 <= d.x)
		{
            if (beg.y == end.y)
				break;
            D += d.x;
            beg.y += s.y;
		}
	}
}
