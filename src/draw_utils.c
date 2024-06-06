/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:02:20 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/06/06 19:11:16 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Convert rgb array to int */
int	rgb_to_int(int *color)
{
	return ((color[0] << 16) | (color[1] << 8) | color[2]);
}

/* Put a pixel on the screen */
void	put_pixel(t_img *img, int x, int y, int color)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bpp / 8));
	*((unsigned int *)(offset + img->pixel_addr)) = color;
}

void	paint_square(t_cube *cube, int start_x, int start_y, double scale)
{
	int	x;
	int	y;
	int	size;

	x = -1;
	y = -1;
	size = SIZE * scale;
	while (++x <= size)
	{
		y = -1;
		while (++y <= size)
			put_pixel(&cube->data->img, (start_x * scale) + x,
				(start_y * scale) + y, cube->clr);
	}
}

/* Draw line from `p1` to `p2`. Variable `i` has to be `-1` */
void	draw_lines(t_point *p1, t_point *p2, t_data *data, int i)
{
	int	dx;
	int	dy;

	dx = fabs(p2->x - p1->x);
	dy = fabs(p2->y - p1->y);
	data->err = dx - dy;
	while (++i < ft_int_max(dx, dy))
	{
		if (p1->x > 0 && p1->x < WIN_W - 5 && p1->y > 0
			&& p1->y < WIN_H - 5)
			put_pixel(&data->img, p1->x, p1->y, CLR_PERSIAN);
		if (p1->x == p2->x && p1->y == p2->y)
			break ;
		if (2 * data->err > -dy)
		{
			data->err -= dy;
			p1->x += get_slope(p1->x, p2->x);
		}
		if (2 * data->err < dx)
		{
			data->err += dx;
			p1->y += get_slope(p1->y, p2->y);
		}
	}
}
