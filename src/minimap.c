/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:06:02 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/02 22:25:35 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Create the first output image in isometric perspective */
void	set_map(t_data *data)
{
	clean_screen(data);
	data->c_pos_x = WIN_W / 2;
	data->c_pos_y = WIN_H / 2;
	set_coordinates(data);
	translate_center(data, -1, -1);
	fit_to_window(data, 30);
}

void	process_minimap(t_data *data)
{
	set_map(data);
	draw_map(data);
	draw_player(data);
	return ;
}

/* Set coordinates for standard map values */
void	set_coordinates(t_data *data)
{
	int	spc_h;
	int	spc_w;
	int	spacing;
	int	i;
	int	j;

	i = -1;
	j = -1;
	spc_w = (WIN_W - 10) / (data->map_w - 1);
	spc_h = (WIN_H - 10) / (data->map_h - 1);
	if ((spc_h * (data->map_h - 1) >= WIN_H) || 
		(spc_h * (data->map_w - 1) >= WIN_W))
		spacing = spc_w;
	else
		spacing = spc_h;
	while (++i < data->map_h)
	{
		j = -1;
		while (++j < data->map_w)
		{
			data->map[i][j].x = 10 + (j * spacing);
			data->map[i][j].y = 10 + (i * spacing);
		}
	}
}

/* Scale map with a given factor */
void	scale_map(t_data *data, double factor)
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
			data->map[i][j].x = (double)data->map[i][j].x * factor;
			data->map[i][j].y = (double)data->map[i][j].y * factor;
		}
	}
	//data->scale_ratio = factor;
}

/* Center map on the window */
void	translate_center(t_data *data, int i, int j)
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
			data->map[i][j].x = data->map[i][j].x + move_x;
			data->map[i][j].y = data->map[i][j].y + move_y;
		}
	}
	get_map_center(data);
}

/* Fit isometric view to window */
void	fit_to_window(t_data *data, double angle)
{
	double	ratio;

	(void)angle;
	ratio = 1;
	while ((data->map[data->map_h - 1][data->map_w - 1].y - 
		data->map[0][0].y >= WIN_H - 300))
	{
		if (data->map[data->map_h - 1][data->map_w - 1].y - 
		data->map[0][0].y >= WIN_H - 300)
			scale_map(data, pow(0.9, ratio));
		else if (data->map[data->map_h - 1][data->map_w - 1].y - 
		data->map[0][0].y <= WIN_H / 2)
			scale_map(data, pow(1.1, ratio));
		translate_center(data, -1, -1);
		ratio = ratio + 1;
	}
}
