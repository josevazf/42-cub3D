/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:23:26 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/21 18:11:17 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_walls(t_data *data)
{
	int i;
	int	dist_pp;
	t_point line_start;
	t_point	line_end;
	
	i = -1;
	dist_pp = (WIN_W / 2) / tan(FOV_ANG / 2);
	while (++i < NUM_RAYS)
	{
		data->rays[i].distance = data->rays[i].distance * cos(data->rays[i].angle - data->player.rot_ang);
		data->rays[i].height = (SIZE * dist_pp) / data->rays[i].distance;
		line_start.x = i + 1;
		line_start.y = (WIN_H / 2) + (data->rays[i].height / 2);
		line_end.x = i + 1;
		line_end.y = (WIN_H / 2) - (data->rays[i].height / 2);
		draw_lines(&line_start, &line_end, data, -1);
	}
}
