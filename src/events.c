/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:56:30 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/06/06 12:07:39 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Set flag for key release */
int	key_release(int key, t_data *data)
{
	if (key == XK_w)
		data->key.w = 0;
	else if (key == XK_a)
		data->key.a = 0;
	else if (key == XK_s)
		data->key.s = 0;
	else if (key == XK_d)
		data->key.d = 0;
	else if (key == XK_Left)
		data->key.left = 0;
	else if (key == XK_Right)
		data->key.right = 0;
	else if (key == XK_Escape)
		data->key.esc += 1;
	return (0);
}

/* Set flag for key press */
int	key_press(int key, t_data *data)
{
	if (key == XK_w)
		data->key.w = 1;
	else if (key == XK_a)
		data->key.a = 1;
	else if (key == XK_s)
		data->key.s = 1;
	else if (key == XK_d)
		data->key.d = 1;
	else if (key == XK_Left)
		data->key.left = 1;
	else if (key == XK_Right)
		data->key.right = 1;
	return (0);
}

/* Esc-Press - close window and free all memory */
int	free_game(t_data *data)
{
	int	i;

	i = -1;
	free_map(data->og_map);
	if (data)
	{
		while (++i < 4)
		{
			if (data->txts_img[i].img)
				mlx_destroy_image(data->mlx_ptr, data->txts_img[i].img);
			ft_safe_free(data->txts_path[i]);
		}
		mlx_destroy_image(data->mlx_ptr, data->img.img);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		data->win_ptr = NULL;
		ft_safe_free(data->mlx_ptr);
		ft_safe_free(data->map_name);
		ft_safe_free(data->rays);
		ft_free_matrix((void **)data->map);
		exit (EXIT_SUCCESS);
	}
	return (SUCCESS);
}

/* Route key events */
void	input_router(t_data *data)
{
	if (data->key.esc >= 1)
		free_game(data);
	if (data->key.w)
		move_player(data, XK_w);
	if (data->key.s)
		move_player(data, XK_s);
	if (data->key.a)
		move_player(data, XK_a);
	if (data->key.d)
		move_player(data, XK_d);
	if (data->key.left)
		move_player(data, XK_Left);
	if (data->key.right)
		move_player(data, XK_Right);
}
