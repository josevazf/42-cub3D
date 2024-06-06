/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 22:20:33 by tiaferna          #+#    #+#             */
/*   Updated: 2024/06/06 14:50:10 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	list_printer(t_map_list *map_list)
{
	t_map_list	*node;

	node = map_list;
	while (node)
	{
		printf("%s", node->row);
		node = node->next;
	}
}

void	grid_printer(char **grid)
{
	int	i;

	i = -1;
	while (grid[++i])
		printf("* %s", grid[i]);
}

void	map_struct_printer(t_map *map)
{
	printf("\n/************* MAP STRUCT *************\\\n* \n");
	printf("* map->north_wall: %s\n", map->north_wall);
	printf("* map->south_wall: %s\n", map->south_wall);
	printf("* map->east_wall: %s\n", map->east_wall);
	printf("* map->west_wall: %s\n", map->west_wall);
	printf("*\n");
	printf("* map->floor_color: %d,%d,%d\n", map->floor[0], \
					map->floor[1], map->floor[2]);
	printf("* map->ceiling_color: %d,%d,%d\n", map->ceiling[0], \
					map->ceiling[1], map->ceiling[2]);
	printf("* \n*  *** map->map_grid ***\n* \n");
	grid_printer(map->map_grid);
	printf("\n*\n\\**************************************/\n");
}
