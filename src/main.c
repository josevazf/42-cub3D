/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:37:56 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/06/05 17:06:24 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	run_game(t_data *data)
{
	input_router(data);
	cast_rays(data);
	render_walls(data, -1, -1);
	process_minimap(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img,
		0, 0);
	return (SUCCESS);
}

void	load_textures(t_data *data)
{
	int	i;

	i = -1;
	data->txts_path[NO] = ft_strdup("textures/bookshelf.xpm");
	data->txts_path[SO] = ft_strdup("textures/bookshelf_01.xpm");
	data->txts_path[WE] = ft_strdup("textures/bookshelf_02.xpm");
	data->txts_path[EA] = ft_strdup("textures/bookshelf_03.xpm");
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

int	main(int argc, char **argv)
{
	t_data	data;
	t_map	*map;

	if (argc == 1)
		no_map_error();
	else if (argc == 2 && is_file_extension_correct(argv[1]) == false)
		ft_perror_exit(RED"Error\nThe executable only "
			"accepts a \'.cub\' argument\n"RESET, 2);
	else if (argc == 2)
		map = parse_map(argv[1]);
	else
		ft_perror_exit(RED"Error\nThe executable only accepts "
			BOLD"one"RESET RED" \'.cub\' argument\n"RESET, 2);
	process_map(argv[1], &data, map);
	data.map_name = ft_strjoin("[padaria]   Cub3D: ", argv[1]);
	init_mlx_textures(&data);
	mlx_hook(data.win_ptr, 2, 1L << 0, &key_press, &data);
	mlx_hook(data.win_ptr, 3, 1L << 1, &key_release, &data);
	mlx_hook(data.win_ptr, 17, 1L << 0, &free_game, &data);
	mlx_loop_hook(data.mlx_ptr, &run_game, &data);
	mlx_loop(data.mlx_ptr);
	return (SUCCESS);
}
