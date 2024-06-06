/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:06:02 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/06/06 19:10:53 by jrocha-v         ###   ########.fr       */
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
			paint_square(&data->map[i][j], j * (int)SIZE, i * (int)SIZE,
				data->mm_scale);
	}
}

/* Draw Player direction vector (just to debug) */
void	draw_direction(t_data *data)
{
	t_point		dir;
	t_point		pos;

	pos.x = data->player.px;
	pos.y = data->player.py;
	dir.x = pos.x + cos(data->player.rot_ang) * 20;
	dir.y = pos.y + sin(data->player.rot_ang) * 20;
	draw_lines(&pos, &dir, data, -1);
}

/* Draw Player representation as a filled square */
static void	draw_player(t_data *data)
{
	int	i;
	int	j;

	i = 3;
	j = 3;
	if (data->init == true)
	{
		set_player_pos(data);
		data->init = false;
	}
	while (--i > -3)
	{
		j = 3;
		while (--j > -3)
			put_pixel(&data->img, data->player.px * data->mm_scale - i,
				data->player.py * data->mm_scale - j, CLR_PERSIAN);
	}
}

void	process_minimap(t_data *data)
{
	data->c_pos_x = WIN_W / 2.0;
	data->c_pos_y = WIN_H / 2.0;
	draw_minimap(data);
	draw_player(data);
	draw_rays(data);
	return ;
}
