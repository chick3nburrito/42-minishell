/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:40:13 by bamdjar           #+#    #+#             */
/*   Updated: 2025/04/07 21:43:47 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	is_digit(char *str)
{
	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;
	if (*str == '+' || *str == '-')
		str++;
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if ((*str < '0' || *str > '9') && (*str != '.' && *str != ','))
			return (0);
		str++;
	}
	return (1);
}

int	closing(t_fractol *fractol, t_data *img, int x)
{
	mlx_destroy_image(fractol->mlx, img->img);
	mlx_destroy_window(fractol->mlx, fractol->mlx_win);
	mlx_destroy_display(fractol->mlx);
	free(fractol->mlx);
	exit(x);
}

void	handle_input(char *str, char *set)
{
	int	i;

	if (*str == '\0')
	{
		exit((write(2, MS, 73), write(2, G, 73) & 1));
	}
	while (*str == ' ' || *str == '\t')
		str++;
	i = 0;
	while (set[i] && (str[i] == set[i] || str[i] == set[i] - 32))
		i++;
	if (set[i] == '\0')
	{
		str += i;
		while (*str == ' ' || *str == '\t')
			str++;
		if (*str == '\0')
			return ;
	}
	exit((write(2, MS, 46), write(2, G, 25) & 1));
}

int	main(int arc, char **arv)
{
	t_fractol	fractol;
	t_data		img;

	fractol.x = 0;
	fractol.y = 0;
	fractol.zoom = 1;
	if (arc == 2)
	{
		handle_input(arv[1], "mandelbrot");
		fractol_init(&fractol, &img, "Mandelbrot");
	}
	else if (arc == 4 && is_digit(arv[2]) && is_digit(arv[3]))
	{
		handle_input(arv[1], "julia");
		fractol.julia.real = atod(arv[2]);
		fractol.julia.i = atod(arv[3]);
		fractol_init(&fractol, &img, "Julia");
	}
	else
		exit((write(2, MS, 46), write(2, G, 25) & 1));
	return (0);
}
