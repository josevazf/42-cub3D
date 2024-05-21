/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:06:02 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/20 14:03:49 by jrocha-v         ###   ########.fr       */
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
	draw_rays(data);
	//printf("player_cube[%d][%d]\n", data->player.c_pos.row, data->player.c_pos.col);
	return ;
}

/* Set coordinates for each cube V1 point */
void	set_coordinates(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	data->mm_spc = SIZE;
	while (++i < data->map_h)
	{
		j = -1;
		while (++j < data->map_w)
		{
			data->map[i][j].v1.x = j * data->mm_spc;
			data->map[i][j].v1.y = i * data->mm_spc;
		}
	}
}

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
			cube[i][j].row = i;
			cube[i][j].col = j;
			cube[i][j].v2.x = cube[i][j].v1.x + data->mm_spc;
			cube[i][j].v2.y = cube[i][j].v1.y;
			cube[i][j].v3.x = cube[i][j].v2.x;
			cube[i][j].v3.y = cube[i][j].v1.y + data->mm_spc;
			cube[i][j].v4.x = cube[i][j].v1.x;
			cube[i][j].v4.y = cube[i][j].v1.y + data->mm_spc;
		}
	}
}
