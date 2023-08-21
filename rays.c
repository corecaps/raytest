//
// Created by corecaps on 27/07/23.
//

#include "raycast.h"
void draw_rays(t_data *data){
    t_color ray_color = {0x00FF00};
    t_color ceil_color = {0xb000b0};
    t_color floor_color = {0x300030};
    int grid_size = WIDTH / GRID_WIDTH;
    t_point pos = {data->player->pos.x / grid_size, data->player->pos.y/grid_size};
    for (int x = 0; x< WIDTH;x++) {
        double cameraX = 2 * x / (double)WIDTH - 1;
        t_point ray_dir = {data->player->dir_vector.x + data->player->plane_vector.x * cameraX, data->player->dir_vector.y + data->player->plane_vector.y * cameraX};
        int MapX = (int)pos.x;
        int MapY = (int)pos.y;
        t_point sideDist;
        t_point deltaDist = {fabs(1 / ray_dir.x), fabs(1 / ray_dir.y)};
        double perpWallDist;
        int stepX;
        int stepY;
        int hit = 0;
        int side;
        if (ray_dir.x < 0)
        {
            stepX = -1;
            sideDist.x = (pos.x - MapX) * deltaDist.x;
        }
        else
        {
            stepX = 1;
            sideDist.x = (MapX + 1.0 - pos.x) * deltaDist.x;
        }
        if (ray_dir.y < 0)
        {
            stepY = -1;
            sideDist.y = (pos.y - MapY) * deltaDist.y;
        }
        else
        {
            stepY = 1;
            sideDist.y = (MapY + 1.0 - pos.y) * deltaDist.y;
        }
        while (hit == 0)
        {
            if (sideDist.x < sideDist.y)
            {
                sideDist.x += deltaDist.x;
                MapX += stepX;
                side = 0;
            }
            else
            {
                sideDist.y += deltaDist.y;
                MapY += stepY;
                side = 1;
            }
            if (data->map[MapY][MapX] > 0)
                hit = 1;
        }
        draw_line(data, ray_color, (t_point){pos.x * grid_size, pos.y * grid_size}, (t_point){MapX * grid_size, MapY * grid_size});
        if (side == 0)
            perpWallDist = sideDist.x - deltaDist.x;
        else
            perpWallDist = sideDist.y - deltaDist.y;
        int lineHeight = (int)(HEIGHT / perpWallDist);
        int drawStart = -lineHeight / 2 + HEIGHT / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + HEIGHT / 2;
        if (drawEnd >= HEIGHT)
            drawEnd = HEIGHT - 1;
        if (side == 1) {
            ray_color.s_rgb.b = 0xF0 - perpWallDist * 10;
            ray_color.s_rgb.g = 0xF0 - perpWallDist * 10;
            ray_color.s_rgb.r = 0xF0 - perpWallDist * 10;
        } else {
            ray_color.s_rgb.b = 0xFF - perpWallDist * 10;
            ray_color.s_rgb.g = 0xFF - perpWallDist * 10;
            ray_color.s_rgb.r = 0xFF - perpWallDist * 10;
        }
        draw_line(data,ceil_color, (t_point){x + OFFSET_3D, 0}, (t_point){x + OFFSET_3D, drawStart});
        draw_line(data, ray_color, (t_point){x + OFFSET_3D, drawStart}, (t_point){x+OFFSET_3D, drawEnd});
        draw_line(data, floor_color, (t_point){x + OFFSET_3D, drawEnd}, (t_point){x + OFFSET_3D, HEIGHT});
    }
}