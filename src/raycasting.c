/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:49:33 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/21 16:51:58 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		distance_between_points(int x1, int y1, int x2, int y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
void	get_final_hit(t_data *data, t_rays *rays, int h_dist, int v_dist)
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
	if (h_dist <= v_dist)
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
	int 	next_x;
	int		next_y;
	int		dec;
	
	next_x = rays->xv_hit;
	next_y = rays->yv_hit;
	if (rays->is_right)
		dec = 5;
	else
		dec = -5;
	while (!rays->vwall_hit && next_x >= data->map[0][0].v1.x + 5 && \
			next_x <= data->map[0][data->map_w - 1].v2.x - 5 && \
			next_y >= data->map[0][0].v1.y + 5 && \
			next_y <= data->map[data->map_h - 1][0].v3.y - 5)
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
	int	x_step;
	int	y_step;
	int x_hit;
	int y_hit;

	x_step = SIZE;
	y_step = SIZE * tan(rays->angle);
	if (rays->is_right)
	{
		x_hit = floor(data->player.px / SIZE) * SIZE + SIZE;
		if (rays->is_up)
			y_hit = data->player.py - (x_hit - data->player.px) * tan((2 * M_PI) - rays->angle);
		else
			y_hit = data->player.py + (x_hit - data->player.px) * tan(rays->angle);
	}
	else
	{
		x_hit = floor(data->player.px / SIZE) * SIZE;
		if (rays->is_up)
			y_hit = data->player.py - (data->player.px - x_hit) * tan(rays->angle);
		else
			y_hit = data->player.py + (data->player.px - x_hit) * tan((2 * M_PI) - rays->angle);
		x_step *= -1;
	}
	if ((y_step > 0 && rays->is_up) || (y_step < 0 && !rays->is_up))
		y_step *= -1;
	rays->xv_hit = x_hit;
	rays->yv_hit = y_hit;
	vertical_wall_hit(data, rays, x_step, y_step);
}

void	horizontal_wall_hit(t_data *data, t_rays *rays, int x_step, int y_step)
{
	int 	next_x;
	int		next_y;
	int 	dec;
	
	next_x = rays->xh_hit;
	next_y = rays->yh_hit;
	if (rays->is_up)
		dec = -5;
	else
		dec = 5;
	while (!rays->hwall_hit && next_x >= data->map[0][0].v1.x + 5 && \
			next_x <= data->map[0][data->map_w - 1].v2.x - 5 && \
			next_y >= data->map[0][0].v1.y + 5 && \
			next_y <= data->map[data->map_h - 1][0].v3.y - 5)
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
	int	x_step;
	int	y_step;
	int x_hit;
	int y_hit;

	y_step = SIZE;
	x_step = SIZE / tan(rays->angle);
	if (rays->is_up)
	{
		y_hit = floor(data->player.py / SIZE) * SIZE;
		x_hit = data->player.px + (data->player.py - y_hit) / tan((2 * M_PI) - rays->angle);
		y_step *= -1;
	}
	else
	{
		y_hit = floor(data->player.py / SIZE) * SIZE + SIZE;
		x_hit = data->player.px + (y_hit - data->player.py) / tan(rays->angle);
	}
	if ((x_step > 0 && !rays->is_right) || (x_step < 0 && rays->is_right))
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
	ray_angle = data->player.rot_ang - (FOV_ANG / 2);
	while (++i < NUM_RAYS)
	{
		data->rays[i].angle = wrap_angle(ray_angle + ((FOV_ANG / NUM_RAYS) * i));
		data->rays[i].is_up = true;
		data->rays[i].is_right = true;	
		if (data->rays[i].angle > 0 && data->rays[i].angle < M_PI)
			data->rays[i].is_up = false;
		if (data->rays[i].angle > (M_PI / 2) && data->rays[i].angle < (1.5 * M_PI))
			data->rays[i].is_right = false;
		data->rays[i].hwall_hit = false;
		data->rays[i].vwall_hit = false;
		data->rays[i].distance = 0;
		data->rays[i].height = 0;
		data->rays[i].x_hit = 0;
		data->rays[i].y_hit = 0;
		horizontal_grid_hit(data, &data->rays[i]);
		vertical_grid_hit(data, &data->rays[i]);
		get_final_hit(data, &data->rays[i], 0, 0);
		printf("RAY[%d]", i);
		printf("\tangle_diff:: %f\n", data->rays[i + 1].angle - data->rays[i].angle);
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
	cast_rays(data);
	ray_start.x = data->player.px * MM_SCALE;
	ray_start.y = data->player.py * MM_SCALE;
	while (++i < NUM_RAYS)
	{
		ray_end.x = data->rays[i].x_hit * MM_SCALE;
		ray_end.y = data->rays[i].y_hit * MM_SCALE;
		put_pixel(&data->img, ray_end.x, ray_end.y, CLR_RED);
		//draw_lines(&ray_end, &ray_start, data, -1);
		if (i == 0 || i == NUM_RAYS - 1)
			draw_lines(&ray_end, &ray_start, data, -1);	
	}
}
