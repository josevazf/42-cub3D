/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:58:59 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/21 13:56:05 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Check collisions between Player movement and closed cubes */
bool	is_valid_cube(t_data *data, double mx, double my)
{
	data->player.c_pos = point_cube_position_player(data, mx, my);
	if (data->player.c_pos.cube_type == CLOSED)
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

/* Strafe to the left `A` or to the right `D` */
void	move_strafe(t_data *data, int key)
{
	double px;
	double py;
	double angle;

	angle = data->player.rot_ang;
	if (key == XK_a)
	{
		angle -= (M_PI / 2);
		angle = wrap_angle(angle);
	}
	else
	{
		angle += (M_PI / 2);
		angle = wrap_angle(angle);
	}
	px = data->player.px + cos(angle) * MV_SPD;
	py = data->player.py + sin(angle) * MV_SPD;
	if (is_valid_cube(data, px, py))
	{
		data->player.px = px;
		data->player.py = py;
	}
}

/* Move Player FOV left or right */
void	move_rotate(t_data *data, int key)
{
	if (key == XK_Left)
	{
		data->player.rot_ang -= ROT_SPD;
		data->player.rot_ang = wrap_angle(data->player.rot_ang);
	}
	else
	{
		data->player.rot_ang += ROT_SPD;
		data->player.rot_ang = wrap_angle(data->player.rot_ang);
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
		move_strafe(data, key);
	else if (key == XK_Left || key == XK_Right)
		move_rotate(data, key);
}
