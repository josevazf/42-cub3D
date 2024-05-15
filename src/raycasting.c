/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:49:33 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/15 13:25:30 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_rays(t_data *data)
{
	int		i;
	double	ray_angle;
	
	i = -1;
	ray_angle = data->player.rot_ang - (FOV_ANG / 2);
	while (++i < NUM_RAYS)
	{
		data->rays[i].angle = ray_angle + ((FOV_ANG / NUM_RAYS) * i);
		if (data->rays[i].angle > 0 && data->rays[i].angle < M_PI)
			data->rays[i].is_up = false;
		if (data->rays[i].angle > (M_PI / 2) && data->rays[i].angle < (1.5 * M_PI))
			data->rays[i].is_right = false;
		data->rays[i].distance = 0;
		data->rays[i].height = 0;
		data->rays[i].x_hit = 0;
		data->rays[i].y_hit = 0;
	}
}

/* void	horizontal_collisions(t_data *data)
{
	int	x_step;
	int	y_step;
	int x_clsn;
	int y_clsn;

	if ()
	
	
} */

void	draw_rays(t_data *data)
{
	int i;
	t_point ray_start;
	t_point	ray_end;
	
	i = -1;
	cast_rays(data);
	//horizontal_collisions(data);
	ray_start.x = data->player.px;
	ray_start.y = data->player.py;
	while (++i < NUM_RAYS)
	{
		ray_end.x = data->player.px + cos(data->rays[i].angle) * 100;
		ray_end.y = data->player.py + sin(data->rays[i].angle) * 100;
		draw_lines(&ray_end, &ray_start, data, -1);
	}
}
