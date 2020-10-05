/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d_image_c3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 19:18:01 by miphigen          #+#    #+#             */
/*   Updated: 2020/10/04 19:38:52 by miphigen         ###   ########.fr       */
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

typedef struct	s_line
{
	double		x0;
	double		y0;
	double		x1;
	double		y1;
	int			steep;
}				t_line;

t_line	line_params(double x0, double y0, double x1, double y1)
{
	t_line	l;

	l.x0 = x0;
	l.y0 = y0;
	l.x1 = x1;
	l.y1 = y1;
	l.steep = 0;
	return (l);
}

void	draw_line(t_map *map, t_line l)
{
	double	x;
	double	y;
	double	t;

	l.x0 = map->hero_x / 4;
	l.y0 = map->hero_y / 4;
	if ((fabs(l.x1 - l.x0)) < (fabs(l.y1 - l.y0)))
	{
		swap_double(&l.x0, &l.y0);
		swap_double(&l.x1, &l.y1);
		l.steep = 1;
	}
	if (l.x0 > l.x1)
	{
		swap_double(&l.x0, &l.x1);
		swap_double(&l.y0, &l.y1);
	}
	x = l.x0;
	while (x <= l.x1)
	{
		t = (x - l.x0) / (float)(l.x1 - 0);
		y = l.y0 * (1.0 - t) + l.y1 * t;
		if (l.steep)
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
		x = fabs(cos(angle)) * i;
		y = fabs(sin(angle)) * i;
		mh_correct_values(angle, &x, &y);
		if (move_on(map, x + map->hero_x / 4, y + map->hero_y / 4, map->scale / 4))
			break ;
		else
	 	{
			x1 = x;
			y1 = y;
		}
	}
	draw_line(map, line_params(map->hero_x / 4, map->hero_y / 4,
				map->hero_x / 4 + x1, map->hero_y / 4 + y1));
}

void	draw_rays(t_img *img, t_map *map)
{
	double	d_min;
	double	d_max;
	
	d_min = map->hero_direction - ANGLE_OV / 2;
	d_max = map->hero_direction + ANGLE_OV / 2;
	create_ray(map, d_min);
	create_ray(map, d_max);
}

void	draw_hero(t_map *map, t_img *img, int hero_x, int hero_y)
{
	int	width;
	int	height;
	int	ax;
	int	ay;
	int	bx;
	int	by;

	ax = (int)ceil(cos(map->hero_direction * (map->img.width / map->maze_width)));
	ay = (int)ceil(sin(map->hero_direction * ( map->img.width / map->maze_width)));
	bx = (int)ceil(cos((map->hero_direction + M_PI_4 * 3) * map->img.width / map->maze_width));
	by = (int)ceil(sin((map->hero_direction + M_PI_4 * 3) * map->img.width / map->maze_width));

	draw_line(map, line_params(ax, ay, bx, by));
	//draw_line(map, line_params(map, ax, ay, bx + (ax - bx), by));

	
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

void	draw_2d_image(t_map *map)
{
	int		i;
	int		j;
	char	**maze;
	int		color;
	int		scale;


	maze = map->maze;
	i = -1;
	scale = map->img.width / map->maze_width;
	while (++i < map->maze_height)
	{
		j = -1;
		while (maze[i][++j] != '\0')
		{
			char c = maze[i][j];
			if (c == '1')
				draw_012(&map->img, j, i, scale, 0xffffff);
			else if (c == '2')
				draw_012(&map->img, j, i, scale, 0xfff000);
			else if (c == '0')
				draw_012(&map->img, j, i, scale, 0x777777);
		}
	}
	i = scale;
	while (i < map->img.height)
	{	
		draw_check_pattern(&map->img, i, map->img.width, 'h');
		i += scale;
	}
	i = scale;
	while (i < map->img.width)
	{	
		draw_check_pattern(&map->img, i, map->img.height, 'v');
		i += scale;
	}
//	draw_hero(map, &map->img, (int)map->hero_x / 4, (int)map->hero_y / 4);
//	draw_rays(&map->img, map);
	put_image_to_window(&map->img, 0, map->res_height / 4 * 3 );
}
