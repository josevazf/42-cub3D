/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:03:12 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/14 15:17:08 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Set vars to standard values */
void	init_data(t_data *data)
{
	data->map_h = 0;
	data->map_w = 0;
	data->trs_x = 0;
	data->trs_y = 0;
	data->err = 0;
	data->x1 = 0;
	data->y1 = 0;
	data->c_pos_x = WIN_W / 2;
	data->c_pos_y = WIN_H / 2;
	data->init = true;
	data->player.px = data->c_pos_x;
	data->player.py = data->c_pos_y;
	data->player.rot_ang = (M_PI / 2) * 3;
}

/* Get outter dimensions of the map, w (width) and h (height)*/
void	get_dimensions(char *file_name, t_data *data)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open(file_name, O_RDONLY, 0);
	fd_error(fd);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			free(line);
			break ;
		}
		if (data->map_w == 0)
			data->map_w = ft_count_words(line);
		data->map_h++;
		free(line);
	}
	close(fd);
}

/* Create an empty matrix representation of the map */
void	create_map(t_data *data)
{
	int	i;
	
	i = -1;
	data->map = ft_safe_malloc(sizeof(t_cube *) * (data->map_h + 1));
	while (++i < data->map_h)
		data->map[i] = ft_safe_malloc(sizeof(t_cube) * (data->map_w + 1));
}

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

/* Fill the matrix representation of the map with info for each cube */
void	fill_map(t_cube *map, char *line, t_data *data)
{
	char	**nums;
	int		i;

	(void)data;
	i = -1;
	nums = ft_split(line, ' ');
	while (nums[++i])
	{
		map[i].cnt.x = 0;
		map[i].cnt.y = 0;
		if (!ft_strncmp(nums[i], "0", 1))
		{
			map[i].cube_type = OPEN;
			map[i].cube_start = FALSE;
			map[i].clr = CLR_WHITE;
		}
		else if (!ft_strncmp(nums[i], "1", 1))
		{
			map[i].cube_type = CLOSED;
			map[i].cube_start = FALSE;
			map[i].clr = CLR_SILK;
		}
		else if (ft_strncmp(nums[i], "0", 1) && ft_strncmp(nums[i], "1", 1))
		{
			map[i].cube_type = OPEN;
			map[i].cube_start = get_player_start_dir(nums[i][0], data);
			map[i].clr = CLR_WHITE;
		}
		map[i].data = data;
		free(nums[i]);
	}
	free(nums);
}

/* Get all map info */
void	process_map(char *file_name, t_data *data)
{
	char	*line;
	int		i;
	int		fd;

	i = -1;
	init_data(data);
	get_dimensions(file_name, data);
	fd = open(file_name, O_RDONLY, 0);
	fd_error(fd);
	create_map(data);
	while (++i < data->map_h)
	{
		line = get_next_line(fd);
		fill_map(data->map[i], line, data);
		free(line);
	}
	line = get_next_line(fd);
	free(line);
	close(fd);
	data->map[i] = NULL;
}
