/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d_image_c3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 19:18:01 by miphigen          #+#    #+#             */
/*   Updated: 2020/10/15 19:48:06 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_012(t_img *img, int x, int y, int scale, int color)
{
	int	i;
	int	j;

	y *= scale;
	x *= scale;
	i = -1;
	while (++i < scale)
	{
		j = -1;
		while (++j < scale)
			img_pixel_put(img, x + i, y + j, color);
	}
//	img_pixel_put(img, x , y, 0);

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

void	draw_line(t_line l, int color)
{
	double	x;
	double	y;
	double	t;

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
			img_pixel_put(&g_map->img, y, x, color);
		else
			img_pixel_put(&g_map->img, x, y, color);
		x++;
	}
}

char	d2_move_on(double x, double y, int scale)
{
	char c;

	c = g_map->maze[(int)(y / scale)][(int)(x /  g_map->img.height / g_map->maze_height)];
	if (c == '1')
		return (0);
	else
		return (c);
}
void	create_ray(double angle)
{
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
	double tg = fabs(tan(angle));
	while (++i)
	{
		x = i;
		y = tg * x;
		mh_correct_values(angle, &x, &y);
		if (!d2_move_on(x + g_map->hero_x / 4, y + g_map->hero_y / 4, g_map->img.width / g_map->maze_width))
			break ;
		else
	 	{
			x1 = x;
			y1 = y;
		}
	}
	draw_line(line_params(g_map->hero_x / 4, g_map->hero_y / 4,
				g_map->hero_x / 4 + x1, g_map->hero_y / 4 + y1), 0);
}

void	draw_rays(t_img *img)
{
	double	d_min;
	double	d_max;
	
	d_min = g_map->hero_direction - ANGLE_OV / 2;
	d_max = g_map->hero_direction + ANGLE_OV / 2;
	while (d_max >= d_min)
	{	
		create_ray(d_max);
		d_max -= (M_PI / 3) / 60; 
	}
}

void	draw_hero(t_img *img, double hero_x, double hero_y)
{
	int x = (int)(hero_x / 4);
	int y = (int)(hero_y / 4);
	int i = -1;
	while (++i < 5)
	{
		int j = -1;
		while (++j < 5)
			img_pixel_put(img, x + i, y + j, 0);			
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

void	draw_2d_image()
{
	int		i;
	int		j;
	char	**maze;
	int		color;
	int		scale;


	maze = g_map->maze;
	i = -1;
	scale = g_map->img.width / g_map->maze_width;
	while (++i < g_map->maze_height)
	{
		j = -1;
		while (maze[i][++j] != '\0')
		{
			char c = maze[i][j];
			if (c == '1')
				draw_012(&g_map->img, j, i, scale, 0x777777);
			else if (c == '2')
				draw_012(&g_map->img, j, i, scale, 0xfff000);
			else if (c == '0')
				draw_012(&g_map->img, j, i, scale, 0xfffffff);
		}
	}
	draw_hero(&g_map->img, g_map->hero_x, g_map->hero_y);
	put_image_to_window(&g_map->img, 0, 0);
}
