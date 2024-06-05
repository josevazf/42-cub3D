/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:40:54 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/06/05 14:44:54 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/libft/libft.h"
# include "../libs/minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <limits.h>

# define ERROR 1
# define SUCCESS 0

// Window settings
# define WIN_W 1024
# define WIN_H 768

# define CLR_RED			0xFF0000
# define CLR_ROSYBROWN		0xBC8F8F
# define CLR_GREY			0x808080
# define CLR_PERSIAN		0xCA3433
# define CLR_GREEN			0x00FF00
# define CLR_BLUE			0x0000FF
# define CLR_SILK			0x488AC7
# define CLR_WHITE			0xFFFFFF
# define CLR_BLACK			0x000000
# define CLR_OLIVE			0x808000
# define CLR_TEAL			0x008080
# define CLR_NEON			0xFF10F0

// Game settings
# define MM_SCALE 0.1
# define SIZE 64.0
# define FOV_ANG (double)(60.0 * (M_PI / 180.0))
//# define FOV_ANG 1.0472
# define NUM_RAYS WIN_W
//# define NUM_RAYS 5
# define CLS_MARGIN 10.0
# define MV_SPD 1
# define ROT_SPD (double)(2.0 * (M_PI / 180.0))

typedef struct s_data	t_data;

typedef enum e_texture
{
	NO,
	SO,
	WE,
	EA
}	t_texture;

typedef enum e_cubeType
{
	OPEN,
	CLOSED,
	EMPTY
}	t_cubeType;

typedef enum e_cubeStart
{
	FALSE,
	N,
	S,
	E,
	W
}	t_cubeStart;

typedef struct s_img
{
	void		*img;
	char		*pixel_addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}	t_img;

typedef struct s_key
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			esc;
	int			left;
	int			right;
}	t_key;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}	t_color;

typedef struct s_point
{
	double		x;
	double		y;
	int			clr;
	t_color		rgb;
}	t_point;

typedef struct s_rays
{
	double		height;
	double		distance;
	double		x_hit;
	double		y_hit;
	double		xh_hit;
	double		yh_hit;
	double		xv_hit;
	double		yv_hit;
	double		wall_start;
	double		wall_end;
	bool		hit_vert;
	bool		hwall_hit;
	bool		vwall_hit;
	bool		is_up;
	bool		is_right;
	double		angle;
}	t_rays;

typedef struct s_cube
{
	int				clr;
	int				row;
	int				col;
	t_cubeType		cube_type;
	t_cubeStart		cube_start;
	t_data			*data;
}	t_cube;

typedef struct s_player
{
	double		px;
	double		py;
	double		rot_ang;
	t_cube		c_pos;
	t_data		*data;
}	t_player;

typedef struct s_data
{
	int			err;
	int			x1;
	int			y1;
	int			clr_ceiling;
	int			clr_floor;
	int			map_w;
	int			map_h;
	double		c_pos_x;
	double		c_pos_y;
	char		*txts_path[4];
	char		*map_name;
	void		*mlx_ptr;
	void		*win_ptr;
	bool		init;
	t_rays		*rays;
	t_player	player;
	t_cube		**map;
	t_key		key;
	t_img		txts_img[4];
	t_img		img;
}	t_data;

// main.c

// init.c
void	init_data(t_data *data);
void	get_dimensions(char *file_name, t_data *data);
void	create_map(t_data *data);
void	fill_map(t_cube *map, char *line, t_data *data, int i);
void	process_map(char *file_name, t_data *data);

// events.c
int		free_game(t_data *data);
int		key_release(int key, t_data *data);
int		key_press(int key, t_data *data);
void	input_router(t_data *data);

// minimap.c
void	process_minimap(t_data *data);
void	draw_direction(t_data *data);
void	draw_player(t_data *data);
void	draw_minimap(t_data *data);

// player.c
enum e_cubeStart	get_player_start_dir(char dir, t_data *data);
t_cube				point_cube_position(t_data *data, double x, double y);
void				set_player_pos(t_data *data);

// player_move.c
bool	is_valid_cube(t_data *data, double mx, double my);
void	move_linear(t_data *data, int key);
void	move_strafe(t_data *data, int key);
void	move_rotate(t_data *data, int key);
void	move_player(t_data *data, int key);

// draw_utils.c
void	put_pixel(t_img *img, int x, int y, int color);
void	hex_to_rgb(int hex_color, t_point *point);
void	paint_square(t_cube *cube, int start_x, int start_y);
void	draw_lines(t_point *p1, t_point *p2, t_data *data, int i);
float	get_pnt_position(float z, t_data *data);
int		get_pnt_color(t_point *p1, t_point *p2, float pos, int len);
void	make_gradient(t_data *data, int clr1, int clr2);

//void	vertical_lines(t_data *data);
//void	horizontal_lines(t_data *data);

// raycasting.c
double	distance_between_points(double x1, double y1, double x2, double y2);
void	get_final_hit(t_data *data, t_rays *rays, double h_dist, double v_dist);
void	cast_rays(t_data *data);
void	draw_rays(t_data *data);

// raycasting_utils.c
void	vertical_wall_hit(t_data *data, t_rays *rays, double x_step, double y_step);
void	vertical_grid_hit(t_data *data, t_rays *rays);
void	horizontal_wall_hit(t_data *data, t_rays *rays, double x_step, double y_step);
void	horizontal_grid_hit(t_data *data, t_rays *rays);

// walls.c
void	render_walls(t_data *data, int i, int j);

// utils.c
double	wrap_angle(double angle);
void	clean_screen(t_data *data);
int		get_slope(int p1, int p2);
double	get_rad(double deg);
double	get_deg(double rad);

// error.c
int		fd_error(int fd);
int		args_error(void);
void	ft_free_map(t_cube **matrix);
void	ft_error_exit(char *msg, t_data *data);

#endif
