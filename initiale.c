/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiale.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:39:59 by bamdjar           #+#    #+#             */
/*   Updated: 2025/04/07 21:45:02 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	handle_pixel_julia(t_complex num, t_data *img, t_fractol *fractol)
{
	t_complex	z;
	t_complex	c;
	int			color;
	int			i;
	double		temp;

	c.real = fractol->julia.real;
	c.i = fractol->julia.i;
	z.real = scale(num.real, 2, WIDTH) * fractol->zoom + fractol->x;
	z.i = scale(num.i, 2, HEIGHT) * fractol->zoom + fractol->y;
	i = 0;
	while (i++ < ITR)
	{
		temp = z.real;
		z.real = (z.real * z.real) - (z.i * z.i) + c.real;
		z.i = 2 * temp * z.i + c.i;
		if ((z.real * z.real) + (z.i * z.i) > 4)
		{
			color = scale(i, 0xFFFFFF, ITR);
			my_mlx_pixel_put(img, (int)num.real, (int)num.i, color);
			return ;
		}
	}
	my_mlx_pixel_put(img, (int)num.real, (int)num.i, 0x000000);
}

void	handle_pixel(t_complex num, t_data *img, t_fractol *fractol)
{
	t_complex	z;
	t_complex	c;
	int			color;
	int			i;
	double		temp;

	z.real = 0;
	z.i = 0;
	c.real = scale(num.real, 2, WIDTH) * fractol->zoom + fractol->x;
	c.i = scale(num.i, 2, HEIGHT) * fractol->zoom + fractol->y;
	i = 0;
	while (i++ < ITR)
	{
		temp = z.real;
		z.real = (z.real * z.real) - (z.i * z.i) + c.real;
		z.i = 2 * temp * z.i + c.i;
		if ((z.real * z.real) + (z.i * z.i) > 4)
		{
			color = scale(i, 0xFFFFFF, ITR);
			my_mlx_pixel_put(img, (int)num.real, (int)num.i, color);
			return ;
		}
	}
	my_mlx_pixel_put(img, (int)num.real, (int)num.i, 0x000000);
}

void	draw_to_img(t_data *img, t_fractol *fractol)
{
	t_complex	num;

	num.real = 1;
	while (num.real < WIDTH)
	{
		num.i = 1;
		while (num.i < HEIGHT)
		{
			if (fractol->m)
				handle_pixel_julia(num, img, fractol);
			else
				handle_pixel(num, img, fractol);
			num.i++;
		}
		num.real++;
	}
	mlx_put_image_to_window(fractol->mlx, fractol->mlx_win, img->img, 0, 0);
}

void	fractol_init(t_fractol *fractol, t_data *img, char *name)
{
	fractol->mlx = mlx_init();
	if (!(fractol->mlx))
		exit(1);
	fractol->mlx_win = mlx_new_window(fractol->mlx, WIDTH, HEIGHT, name);
	if (!(fractol->mlx_win))
	{
		exit((mlx_destroy_display(fractol->mlx), free(fractol->mlx), 1));
	}
	img->img = mlx_new_image(fractol->mlx, WIDTH, HEIGHT);
	if (!img->img)
	{
		mlx_destroy_window(fractol->mlx, fractol->mlx_win);
		exit((mlx_destroy_display(fractol->mlx), free(fractol->mlx), 1));
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (name[0] == 'M')
		fractol->m = 0;
	else
		fractol->m = 1;
	draw_to_img(((fractol->image = img), fractol->image), fractol);
	mlx_key_hook(fractol->mlx_win, key_handler, fractol);
	mlx_mouse_hook(fractol->mlx_win, mouse_hook, fractol);
	mlx_hook(fractol->mlx_win, 17, 0, x_on, fractol);
	mlx_loop(fractol->mlx);
}
