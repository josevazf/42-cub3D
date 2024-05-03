/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:40:54 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/05/03 12:32:32 by jrocha-v         ###   ########.fr       */
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

# define WIN_W 1280
# define WIN_H 720

# define CLR_RED			0xFF0000
# define CLR_GREEN			0x00FF00
# define CLR_BLUE			0x0000FF
# define CLR_WHITE			0xFFFFFF
# define CLR_BLACK			0x000000
# define CLR_NEON			0xFF10F0

typedef struct s_data	t_data;

enum e_CubeType
{
	OPEN,
	CLOSED,
};

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

typedef struct s_point
{
	int			x;
	int			y;
	int			clr;
	t_color		rgb;
}	t_point;

typedef struct s_cube
{
	t_point			cnt;
	t_point			v1;
	t_point			v2;
	t_point			v3;
	t_point			v4;
	int				clr;
	t_color			rgb;
	enum e_CubeType cube_type;
	t_data			*data;
}	t_cube;

typedef struct s_player
{
	double		px;
	double		py;
	t_cube		ps;
	t_data		*data;
}	t_player;

typedef struct s_data
{
	int			map_w;
	int			map_h;
	int			trs_x;
	int			trs_y;
	int			c_pos_x;
	int			c_pos_y;
	int			err;
	int			x1;
	int			y1;
	int			mm_spc;
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
void	set_map(t_data *data);
void	process_minimap(t_data *data);
void	set_cube_vertex(t_data *data);
void	set_coordinates(t_data *data);
void	scale_map(t_data *data, double factor);
void	translate_center(t_data *data, int i, int j);
void	fit_to_window(t_data *data, double angle);


// player.c
void	move_player(t_data *data, int key);
void	draw_player(t_data *data);

// draw.c
void	put_pixel(t_img *img, int x, int y, int color);
void	hex_to_rgb(int hex_color, t_point *point);
//int		get_pnt_color(t_point *p1, t_point *p2, float pos, int len);
void	paint_square(t_cube *cube);
void	draw_minimap(t_data *data);
//void	vertical_lines(t_data *data);
//void	horizontal_lines(t_data *data);
//void	draw_lines(t_point *p1, t_point *p2, t_data *data, int i);


// utils.c
void	clean_screen(t_data *data);
int		get_slope(int p1, int p2);
double	get_rad(double deg);
float	get_average(t_data *data, int t);
void	get_map_center(t_data *data);


// error.c
int		fd_error(int fd);
int		args_error(void);
void	ft_free_map(t_cube **matrix);
