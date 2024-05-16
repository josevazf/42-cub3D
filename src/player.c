/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 20:31:05 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/16 12:25:25 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Get Player starting direction */
enum s_cubeStart	get_player_start_dir(char dir, t_data *data)
{
	if (dir == 'N')
	{
		data->player.rot_ang = (M_PI / 2) * 3;
		return (N);
	}
	else if (dir == 'S')
	{
		data->player.rot_ang = (M_PI / 2) * 1;
		return (S);
	}
	else if (dir == 'E')
	{
		data->player.rot_ang = (M_PI / 2) * 2;
		return (E);
	}
	else if (dir == 'W')
	{
		data->player.rot_ang = 0;
		return (W);
	}
	else
		return (FALSE);
}

/* Return the Cube where the point is positioned */
t_cube	point_cube_position(t_data *data, double x, double y)
{
	int i;
	int j;

	i = -1;
	j = -1;
	printf("X: %f\n", x);
	printf("Y: %f\n\n", y);
	if (x <= data->map[0][0].v1.x + 5)
		x = data->map[0][0].v1.x + 5;
	else if (x >= data->map[0][data->map_w - 1].v2.x - 5)
		x = data->map[0][data->map_w - 1].v2.x - 5;
	if (y <= data->map[0][0].v1.y + 5)
		y = data->map[0][0].v1.y + 5;
	else if (y >= data->map[data->map_h - 1][0].v3.y - 5)
		y = data->map[data->map_h - 1][0].v3.y - 5;
	printf("X after: %f\n", x);
	printf("Y after: %f\n\n", y);
	while (++i < data->map_h)
	{
		j = -1;
		while (++j < data->map_w)
		{
			if (x >= data->map[i][j].v1.x && \
				y >= data->map[i][j].v1.y && \
				x <= data->map[i][j].v3.x && \
				y <= data->map[i][j].v3.y)
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
