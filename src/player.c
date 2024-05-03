/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 20:31:05 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/03 13:07:39 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_data *data, int key)
{
	clean_screen(data);
	draw_minimap(data);
	if (key == XK_w)
		data->player.py -= 5;
	else if (key == XK_s)
		data->player.py += 5;
	else if (key == XK_a)
		data->player.px -= 5;
	else if (key == XK_d)
		data->player.px += 5;
	draw_player(data);
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
			put_pixel(&data->img, data->player.px - i, data->player.py - j, CLR_RED);
		}
	}
}
