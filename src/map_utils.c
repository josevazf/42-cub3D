/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:34:58 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/14 15:35:14 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Scale map with a given factor */
/* void	scale_map(t_data *data, double factor)
{
	int		i;
	int		j;

	i = -1;
	set_coordinates(data);
	while (++i < data->map_h)
	{
		j = -1;
		while (++j < data->map_w)
		{
			data->map[i][j].cnt.x = (double)data->map[i][j].cnt.x * factor;
			data->map[i][j].cnt.y = (double)data->map[i][j].cnt.y * factor;
		}
	}
	//data->scale_ratio = factor;
} */

/* Center map on the window */
/* void	translate_center(t_data *data, int i, int j)
{
	float	move_x;
	float	move_y;

	i = -1;
	if (data->trs_x != 0 || data->trs_y != 0)
	{
		move_x = data->trs_x;
		move_y = data->trs_y;
	}
	else
	{
		move_x = data->c_pos_x - get_average(data, 0);
		move_y = data->c_pos_y - get_average(data, 1);
	}
	while (++i < data->map_h)
	{
		j = -1;
		while (++j < data->map_w)
		{
			data->map[i][j].v1.x = data->map[i][j].v1.x + move_x;
			data->map[i][j].v1.y = data->map[i][j].v1.y + move_y;
		}
	}
	get_map_center(data);
} */

/* Fit map view to window */
/* void	fit_to_window(t_data *data, double angle)
{
	double	ratio;

	(void)angle;
	ratio = 1;
	while ((data->map[data->map_h - 1][data->map_w - 1].v1.y - 
		data->map[0][0].v1.y >= WIN_H - 100))
	{
		if (data->map[data->map_h - 1][data->map_w - 1].v1.y - 
		data->map[0][0].v1.y >= WIN_H - 100)
			scale_map(data, pow(0.9, ratio));
		else if (data->map[data->map_h - 1][data->map_w - 1].v1.y - 
		data->map[0][0].v1.y <= WIN_H / 2)
			scale_map(data, pow(1.1, ratio));
		translate_center(data, -1, -1);
		ratio = ratio + 1;
	}
} */