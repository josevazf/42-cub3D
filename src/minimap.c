/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:06:02 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/14 12:13:36 by jrocha-v         ###   ########.fr       */
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
	//translate_center(data, -1, -1);
	//fit_to_window(data, 30);
	set_cube_vertex(data, -1, -1);
}

void	process_minimap(t_data *data)
{
	set_map(data);
	draw_minimap(data);
	draw_player(data);
	return ;
}

/* Set coordinates for each cube V1 point */
void	set_coordinates(t_data *data)
{
/* 	int	spc_h;
	int	spc_w; */
	int	i;
	int	j;

	i = -1;
	j = -1;
/* 	spc_w = (WIN_W - 50) / (data->map_w - 1);
	spc_h = (WIN_H - 50) / (data->map_h - 1);
	if ((spc_h * (data->map_h - 1) >= WIN_H) || 
		(spc_h * (data->map_w - 1) >= WIN_W))
		data->mm_spc = spc_w;
	else */
	data->mm_spc = 64;
	while (++i < data->map_h)
	{
		j = -1;
		while (++j < data->map_w)
		{
			data->map[i][j].v1.x = 50 + j * data->mm_spc;
			data->map[i][j].v1.y = 50 + i * data->mm_spc;
		}
	}
}

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

/* Set coordinates for each cube vertex point */
void	set_cube_vertex(t_data *data, int i, int j)
{
	t_cube	**cube;

	cube = data->map;
	while (++i < data->map_h)
	{
		j = -1;
		while (++j < data->map_w)
		{
			cube[i][j].x = i;
			cube[i][j].y = j;
			cube[i][j].v2.x = cube[i][j].v1.x + data->mm_spc;
			cube[i][j].v2.y = cube[i][j].v1.y;
			cube[i][j].v3.x = cube[i][j].v2.x;
			cube[i][j].v3.y = cube[i][j].v1.y + data->mm_spc;
			cube[i][j].v4.x = cube[i][j].v1.x;
			cube[i][j].v4.y = cube[i][j].v1.y + data->mm_spc;
		}
	}
}
