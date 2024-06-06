/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 08:50:28 by tiaferna          #+#    #+#             */
/*   Updated: 2024/06/06 14:49:10 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void	free_map(t_map *map)
{
	ft_safe_free(map->north_wall);
	ft_safe_free(map->south_wall);
	ft_safe_free(map->east_wall);
	ft_safe_free(map->west_wall);
	ft_safe_free(map->floor);
	ft_safe_free(map->ceiling);
	ft_safe_free(map->starting_position);
	if (map->map_grid)
		ft_free_matrix((void **)map->map_grid);
	if (map->map_list)
		free_map_list(map->map_list);
	ft_safe_free(map);
}

void	ft_perror_shutdown(char *str, int error, t_map *map)
{
	free_map(map);
	if (str)
		write(error, str, ft_strlen(str));
	exit(error);
}

void	ft_rgb_perror_shutdown(char *str, t_map *map, int *rgb, char**rgb_str)
{
	free(rgb);
	ft_free_matrix((void **)rgb_str);
	free_map(map);
	if (str)
		write(2, str, ft_strlen(str));
	exit(2);
}
