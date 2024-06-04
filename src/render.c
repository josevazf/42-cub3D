/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:23:26 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/06/04 17:00:17 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_walls(t_data *data)
{
	int i;
	int j;
	double	dist_pp;
	double	wall_start;
	double	wall_end;
	
	i = -1;
	j = -1;
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
				if (!data->rays[i].hit_vert && data->rays[i].is_up)
					put_pixel(&data->img, i, j, CLR_BLUE);
				else if (!data->rays[i].hit_vert && !data->rays[i].is_up)
					put_pixel(&data->img, i, j, CLR_ROSYBROWN);
				else if (data->rays[i].hit_vert && data->rays[i].is_right)
					put_pixel(&data->img, i, j, CLR_OLIVE);
				else if (!data->rays[i].hit_vert && !data->rays[i].is_right)
					put_pixel(&data->img, i, j, CLR_TEAL);
			}
			//put_pixel(&data->img, i, j, CLR_GREY);
		}		
		//draw_lines(&line_start, &line_end, data, -1);
	}
}
