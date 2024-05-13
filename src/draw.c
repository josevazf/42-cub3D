/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:02:20 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/13 16:45:17 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Put a pixel on the screen */
void	put_pixel(t_img *img, int x, int y, int color)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bpp / 8));
	*((unsigned int *)(offset + img->mlx_pixel_addr)) = color;
}

/* Converts hex RGB representation to each value of r, g and b */
void	hex_to_rgb(int hex_color, t_point *point)
{
	point->rgb.r = (hex_color >> 16) & 0xFF;
	point->rgb.g = (hex_color >> 8) & 0xFF;
	point->rgb.b = (hex_color & 0xFF);
}

/* Get the color for the gradient point between p1 and p2*/
/* int		get_pnt_color(t_point *p1, t_point *p2, float pos, int len)
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

void	paint_square(t_cube *cube)
{
	int	x;
	int	y;
	int	size;

	x = -1;
	y = -1;
	size = ft_int_max(abs(cube->v3.x - cube->v1.x), abs(cube->v3.y - cube->v1.y));
	while (++x < size)
	{
		y = -1;
		while (++y < size)
		{
			put_pixel(&cube->data->img, cube->v1.x + x, cube->v1.y + y, cube->clr);
			if (x == 0 || x == size - 1 || y == 0 || y == size - 1)
				put_pixel(&cube->data->img, cube->v1.x + x, cube->v1.y + y, CLR_BLACK);
		}
	}
}

/* Draw map by vertical and horizontal lines */
void	draw_minimap(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < data->map_h)
	{
		j = -1;
		while (++j < (data->map_w))
			paint_square(&data->map[i][j]);
	}
/* 	vertical_lines(data);
	horizontal_lines(data);
	if (data->x1 > 0 && data->x1 < WIN_W - 5 && data->y1 > 0 && 
		data->y1 < WIN_H - 5)
		put_pixel(&data->img, data->map[data->map_h - 1][data->map_w - 1].cnt.x, 
			data->map[data->map_h - 1][data->map_w - 1].cnt.y, 
			data->map[data->map_h - 1][data->map_w - 1].clr); */
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

/* Draw lines between p1 and p2 */
void	draw_lines(t_point *p1, t_point *p2, t_data *data, int i)
{
	int	dx;
	int	dy;

	dx = abs(p2->x - p1->x);
	dy = abs(p2->y - p1->y);
	data->err = dx - dy;
	while (++i < ft_int_max(dx, dy))
	{
		if (p1->x > 0 && p1->x < WIN_W - 5 && p1->y > 0 && 
			p1->y < WIN_H - 5)
			put_pixel(&data->img, p1->x, p1->y, CLR_GREEN);
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
