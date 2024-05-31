/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:49:33 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/31 14:08:54 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	distance_between_points(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	get_final_hit(t_data *data, t_rays *rays, double h_dist, double v_dist)
{
	if (rays->hwall_hit)
		h_dist = distance_between_points(data->player.px, \
			data->player.py, rays->xh_hit, rays->yh_hit);
	else
		h_dist = INT_MAX;
	if (rays->vwall_hit)
		v_dist = distance_between_points(data->player.px, \
			data->player.py, rays->xv_hit, rays->yv_hit);
	else
		v_dist = INT_MAX;
	if (h_dist < v_dist)
	{
		rays->x_hit = rays->xh_hit;
		rays->y_hit = rays->yh_hit;
		rays->distance = h_dist;
		rays->hit_vert = false;
	}
	else
	{
		rays->x_hit = rays->xv_hit;
		rays->y_hit = rays->yv_hit;
		rays->distance = v_dist;
		rays->hit_vert = true;
	}
}

void	vertical_wall_hit(t_data *data, t_rays *rays, int x_step, int y_step)
{
	double 	next_x;
	double	next_y;
	int		dec;
	
	dec = -1;
	next_x = rays->xv_hit;
	next_y = rays->yv_hit;
	if (rays->is_right)
		dec = 1;
	while (next_x >= 5 && \
			next_x <= data->map_w * SIZE - 5 && \
			next_y >= 5 && \
			next_y <= data->map_h * SIZE - 5)
	{
		if (point_cube_position(data, next_x + dec, next_y).cube_type == CLOSED)
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
	double	x_step;
	double	y_step;

	x_step = SIZE;
	y_step = SIZE * tan(rays->angle);
	rays->xv_hit = floor(data->player.px / SIZE) * SIZE;
	if (rays->is_right)
		rays->xv_hit = floor(data->player.px / SIZE) * SIZE + SIZE;
	else
		x_step *= -1;
	rays->yv_hit = data->player.py + (rays->xv_hit - data->player.px) * tan(rays->angle);
	if ((y_step > 0 && rays->is_up) || (y_step < 0 && !rays->is_up))
		y_step *= -1;
	vertical_wall_hit(data, rays, x_step, y_step);
}

void	horizontal_wall_hit(t_data *data, t_rays *rays, double x_step, double y_step)
{
	double 	next_x;
	double	next_y;
	int		dec;
	
	dec = 1;
	next_x = rays->xh_hit;
	next_y = rays->yh_hit;
	if (rays->is_up)
		dec = -1;
	while (next_x >= 5 && \
			next_x <= data->map_w * SIZE - 5 && \
			next_y >= 5 && \
			next_y <= data->map_h * SIZE - 5)
	{
		if (point_cube_position(data, next_x, next_y + dec).cube_type == 1)
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
	double	x_step;
	double	y_step;

	y_step = SIZE;
	x_step = SIZE / tan(rays->angle);
	if (rays->is_up)
	{
		rays->yh_hit = floor(data->player.py / SIZE) * SIZE;
		y_step *= -1;
	}
	else
		rays->yh_hit = floor(data->player.py / SIZE) * SIZE + SIZE;
	rays->xh_hit = data->player.px + (rays->yh_hit - data->player.py) / tan(rays->angle);
	if ((x_step > 0 && !rays->is_right) || (x_step < 0 && rays->is_right))
		x_step *= -1;
	horizontal_wall_hit(data, rays, x_step, y_step);
}

void	cast_rays(t_data *data)
{
	int		i;
	double	ray_angle;
	
	i = -1;
	ray_angle = data->player.rot_ang - (FOV_ANG / 2.0);
	while (++i < NUM_RAYS)
	{
		ray_angle += FOV_ANG / NUM_RAYS;
		data->rays[i].angle = wrap_angle(ray_angle);		
		data->rays[i].is_up = true;
		data->rays[i].is_right = true;
		if (data->rays[i].angle > 0 && data->rays[i].angle < M_PI)
			data->rays[i].is_up = false;
		if (data->rays[i].angle > (0.5 * M_PI) && data->rays[i].angle < (1.5 * M_PI))
			data->rays[i].is_right = false;
		data->rays[i].hit_vert = false;
		data->rays[i].hwall_hit = false;
		data->rays[i].vwall_hit = false;
		data->rays[i].distance = 0;
		data->rays[i].height = 0;
		data->rays[i].xh_hit = 0;
		data->rays[i].yh_hit = 0;
		data->rays[i].xv_hit = 0;
		data->rays[i].yv_hit = 0;
		data->rays[i].x_hit = 0;
		data->rays[i].y_hit = 0;
		horizontal_grid_hit(data, &data->rays[i]);
		vertical_grid_hit(data, &data->rays[i]);
		get_final_hit(data, &data->rays[i], 0, 0);
		//printf("RAY[%d]", i);
		//printf("\thit_vertical? %d\n", data->rays[i].hit_vert);
		//printf("\tangle_diff: %f\n", data->rays[i + 1].angle - data->rays[i].angle);
		//printf("\thit_x: %d\thit_y: %d\n", data->rays[i].x_hit, data->rays[i].y_hit);
		//printf("\tangle: %f\tdistance: %d\n", data->rays[i].angle, data->rays[i].distance);
	}
}

void	draw_rays(t_data *data)
{
	int i;
	t_point ray_start;
	t_point	ray_end;
	
	i = -1;
	ray_start.x = data->player.px * MM_SCALE;
	ray_start.y = data->player.py * MM_SCALE;
	while (++i < NUM_RAYS)
	{
		ray_end.x = data->rays[i].x_hit * MM_SCALE;
		ray_end.y = data->rays[i].y_hit * MM_SCALE;
		draw_lines(&ray_end, &ray_start, data, -1);
	}
}
