/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_key_c3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 21:03:54 by miphigen          #+#    #+#             */
/*   Updated: 2020/10/22 17:29:57 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		a += ((M_PI / 90) * 0.75);
	g_map->hero_direction = a;
}

void	mh_correct_values(double angle, double *x, double *y)
{
	if (angle > M_PI_2 && angle < M_PI_2 * 3)
		*x = *x * -1;
	if (angle == 0 || angle == M_PI)
		*x = angle == 0 ? STEP : -STEP;
	else if (angle == M_PI_2 || angle == M_PI_2 * 3)
		*x = 0;
}

void	move_hero(double angle)
{
	double	x;
	double	y;
	int		scale;

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
	scale = g_map->scale;
	int y_coord = (int)floor(y / scale);
	int x_coord = (int)floor(x / scale);
	if (g_map->maze[y_coord][x_coord] != '1')
	{
		g_map->hero_x = x;
		g_map->hero_y = y;
	}
}

int		process_key(int key)
{
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
