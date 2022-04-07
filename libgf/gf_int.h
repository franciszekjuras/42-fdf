#ifndef GF_INT_H
# define GF_INT_H

# include "gf.h"

void		gf_int_img_pxput4(t_gf_img *img, t_gf_point pt, int good_color);
int			gf_iround(double v);
int			gf_inimage(t_gf_img *img, t_gf_point *pt);

#endif
