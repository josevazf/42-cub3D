/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 08:50:28 by tiaferna          #+#    #+#             */
/*   Updated: 2024/06/05 17:03:56 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/// @brief Frees a t_map_list linked list
/// @param list 
void	free_map_list(t_map_list *list)
{
	t_map_list	*temp;

	while (list)
	{
		temp = list;
		free(list->row);
		list = list->next;
		free(temp);
	}
}

/// @brief Frees a t_map struct
/// @param map 
void	free_map(t_map *map)
{
	if (map->north_wall)
		free(map->north_wall);
	if (map->south_wall)
		free(map->south_wall);
	if (map->east_wall)
		free(map->east_wall);
	if (map->west_wall)
		free(map->west_wall);
	if (map->floor_color)
		free(map->floor_color);
	if (map->ceiling_color)
		free(map->ceiling_color);
	if (map->starting_position)
		free(map->starting_position);
	if (map->map_grid)
		ft_free_matrix((void **)map->map_grid);
	if (map->map_list)
		free_map_list(map->map_list);
	free(map);
}

/// @brief Frees all allocated memory and exits the program with a custom error
/// @param str 
/// @param error 
/// @param map 
/// @param map_list 
void	ft_perror_shutdown(char *str, int error, t_map *map)
{
	free_map(map);
	if (str)
		write(error, str, ft_strlen(str));
	exit(error);
}

/// @brief Used within the rgb_char_to_int() function.
/// @brief Frees all allocated memory and exits the program with a custom error
/// @param str 
/// @param error 
/// @param map 
/// @param map_list 
void	ft_rgb_perror_shutdown(char *str, t_map *map, int *rgb, char**rgb_str)
{
	free(rgb);
	ft_free_matrix((void **)rgb_str);
	free_map(map);
	if (str)
		write(2, str, ft_strlen(str));
	exit(2);
}
