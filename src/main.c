/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:37:56 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/06/05 08:51:08 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		run_game(t_data *data)
{
	input_router(data);
	cast_rays(data);
	render_walls(data, -1, -1);
	process_minimap(data);
	//printf("player(%f, %f)\n", data->player.px, data->player.py);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 
		0, 0);
	return (SUCCESS);
}

void	load_textures(t_data *data)
{
	int i;

	i = -1;
	data->txts_path[NO] = ft_strdup("textures/tech_1.xpm");
	data->txts_path[SO] = ft_strdup("textures/tech_2.xpm");
	data->txts_path[WE] = ft_strdup("textures/tech_3.xpm");
	data->txts_path[EA] = ft_strdup("textures/tech_4.xpm");
	while (++i < 4)
	{
		data->txts_img[i].img = mlx_xpm_file_to_image(data->mlx_ptr, 
			data->txts_path[i], &data->txts_img[i].width, 
			&data->txts_img[i].height);
		if (!data->txts_img[i].img)
			ft_error_exit("cub3D: failed to load textures", data);
		data->txts_img[i].pixel_addr = mlx_get_data_addr(data->txts_img[i].img,
			&data->txts_img[i].bpp, &data->txts_img[i].line_len,
			&data->txts_img->endian);
		if (!data->txts_img[i].pixel_addr)
			ft_error_exit("cub3D: failed to get texture address", data);
	}
}

void	init_mlx_textures(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		ft_error_exit("cub3D: failed to initialize MLX", data);
	load_textures(data);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_W, WIN_H, data->map_name);
	if (!data->win_ptr)
		ft_error_exit("cub3D: failed to create window", data);
	data->img.width = WIN_W;
	data->img.height = WIN_H;
	data->img.img = mlx_new_image(data->mlx_ptr, data->img.width, 
		data->img.height);
	if (!data->img.img)
		ft_error_exit("cub3D: failed to create image", data);
	data->img.pixel_addr = mlx_get_data_addr(data->img.img, 
		&data->img.bpp, &data->img.line_len, &data->img.endian);
	if (!data->img.pixel_addr)
		ft_error_exit("cub3D: failed to get image address", data);
}

int		main(int argc, char **argv)
{
	t_data	data;

	(void)argc;
/* 
	if (argc != 2 || ft_check_ext(argv[1], ".cub"))
		args_error(); */
	process_map(argv[1], &data);
	data.map_name = ft_strjoin("[padaria]   Cub3D: ", argv[1]);
	init_mlx_textures(&data);
	mlx_hook(data.win_ptr, 2, 1L << 0, &key_press, &data);
	mlx_hook(data.win_ptr, 3, 1L << 1, &key_release, &data);
	mlx_hook(data.win_ptr, 17, 1L << 0, &free_game, &data);
	mlx_loop_hook(data.mlx_ptr, &run_game, &data);
	mlx_loop(data.mlx_ptr);
	return (SUCCESS);
}
