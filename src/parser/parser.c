/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:25:23 by tiaferna          #+#    #+#             */
/*   Updated: 2024/06/06 09:37:17 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_file_extension_correct(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (str[len - 4] != '.' || str[len -3] != 'c' || \
						str[len - 2] != 'u' || str[len - 1] != 'b')
		return (false);
	return (true);
}

void	no_map_error(void)
{
	printf(RED"Error\n"RESET);
	printf(CYAN"Please enter one of the following maps "
		"after the executable's name:\n\n"RESET);
	printf(BLUE"\tmap_1.cub\n");
	printf("\tmap_2.cub\n");
	printf("\tmap_3.cub\n\n"RESET);
	ft_perror_exit(NULL, 2);
}

t_map	*parse_map(char *map_file)
{
	int			map_fd;
	char		*address;
	t_map		*map;

	address = ft_strjoin("./maps/", map_file);
	map_fd = open(address, O_RDONLY);
	free(address);
	if (map_fd == -1)
		ft_perror_exit(RED"Error\nUnable to open the file\n"RESET, 2);
	map = (t_map *)malloc(sizeof(t_map));
	map_init(map);
	map->map_list = create_map_list_from_fd(map_fd, map);
	close(map_fd);
	map_fetch_struct_info(map);
	map_checker(map);
	map_struct_printer(map);
	return(map);
}
