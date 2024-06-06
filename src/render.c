/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:23:26 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/06/06 14:48:50 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_txt_pxl(t_img *img, int x, int y)
{
	return (*(unsigned int *)(img->pixel_addr + \
		(y * img->line_len) + (x * (img->bpp / 8))));
}

static int	fade_color(int color, double factor)
{
	int	r;
	int	g;
	int	b;

	factor /= 5;
	if (factor < 1)
		return (color);
	r = (color >> 16) / factor;
	g = (color >> 8 & 0xFF) / factor;
	b = (color & 0xFF) / factor;
	return (r << 16 | g << 8 | b);
}

static void	draw_textured_wall(t_data *data, int i, int j)
{
	double	rel_pos;

	rel_pos = ((j - data->rays[i].wall_start)
			/ (data->rays[i].wall_end - data->rays[i].wall_start)) * 64.0;
	if (!data->rays[i].hit_vert && data->rays[i].is_up)
		put_pixel(&data->img, i, j, fade_color(get_txt_pxl(&data->txts_img[NO],
					(int)data->rays[i].x_hit % 64, rel_pos),
				data->rays[i].distance / 50));
	else if (!data->rays[i].hit_vert && !data->rays[i].is_up)
		put_pixel(&data->img, i, j, fade_color(get_txt_pxl(&data->txts_img[SO],
					(int)data->rays[i].x_hit % 64, rel_pos),
				data->rays[i].distance / 50));
	else if (data->rays[i].hit_vert && data->rays[i].is_right)
		put_pixel(&data->img, i, j, fade_color(get_txt_pxl(&data->txts_img[EA],
					(int)data->rays[i].y_hit % 64, rel_pos),
				data->rays[i].distance / 50));
	else
		put_pixel(&data->img, i, j, fade_color(get_txt_pxl(&data->txts_img[WE],
					(int)data->rays[i].y_hit % 64, rel_pos),
				data->rays[i].distance / 50));
}

void	render_walls(t_data *data, int i, int j)
{
	double	dist_pp;

	dist_pp = (WIN_W / 2.0) / tan(FOV_ANG / 2.0);
	while (++i < NUM_RAYS)
	{
		data->rays[i].distance = data->rays[i].distance
			* cos(data->rays[i].angle - data->player.rot_ang);
		data->rays[i].height = (SIZE * dist_pp) / data->rays[i].distance;
		data->rays[i].wall_start = (WIN_H / 2) - (data->rays[i].height / 2);
		data->rays[i].wall_end = (WIN_H / 2) + (data->rays[i].height / 2);
		j = -1;
		while (++j < WIN_H)
		{
			if (j < data->rays[i].wall_start)
				put_pixel(&data->img, i, j, rgb_to_int(data->og_map->ceiling));
			else if (j > data->rays[i].wall_end)
				put_pixel(&data->img, i, j, rgb_to_int(data->og_map->floor));
			else
				draw_textured_wall(data, i, j);
		}
	}
}
