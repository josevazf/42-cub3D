/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 20:31:05 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/13 17:54:54 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_data *data, int key)
{
	clean_screen(data);
	draw_minimap(data);
	if (key == XK_w)
		data->player.py -= 1 * MV_SPD;
	else if (key == XK_s)
		data->player.py += 1 * MV_SPD;
	else if (key == XK_a)
		data->player.px -= 1 * MV_SPD;
	else if (key == XK_d)
		data->player.px += 1 * MV_SPD;
	else if (key == XK_Left)
		data->player.rot_ang -= ROT_SPD;
	else if (key == XK_Right)
		data->player.rot_ang += ROT_SPD;
	draw_player(data);
}

void	draw_direction(t_data *data)
{
	t_point		dir;
	t_point		pos;

	//printf("Player (x: %f, y: %f)\n", data->player.px, data->player.py);
	pos.x = data->player.px;
	pos.y = data->player.py;
	dir.x = pos.x + cos(data->player.rot_ang) * 20;
	dir.y = pos.y + sin(data->player.rot_ang) * 20;
	draw_lines(&pos, &dir, data, -1);
}

void	draw_player(t_data *data)
{
	int	i;
	int	j;
	
	i = 10;
	j = 10;
	while (--i > 0)
	{
		j = 10;
		while (--j > 0)
		{
			put_pixel(&data->img, (data->player.px + 5) - i, (data->player.py + 5) - j, CLR_PERSIAN);
		}
	}
	draw_direction(data);
}
