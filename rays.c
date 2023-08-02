//
// Created by corecaps on 27/07/23.
//

#include "raycast.h"

void draw_rays(t_data *data)
{
    t_color ray_color = {0x00FF00};
    for (int offset=-30;offset < 31;offset ++)
    {
        t_point ray_pos = {data->player->pos.x, data->player->pos.y};
        double ray_angle = (data->player->angle + offset) * RADIAN;
        int dof = 0;
        double dist_v = 1000000;
        double dist_h = 1000000;
        int grid_size = WIDTH / GRID_WIDTH;
        t_int_point A; // first
        t_int_point inc; // increment
        t_point dest_v;
        t_point dest_h;
        // horizontal
        ray_color = (t_color){0x00FF00};

        if (sin(ray_angle) == 0)
            (void) 0;
        else if (sin(ray_angle) < 0) {
            inc.x = grid_size / tan(ray_angle);
            inc.y = grid_size;
            A.y = (int) (ray_pos.y / grid_size) * grid_size;
            A.x = (int) (data->player->pos.x + (A.y - data->player->pos.y) / tan(ray_angle));
            t_point ray = {A.x, A.y};
            draw_line(data, ray_color, ray_pos, (t_point) {(double) A.x, (double) A.y});
            for (int i = 0; i < 15; i++) {
                t_point tmp = {ray.x, ray.y};
                ray.x -= inc.x;
                ray.y -= inc.y;
                if (ray.x < 0 || ray.y < 0 || ray.x > WIDTH || ray.y > HEIGHT)
                    break;

                if (data->map[(int) (ray.y / grid_size)][(int) (ray.x / grid_size)] == 1) {
                    dist_h = sqrt(pow(ray_pos.x - ray.x, 2) + pow(ray_pos.y - ray.y, 2));
                    dest_h = ray;
                    break;
                }
                draw_line(data, ray_color, tmp, ray);
            }
        } else {
            inc.x = grid_size / tan(ray_angle);
            inc.y = grid_size;
            A.y = (int) ((ray_pos.y / grid_size) + 1) * grid_size;
            A.x = (int) (data->player->pos.x + (A.y - data->player->pos.y) / tan(ray_angle));
            t_point ray = {A.x, A.y};
            draw_line(data, ray_color, ray_pos, (t_point) {(double) A.x, (double) A.y});
            for (int i = 0; i < 8; i++) {
                t_point tmp = {ray.x, ray.y};
                ray.x += inc.x;
                ray.y += inc.y;
                if (ray.x < 0 || ray.y < 0 || ray.x > WIDTH || ray.y > HEIGHT)
                    break;

                if (data->map[(int) (ray.y / grid_size)][(int) (ray.x / grid_size)] == 1) {
                    dist_h = sqrt(pow(ray_pos.x - ray.x, 2) + pow(ray_pos.y - ray.y, 2));
                    dest_h = ray;
                    break;
                }
                draw_line(data, ray_color, tmp, ray);
            }
        }
        // vertical
        ray_color = (t_color){0x0000FF};
        if (cos(ray_angle) == 0)
            (void) 0;
        else if (cos(ray_angle) < 0) {
            inc.y = grid_size * tan(ray_angle);
            inc.x = grid_size;
            A.x = (int) (ray_pos.x / grid_size) * grid_size;
            A.y = (int) (data->player->pos.y + (A.x - data->player->pos.x) * tan(ray_angle));
            t_point ray = {A.x, A.y};
            draw_line(data, ray_color, ray_pos, (t_point) {(double) A.x, (double) A.y});
            for (int i = 0; i < 15; i++) {
                t_point tmp = {ray.x, ray.y};
                ray.x -= inc.x;
                ray.y -= inc.y;
                if (ray.x < 0 || ray.y < 0 || ray.x > WIDTH || ray.y > HEIGHT)
                    break;

                if (data->map[(int) (ray.y / grid_size)][(int) (ray.x / grid_size)] == 1) {
                    dist_v = sqrt(pow(ray_pos.x - ray.x, 2) + pow(ray_pos.y - ray.y, 2));
                    dest_v = ray;
                    break;
                }
                draw_line(data, ray_color, tmp, ray);
            }
        } else {
            inc.y = grid_size * tan(ray_angle);
            inc.x = grid_size;
            A.x = (int) (ray_pos.x / grid_size) * grid_size;
            A.y = (int) (data->player->pos.y + (A.x - data->player->pos.x) * tan(ray_angle));
            t_point ray = {A.x, A.y};
            draw_line(data, ray_color, ray_pos, (t_point) {(double) A.x, (double) A.y});
            for (int i = 0; i < 15; i++) {
                t_point tmp = {ray.x, ray.y};
                ray.x += inc.x;
                ray.y += inc.y;
                if (ray.x < 0 || ray.y < 0 || ray.x > WIDTH || ray.y > HEIGHT)
                    break;

                if (data->map[(int) (ray.y / grid_size)][(int) (ray.x / grid_size)] == 1) {
                    dist_v = sqrt(pow(ray_pos.x - ray.x, 2) + pow(ray_pos.y - ray.y, 2));
                    dest_v = ray;
                    break;
                }
                draw_line(data, ray_color, tmp, ray);
            }
        }
        if (dist_h < dist_v) {

//            printf("dist_h: %f\n", dist_h);
        }else {
            dist_h = dist_v;
//            printf("dist_v: %f\n", dist_v);
        }
        if (dist_h < 1000) {
//            printf("dist_h: %f\n", dist_h);
            double dist_plane = (WIDTH / 2) / - tan(60.0 / 2);
//        double dist_wall = dist_h * cos(ray_angle - data->player->angle);
            double wall_height = (grid_size * 3 / dist_h) * dist_plane;
            double wall_start = (HEIGHT /2 ) - (wall_height *2 );
            double wall_end = (HEIGHT /2 ) + (wall_height * 2);
            int slice_width = (int) (WIDTH / 60);
            t_point top_left_wall = {(offset + 30) * 12 + OFFSET_3D, wall_start};
            t_point bottom_right_wall = {(offset + 30) * 12 + OFFSET_3D + slice_width, wall_end};
            t_color wall_color;
            wall_color.s_rgb.r = (int)(500 - dist_h) % 500 * 255;
            wall_color.s_rgb.g = (int)(500 - dist_h) % 500 * 255;
            wall_color.s_rgb.b = (int)(500 - dist_h) % 500 * 255;
            fill_rectangle(data, wall_color, top_left_wall, bottom_right_wall);
//            printf("Slice from [%d, %d] to [%d, %d]\n", (int) top_left_wall.x, (int) top_left_wall.y,
//                   (int) bottom_right_wall.x, (int) bottom_right_wall.y);
//        draw_line(data, (t_color){0x00FF00}, start, wall);}
        }
    }
}