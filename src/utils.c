/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:08:08 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/30 19:08:57 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Fills the screen with black pixels */
void	clean_screen(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < WIN_W)
	{
		j = -1;
		while (++j < WIN_H)
			put_pixel(&data->img, i, j, CLR_BLACK);
	}
}
