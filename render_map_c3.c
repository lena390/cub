/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map_c3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 19:32:00 by miphigen          #+#    #+#             */
/*   Updated: 2020/08/27 19:19:24 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct	s_struct
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	*img;
	t_img	*img1;
	t_map	*map;
}				t_struct;

void	draw_map_2d(t_struct *a)
{
	t_img *img;
	int x;
	int y;

	img = a->img1;
	if (a->map->maze_width > a->map->maze_height)
	{
		x = img->width;
		y = a->map->maze_height - 2 * img->width / a->map->maze_width - 1;
	}
	else
	{
		y = img->height;
		x = a->map->maze_width - 1 * img->height / a->map->maze_height - 2;
	}
	

}

int	key_hook(int key, void *param)
{
	t_struct	*a;
	int			x;
	int			y;
	
	x = 0;
	y = 0;
	a = (t_struct *)param;
	if (key == 0)
		x -= 5;
	else if (key == 1)
		y += 5;
	else if (key == 2)
		x += 5;
	else if (key == 13)
		y -= 5;
	a->map->hero.x += x;
	a->map->hero.y += y;
	mlx_put_image_to_window(a->mlx_ptr, a->win_ptr, a->img1->ptr, 0, 0);
	mlx_put_image_to_window(a->mlx_ptr, a->win_ptr, a->img->ptr, a->map->hero.x, a->map->hero.y);
	return (0);
}

int mouse_hook(int button, int x, int y, void *param)
{
	printf("buton: %d, x: %d, y: %d\n", button, x, y);
	return (0);
}

int expose_hook(void *param)
{
	return (0);
}

void	render_map(t_map *map)
{
	t_img		img_hero;
	t_img		img_black;
	t_struct	a;

	a.mlx_ptr = mlx_init();
	a.win_ptr = mlx_new_window(a.mlx_ptr, 1024, 1024, "Hello raycaster");
	a.map = map;
	new_image(a.mlx_ptr, &img_hero, 64, 64, 0xfff000); a.img = &img_hero;
	new_image(a.mlx_ptr, &img_black, 1024, 1024, -1); a.img1 = &img_black;
	draw_map_2d(&a);
	mlx_key_hook(a.win_ptr, key_hook, &a);
//	mlx_loop(a.mlx_ptr);
}
