/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:03:12 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/06/06 19:11:41 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Initialize vars to standard values */
static void	init_data(t_data *data)
{
	data->mm_scale = 1.0;
	data->map_h = 0;
	data->map_w = 0;
	data->err = 0;
	data->x1 = 0;
	data->y1 = 0;
	data->c_pos_x = WIN_W / 2.0;
	data->c_pos_y = WIN_H / 2.0;
	data->init = true;
	data->key.esc = 0;
	data->key.w = 0;
	data->key.s = 0;
	data->key.a = 0;
	data->key.d = 0;
	data->key.left = 0;
	data->key.right = 0;
	data->player.px = data->c_pos_x;
	data->player.py = data->c_pos_y;
	data->player.rot_ang = (M_PI / 2.0) * 3.0;
	data->rays = ft_safe_malloc(sizeof(t_rays) * NUM_RAYS);
}

/* Get outter dimensions of the map, w (width) and h (height)*/
static void	get_dimensions(char *file_name, t_data *data, t_map *map)
{
	int		i;
	int		temp_width;

	(void)file_name;
	i = -1;
	temp_width = 0;
	while (map->map_grid[++i])
	{
		temp_width = ft_strlen(map->map_grid[i]) - 1;
		if (data->map_w <= temp_width)
			data->map_w = temp_width;
		data->map_h++;
	}
}

/* Create an empty matrix representation of the map */
static void	create_map(t_data *data)
{
	int	i;

	i = -1;
	data->map = ft_safe_malloc(sizeof(t_cube *) * (data->map_h + 1));
	while (++i < data->map_h)
		data->map[i] = ft_safe_malloc(sizeof(t_cube) * (data->map_w + 1));
}

/* Fill the matrix representation of the map with info for each cube */
static void	fill_map(t_cube *map, char *line, t_data *data, int i)
{
	while (++i < data->map_w)
	{
		map[i].cube_start = FALSE;
		map[i].clr = CLR_BLACK;
		if (i >= (int)ft_strlen(line) - 1 || line[i] == ' ')
			map[i].cube_type = EMPTY;
		else if (line[i] == '0')
		{
			map[i].cube_type = OPEN;
			map[i].clr = CLR_WHITE;
		}
		else if (line[i] == '1')
			map[i].cube_type = CLOSED;
		else if (line[i] != '0' && line[i] != '1')
		{
			map[i].cube_type = OPEN;
			map[i].cube_start = get_player_start_dir(line[i], data);
			map[i].clr = CLR_WHITE;
		}
		map[i].data = data;
	}
}

/* Get all map info */
void	process_map(char *file_name, t_data *data, t_map *map)
{
	int		i;

	data->og_map = map;
	i = -1;
	init_data(data);
	get_dimensions(file_name, data, map);
	if (data->map_w >= data->map_h)
		data->mm_scale = 200 / (data->map_w * SIZE);
	else
		data->mm_scale = 200 / (data->map_h * SIZE);
	create_map(data);
	while (++i < data->map_h)
		fill_map(data->map[i], map->map_grid[i], data, -1);
	data->map[i] = NULL;
}
