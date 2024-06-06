/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 08:37:21 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/06/06 14:36:16 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	vertical_wall_hit(t_data *data, t_rays *rays, double x_step,
			double y_step)
{
	double	next_x;
	double	next_y;
	int		dec;

	dec = -1;
	next_x = rays->xv_hit;
	next_y = rays->yv_hit;
	if (rays->is_right)
		dec = 1;
	while (next_x >= 0 && next_x <= data->map_w * SIZE && \
			next_y >= 0 && next_y <= data->map_h * SIZE)
	{
		if (point_cube_position(data, next_x + dec, next_y).cube_type == 1
			|| point_cube_position(data, next_x + dec, next_y).cube_type == 2)
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
		rays->xv_hit += SIZE;
	else
		x_step *= -1;
	rays->yv_hit = data->player.py + (rays->xv_hit - data->player.px)
		* tan(rays->angle);
	if ((y_step > 0 && rays->is_up) || (y_step < 0 && !rays->is_up))
		y_step *= -1;
	vertical_wall_hit(data, rays, x_step, y_step);
}

static void	horizontal_wall_hit(t_data *data, t_rays *rays, double x_step,
			double y_step)
{
	double	next_x;
	double	next_y;
	int		dec;

	dec = 1;
	next_x = rays->xh_hit;
	next_y = rays->yh_hit;
	if (rays->is_up)
		dec = -1;
	while (next_x >= 0 && next_x <= data->map_w * SIZE
		&& next_y >= 0 && next_y <= data->map_h * SIZE)
	{
		if (point_cube_position(data, next_x, next_y + dec).cube_type == 1
			|| point_cube_position(data, next_x, next_y + dec).cube_type == 2)
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
	rays->xh_hit = data->player.px + (rays->yh_hit - data->player.py)
		/ tan(rays->angle);
	if ((x_step > 0 && !rays->is_right) || (x_step < 0 && rays->is_right))
		x_step *= -1;
	horizontal_wall_hit(data, rays, x_step, y_step);
}
