/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 20:31:05 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/14 17:45:32 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Return the Cube where the Player is positioned */
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
