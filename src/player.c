/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 20:31:05 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/14 15:19:16 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cube	player_cube_position(t_data *data, double px, double py)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < data->map_h)
	{
		j = -1;
		while (++j < data->map_w)
		{
			if (px >= data->map[i][j].v1.x && \
				py >= data->map[i][j].v1.y && \
				px <= data->map[i][j].v3.x && \
				py <= data->map[i][j].v3.y)
			return (data->map[i][j]);
		}
	}
	return (data->map[i][j]);
}

bool	is_valid_cube(t_data *data, double mx, double my)
{
	if (player_cube_position(data, mx, my).cube_type == CLOSED)
		return (false);
	return (true);
}

void	move_player(t_data *data, int key)
{
	clean_screen(data);
	draw_minimap(data);
	if (key == XK_w && is_valid_cube(data, \
		data->player.px + cos(data->player.rot_ang) * MV_SPD, \
		data->player.py + sin(data->player.rot_ang) * MV_SPD))
	{
		data->player.px += cos(data->player.rot_ang) * MV_SPD;
		data->player.py += sin(data->player.rot_ang) * MV_SPD;
	}
	else if (key == XK_s)
	{
		data->player.px -= cos(data->player.rot_ang) * MV_SPD;
		data->player.py -= sin(data->player.rot_ang) * MV_SPD;
	}
	else if (key == XK_a)
	{
		data->player.px += cos(data->player.rot_ang) * MV_SPD;
		data->player.py -= sin(data->player.rot_ang) * MV_SPD;
	}
	else if (key == XK_d)
	{
		data->player.px += cos((2 * M_PI) - data->player.rot_ang) * MV_SPD;
		data->player.py += sin((2 * M_PI) - data->player.rot_ang) * MV_SPD;
	}
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

void	draw_direction(t_data *data)
{
	t_point		dir;
	t_point		pos;

	//printf("Player (x: %f, y: %f)\n", data->player.px, data->player.py);
	pos.x = data->player.px;
	pos.y = data->player.py;
	dir.x = pos.x + cos(data->player.rot_ang) * 20;
	dir.y = pos.y + sin(data->player.rot_ang) * 20;
	draw_lines(&pos, &dir, data, -1);
}

/* Set initial Player position in the map */
void	set_player_pos(t_data *data)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < data->map_h)
	{
		j = -1;
		while (++j < data->map_w)
		{
			if (data->map[i][j].cube_start != FALSE)
			{
				//printf("player.cube[%d][%d]\n", i, j);
				data->player.c_pos = data->map[i][j];
				data->player.px = get_cube_center(&data->player.c_pos, 0);
				//printf("cube.cx: %f\n", data->player.px);
				data->player.py = get_cube_center(&data->player.c_pos, 1);
				//printf("cube.cy: %f\n", data->player.py);
				return ;
			}
		}
	}
}

void	draw_player(t_data *data)
{
	int	i;
	int	j;
	
	i = 10;
	j = 10;
	draw_direction(data);
	if (data->init == true)
	{
		set_player_pos(data);
		data->init = false;
	}
	//data->player.c_pos = player_cube_position(data, data->player.px, data->player.py);
	while (--i > 0)
	{
		j = 10;
		while (--j > 0)
		{
			put_pixel(&data->img, (data->player.px + 5) - i, (data->player.py + 5) - j, CLR_PERSIAN);
		}
	}
}
