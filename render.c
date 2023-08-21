//
// Created by corecaps on 17/02/23.
//

#include "raycast.h"

int render(t_data *data)
{
	clear_buffer(data);
	t_color white = {0xFFFFFF};
    int grid_size_x = WIDTH / GRID_WIDTH;
    int grid_size_y = HEIGHT / GRID_HEIGHT;

    t_color grid_color;
    grid_color.s_rgb.r = (char)40;
    grid_color.s_rgb.g = (char)40;
    grid_color.s_rgb.b = (char)40;
    for (int i = 0; i < GRID_HEIGHT * grid_size_y;i += grid_size_y)
    {
        draw_line(data, grid_color,(t_point) {(double)0, (double)i},(t_point) {(double)WIDTH, (double)i});
    }
    for (int i = 0; i < GRID_WIDTH * grid_size_x;i += grid_size_x)
    {
        draw_line(data, grid_color,(t_point) {(double)i, (double)0},(t_point) {(double)i, (double)HEIGHT});
    }
    for (int i = 0; i < GRID_WIDTH;i++) {
        for (int j = 0; j < GRID_HEIGHT;j ++) {
            if (data->map[j][i] == 1) {
                fill_rectangle(data, grid_color,
                               (t_point) {(double)(i * grid_size_x), (double)(j * grid_size_y)},
                               (t_point) {(double)((i + 1) * grid_size_x), (double)((j + 1) * grid_size_y)});
            }
        }
    }
    draw_line(data, white,(t_point) {(double)WIDTH, (double)0},(t_point) {(double)WIDTH, (double)HEIGHT});
    draw_player(data);
    draw_rays(data);
	mlx_put_image_to_window(data->mlx,
							data->mlx_win,
							data->img_buffer->img,
							0 ,0);
	return (0);
}