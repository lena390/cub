/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_2d_c3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 19:18:01 by miphigen          #+#    #+#             */
/*   Updated: 2020/09/23 13:56:47 by miphigen         ###   ########.fr       */
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

void	draw_ray(t_img *img, int x0, int y0, int angle, t_map *map)
{
	double	tg;
	int		x1;
	int		y1;
	int		i;

	if (angle < 0)
		angle += 360;
	else if (angle >= 360)
		angle -= 360;
	tg = tan(angle / (180.0 / M_PI));
	i = -1;
	while (++i > -1)
	{
		x1 = i;
		y1 = floor(fabs(x1 * tg));	
		if (angle == 0 || angle == 180)
			y1 = 0;
		else if (angle == 90 || angle == 270)
		{	
			x1 = 0;
			y1 = angle == 270 ? i : -i;
		}
		else if (angle > 0 && angle < 180)
			y1 = -y1;
		if (angle > 90 && angle < 270)
			x1 = -x1;
		x1 = (x0 + x1);
		y1 = (y0 + y1);
		if (y1 / map->scale >= map->maze_height || x1 / map->scale >= map->maze_width ||
			y1 / map->scale < 0 || x1 < map->scale | map->maze[y1 / map->scale][x1 / map->scale] != '0')
			break;
/*		
		if (angle != map->hero_direction)
			img_pixel_put(img, x1, y1 , 0);
		else
			img_pixel_put(img, x1, y1 , 0xff0000);
*/
	}
	int 	steep;
	int		x;
	float	t;

	steep = 0;
	if ((int)fabs(x1 - x0) < (int)fabs(y1 - y0))
	{
		swap(x0, y0);
		swap(x1, y1);
		steep = 1;
	}
	if (x1 > x1)
	{
		swap(x0, x1);
		swap(y0. y1);
	}
	x = x0 - 1;
	while (++x < x1)
	{
		
	}

}

void	draw_rays(t_img *img, t_map *map)
{
	int d_min;
	int	d_max;
	d_min = map->hero_direction - ANGLE_OV / 2;
	d_max = map->hero_direction + ANGLE_OV / 2;
	while (++d_min < d_max)
	{
		draw_ray(img, map->hero_x, map->hero_y, d_min, map);
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

void	draw_line(t_img *img, int i, int length, char c)
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
		draw_line(&map->img, i, map->img.width, 'h');
		i += map->scale;
	}
	i = map->scale;
	while (i < map->img.width)
	{	
		draw_line(&map->img, i, map->img.height, 'v');
		i += map->scale;
	}
	draw_hero(&map->img, map->hero_x, map->hero_y);
//	draw_rays(&map->img, map);
	draw_ray(&map->img, map->hero_x, map->hero_y, map->hero_direction, map);
//	put_image_to_window(&map->img, 0, map->res_height / 4 * 3 );
}
