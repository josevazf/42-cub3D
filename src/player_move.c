/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:58:59 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/14 17:39:10 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Check collisions between Player movement and closed cubes */
bool	is_valid_cube(t_data *data, double mx, double my)
{
	if (player_cube_position(data, mx, my).cube_type == CLOSED)
		return (false);
	return (true);
}

/* Move forward `W` or backwards `S` */
void	move_linear(t_data *data, int key)
{
	double px;
	double py;

	if (key == XK_w)
	{
		px = data->player.px + cos(data->player.rot_ang) * MV_SPD;
		py = data->player.py + sin(data->player.rot_ang) * MV_SPD;
	}
	else
	{
		px = data->player.px - cos(data->player.rot_ang) * MV_SPD;
		py = data->player.py - sin(data->player.rot_ang) * MV_SPD;
	}
	if (is_valid_cube(data, px, py))
	{
		data->player.px = px;
		data->player.py = py;
	}
}

/* Move to the left side `A` or to the right side `D` */
void	move_sides(t_data *data, int key)
{
	double px;
	double py;
	double angle;

	angle = data->player.rot_ang;
	if (key == XK_a)
	{
		angle -= (M_PI / 2);
		if (angle < 0)
			angle += 2 * M_PI;
	}
	else
	{
		angle += (M_PI / 2);
		if (angle >= 2 * M_PI)
			angle -= 2 * M_PI;
	}
	px = data->player.px + cos(angle) * MV_SPD;
	py = data->player.py + sin(angle) * MV_SPD;
	if (is_valid_cube(data, px, py))
	{
		data->player.px = px;
		data->player.py = py;
	}
}

/* Function to trigger Player movement */
void	move_player(t_data *data, int key)
{
	clean_screen(data);
	draw_minimap(data);
	if (key == XK_w || key == XK_s)
		move_linear(data, key);
	else if (key == XK_a || key == XK_d)
		move_sides(data, key);
	else if (key == XK_Left)
	{
		data->player.rot_ang -= ROT_SPD;
		if (data->player.rot_ang < 0)
			data->player.rot_ang += 2 * M_PI;		
	}
	else if (key == XK_Right)
	{
		data->player.rot_ang += ROT_SPD;
		if (data->player.rot_ang >= 2 * M_PI)
			data->player.rot_ang -= 2 * M_PI;
	}
	draw_player(data);
}
