/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:49:33 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/16 12:46:48 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		distance_between_points(int x1, int y1, int x2, int y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
void	get_final_hit(t_data *data, t_rays *rays)
{
	int	horizontal_dist;
	int	vertical_dist;

	(void)data;
	if (rays->hwall_hit)
		horizontal_dist = distance_between_points(data->player.px, data->player.py, rays->xh_hit, rays->yh_hit);
	else
		horizontal_dist = INT_MAX;
	if (rays->vwall_hit)
		vertical_dist = distance_between_points(data->player.px, data->player.py, rays->xv_hit, rays->yv_hit);
	else
		vertical_dist = INT_MAX;
	if (horizontal_dist < vertical_dist)
	{
		rays->x_hit = rays->xh_hit;
		rays->y_hit = rays->yh_hit;
	}
	else
	{
		rays->x_hit = rays->xv_hit;
		rays->y_hit = rays->yv_hit;
	}
}

void	vertical_wall_hit(t_data *data, t_rays *rays, int x_step, int y_step)
{
	int 	next_x;
	int		next_y;

	rays->vwall_hit = false;
	next_x = rays->xv_hit;
	next_y = rays->yv_hit;
	if (rays->is_right)
		next_x++;
	else
		next_x--;
	while (!rays->vwall_hit && next_x >= data->map[0][0].v1.x + 5 && \
			next_x <= data->map[0][data->map_w - 1].v2.x - 5 && \
			next_y >= data->map[0][0].v1.y + 5 && \
			next_y <= data->map[data->map_h - 1][0].v3.y - 5)
	{
		if (point_cube_position(data, next_x, next_y).cube_type == 1)
		{
			rays->vwall_hit = true;
			rays->xv_hit = next_x;
			rays->yv_hit = next_y;
			break ;
		}
		next_x += x_step;
		next_y += y_step;
	}
}

void	vertical_grid_hit(t_data *data, t_rays *rays)
{
	int	x_step;
	int	y_step;
	int x_hit;
	int y_hit;

	x_step = SIZE;
	y_step = SIZE * tan(rays->angle);
	if (rays->is_right)
	{
		x_hit = data->player.c_pos.v2.x;
		if (rays->is_up)
			y_hit = data->player.py - (x_hit - data->player.px) * tan(rays->angle);
		else
			y_hit = data->player.py + (x_hit - data->player.px) * tan(rays->angle);
	}
	else
	{
		x_hit = data->player.c_pos.v1.x;
		if (rays->is_up)
			y_hit = data->player.py - (data->player.px - x_hit) * tan(rays->angle);
		else
			y_hit = data->player.py + (data->player.px - x_hit) * tan(rays->angle);
		x_step *= -1;
	}
	if (y_step > 0 && rays->is_up)
		y_step *= -1;
	if (y_step < 0 && !rays->is_up)
		y_step *= -1;
	rays->xv_hit = x_hit;
	rays->yv_hit = y_hit;
	vertical_wall_hit(data, rays, x_step, y_step);
}

void	horizontal_wall_hit(t_data *data, t_rays *rays, int x_step, int y_step)
{
	int 	next_x;
	int		next_y;

	rays->hwall_hit = false;
	next_x = rays->xh_hit;
	next_y = rays->yh_hit;
	if (rays->is_up)
		next_y--;
	else
		next_y++;
	while (!rays->hwall_hit && next_x >= data->map[0][0].v1.x + 5 && \
			next_x <= data->map[0][data->map_w - 1].v2.x - 5 && \
			next_y >= data->map[0][0].v1.y + 5 && \
			next_y <= data->map[data->map_h - 1][0].v3.y - 5)
	{
		if (point_cube_position(data, next_x, next_y).cube_type == 1)
		{
			rays->hwall_hit = true;
			rays->xh_hit = next_x;
			rays->yh_hit = next_y;
			break ;
		}
		next_x += x_step;
		next_y += y_step;
	}
}

void	horizontal_grid_hit(t_data *data, t_rays *rays)
{
	int	x_step;
	int	y_step;
	int x_hit;
	int y_hit;

	y_step = SIZE;
	x_step = SIZE / tan(rays->angle);
	if (rays->is_up)
	{
		y_hit = data->player.c_pos.v1.y;
		x_hit = data->player.px + (data->player.py - y_hit) / tan((2 * M_PI) - rays->angle);
		y_step *= -1;
	}
	else
	{
		y_hit = data->player.c_pos.v3.y;
		x_hit = data->player.px + (y_hit - data->player.py) / tan(rays->angle);
	}
	if (x_step > 0 && !rays->is_right)
		x_step *= -1;
	if (x_step < 0 && rays->is_right)
		x_step *= -1;
	rays->xh_hit = x_hit;
	rays->yh_hit = y_hit;
	horizontal_wall_hit(data, rays, x_step, y_step);
}

void	cast_rays(t_data *data)
{
	int		i;
	double	ray_angle;
	
	i = -1;
	ray_angle = wrap_angle(data->player.rot_ang - (FOV_ANG / 2));
	while (++i < NUM_RAYS)
	{
		data->rays[i].angle = wrap_angle(ray_angle + ((FOV_ANG / NUM_RAYS) * i));
		data->rays[i].is_up = true;
		data->rays[i].is_right = true;	
		if (data->rays[i].angle > 0 && data->rays[i].angle < M_PI)
			data->rays[i].is_up = false;
		if (data->rays[i].angle > (M_PI / 2) && data->rays[i].angle < (1.5 * M_PI))
			data->rays[i].is_right = false;
		data->rays[i].distance = 0;
		data->rays[i].height = 0;
		data->rays[i].x_hit = 0;
		data->rays[i].y_hit = 0;
		horizontal_grid_hit(data, &data->rays[i]);
		vertical_grid_hit(data, &data->rays[i]);
		get_final_hit(data, &data->rays[i]);
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
	while (++i < NUM_RAYS)
	{
		ray_end.x = data->rays[i].x_hit;
		ray_end.y = data->rays[i].y_hit;
		draw_lines(&ray_end, &ray_start, data, -1);
	}
}
