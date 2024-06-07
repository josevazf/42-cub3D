/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_geter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:59:55 by tiaferna          #+#    #+#             */
/*   Updated: 2024/06/07 14:42:22 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	is_valid_texture_path(char **path, t_map *map)
{
	int	path_fd;

	path_fd = open(*path, R_OK);
	if (path_fd != -1)
	{
		close(path_fd);
		if (ft_strcmp(*path + ft_strlen(*path) - 3, ".xpm"))
			return (true);
	}
	else
	{
		ft_safe_free(*path);
		ft_perror_shutdown(RED"Error\nUnable to "
			"open texture file\n"RESET, 2, map);
	}
	return (false);
}

char	*texture_path(int i, t_map_list *node, char *path, t_map *map)
{
	int	j;

	i += 2;
	while (node->row && ft_iswhitespace(node->row[i]) && \
					(node->row + i)[0] != '\n')
		i++;
	j = 0;
	while (node->row[i + j] && !ft_iswhitespace(node->row[i + j]))
		j++;
	if (node->row + i)
	{
		path = ft_strldup(node->row + i, \
		ft_strlen(node->row) - (ft_strlen(node->row) - j));
		if (is_valid_texture_path(&path, map) == true)
			return (path);
		ft_safe_free(path);
	}
	return (NULL);
}

char	*get_texture_path(t_map *map, t_direction dir_code, int i)
{
	t_map_list	*node;
	char		*path;
	char		*direction;

	path = NULL;
	direction = set_direction(dir_code);
	node = map->map_list;
	while (node)
	{
		while (node->row && ft_iswhitespace(node->row[i]))
			i++;
		if (ft_strncmp(node->row + i, direction, 3) == 0)
		{
			free(direction);
			path = texture_path(i, node, path, map);
			if (path)
				return (path);
			break ;
		}
		node = node->next;
	}
	free(direction);
	ft_perror_shutdown(RED"Error\nInvalid texture path\n"RESET, 2, map);
	return (NULL);
}
