/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:02:20 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/06/05 10:23:18 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Put a pixel on the screen */
void	put_pixel(t_img *img, int x, int y, int color)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bpp / 8));
	*((unsigned int *)(offset + img->pixel_addr)) = color;
}

/* Converts hex RGB representation to each value of r, g and b */
void	hex_to_rgb(int hex_color, t_point *point)
{
	point->rgb.r = (hex_color >> 16) & 0xFF;
	point->rgb.g = (hex_color >> 8) & 0xFF;
	point->rgb.b = (hex_color & 0xFF);
}

/* Get the position of the point relative to total h */
/* float	get_pnt_position(float z, t_data *data)
{
	float	norm;

	norm = (z - data->z_min) / (data->z_max - data->z_min);
	return (norm * data->z_range);
} */

/* Get the color for the gradient point between p1 and p2*/
/* int	get_pnt_color(t_point *p1, t_point *p2, float pos, int len)
{
	int		r;
	int		g;
	int		b;
	float	ratio;

	ratio = pos / (float)len;
	hex_to_rgb(p1->clr, p1);
	hex_to_rgb(p2->clr, p2);
	if ((p1->clr == p2->clr) || len == 0)
		return (p1->clr);
	else
	{
		r = p1->rgb.r + ((p2->rgb.r - p1->rgb.r) * ratio);
		g = p1->rgb.g + ((p2->rgb.g - p1->rgb.g) * ratio);
		b = p1->rgb.b + ((p2->rgb.b - p1->rgb.b) * ratio);
		return (r << 16 | g << 8 | b);
	}
} */

/* Get the color for all the map points given the gradient */
/* void	make_gradient(t_data *data, int clr1, int clr2)
{
	int		i;
	int		j;
	float	pnt_pos;
	t_point	*p1;
	t_point	*p2;

	i = -1;
	j = -1;
	p1 = malloc(sizeof(t_point));
	p2 = malloc(sizeof(t_point));
	p1->clr = clr1;
	p2->clr = clr2;
	pnt_pos = get_pnt_position(data->map[i][j].z, data);
	data->map[i][j].clr = get_pnt_color(p1, p2, pnt_pos, data->z_range);
	draw_map(data);
	free(p1);
	free(p2);
} */

void	paint_square(t_cube *cube, int  start_x, int start_y)
{
	int	x;
	int	y;
	int	size;

	x = -1;
	y = -1;
	size = SIZE * MM_SCALE;
	while (++x <= size)
	{
		y = -1;
		while (++y <= size)
		{
			put_pixel(&cube->data->img, (start_x * MM_SCALE) + x, (start_y * MM_SCALE) + y, cube->clr);
			/* if (x == 0 || x == (size - 1) * MM_SCALE || y == 0 || y == (size - 1) * MM_SCALE)
				put_pixel(&cube->data->img, (cube->v1.x * MM_SCALE) + x, (cube->v1.y * MM_SCALE) + y, CLR_BLACK); */
		}
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
		if (p1->x > 0 && p1->x < WIN_W - 5 && p1->y > 0 && 
			p1->y < WIN_H - 5)
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

/* Define and draw vertical lines */
/* void	vertical_lines(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < data->map_h - 1)
	{
		j = -1;
		while (++j < (data->map_w))
		{
			data->x1 = data->map[i][j].cnt.x;
			data->y1 = data->map[i][j].cnt.y;
			draw_lines(&data->map[i][j], &data->map[i + 1][j], data, -1);
		}
	}
} */

/* Define and draw horizontal lines */
/* void	horizontal_lines(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++j < data->map_w - 1)
	{
		i = -1;
		while (++i < data->map_h)
		{
			data->x1 = data->map[i][j].cnt.x;
			data->y1 = data->map[i][j].cnt.y;
			draw_lines(&data->map[i][j], &data->map[i][j + 1], data, -1);
		}
	}
} */
