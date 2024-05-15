/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:49:33 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/15 09:44:19 by jrocha-v         ###   ########.fr       */
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
		data->rays[i].direction = ray_angle + ((FOV_ANG / NUM_RAYS) * i);
}

void	draw_rays(t_data *data)
{
	int i;
	t_point ray_start;
	t_point	ray_end;
	
	i = -1;
	cast_rays(data);
	ray_start.x = data->player.px;
	ray_start.y = data->player.py;
	while (++i < NUM_RAYS)
	{
		ray_end.x = data->player.px + cos(data->rays[i].direction) * 100;
		ray_end.y = data->player.py + sin(data->rays[i].direction) * 100;
		draw_lines(&ray_end, &ray_start, data, -1);
	}
}
