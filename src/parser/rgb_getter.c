/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_getter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 08:54:59 by tiaferna          #+#    #+#             */
/*   Updated: 2024/06/06 22:57:34 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*set_direction(t_direction dir_code)
{
	char		*direction;

	direction = NULL;
	if (dir_code == NORTH)
		direction = ft_strdup("NO ");
	else if (dir_code == SOUTH)
		direction = ft_strdup("SO ");
	else if (dir_code == EAST)
		direction = ft_strdup("EA ");
	else if (dir_code == WEST)
		direction = ft_strdup("WE ");
	else if (dir_code == FLOOR_RGB)
		direction = ft_strdup("F ");
	else if (dir_code == CEILING_RGB)
		direction = ft_strdup("C ");
	else
		ft_perror_exit("Wrong dir_code entered in get_texture_path()\n", 2);
	return (direction);
}

static int	*rgb_char_to_int(char **rgb_str, t_map *map)
{
	int	l;
	int	*rgb;
	int	i;
	int	j;

	l = 0;
	i = -1;
	rgb = (int *)malloc(sizeof(int) * 3);
	while (rgb_str[l])
	{
		j = -1;
		while (rgb_str[l][++j])
			if (!ft_isdigit(rgb_str[l][j]) && !ft_iswhitespace(rgb_str[l][j]))
				ft_rgb_perror_shutdown(RED"Error\nInvalid rgb "
					"color entered\n"RESET, map, rgb, rgb_str);
		rgb[++i] = ft_atoi(rgb_str[l]);
		l++;
		if (l > 3 || rgb[i] < 0 || rgb[i] > 255)
			ft_rgb_perror_shutdown(RED"Error\nInvalid rgb color "
				"entered\n"RESET, map, rgb, rgb_str);
	}
	if (l < 3)
		ft_rgb_perror_shutdown(RED"Error\nInvalid rgb color "
			"entered\n"RESET, map, rgb, rgb_str);
	return (rgb);
}

static int	*return_rgb(t_map_list *node, int i, t_map *map)
{
	int		*rgb;
	char	*temp;
	char	**rgb_str;

	rgb = NULL;
	rgb_str = NULL;
	while (node->row && ft_iswhitespace(node->row[i]))
		i++;
	if (node->row + i)
	{
		temp = ft_strldup(node->row + i, ft_strlen(node->row) - 3);
		rgb_str = ft_split(temp, ',');
		free(temp);
		rgb = rgb_char_to_int(rgb_str, map);
		ft_free_matrix((void **)rgb_str);
	}
	return (rgb);
}

int	*get_rgb(t_map *map, t_direction dir_code)
{
	int			i;
	char		*direction;
	t_map_list	*node;

	direction = set_direction(dir_code);
	node = map->map_list;
	while (node)
	{
		i = 0;
		while (node->row && ft_iswhitespace(node->row[i]))
			i++;
		if (ft_strncmp(node->row + i, direction, 2) == 0)
		{
			free(direction);
			i++;
			while (node->row && ft_iswhitespace(node->row[i]))
				i++;
			if (node->row + i)
				return (return_rgb(node, i, map));
		}
		node = node->next;
	}
	free(direction);
	ft_perror_shutdown(RED"Error\nC or F is not defined\n"RESET, 2, map);
	return (NULL);
}
