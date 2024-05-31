/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:43:02 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/31 14:04:09 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Draw minimap with squares and gridlines */
void	draw_minimap(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < data->map_h)
	{
		j = -1;
		while (++j < (data->map_w))
			paint_square(&data->map[i][j], j * (int)SIZE, i * (int)SIZE);
	}
}

/* Draw Player direction vector (just to debug) */
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

/* Draw Player representation as a filled square */
void	draw_player(t_data *data)
{
	int	i;
	int	j;
	
	i = 3;
	j = 3;
	//draw_direction(data);
	if (data->init == true)
	{
		set_player_pos(data);
		data->init = false;
	}
	//data->player.c_pos = player_cube_position(data, data->player.px, data->player.py);
	while (--i > -3)
	{
		j = 3;
		while (--j > -3)
			put_pixel(&data->img, data->player.px * MM_SCALE - i, data->player.py * MM_SCALE - j, CLR_PERSIAN);
	}
}
