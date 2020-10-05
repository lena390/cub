/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map_c3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 19:32:00 by miphigen          #+#    #+#             */
/*   Updated: 2020/10/04 19:35:55 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//int	mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color);

void	change_direction(t_map *map, double angle)
{
	double a;

	a = map->hero_direction;
	a += angle;

	if (a >= M_PI * 2)
		a -= (M_PI * 2);
	else if (a < 0)
		a += (M_PI * 2);
	if (a == M_PI_2 || a == M_PI_2 * 3)
		a += (ROTATION_SPEED * 0.75);
	map->hero_direction = a;
}

char	move_on(t_map *map, double x, double y, int scale)
{
	if (map->maze[(int)(y / scale)][(int)(x / scale)] == '1')
		return 0;//добавить распознавалку о стороне света
	else if (map->maze[(int)(y / scale)][(int)(x / scale)] == '2')
		return 2;
	else 
		return 10;
}

void	swap_double(double *a, double *b)
{
	double c;

	c = *a;
	*a = *b;
	*b = c;
}

void	mh_correct_values(double angle, double *x, double *y)//
{
	if (angle > 0 && angle < M_PI)
		*y = *y * -1;
	if (angle > M_PI_2 && angle < M_PI_2 * 3)
		*x = *x * -1;
	if (angle == 0 || angle == M_PI)
	{
		*x = angle == 0 ? STEP : -STEP;
		*y = 0;
	}
	else if (angle == M_PI_2 || angle == M_PI_2 * 3)
	{
		*x = 0;
		*y = angle == M_PI_2 ? -STEP : STEP;
	}
}

void	move_hero(t_map *map, double angle)
{
	double	x;
	double	y;

	if (angle < 0)
		angle += (M_PI) * 2;
	else if (angle >= M_PI * 2)
		angle -= (M_PI * 2);
	x = fabs(cos(angle)) * STEP;
	y = fabs(sin(angle)) * STEP;
	mh_correct_values(angle, &x, &y);
	x += map->hero_x;
	y += map->hero_y;
	if (move_on(map, x, y, map->scale))
	{
		map->hero_x = x;
		map->hero_y = y;
	}
//	printf("hero_new_location: %f %f\n", x, y);
}

int	process_key(int key, t_map *map)
{
	//printf("key = %d direction = %f\n", key, map->hero_direction);
	if (key == 0 || key == 97)
		move_hero(map, map->hero_direction + M_PI_2);
	else if (key == 1 || key == 115 || key == 65364)
		move_hero(map, map->hero_direction + M_PI);
	else if (key == 2 || key == 100)
		move_hero(map, map->hero_direction - M_PI_2);
	else if (key == 13 || key == 119 || key == 65362)
		move_hero(map, map->hero_direction);
	else if (key == 123 || key == 65361)
		change_direction(map, ROTATION_SPEED);
	else if (key == 124 || key == 65363)
		change_direction(map, -ROTATION_SPEED);
	else if (key == 65307)
		set_error_and_exit(NULL, map);
	else
		return (0);
	draw_3d_image(map);
	return (0);
}

void	set_new_coordinates(t_map *map)
{
	map->scale = map->res_width/map->maze_width < map->res_height/map->maze_height ?
				map->res_width/map->maze_width : map->res_height/map->maze_height;	
	map->hero_x *= map->scale;
	map->hero_y *= map->scale;

}

void	check_resolution(t_map *map)
{
	int		x_screen_size;
	int		y_screen_size;
	
	mlx_get_screen_size(g_mlx_ptr, &x_screen_size, &y_screen_size);
	map->res_width = map->res_width > x_screen_size ? x_screen_size : map->res_width;
	map->res_height = map->res_height > y_screen_size ? y_screen_size : map->res_height;	
}

void	render_map(t_map *map)
{
	g_mlx_ptr = mlx_init();
	check_resolution(map);
	set_new_coordinates(map);	
	g_win_ptr = mlx_new_window(g_mlx_ptr, map->res_width, map->res_height, "Hello raycaster");
	new_image(&map->img, map->maze_width * (map->scale / 4), map->maze_height * (map->scale / 4));
	draw_3d_image(map);
	save_in_bmp(map->img2);
	mlx_hook(g_win_ptr, 2, 1L<<0, process_key, map);
	mlx_hook(g_win_ptr, 17, 1L<<17, set_error_and_exit, NULL);
	mlx_loop(g_mlx_ptr);
}
