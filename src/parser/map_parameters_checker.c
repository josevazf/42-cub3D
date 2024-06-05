/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parameters_checker.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:27:04 by tiaferna          #+#    #+#             */
/*   Updated: 2024/06/05 15:55:31 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	check_for_repeated_texture_definitions(t_map *map, t_direction dir_code)
{
	t_map_list	*node;
	char		*direction;
	int			i;
	int			count;

	direction = set_direction(dir_code);
	node = map->map_list;
	count = 0;
	while (node)
	{
		i = 0;
		while (node->row && ft_iswhitespace(node->row[i]))
			i++;
		if (ft_strncmp(node->row + i, direction, 2) == 0
			&& ft_iswhitespace(node->row[i + 2]))
			count++;
		node = node->next;
	}
	free (direction);
	if (count != 1)
		ft_perror_shutdown(RED"Error\nMultiple definitions for "
			"the same parameter found\n"RESET, 2, map);
	return (false);
}

bool	check_for_repeated_color_definitions(t_map *map, t_direction dir_code)
{
	t_map_list	*node;
	char		*direction;
	int			i;
	int			count;

	direction = set_direction(dir_code);
	node = map->map_list;
	count = 0;
	while (node)
	{
		i = 0;
		while (node->row && ft_iswhitespace(node->row[i]))
			i++;
		if (ft_strncmp(node->row + i, direction, 1) == 0
			&& ft_iswhitespace(node->row[i + 1]))
			count++;
		node = node->next;
	}
	free (direction);
	if (count != 1)
		ft_perror_shutdown(RED"Error\nMultiple definitions for "
			"the same parameter found\n"RESET, 2, map);
	return (false);
}
