/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:08:08 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/13 14:49:18 by jrocha-v         ###   ########.fr       */
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

/* Get center point for x ->(t = 0) else y */
float	get_average(t_data *data, int t)
{
	float	v1;
	float	v2;
	float	v3;
	float	v4;

	if (t == 0)
	{
		v1 = (float)data->map[0][0].cnt.x;
		v2 = (float)data->map[0][data->map_w - 1].cnt.x;
		v3 = (float)data->map[data->map_h - 1][0].cnt.x;
		v4 = (float)data->map[data->map_h - 1][data->map_w - 1].cnt.x;
	}
	else
	{
		v1 = (float)data->map[0][0].cnt.y;
		v2 = (float)data->map[0][data->map_w - 1].cnt.y;
		v3 = (float)data->map[data->map_h - 1][0].cnt.y;
		v4 = (float)data->map[data->map_h - 1][data->map_w - 1].cnt.y;
	}
	return ((v1 + v2 + v3 + v4) / 4);
}

/* Get center of map representation */
void	get_map_center(t_data *data)
{
	data->c_pos_x = get_average(data, 0);
	data->c_pos_y = get_average(data, 1);
}
