/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:49:33 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/15 18:07:14 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	horizontal_hit(t_data *data, t_rays *rays)
{
	t_cube	cube;
	//int	x_step;
	//int	y_step;
	int x_hit;
	int y_hit;

	if (rays->is_up)
	{
		y_hit = data->player.c_pos.v1.y;
		x_hit = fmod(data->player.px + (data->player.py - y_hit) / tan((2 * M_PI) - rays->angle), (double)WIN_W);
	}
	else
	{
		y_hit = data->player.c_pos.v3.y;
		x_hit = data->player.px + (y_hit - data->player.py) / tan(rays->angle);
	}
/* 	printf("Player(%f, %f)\n", data->player.px, data->player.py);
	printf("x_hit: %d || ", x_hit);
	printf("y_hit: %d\n", y_hit); */
	cube = point_cube_position(data, x_hit, y_hit);
	rays->x_hit = x_hit;
	rays->y_hit = y_hit;
/* 	if (point_cube_position(data, x_hit, y_hit).cube_type == 1)
	{
		rays->x_hit = x_hit;
		rays->y_hit = y_hit;			
	} */
	printf("cube(%d, %d)\n", cube.row, cube.col);
}

void	cast_rays(t_data *data)
{
	int		i;
	double	ray_angle;
	
	i = -1;
	ray_angle = wrap_angle(data->player.rot_ang - (FOV_ANG / 2));
	while (++i < 1)
	{
		data->rays[i].angle = wrap_angle(ray_angle + ((FOV_ANG / NUM_RAYS) * i));
		data->rays[i].is_up = true;
		data->rays[i].is_right = true;	
		if (data->rays[i].angle > 0 && data->rays[i].angle < M_PI)
			data->rays[i].is_up = false;
		if (data->rays[i].angle > (M_PI / 2) && data->rays[i].angle < (1.5 * M_PI))
			data->rays[i].is_right = false;
		printf("RAY[%d]: %f || ", i, data->rays[i].angle);
		//printf("RAY[%d]: %d\n", i, data->rays[i].is_up);
		data->rays[i].distance = 0;
		data->rays[i].height = 0;
		data->rays[i].x_hit = 0;
		data->rays[i].y_hit = 0;
		horizontal_hit(data, &data->rays[i]);
	}
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
	while (++i < 1)
	{
/* 		ray_end.x = data->player.px + cos(data->rays[i].angle) * 100;
		ray_end.y = data->player.py + sin(data->rays[i].angle) * 100; */
		ray_end.x = data->rays[i].x_hit;
		ray_end.y = data->rays[i].y_hit;
		draw_lines(&ray_end, &ray_start, data, -1);
	}
}
