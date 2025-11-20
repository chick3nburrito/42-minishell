/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:40:23 by bamdjar           #+#    #+#             */
/*   Updated: 2025/04/07 20:31:52 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_handler(int key, t_fractol *fractol)
{
	if (key == 65307)
		closing(fractol, fractol->image, 0);
	else if (key == 65362)
		draw_to_img((fractol->y -= 0.1, fractol->image), fractol);
	else if (key == 65364)
		draw_to_img((fractol->y += 0.1, fractol->image), fractol);
	else if (key == 65361)
		draw_to_img((fractol->x += 0.1, fractol->image), fractol);
	else if (key == 65363)
		draw_to_img((fractol->x -= 0.1, fractol->image), fractol);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_fractol *fractol)
{
	(void)x;
	(void)y;
	if (button == 4)
	{
		fractol->zoom /= 1.1;
		draw_to_img(fractol->image, fractol);
	}
	else if (button == 5)
	{
		fractol->zoom *= 1.1;
		draw_to_img(fractol->image, fractol);
	}
	return (0);
}

int	x_on(t_fractol *fractol)
{
	closing(fractol, fractol->image, 0);
	return (0);
}
