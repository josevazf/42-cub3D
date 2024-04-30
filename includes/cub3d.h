/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:40:54 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/30 19:03:25 by jrocha-v         ###   ########.fr       */
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

# define WIN_W 1600
# define WIN_H 900

# define CLR_RED			0xFF0000
# define CLR_GREEN			0x00FF00
# define CLR_BLUE			0x0000FF
# define CLR_WHITE			0xFFFFFF
# define CLR_BLACK			0x000000
# define CLR_NEON			0xFF10F0

typedef struct s_img
{
	void	*mlx_img;
	char	*mlx_pixel_addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}	t_color;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		clr;
	t_color	rgb;
}	t_point;

typedef struct s_data
{
	int		win_w;
	int		win_h;
	int		trs_x;
	int		trs_y;
	int		c_pos_x;
	int		c_pos_y;
	void	*mlx_ptr;
	void	*win_ptr;
	char	*map_name;
	t_img	img;
	t_point	**map;
}	t_data;

#endif

// main.c

// events.c
int	esc_key(t_data *data);
int	key_events(int key, t_data *data);

// draw.c
void	put_pixel(t_img *img, int x, int y, int color);
