//
// Created by corecaps on 17/02/23.
//

#include "raycast.h"

void clamp_player(t_data *data);

int key_pressed(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		mlx_destroy_image(data->mlx,data->img_buffer->img);
		free(data->img_buffer);
		mlx_destroy_window(data->mlx,data->mlx_win);
		mlx_destroy_display(data->mlx);
        free(data->player);
		free(data->mlx);
		free(data);
		exit(0);
	}
	if (keycode == 97 || keycode == 65361)
	{
        t_point old_dir = data->player->dir_vector;
        t_point old_plane = data->player->plane_vector;
        data->player->dir_vector.x = data->player->dir_vector.x * cos(-3 * RADIAN) - data->player->dir_vector.y * sin(-3 * RADIAN);
        data->player->dir_vector.y = old_dir.x * sin(-3 * RADIAN) + data->player->dir_vector.y * cos(-3 * RADIAN);
        data->player->plane_vector.x = data->player->plane_vector.x * cos(-3 * RADIAN) - data->player->plane_vector.y * sin(-3 * RADIAN);
        data->player->plane_vector.y = old_plane.x * sin(-3 * RADIAN) + data->player->plane_vector.y * cos(-3 * RADIAN);

        data->player->angle -= 3;
        if (data->player->angle < 0)
            data->player->angle = 359;
	}
	if (keycode == 100 || keycode == 65363)
	{
        t_point old_dir = data->player->dir_vector;
        t_point old_plane = data->player->plane_vector;
        data->player->dir_vector.x = data->player->dir_vector.x * cos(3 * RADIAN) - data->player->dir_vector.y * sin(3 * RADIAN);
        data->player->dir_vector.y = old_dir.x * sin(3 * RADIAN) + data->player->dir_vector.y * cos(3 * RADIAN);
        data->player->plane_vector.x = data->player->plane_vector.x * cos(3 * RADIAN) - data->player->plane_vector.y * sin(3 * RADIAN);
        data->player->plane_vector.y = old_plane.x * sin(3 * RADIAN) + data->player->plane_vector.y * cos(3 * RADIAN);
        data->player->angle += 3;
        if (data->player->angle > 359)
            data->player->angle = 0;
	}
    if (keycode == 119 || keycode == 65362)
    {
        data->player->pos.x +=	10 * cos(data->player->angle * RADIAN);
        data->player->pos.y +=  10 * (sin(data->player->angle * RADIAN));
        clamp_player(data);
    }
    if (keycode == 115 || keycode == 65364)
    {
        data->player->pos.x -=	cos(data->player->angle * RADIAN) * 10;
        data->player->pos.y -= sin(data->player->angle * RADIAN) * 10;
        clamp_player(data);
    }
	return (0);
}

void clamp_player(t_data *data) {
    if (data->player->pos.x < 0 + (data->player->size * 2))
        data->player->pos.x =(double) (0 + (data->player->size * 2));
    if (data->player->pos.y < 0 + (data->player->size * 2))
        data->player->pos.y = (double)(0 + (data->player->size * 2));
    if (data->player->pos.x > (double)(WIDTH - (data->player->size * 2)))
        data->player->pos.x =(double)( WIDTH - (data->player->size * 2));
    if (data->player->pos.y >(double)( HEIGHT - (data->player->size * 2)))
        data->player->pos.y = (double)(HEIGHT - (data->player->size * 2));
}