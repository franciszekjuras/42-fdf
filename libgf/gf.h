#ifndef GF_H
# define GF_H

typedef struct s_gf_color
{
	int	b;
	int	g;
	int	r;
	int	a;
}	t_gf_color;

typedef struct s_gf_grad
{
	t_gf_color	beg;
	t_gf_color	end;
}	t_gf_grad;

typedef struct s_gf_point
{
	int	x;
	int	y;
}	t_gf_point;

typedef struct s_gf_img
{
	void	*img;
	void	*adr;
	int		bypp;
	int		lnlen;
	int		endn;
	int		w;
	int		h;
	void	(*pxput)(struct s_gf_img* , t_gf_point, int);
}	t_gf_img;

typedef struct s_gf_ctx
{
	void		*mlx;
	void		*win;
	t_gf_img	img;
	int			w;
	int 		h;
	int			do_repaint;
	void		*data;
}	t_gf_ctx;


t_gf_point	gf_point(int x, int y);
int			gf_ctoi(t_gf_color color);
t_gf_color	gf_rgb(int r, int g, int b);
void		gf_point_put(t_gf_ctx* ctx, t_gf_point point, t_gf_color color);
void		gf_point_put_gc(t_gf_ctx* ctx, t_gf_point point, int good_color);
void		gf_framebox_put(t_gf_ctx* ctx, t_gf_point pt_tl,
				t_gf_point pt_br, t_gf_color color);
void	gf_line_put(t_gf_ctx* ctx, 
				t_gf_point beg, t_gf_point end, t_gf_color color);
t_gf_img	gf_img(void *mlx, int w, int h);

#endif
