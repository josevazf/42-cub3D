/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:58:21 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/03 09:12:02 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Deal with file descriptor failure */
int	fd_error(int fd)
{
	if (fd == -1)
		ft_error("cub3D: file error", ERROR);
	return (SUCCESS);
}

/* Deal with bad arguments */
int	args_error(void)
{
	printf("cub3D usage: ./cub3d map_name.cub\n");
	exit (SUCCESS);
}

/* Free the map matrix */
void	ft_free_map(t_cube **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
