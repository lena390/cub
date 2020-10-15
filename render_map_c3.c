/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map_c3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 19:32:00 by miphigen          #+#    #+#             */
/*   Updated: 2020/10/15 21:29:46 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//int	mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color);

void	change_direction(double angle)
{
	double a;

	g_map->status = 10;
	a = g_map->hero_direction;
	a += angle;

	if (a >= M_PI * 2)
		a -= (M_PI * 2);
	else if (a < 0)
		a += (M_PI * 2);
	if (a == M_PI_2 || a == M_PI_2 * 3)
		a += (ROTATION_SPEED * 0.75);
	g_map->hero_direction = a;
}

char	mh_move_on(double x, double y, int scale)
{
	char c;

	c = g_map->maze[(int)floor(y / scale)][(int)floor(x / scale)];
	if (c == '1')
		return (0);
	else
		return (c);
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
//	if (angle > 0 && angle < M_PI)
//		*y = *y * -1;
	if (angle > M_PI_2 && angle < M_PI_2 * 3)
		*x = *x * -1;
	if (angle == 0 || angle == M_PI)
	{
		*x = angle == 0 ? STEP : -STEP;
//		*y = 0;
	}
	else if (angle == M_PI_2 || angle == M_PI_2 * 3)
	{
		*x = 0;
//		*y = angle == M_PI_2 ? -STEP : STEP;
	}
}

void	move_hero(double angle)
{
	double	x;
	double	y;

	g_map->status = 9;
	if (angle < 0)
		angle += (M_PI) * 2;
	else if (angle >= M_PI * 2)
		angle -= (M_PI * 2);
	x = fabs(cos(angle)) * STEP;
	y = -sin(angle) * STEP;
	mh_correct_values(angle, &x, &y);
	x += g_map->hero_x;
	y += g_map->hero_y;
	if (mh_move_on(x, y, g_map->scale))
	{
		g_map->hero_x = x;
		g_map->hero_y = y;
	}
//	printf("hero_new_location: %f %f\n", x, y);
}

int	process_key(int key)
{
//	printf("key = %d direction = %f\n", key, g_map->hero_direction);
	g_map->status = 8;
	if (key == 0 || key == 97)
		move_hero(g_map->hero_direction + M_PI_2);
	else if (key == 1 || key == 115 || key == 65364)
		move_hero(g_map->hero_direction + M_PI);
	else if (key == 2 || key == 100)
		move_hero(g_map->hero_direction - M_PI_2);
	else if (key == 13 || key == 119 || key == 65362)
		move_hero(g_map->hero_direction);
	else if (key == 123 || key == 65361)
		change_direction(ROTATION_SPEED);
	else if (key == 124 || key == 65363)
		change_direction(-ROTATION_SPEED);
	else if (key == 65307)
		set_error_and_exit(NULL);
	else
		return (0);
	draw_3d_image();
	draw_2d_image();
	return (0);
}

void	set_new_coordinates()
{
	g_map->scale = g_map->res_width/g_map->maze_width < g_map->res_height/g_map->maze_height ?
				g_map->res_width/g_map->maze_width : g_map->res_height/g_map->maze_height;	
	g_map->hero_x *= g_map->scale;
	g_map->hero_y *= g_map->scale;

}

void	check_resolution()
{
	int		x_screen_size;
	int		y_screen_size;
	
	mlx_get_screen_size(g_mlx_ptr, &x_screen_size, &y_screen_size);
	g_map->res_width = g_map->res_width > x_screen_size ? x_screen_size : g_map->res_width;
	g_map->res_height = g_map->res_height > y_screen_size ? y_screen_size : g_map->res_height;	
}

void	render_map()
{
	g_map->status = 7;
	g_mlx_ptr = mlx_init();
	check_resolution();
	set_new_coordinates();	
	if (g_map->screenshot_needed == 0)
		g_win_ptr = mlx_new_window(g_mlx_ptr, g_map->res_width, g_map->res_height, "Hello raycaster");
	new_image(&g_map->img, g_map->maze_width * (g_map->scale / 4), g_map->maze_height * (g_map->scale / 4));
	dl_textures();
	draw_3d_image();
	if (g_map->screenshot_needed == 0)
		draw_2d_image();
	mlx_hook(g_win_ptr, 2, 1L<<0, process_key, NULL);
	mlx_hook(g_win_ptr, 17, 1L<<17, set_error_and_exit, NULL);
	mlx_loop(g_mlx_ptr);
}
