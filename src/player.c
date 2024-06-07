/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 20:31:05 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/06/07 12:15:57 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Get Player starting direction */
enum e_cubeStart	get_player_start_dir(char dir, t_data *data)
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
	else if (dir == 'W')
	{
		data->player.rot_ang = M_PI;
		return (W);
	}
	else if (dir == 'E')
	{
		data->player.rot_ang = 0.0;
		return (E);
	}
	else
		return (FALSE);
}

/* Return the Cube where the point is positioned */
t_cube	point_cube_position(t_data *data, double x, double y)
{
	x = floor(x / SIZE);
	y = floor(y / SIZE);
	return (data->map[(int)y][(int)x]);
}

/* Set initial Player position in the map */
void	set_player_pos(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < data->map_h)
	{
		j = -1;
		while (++j < data->map_w)
		{
			if (data->map[i][j].cube_start != FALSE)
			{
				data->player.c_pos = data->map[i][j];
				data->player.px = (j * SIZE) + (SIZE / 2);
				data->player.py = (i * SIZE) + (SIZE / 2);
				return ;
			}
		}
	}
}
