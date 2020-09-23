/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map_c3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 19:32:00 by miphigen          #+#    #+#             */
/*   Updated: 2020/09/22 23:24:15 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//int	mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color);

void	change_direction(t_map *map, int angle)
{
	
	map->hero_direction += angle;
	map->hero_direction >= 360 ? map->hero_direction %= 360 : 0;
	map->hero_direction < 0 ? map->hero_direction += 360 : 0;
}

void	move_hero(t_map *map, int angle, int step)
{
	int		x0;
	int		y0;

	if (angle < 0)
		angle += 360;
	else if (angle >= 360)
		angle -= 360;
	x0 = ceil(fabs(cos(angle / (180.0 / M_PI)) * (double)step));
	y0 = ceil(fabs(x0 * tan(angle / (180.0 / M_PI))));
	if (angle > 0 && angle < 180)
		y0 = -y0;
	if (angle > 90 && angle < 270)
		x0 = -x0;
	if (angle == 0 || angle == 180)
	{
		x0 = angle == 0 ? step : -step;
		y0 = 0;
	}
	else if (angle == 90 || angle == 270)
	{
		x0 = 0;
		y0 = angle == 90 ? -step : step;
	}
	if (map->maze[(map->hero_y + y0)/map->scale][(map->hero_x + x0) / map->scale] == '0')
	{
		map->hero_x += x0;
		map->hero_y += y0;
	}
}

int	process_key(int key, t_map *map)
{
	int		step;

//	printf("key = %d\n", key);
	step = 2;
//	printf("%d\n", step);
	if (key == 0 || key == 97)
		move_hero(map, map->hero_direction + 90, step);
	else if (key == 1 || key == 115 || key == 65364)
		move_hero(map, map->hero_direction + 180, step);
	else if (key == 2 || key == 100)
		move_hero(map, map->hero_direction - 90, step);
	else if (key == 13 || key == 119 || key == 65362)
		move_hero(map, map->hero_direction, step);
	else if (key == 123 || key == 65361)
		change_direction(map, 1);
	else if (key == 124 || key == 65363)
		change_direction(map, -1);
	else if (key == 65307)
		set_error_and_exit(NULL, map);
	else
		return (0);
	draw_map_3d(map);
	//draw_map_2d(map);
	return (0);
}

void	render_map(t_map *map)
{
	int		x_screen_size;
	int		y_screen_size;
	
	g_mlx_ptr = mlx_init();
	mlx_get_screen_size(g_mlx_ptr, &x_screen_size, &y_screen_size);
	map->res_width = map->res_width > x_screen_size ? x_screen_size : map->res_width;
	map->res_height = map->res_height > y_screen_size ? y_screen_size : map->res_height;
	g_win_ptr = mlx_new_window(g_mlx_ptr, map->res_width, map->res_height, "Hello raycaster");
	new_image(&map->img, map->res_width / 4, map->res_height / 4);
	map->img2 = malloc(sizeof(t_img));//free()!!	
	map->scale = map->img.width/map->maze_width < map->img.height/map->maze_height ?
		map->img.width/map->maze_width : map->img.height/map->maze_height;
	map->hero_x *= map->scale;
	map->hero_y = map->hero_y * map->scale;	
	draw_map_3d(map);
	//draw_map_2d(map);
	save_in_bmp(map->img2);
	mlx_hook(g_win_ptr, 2, 1L<<0, process_key, map);
	mlx_hook(g_win_ptr, 17, 1L<<17, set_error_and_exit, NULL);
//	mlx_hook(g_win_ptr, )
	mlx_loop(g_mlx_ptr);
}
