/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_c3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 19:18:01 by miphigen          #+#    #+#             */
/*   Updated: 2020/09/01 19:35:56 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_1(t_img *img, int x, int y, int side_length)
{
	int	i;
	int	j;

	y *= side_length;
	x *= side_length;
	i = -1;
	j = -2;
	while (++j < side_length - 1)
		img_pixel_put(img, x - 1, y + j, 0);
	while (++i < side_length - 1)
	{
		j = -1;
		while (++j < side_length - 1)
			img_pixel_put(img, x + i, y + j, 0xffffff);
	}
}

void	draw_2(t_img *img, int x, int y, int side_length)
{
	int	i;
	int	j;

	y *= side_length;
	x *= side_length;
	i = -1;
	j = -2;
	while (++j < side_length - 1)
		img_pixel_put(img, x - 1, y + j, 0);
	while (++i < side_length)
	{
		j = -1;
		while (++j < side_length)
			img_pixel_put(img, x + i, y + j, 0xfff000);
	}
}

void	draw_0(t_img *img, int x, int y, int side_length)
{
	int	i;
	int	j;

	y *= side_length;
	x *= side_length;
	j = -1;
	--side_length;
	while (++j < side_length)
	{
		img_pixel_put(img, x + side_length, y + j, 0xffffff);
		img_pixel_put(img, x + j, y + side_length, 0xffffff);
	}
}

void	draw_hero(t_img *img, int x, int y, int side_length)
{
	int	i;
	int	j;
	y *= side_length;
	x *= side_length;
	side_length -= 3;
	i = 1;
	while (++i < side_length)
	{
		j = 1;
		while (++j < side_length)
			img_pixel_put(img, x + i, y + j, 0xff00);
	}
}

void	draw_map_2d(t_img *img, t_map *map, int side_length)
{
	int		i;
	int		j;
	char	**maze;

	printf("draw_map() at %d %d\n", map->hero_x, map->hero_y);
	maze = map->maze;
	i = -1;
	while (++i < map->maze_height)
	{
		j = -1;
		while (maze[i][++j] != '\0')
		{
			char c = maze[i][j];
			if (c == '1')
				draw_1(img, j, i, side_length);
			else if (c == '2')
				draw_2(img, j, i, side_length);
			else if (c == '0')
				draw_0(img, j, i, side_length);
		}
	}
	draw_hero(img, map->hero_x, map->hero_y, side_length);
	draw_0(img, map->hero_x, map->hero_y, side_length);
}
