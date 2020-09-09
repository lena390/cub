/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_c3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 19:18:01 by miphigen          #+#    #+#             */
/*   Updated: 2020/09/09 15:47:01 by miphigen         ###   ########.fr       */
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
	while (++i < scale - 1)
	{
		j = -1;
		while (++j < scale - 1)
			img_pixel_put(img, x + i, y + j, color);
	}
}

void	draw_rays(t_img *img, int x, int y, t_map *map)
{
	double	tg;
	int		i;

	i = 0;
	while (i < 50)
	{
		y = y - (x * tan(rad));
		printf("x, y %d, %d\n", x + i, y);
		img_pixel_put(img, x + i, y , 0xff0000);
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
			img_pixel_put(img, x + i, y + j, 0);
			img_pixel_put(img, x + j, y + i, 0);
		}
	}
	img_pixel_put(img, x, y, 0xff0000);
}

void	draw_map_2d(t_img *img, t_map *map, int scale)
{
	int		i;
	int		j;
	char	**maze;
	int		color;

	maze = map->maze;
	i = -1;
	puts("draw_map");
	while (++i < map->maze_height)
	{
		j = -1;
		while (maze[i][++j] != '\0')
		{
			char c = maze[i][j];
			if (c == '1')
				color = 0xffffff;
			else if (c == '2')
				color = 0xfff000;
			else if (c == '0')
				color = 0x777777;
			draw_012(img, j, i, scale, color);
		}
	}
	puts("draw hero");
	draw_hero(img, map->hero_x, map->hero_y);
//	draw_rays(img, map->hero_x, map->hero_y, map);
}
