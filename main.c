/* ************************************************************************** */
/*                                                4                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 23:50:13 by jgarcia           #+#    #+#             */
/*   Updated: 2023/02/15 23:50:48 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
void fill_array_from_file(t_data *data, const char *filename) {
    int fd = open(filename, O_RDONLY);
    char buffer[BUFFER_SIZE];
    int len;

    if (fd == -1) {
        printf("Failed to open file %s\n", filename);
        return;
    }


    char* lines[GRID_HEIGHT];
    int i = 0, lineCount = 0;
    while ((len = read(fd, buffer, BUFFER_SIZE - 1)) > 0) {
        buffer[len] = '\0';
        char *line = strtok(buffer, "\n");

        while (line) {
            lines[lineCount] = malloc(strlen(line) + 1);
            strcpy(lines[lineCount], line);
            lineCount++;
            line = strtok(NULL, "\n");
        }
    }

    for (i = 0; i < lineCount; i++) {
        char *num = strtok(lines[i], ",");
        int j = 0;
        while (num) {
            data->map[i][j] = atoi(num);
            j++;
            num = strtok(NULL, ",");
        }
        free(lines[i]);
    }
    for (int k = 0; k < GRID_HEIGHT; k++) {
        for (int l = 0; l < GRID_WIDTH; l++) {
            printf("%d ", data->map[k][l]);
        }
        printf("\n");
    }
    close(fd);
}

int main(void)
{
	t_data	*data;

	data = malloc(sizeof (t_data));
	if (!data)
		return (1);
	data->img_buffer = malloc(sizeof(t_buffer));
	if (!data->img_buffer)
		return (1);
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx,TWIDTH,HEIGHT,"RAYCAST");
	data->img_buffer->img = mlx_new_image(data->mlx,
										  TWIDTH +  1,
										  HEIGHT + 1);
	data->img_buffer->address = mlx_get_data_addr(data->img_buffer->img,
												  &data->img_buffer->bit_per_pixel,
												  &data->img_buffer->line_length,
												  &data->img_buffer->endian);
    fill_array_from_file(data, "map.txt");
    data->player = malloc(sizeof (t_player));
	data->player->pos.x = (double)HEIGHT /2;
	data->player->pos.y = (double) WIDTH /2;
    data->player->angle = 0;
    data->player->size = 10;
    data->player->fov = 60;
//	printf("brick hitbox start x: %f end x: %f start y: %f end y: %f",data->brick_hitbox.start_x,data->brick_hitbox.end_x,data->brick_hitbox.start_y,data->brick_hitbox.end_y);
	mlx_hook(data->mlx_win, 2, 1L << 0, key_pressed, data);
	mlx_loop_hook(data->mlx,render,data);
	mlx_loop(data->mlx);
//	mlx_destroy_image(data->mlx,data->img_buffer->img);
//	free(data->img_buffer);
//	mlx_destroy_window(data->mlx,data->mlx_win);
//	mlx_destroy_display(data->mlx);
//	free(data->mlx);
//	free(data);
	return (0);
}