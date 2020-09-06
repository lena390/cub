/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map_c3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 19:32:00 by miphigen          #+#    #+#             */
/*   Updated: 2020/09/01 19:36:05 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_keynumber(int key, void *param)
{
	printf("%d\n", key);
}

int	mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color);

void	remove_hero(int x, int y, int side_length)
{
	int	i;
	int	j;
	puts("remove_hero()");
	y *= side_length;
	x *= side_length;
	side_length -= 3;
	i = 1;
	while (++i < side_length)
	{
		j = 1;
		while (++j < side_length)
			mlx_pixel_put(g_mlx_ptr, g_win_ptr, x + y, y + j, 0);
	}
}

int	move_hero(int key, t_map *map)
{
	if (key >= 123 && key <= 126)
		remove_hero(map->hero_x, map->hero_y, map->side_length);
	if (key == 0 || key == 123)
		map->hero_x--;
	else if (key == 1 || key == 125)
		map->hero_y++;
	else if (key == 2 || key == 124)
		map->hero_x++;
	else if (key == 13 || key == 126)
		map->hero_y--;
	else
		return (0);
	draw_map_2d(&map->img, map, map->side_length);
	put_image_to_window(&map->img, 0, 0);
	return (0);
}

void	render_map(t_map *map)
{
	g_mlx_ptr = mlx_init();
	g_win_ptr = mlx_new_window(g_mlx_ptr, map->res_width, map->res_height, "Hello raycaster");
	new_image(&map->img, map->res_width, map->res_height);
	map->side_length = map->maze_width > map->maze_height ?
		map->img.width/map->maze_width : map->img.height/map->maze_width;
	draw_map_2d(&map->img, map, map->side_length);
	put_image_to_window(&map->img, 0, 0);
	mlx_key_hook(g_win_ptr, move_hero, map);
	mlx_loop(g_mlx_ptr);
}
int mouse_hook(int button, int x, int y, void *param) {return 0;}

int expose_hook(void *param) {return 0;}
