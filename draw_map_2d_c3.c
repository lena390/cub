/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_2d_c3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 19:18:01 by miphigen          #+#    #+#             */
/*   Updated: 2020/09/28 15:57:21 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_012(t_img *img, int x, int y, int scale, int color)
{
	int	i;
	int	j;

	y *= scale;
	x *= scale;
	i = 0;
	while (++i < scale)
	{
		j = 0;
		while (++j < scale)
			img_pixel_put(img, x + i, y + j, color);
	}
}

void	swap(int *a, int *b)
{
	int c;

	c = *a;
	*a = *b;
	*b = c;
}

void	_create_ray(t_img *img, int x0, int y0, int angle, t_map *map)
{
	int		x1;
	int		y1;
	int		i;
	int		x;
	int		y;
	double	tg;

	printf("create_ray() angle = %d\n", angle);
	x1 = 0;
	y1 = 0;
	if (angle < 0)
		angle += 360;
	else if (angle >= 360)
		angle -= 360;
	i = -1;
	while (++i > -1)
	{
		x = i;
		y = floor(fabs(x1 * tan(angle / (180.0 / M_PI))));	
		if (angle == 0 || angle == 180)
			y = 0;
		else if (angle == 90 || angle == 270)
		{	
			x = 0;
			y = angle == 270 ? i : -i;
		}
		else if (angle > 0 && angle < 180)
			y = -y;
		if (angle > 90 && angle < 270)
			x = -x;
		x = (x0 + x);
		y = (y0 + y);
		if (y / map->scale >= map->maze_height || x / map->scale >= map->maze_width ||
			y / map->scale < 0 || x < map->scale | map->maze[y / map->scale][x / map->scale] != '0')
			break;
		else
		{
			x1 = x;
			y1 = y;
		}
		
		if (angle != map->hero_direction)
			img_pixel_put(img, x1, y1 , 0xffffff);
		else
			img_pixel_put(img, x1, y1 , 0xff0000);

	}
	int 	steep;
//	int		x;
//	int		y;
	float	t;
/*
	steep = 0;
	if ((int)fabs(x1 - x0) < (int)fabs(y1 - y0))
	{
		swap(&x0, &y0);
		swap(&x1, &y1);
		steep = 1;
	}
	if (x0 > x1)
	{
		swap(&x0, &x1);
		swap(&y0, &y1);
	}
	x = x0;
	while (x <= x1)
	{
		t = (x - x0) / (float)(x1 - 0);
		y = y0 * (1.0 - t) + y1 * t;
		if (steep)
			img_pixel_put(img, y, x, 0xffffff);
		else
			img_pixel_put(img, x, y, 0xffffff);
		x++;
	}
*/
}

void	draw_line(t_map *map, double x1, double y1, int steep)
{
	double	x0;
	double	y0;
	double	x;
	double	y;
	double	t;

	steep = 0;
	x0 = map->hero_x;
	y0 = map->hero_y;
	if ((fabs(x1 - x0)) < (fabs(y1 - y0)))
	{
		swap_double(&x0, &y0);
		swap_double(&x1, &y1);
		steep = 1;
	}
	if (x0 > x1)
	{
		swap_double(&x0, &x1);
		swap_double(&y0, &y1);
	}
	x = x0;
	while (x <= x1)
	{
		t = (x - x0) / (float)(x1 - 0);
		y = y0 * (1.0 - t) + y1 * t;
		if (steep)
			img_pixel_put(map->img2, y, x, 0xff0000);
		else
			img_pixel_put(map->img2, x, y, 0xff0000);
		x++;
	}
}

void	create_ray(t_map *map, double angle)
{
//	printf("create_ray() angle = %d\n", angle);
	double	x1;
	double	y1;
	double	x;
	double	y;
	int		i;

	if (angle < 0)
		angle += (M_PI) * 2;
	else if (angle >= M_PI * 2)
		angle -= (M_PI * 2);
	if (angle == 0 || angle == M_PI_2 || angle == M_PI || angle == M_PI_2 * 3)
		angle += M_PI / 180;
	i = 0;
	x1 = 0;
	y1 = 0;
	while (++i)
	{
		x = fabs(cos(angle)) * STEP * i;
		y = fabs(sin(angle)) * STEP * i;
		mh_correct_values(angle, &x, &y);
		if (wall_ahead(map, x + map->hero_x, y + map->hero_y))
			break ;
		else
	 	{
			x1 = x;
			y1 = y;
		}
	}
	draw_line(map, map->hero_x + x1, map->hero_y + y1, 0);
}

void	draw_rays(t_img *img, t_map *map)
{
	double	d_min;
	double	d_max;
	
	d_min = map->hero_direction - ANGLE_OV / 2;
	d_max = map->hero_direction + ANGLE_OV / 2;
	while (d_min < d_max)
	{
		create_ray(map, d_min);
		d_min += M_PI / 180;
	}
}

void	draw_hero(t_img *img, int x, int y)
{
	int		i;
	int		j;
	
	i = -8;
	while (++i < 8)
	{
		j = -3;
		while (++j < 3)
		{	
			img_pixel_put(img, x + i, y + j, 0xff0000);
			img_pixel_put(img, x + j, y + i, 0xff0000);
		}
	}
}

void	draw_check_pattern(t_img *img, int i, int length, char c)
{
	int j;

	j = -1;
	if (c == 'h')
	{
		while (++j < length)
			img_pixel_put(img, j, i, 0);
	}
	else if (c == 'v')
	{
		while (++j < length)
			img_pixel_put(img, i, j, 0);
	}
}

void	draw_map_2d(t_map *map)
{
	int		i;
	int		j;
	char	**maze;
	int		color;

	maze = map->maze;
	i = -1;
	while (++i < map->maze_height)
	{
		j = -1;
		while (maze[i][++j] != '\0')
		{
			char c = maze[i][j];
			if (c == '1')
				draw_012(&map->img, j, i, map->scale, 0xffffff);
			else if (c == '2')
				draw_012(&map->img, j, i, map->scale, 0xfff000);
			else if (c == '0')
				draw_012(&map->img, j, i, map->scale, 0x777777);
		}
	}
	i = map->scale;
	//рисую сетку
	while (i < map->img.height)
	{	
		draw_check_pattern(&map->img, i, map->img.width, 'h');
		i += map->scale;
	}
	i = map->scale;
	while (i < map->img.width)
	{	
		draw_check_pattern(&map->img, i, map->img.height, 'v');
		i += map->scale;
	}
	draw_hero(&map->img, map->hero_x, map->hero_y);
	draw_rays(&map->img, map);
//	create_ray(map, map->hero_direction);
//	put_image_to_window(&map->img, 0, map->res_height / 4 * 3 );
}
