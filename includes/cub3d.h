/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:40:54 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/06/07 14:42:13 by jrocha-v         ###   ########.fr       */
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

// TEXT COLORS
# define RESET "\033[0m"
# define BOLD "\033[1m"
# define FAINT "\033[2m"
# define ITALIC "\033[3m"
# define ULINE "\033[4m"
# define SBLINK "\033[5m"
# define FBLINK "\033[6m"
# define REVCOL "\033[7m"
# define HIDDEN "\033[8m"
# define CROSS "\033[9m"
# define BLACK "\033[1;30m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"

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

// WINDOW SETTINGS
//# define WIN_W 1024
//# define WIN_H 768
# define WIN_W 800
# define WIN_H 600

// GAME SETTINGS
//# define data->mm_scale 0.1
# define SIZE 64.0
# define FOV_ANG 1.047197551
# define NUM_RAYS WIN_W
# define CLS_MARGIN 10.0
# define MV_SPD 2.5
# define ROT_SPD 1.5

typedef struct s_data	t_data;
typedef struct s_map	t_map;

typedef enum e_direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	FLOOR_RGB,
	CEILING_RGB,
}	t_direction;

typedef enum e_tile
{
	FLOOR,
	WALL,
	PLAYER,
}	t_tile;

typedef enum e_color
{
	R,
	G,
	B,
}	t_color;

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
	int			map_w;
	int			map_h;
	double		mm_scale;
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
	t_map		*og_map;
}	t_data;

typedef struct s_map_list
{
	char				*row;
	struct s_map_list	*next;
}	t_map_list;

typedef struct s_map
{
	char		*north_wall;
	char		*south_wall;
	char		*east_wall;
	char		*west_wall;
	int			*floor;
	int			*ceiling;
	int			*starting_position;
	t_direction	starting_direction;
	char		**map_grid;
	t_map_list	*map_list;
}	t_map;

// init.c
void				process_map(char *file_name, t_data *data, t_map *map);

// events.c
int					free_game(t_data *data);
int					key_release(int key, t_data *data);
int					key_press(int key, t_data *data);
void				input_router(t_data *data);

// minimap.c
void				draw_minimap(t_data *data);
void				draw_direction(t_data *data);
void				process_minimap(t_data *data);

// player.c
enum e_cubeStart	get_player_start_dir(char dir, t_data *data);
t_cube				point_cube_position(t_data *data, double x, double y);
void				set_player_pos(t_data *data);

// player_move.c
void				move_player(t_data *data, int key);

// draw_utils.c
int					rgb_to_int(int *color);
void				put_pixel(t_img *img, int x, int y, int color);
void				paint_square(t_cube *cube, int start_x, int start_y,
						double scale);
void				draw_lines(t_point *p1, t_point *p2, t_data *data, int i);

// raycast.c
void				cast_rays(t_data *data);
void				draw_rays(t_data *data);

// raycasting_dda.c
void				vertical_grid_hit(t_data *data, t_rays *rays);
void				horizontal_grid_hit(t_data *data, t_rays *rays);

// render.c
int					get_txt_pxl(t_img *img, int x, int y);
void				render_walls(t_data *data, int i, int j);

// utils.c
double				wrap_angle(double angle);
void				clean_screen(t_data *data);
int					get_slope(int p1, int p2);

// error.c
int					fd_error(int fd);
int					args_error(void);
void				ft_error_exit(char *msg, t_data *data);

/******************     PARSER    ************/
// free_mem.c
void				free_map_list(t_map_list *list);
void				free_map(t_map *map);
void				ft_perror_shutdown(char *str, int error, t_map *map);
void				ft_rgb_perror_shutdown(char *str, t_map *map, \
						int *rgb, char**rgb_str);

//map_checkers_1.c
void				map_checker(t_map *map);

// map_checkers_2.c
bool				is_map_closed(t_map *map);

// visual_getters.c
char				*set_direction(t_direction dir_code);
char				*get_texture_path(t_map *map, t_direction dir_code, int i);
int					*get_rgb(t_map *map, t_direction dir_code);

// map_creators.c
t_map_list			*create_map_list_from_fd(int map_fd, t_map *map);
char				**create_map_grid_from_list(t_map *map);
void				reset_map_grid(t_map *map);

// map_parameters_checker.c
bool				check_for_repeated_texture_definitions(t_map *map, \
						t_direction dir_code);
bool				check_for_repeated_color_definitions(t_map *map, \
						t_direction dir_code);

// parser.c
bool				is_file_extension_correct(char *str);
void				no_map_error(void);
t_map				*parse_map(char *map_file);

// player_utils.c
t_direction			starting_direction(t_map *map);
int					*starting_coordinate(t_map *map);

// printers.c
void				list_printer(t_map_list *map_list);
void				grid_printer(char **grid);
void				map_struct_printer(t_map *map);

// struct_init.c
void				map_init(t_map	*map);
void				map_fetch_struct_info(t_map	*map);

#endif
