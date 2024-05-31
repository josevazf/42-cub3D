/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:08:08 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/31 14:13:43 by jrocha-v         ###   ########.fr       */
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

/* Get direction to draw line */
int	get_slope(int p1, int p2)
{
	if (p1 < p2)
		return (1);
	return (-1);
}

/* Convert degrees to radians */
double	get_rad(double deg)
{
	#include <math.h>

	return (deg * M_PI / 180.0);
}

double	get_deg(double rad)
{
	#include <math.h>

	return (rad * 180.0 / M_PI);

}
