/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creators.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 08:47:23 by tiaferna          #+#    #+#             */
/*   Updated: 2024/06/06 09:36:26 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_map_list	*create_map_list_from_fd(int map_fd, t_map *map)
{
	char		*line;
	t_map_list	*node;

	line = get_next_line(map_fd);
	if (line)
	{
		map->map_list = (t_map_list *)malloc(sizeof(t_map_list));
		map->map_list->row = ft_strdup(line);
		map->map_list->next = NULL;
		free(line);
	}
	node = map->map_list;
	line = get_next_line(map_fd);
	while (line)
	{
		node->next = (t_map_list *)malloc(sizeof(t_map_list));
		node = node->next;
		node->row = ft_strdup(line);
		node->next = NULL;
		free(line);
		line = get_next_line(map_fd);
	}
	return (map->map_list);
}

static bool	check_for_map_tile(t_map_list *node)
{
	int	i;

	i = 0;
	while (node->row[i] && ft_iswhitespace(node->row[i]))
		i++;
	if (node->row[i] && (node->row[i] == '1'
			|| node->row[i] == '0'
			|| (node->row[i] == 'N' && ft_strncmp(node->row + i, "NO", 2))
			|| (node->row[i] == 'S' && ft_strncmp(node->row + i, "SO", 2))
			|| (node->row[i] == 'E' && ft_strncmp(node->row + i, "EA", 2))
			|| (node->row[i] == 'W' && ft_strncmp(node->row + i, "WE", 2))))
		return (true);
	return (false);
}

static int	count_rows_to_alloc(t_map_list *node)
{
	int	ret;

	ret = 0;
	while (node)
	{
		if (check_for_map_tile(node) == true)
		{
			ret++;
			break ;
		}
		node = node->next;
	}
	while (node)
	{
		ret++;
		node = node->next;
	}
	return (ret);
}

char	**create_map_grid_from_list(t_map *map)
{
	t_map_list	*node;
	int			rows_to_alloc;
	int			i;

	node = map->map_list;
	i = 0;
	rows_to_alloc = count_rows_to_alloc(node);
	if (rows_to_alloc == 0)
		ft_perror_shutdown(RED"Error\nNo valid map found\n"RESET, 2, map);
	map->map_grid = (char **)malloc(sizeof(char *) * (rows_to_alloc + 1));
	node = map->map_list;
	while (node)
	{
		if (check_for_map_tile(node) == true)
			break ;
		node = node->next;
	}
	while (node)
	{
		map->map_grid[i++] = ft_strdup(node->row);
		node = node->next;
	}
	map->map_grid[i] = NULL;
	return (map->map_grid);
}

void	reset_map_grid(t_map *map)
{
	ft_free_matrix((void **)map->map_grid);
	create_map_grid_from_list(map);
}
