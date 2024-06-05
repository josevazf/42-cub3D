/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:14:21 by tiaferna          #+#    #+#             */
/*   Updated: 2024/06/05 15:55:31 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	map_init(t_map	*map)
{
	map->north_wall = NULL;
	map->south_wall = NULL;
	map->east_wall = NULL;
	map->west_wall = NULL;
	map->floor_color = NULL;
	map->ceiling_color = NULL;
	map->map_grid = NULL;
	map->starting_position = NULL;
	map->starting_direction = 0;
}

void	map_fetch_struct_info(t_map	*map)
{
	map->north_wall = get_texture_path(map, NORTH);
	map->south_wall = get_texture_path(map, SOUTH);
	map->east_wall = get_texture_path(map, EAST);
	map->west_wall = get_texture_path(map, WEST);
	map->floor_color = get_rgb(map, FLOOR_RGB);
	map->ceiling_color = get_rgb(map, CEILING_RGB);
	map->map_grid = create_map_grid_from_list(map);
	map->starting_position = starting_coordinate(map);
	map->starting_direction = starting_direction(map);
}
