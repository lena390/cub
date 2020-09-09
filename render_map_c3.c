/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map_c3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 19:32:00 by miphigen          #+#    #+#             */
/*   Updated: 2020/09/08 22:04:47 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_keynumber(int key)
{
	printf("%d\n", key);
	return key;
}

//int	mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color);

int	move_hero(int key, t_map *map)
{
	int scale = map->scale;
	if (key == 0 || key == 97)
	{
		map->maze[map->hero_y/scale][(map->hero_x - 18) / scale] == '0' ? map->hero_x -= 10 : 0;
	}
	else if (key == 1 || key == 115)
	{
		map->maze[(map->hero_y + 18) / scale][map->hero_x / scale] == '0' ? map->hero_y += 10 : 0;
	}
	else if (key == 2 || key == 100)
	{
		map->maze[map->hero_y / scale][(map->hero_x + 18) / scale] == '0' ? map->hero_x += 10 : 0;
	}
	else if (key == 13 || key == 119)
	{
		map->maze[(map->hero_y - 18) / scale][map->hero_x / scale] == '0' ? map->hero_y -= 10 : 0;
	}
	else if (key == 123 || key == 65361)
		map->hero_degr += 15; 
	else if (key == 124 || key == 65363)
		map->hero_degr -= 15;
	else
		return (0);
	map->hero_degr >= 360 ? map->hero_degr %= 360 : 0;
	map->hero_degr < 0 ? map->hero_degr += 360 : 0;
	draw_map_2d(&map->img, map, map->scale);
	put_image_to_window(&map->img, 0, 0);
	return (0);
}

void	render_map(t_map *map)
{
	g_mlx_ptr = mlx_init();
	g_win_ptr = mlx_new_window(g_mlx_ptr, map->res_width, map->res_height, "Hello raycaster");
	new_image(&map->img, map->res_width, map->res_height);
	map->scale = map->maze_width > map->maze_height ?
		map->img.width/map->maze_width : map->img.height/map->maze_width;
	map->hero_x = map->hero_x * map->scale + map->scale / 2;
	map->hero_y = map->hero_y * map->scale + map->scale / 2;
	draw_map_2d(&map->img, map, map->scale);
	put_image_to_window(&map->img, 0, 0);
	mlx_key_hook(g_win_ptr, move_hero, map);
	mlx_loop(g_mlx_ptr);
}
int mouse_hook(int button, int x, int y, void *param);

int expose_hook(void *param);
