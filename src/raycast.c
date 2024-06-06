/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:49:33 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/06/06 19:06:07 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	distance_between_points(double x1, double y1, double x2,
	double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

static void	get_final_hit(t_data *data, t_rays *rays, double h_dist,
	double v_dist)
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
		if (data->rays[i].angle > (0.5 * M_PI)
			&& data->rays[i].angle < (1.5 * M_PI))
			data->rays[i].is_right = false;
		data->rays[i].hit_vert = false;
		data->rays[i].hwall_hit = false;
		data->rays[i].vwall_hit = false;
		data->rays[i].distance = 0;
		data->rays[i].height = 0;
		horizontal_grid_hit(data, &data->rays[i]);
		vertical_grid_hit(data, &data->rays[i]);
		get_final_hit(data, &data->rays[i], 0, 0);
	}
}

void	draw_rays(t_data *data)
{
	int		i;
	t_point	ray_start;
	t_point	ray_end;

	i = -1;
	ray_start.x = data->player.px * data->mm_scale;
	ray_start.y = data->player.py * data->mm_scale;
	while (++i < NUM_RAYS)
	{
		ray_end.x = data->rays[i].x_hit * data->mm_scale;
		ray_end.y = data->rays[i].y_hit * data->mm_scale;
		draw_lines(&ray_end, &ray_start, data, -1);
	}
}
