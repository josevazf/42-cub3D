/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:08:08 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/14 12:10:13 by jrocha-v         ###   ########.fr       */
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
		v1 = (float)data->map[0][0].v1.x;
		v2 = (float)data->map[0][data->map_w - 1].v1.x;
		v3 = (float)data->map[data->map_h - 1][0].v1.x;
		v4 = (float)data->map[data->map_h - 1][data->map_w - 1].v1.x;
	}
	else
	{
		v1 = (float)data->map[0][0].v1.y;
		v2 = (float)data->map[0][data->map_w - 1].v1.y;
		v3 = (float)data->map[data->map_h - 1][0].v1.y;
		v4 = (float)data->map[data->map_h - 1][data->map_w - 1].v1.y;
	}
	return ((v1 + v2 + v3 + v4) / 4);
}

/* Get center of map representation */
void	get_map_center(t_data *data)
{
	data->c_pos_x = get_average(data, 0);
	data->c_pos_y = get_average(data, 1);
}

void	print_cube_coords(t_data *data)
{
		int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < data->map_h)
	{
		j = -1;
		while (++j < (data->map_w))
		{
			printf("CUBE[%d,%d]\n", i , j);
			printf("V1->(%d, %d)\n", data->map[i][j].v1.x, data->map[i][j].v1.y);
			printf("V2->(%d, %d)\n", data->map[i][j].v2.x, data->map[i][j].v2.y);
			printf("V3->(%d, %d)\n", data->map[i][j].v3.x, data->map[i][j].v3.y);
			printf("V4->(%d, %d)\n", data->map[i][j].v4.x, data->map[i][j].v4.y);
		}
		printf("^^^^^^^^^^^^^^^\n");
	}
}
