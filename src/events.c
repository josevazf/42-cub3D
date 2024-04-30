/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:56:30 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/30 18:57:47 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Esc-Press - close window and free all memory */
int	esc_key(t_data *data)
{
	if (data)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		data->win_ptr = NULL;
		free(data->mlx_ptr);
		//ft_free_map(data->map);
		exit (EXIT_SUCCESS);
	}
	return (SUCCESS);
}

/* Trigger key press events */
int	key_events(int key, t_data *data)
{
	if (key == XK_w || key == XK_a || key == XK_s || key == XK_d)
		move_player(data, key); // TO DO
	if (key == XK_Left || key == XK_Right)
		look_left_right(data, key); // TO DO
	if (key == XK_Escape)
		esc_key(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 
		0, 0);
	return (SUCCESS);
}
