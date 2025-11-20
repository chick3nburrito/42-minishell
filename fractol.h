/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 21:03:17 by bamdjar           #+#    #+#             */
/*   Updated: 2025/04/07 20:31:52 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 900
# define HEIGHT 900
# define ITR 42
# define MS " \t Error: Wrong input! \n \t Try with mandelbrot"
# define  G "or julia <value> <value>\n"

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			x;
	int			y;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct s_complex
{
	double		real;
	double		i;
}				t_complex;

typedef struct s_farctol
{
	void		*mlx;
	void		*mlx_win;
	double		x;
	double		y;
	double		zoom;
	t_data		*image;
	t_complex	julia;
	int			m;
}				t_fractol;

double			scale(double unscaled_num, double new_max, double old_max);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			fractol_init(t_fractol *fractol, t_data *img, char *name);
int				key_handler(int key, t_fractol *fractol);
int				closing(t_fractol *fractol, t_data *img, int x);
void			draw_to_img(t_data *img, t_fractol *fractol);
int				mouse_hook(int button, int x, int y, t_fractol *fractol);
double			atod(char *s);
int				x_on(t_fractol *fractol);

#endif
