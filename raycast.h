/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arkanoid.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 23:50:53 by jgarcia           #+#    #+#             */
/*   Updated: 2023/02/15 23:58:23 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARKANOID_H
# define ARKANOID_H
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <time.h>
# include <string.h>
# include <math.h>
# include <limits.h>
#include <fcntl.h>
# define BUFFER_SIZE 2048
# define RADIAN 0.0174532925
# define PI 3.14159265359
# define WIDTH 600
# define OFFSET_3D 600
# define HEIGHT 600
# define TWIDTH 1200
# define GRID_WIDTH 20
# define GRID_HEIGHT 20


typedef struct s_point
{
	double x;
	double y;
} t_point;

typedef  struct s_int_point
{
    int x;
    int y;
} t_int_point;

typedef struct s_rgb
{
	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char t;
}t_rgb;

typedef union u_color
{
	int		color;
	t_rgb			s_rgb;
} t_color;

typedef struct player {
    t_point pos;
    double angle;
    double fov;
    double size;
}t_player;

typedef struct s_buffer
{
	void	*img;
	char 	*address;
	int 	bit_per_pixel;
	int 	line_length;
	int 	endian;
} t_buffer;

typedef struct s_data
{
	void	*mlx;
	void	*mlx_win;
	t_buffer	*img_buffer;
	t_player	*player;
    int         map[GRID_WIDTH][GRID_HEIGHT];
	long		last_frame;
} t_data;

int		render(t_data *data);
int		key_pressed(int keycode, t_data *data);
int     my_mlx_pixel_put(t_buffer *data, t_color color, t_int_point coord);
void draw_line(t_data *data, t_color color, t_point from, t_point to);
int ft_abs(int n);
void	clear_buffer(t_data *data);
void draw_player(t_data *data);
void fill_rectangle(t_data *data, t_color color, t_point top_left, t_point bottom_right);
void draw_rays(t_data *data);
t_point calc_point(t_point from, double angle, double distance);
#endif