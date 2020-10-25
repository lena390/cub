/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map_c3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 19:32:00 by miphigen          #+#    #+#             */
/*   Updated: 2020/10/25 11:28:22 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_new_coordinates(void)
{
	int	x1;
	int	x2;

	x1 = g_map->res_width / g_map->maze_width;
	x2 = g_map->res_height / g_map->maze_height;
	g_map->scale = x1 < x2 ? x1 : x2;
	g_map->hero_x *= g_map->scale;
	g_map->hero_y *= g_map->scale;
	g_map->hero_x += g_map->scale * 0.5;
	g_map->hero_y += g_map->scale * 0.5;
}

void	check_resolution(void)
{
	int		x_screen_size;
	int		y_screen_size;

	mlx_get_screen_size(g_mlx_ptr, &x_screen_size, &y_screen_size);
	g_map->res_width =
		g_map->res_width > x_screen_size ? x_screen_size : g_map->res_width;
	g_map->res_height =
		g_map->res_height > y_screen_size ? y_screen_size : g_map->res_height;
}

void	render_map(void)
{
	g_map->status = 7;
	g_mlx_ptr = mlx_init();
	check_resolution();
	set_new_coordinates();
	if (g_map->screenshot_needed == 0)
	{
		g_win_ptr =
		mlx_new_window(g_mlx_ptr, g_map->res_width, g_map->res_height, "");
	}
	new_image(&g_map->img, g_map->maze_width * (g_map->scale / 4),
			g_map->maze_height * (g_map->scale / 4));
	dl_textures();
	get_items_coord(g_map->maze);
	draw_3d_image();
	if (g_map->screenshot_needed == 0)
		draw_2d_image();
	mlx_hook(g_win_ptr, 2, 1L << 0, process_key, NULL);
	mlx_hook(g_win_ptr, 17, 1L << 17, set_error_and_exit, NULL);
	mlx_loop(g_mlx_ptr);
}
