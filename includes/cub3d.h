/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:40:54 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/02 18:26:25 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/libft/libft.h"
# include "../libs/minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

# define ERROR 1
# define SUCCESS 0

# define WIN_W 1024
# define WIN_H 512

# define CLR_RED			0xFF0000
# define CLR_GREEN			0x00FF00
# define CLR_BLUE			0x0000FF
# define CLR_WHITE			0xFFFFFF
# define CLR_BLACK			0x000000
# define CLR_NEON			0xFF10F0

typedef struct s_img
{
	void		*mlx_img;
	char		*mlx_pixel_addr;
	int			bpp;
	int			line_len;
	int			endian;
}	t_img;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}	t_color;

typedef struct s_cube
{
	int			x;
	int			y;
	int			clr;
	t_color		rgb;
}	t_cube;

typedef struct s_player
{
	double		px;
	double		py;
	t_cube		ps;
}	t_player;

typedef struct s_data
{
	int			map_w;
	int			map_h;
	int			trs_x;
	int			trs_y;
	int			c_pos_x;
	int			c_pos_y;
	char		*map_name;
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_cube		**map;
	t_player	player;
}	t_data;

#endif

// main.c

// init.c
void	init_data(t_data *data);
void	get_dimensions(char *file_name, t_data *data);
void	create_map(t_data *data);
void	fill_map(t_cube *map, char *line, t_data *data);
void	process_map(char *file_name, t_data *data);

// events.c
int		esc_key(t_data *data);
int		key_events(int key, t_data *data);

// minimap.c
void	process_minimap(t_data *data);
void	draw_player(t_data *data);
void	move_player(t_data *data, int key);

// draw.c
void	put_pixel(t_img *img, int x, int y, int color);

// utils.c
void	clean_screen(t_data *data);

// error.c
int		fd_error(int fd);
int		args_error(void);
void	ft_free_map(t_cube **matrix);
