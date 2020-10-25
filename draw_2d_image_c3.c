/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d_image_c3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 19:18:01 by miphigen          #+#    #+#             */
/*   Updated: 2020/10/21 12:56:56 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_012(t_img *img, int x, int y, int color)
{
	int	i;
	int	j;
	int	scale;

	scale = g_map->img.width / g_map->maze_width;
	y *= scale;
	x *= scale;
	i = -1;
	while (++i < scale)
	{
		j = -1;
		while (++j < scale)
			img_pixel_put(img, x + i, y + j, color);
	}
}

char	d2_move_on(double x, double y, int scale)
{
	char	c;
	int		i;

	i = (int)(x / g_map->img.height / g_map->maze_height);
	c = g_map->maze[(int)(y / scale)][i];
	if (c == '1')
		return (0);
	else
		return (c);
}

void	draw_hero(t_img *img, double hero_x, double hero_y)
{
	int	x;
	int	y;
	int	i;
	int	j;

	x = (int)(hero_x / 4);
	y = (int)(hero_y / 4);
	i = -1;
	while (++i < 5)
	{
		j = -1;
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

void	draw_2d_image(void)
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
			if (maze[i][j] == '1')
				draw_012(&g_map->img, j, i, 0x777777);
			else if (maze[i][j] == '2')
				draw_012(&g_map->img, j, i, 0xfff000);
			else if (maze[i][j] == '0')
				draw_012(&g_map->img, j, i, 0xfffffff);
		}
	}
	draw_hero(&g_map->img, g_map->hero_x, g_map->hero_y);
	put_image_to_window(&g_map->img, 0, 0);
}
