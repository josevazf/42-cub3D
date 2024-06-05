/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:58:21 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/06/05 14:27:42 by jrocha-v         ###   ########.fr       */
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

void	ft_error_exit(char *msg, t_data *data)
{
	free_game(data);
	ft_error(msg, ERROR);
}
