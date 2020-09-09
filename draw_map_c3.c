/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_c3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 19:18:01 by miphigen          #+#    #+#             */
/*   Updated: 2020/09/09 20:44:44 by miphigen         ###   ########.fr       */
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
	int		x0;
	int		y0;

	tg = tan(map->hero_degr / (180.0 / M_PI));
	int i = -1;
	while (++i < 50)
	{
		x0 = i;
		y0 = floor(fabs(x0 * tg));
		
		if (map->hero_degr == 0 || map->hero_degr == 180)
			y0 = 0;
		else if (map->hero_degr == 90 || map->hero_degr == 270)
		{	
			x0 = 0;
			y0 = map->hero_degr == 270 ? i : -i;
		}
		else if (map->hero_degr > 0 && map->hero_degr < 180)
			y0 = -y0;
		if (map->hero_degr > 90 && map->hero_degr < 270)
			x0 = -x0;
		
		img_pixel_put(img, x + x0, y + y0 , 0);
		printf("%d %d\n", x0, y0);
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

void	draw_map_2d(t_img *img, t_map *map, int scale)
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
				color = 0xffffff;
			else if (c == '2')
				color = 0xfff000;
			else if (c == '0')
				color = 0x777777;
			draw_012(img, j, i, scale, color);
		}
	}
	printf("map->hero_degr %d\n", map->hero_degr);
	draw_hero(img, map->hero_x, map->hero_y);
	draw_rays(img, map->hero_x, map->hero_y, map);
}
