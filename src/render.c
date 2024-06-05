/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:23:26 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/06/05 10:30:39 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_texture_pixel(t_img *img, int x, int y)
{
	return (*(unsigned int *)(img->pixel_addr + \
		(y * img->line_len) + (x * (img->bpp / 8))));
}

/* Get the position of the point relative to total h */
/* double	get_relative_position(double pos, double height, t_data *data)
{
	double	norm;

	norm = (z - data->z_min) / (data->z_max - data->z_min);
	return (norm * data->z_range);
} */

void	render_walls(t_data *data, int i, int j)
{
	double	dist_pp;
	double	wall_start;
	double	wall_end;
	double	rel_pos;
	
	dist_pp = (WIN_W / 2.0) / tan(FOV_ANG / 2.0);
	while (++i < NUM_RAYS)
	{
		data->rays[i].distance = data->rays[i].distance * cos(data->rays[i].angle - data->player.rot_ang);
		data->rays[i].height = (SIZE * dist_pp) / data->rays[i].distance;
		wall_start = (WIN_H / 2) - (data->rays[i].height / 2);
		wall_end = (WIN_H / 2) + (data->rays[i].height / 2);
		j = -1;
		while (++j < WIN_H)
		{
			if (j < wall_start)
				put_pixel(&data->img, i, j, data->clr_ceiling);				
			else if (j > wall_end)
				put_pixel(&data->img, i, j, data->clr_floor);
			else
			{
				rel_pos = floor(((j - wall_start) / (wall_end - wall_start))) * 64.0;
				if (!data->rays[i].hit_vert && data->rays[i].is_up) 			// NO
					//put_pixel(&data->img, i, j, CLR_PERSIAN);
					put_pixel(&data->img, i, j, get_texture_pixel(&data->txts_img[NO], rel_pos, (int)data->rays[i].x_hit % 64));
				else if (!data->rays[i].hit_vert && !data->rays[i].is_up) 		// SO
					//put_pixel(&data->img, i, j, CLR_BLUE);
					put_pixel(&data->img, i, j, get_texture_pixel(&data->txts_img[SO], rel_pos, (int)data->rays[i].x_hit % 64));
				else if (data->rays[i].hit_vert && data->rays[i].is_right) 		// EA
					//put_pixel(&data->img, i, j, CLR_OLIVE);
					put_pixel(&data->img, i, j, get_texture_pixel(&data->txts_img[EA], rel_pos, (int)data->rays[i].y_hit % 64));
				else															// WE
					//put_pixel(&data->img, i, j, CLR_GREY);
					put_pixel(&data->img, i, j, get_texture_pixel(&data->txts_img[WE], rel_pos, (int)data->rays[i].y_hit % 64));
			}
		}
		//draw_lines(&line_start, &line_end, data, -1);
	}
}
