/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:37:18 by olardeux          #+#    #+#             */
/*   Updated: 2025/02/03 14:14:14 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

# define HEIGHT 540
# define WIDTH 960

# define MINIMAP_SIZE 10

# define PI 3.14159265358979323846
# define FOV PI / 3
# define SPEED 0.1
# define ROT_SPEED 0.31 / 2
# define SENSITIVITY 0.005

# define SOUTH PI / 2
# define NORTH 3 * PI / 2
# define EAST 0
# define WEST PI

typedef struct s_map
{
	int			**map;
	int			width;
	int			height;
	int			floor_color;
	int			ceiling_color;
	int			minimap;
}				t_map;

typedef struct s_ray
{
	int			map_x;
	int			map_y;
	double		ray_angle;
	double		ray_dirx;
	double		ray_diry;
	double		stepx;
	double		stepy;
	double		distx;
	double		disty;
	double		delta_distx;
	double		delta_disty;
	double		wall_dist;
}				t_ray;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir;
}				t_player;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_texture
{
	t_img		north;
	t_img		south;
	t_img		east;
	t_img		west;
}				t_texture;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_player	player;
	t_map		map;
	t_ray		ray;
	t_texture	texture;
}				t_data;

void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
void			draw_floor(t_data *data);
void			draw_ceiling(t_data *data);
void			draw_walls(t_data *data);
void			draw_map(t_data *data);

void			move_forward(t_data *data, int keycode);
void			move_sideways(t_data *data, int keycode);

int				init_texture(t_data *data);

#endif