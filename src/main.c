/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:37:56 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/29 15:08:11 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	run_game(t_data *data)
{
	input_router(data);
	cast_rays(data);
	render_walls(data);
	process_minimap(data);
	print_cube_coords(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;

	(void)argc;
/* 
	if (argc != 2 || ft_check_ext(argv[1], ".cub"))
		args_error(); */
	process_map(argv[1], &data);
	data.map_name = ft_strjoin("[padaria]   Cub3D: ", argv[1]);
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		ft_error("cub3D: ", ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_W, WIN_H, data.map_name);
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		ft_error("cub3D: ", ERROR);
	}
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIN_W, WIN_H);
	data.img.mlx_pixel_addr = mlx_get_data_addr(data.img.mlx_img, 
			&data.img.bpp, &data.img.line_len, &data.img.endian);
	mlx_hook(data.win_ptr, 2, 1L << 0, &key_press, &data);
	mlx_hook(data.win_ptr, 3, 1L << 1, &key_release, &data);
	mlx_hook(data.win_ptr, 17, 1L << 0, &free_game, &data);
	mlx_loop_hook(data.mlx_ptr, &run_game, &data);
	mlx_loop(data.mlx_ptr);
	return (SUCCESS);
}
