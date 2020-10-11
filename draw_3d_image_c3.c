/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d_image_c3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:11:05 by miphigen          #+#    #+#             */
/*   Updated: 2020/10/11 14:04:35 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_sprite(t_map *map, double x_start, double dist, int	flag)
{
	double	*tab_new;
	double	*tab;
	static int	capacity;
	static int	size;
	int 		i;

	map->status = 13;
	tab = map->sp_location;
	if (flag == 1)
	{
		capacity = 20;
		size = 0;
		map->sp_location = malloc(sizeof(double) * 20);
		tab = map->sp_location;
		if (!tab) set_error_and_exit("Memory allocation failure", map); 
		return ;
	}
	if (size == capacity)
	{
		capacity *= 2;
		tab_new = malloc(sizeof(double) * capacity);
		if (!tab_new) set_error_and_exit("Memory allocation failure", map); 
		i = -1;
		while (++i < size)
			tab_new[i] = tab[i];
		free(tab);
		map->sp_location = tab_new;
		tab = tab_new;
	}
	tab[size++] = dist;
	tab[size++] = x_start;
}

void	put_sprite(t_map *map, t_img *img, int sp_height, int sp_x)
{
	int x, y;
	y = map->res_height * 0.5;
	while (y < sp_height + map->res_width * 0.5)
	{
		x = sp_x;
		while (x < sp_height + sp_x)
		{
			img_pixel_put(img, x, y, 0);
			x++;
			
		}
		y++;
	}
}

void	put_sprites_to_image(t_map *map)
{
	int		i0;
	int		i1;
	double	sp_width;
	double	sp_height;
	double	*tab;

	map->status = 16;
	tab = map->sp_location;
	i1 = tab[1];
	i0 = 2;
	while (i0 < i1)
	{
		//sp_height = ceil((map->scale * map->img2->height) / (4 * (tab[i0])));
		sp_height = 50;
		sp_width = 0;//написать что-нибудь
		put_sprite(map, map->img2, ceil(sp_height), ceil(tab[i0 + 1]));
		i0 += 2;
	}
	free(tab);
}

char	move_on(t_map *map, double x, double y, int scale)
{
	char c;

	if (y >= map->maze_height * scale || x >= map->maze_width * scale)
	{
		y >= map->img2->height - 1 ? y = map->img2->height : 0 ; 
		x >= map->img2->width - 1 ? x = map->img2->width : 0;
		return (1);
	}
	else if (y < 0 || x < 0)
		return (1);
	c = map->maze[(int)floor(y / scale)][(int)floor(x / scale)];
	if (c == '1' || c == ' ')
		return (1);
	else
		return (c);
}

void	vertical_cross(t_map *map, t_wall *wall, double angle)
{
	
	double	x;
	double	y;
	int		step;
	double	tg;

	step = map->scale;
	tg = tan(angle);
	if ((angle >= M_PI_2 * 3 && angle <= M_PI_2) || x == floor(x))
		x = floor(map->hero_x / step) * step;
	else
	{
		x = floor(map->hero_x / step + 1) * step;
		step *= -1;
	}
	y = (x * tg) + map->hero_y - (map->hero_x * tg);
	while (x < map->img2->width)
	{
		y = (x * tg) + map->hero_y - (map->hero_x * tg);
		wall->type = move_on(map, x, y, map->scale);
		if (wall->type == 1)
			break;
		if (wall->type == 2);//add sprite
		x += step;
	}
	wall->dist = sqrt(pow(x - map->hero_x, 2) + pow(y - map->hero_y, 2));
	if (angle >= M_PI_2 && angle < M_PI_2 * 3)
		wall->type = 'W';
	else
		wall->type = 'E';
}

void	horizontal_cross(t_map *map, t_wall *wall, double angle)
{
	double	x;
	double	y;
	int		step;
	double	tg;

	step = map->scale;
	tg = tan(angle);
	if ((angle >= M_PI && angle <= M_PI * 2) || map->hero_y == floor(map->hero_y))
		y = floor(map->hero_y / step) * step;
	else
	{
		y = floor(map->hero_y / step + 1) * step;
		step *= -1;
	}
	x = (y / tg) + map->hero_x - (map->hero_y / tg);
	while (y < map->img2->height)
	{
		x = (y / tg) + map->hero_x - (map->hero_y / tg);
		wall->type = move_on(map, x, y, map->scale);
		if (wall->type == 1)
			break;
		if (wall->type == 2);//add sprite
		y += step;
	}
	wall->dist = sqrt(pow(x - map->hero_x, 2) + pow(y - map->hero_y, 2));
if (angle >= 0 && angle < M_PI)
		wall->type = 'N';
	else
		wall->type = 'S';
}

t_wall	get_wall_inf_and_collect_sprite_loc(t_map *map, double angle, double next)
{
	t_wall	wall1;
	t_wall	wall2;

	map->status = 12;
	if (angle < 0)
		angle += (M_PI) * 2;
	else if (angle >= M_PI * 2)
		angle -= (M_PI * 2);
	if (angle == 0  || angle == M_PI_2 || angle == M_PI || angle == M_PI_2 * 3)
	{	
		angle += next;
		printf("get_wall_inf() angle == %f\n", angle);
	}
	horizontal_cross(map, &wall1, angle);
	vertical_cross(map, &wall2, angle);
//	printf("wall1 dist: %f. wall2 dist: %f\n", wall1.dist, wall2.dist);
	if (wall1.dist > wall2.dist)
		 wall1 = wall2;
	return wall1;
}

void	draw_section(t_map *map, int x0, int x1, t_wall wall)
{
	t_img			*img;
	int				i;
	unsigned int	wall_h;
	int				y_skyline;
	int				color_wall = 0x887fff;

	if (wall.type == 'N')
		color_wall = 0x887fff;
	else if (wall.type == 'S')
		color_wall = 0xff8884;
	else if (wall.type == 'W')
		color_wall = 0xc2ff78;
	else
		color_wall = 0xfff780;
		
	map->status = 15;
	wall_h = ceil((map->scale * map->img2->height) / (wall.dist));
	wall_h < 0 ? puts("draw_section() высота стены меньше 0") : 0;
	wall_h >= map->img2->height? wall_h = map->img2->height : 0;
	y_skyline = map->img2->height / 2;
	while (x0 < x1)
	{
		i = 0;
		while (++i <= y_skyline - wall_h / 2 + 1)
		{
			img_pixel_put(map->img2, x0, i, map->ceil);
			img_pixel_put(map->img2, x0, map->img2->height - i - 1, map->floor);
		}
		i = -1;
		if (wall.type == 1)
			add_texture(map);
		while (++i < wall_h / 2 - 1)
		{
			img_pixel_put(map->img2, x0, y_skyline + i + 1, color_wall);
			img_pixel_put(map->img2, x0, y_skyline - i, color_wall);
		}
		x0++;
	}
//	printf("dist: %f wall_h: %u\n", wall.dist, wall_h);
}

void	add_texture(t_map *map)
{
	
}

void	draw_3d_image(t_map *map)
{
	double	r_min;
	double	r_max;
	int		rays_number;
	int		i;
	double f = M_PI / 180;
//	printf("direction %f location %f %f\n", map->hero_direction / f, map->hero_x, map->hero_y);
//	puts("new image");
//	printf("%f %f\n", map->hero_x, map->hero_y);
	map->status = 11;
	new_image(map->img2, map->res_width, map->res_height);
	rays_number = map->img2->width / PPR;
	map->section_width = map->img2->width / rays_number;
	r_min = (map->hero_direction - ANGLE_OV / 2);
	r_max = (map->hero_direction + ANGLE_OV / 2);
	add_sprite(map, 0, 0, 1);
	i = 0;
	while (i < map->img2->width)
	{	
		draw_section(map, i, i + map->section_width,
			get_wall_inf_and_collect_sprite_loc(map, r_max, (M_PI / 3) / rays_number));
		i += map->section_width;
		r_max -= (M_PI / 3) / rays_number;
	}
	//2put_sprites_to_image(map);
	put_image_to_window(map->img2, 0, 0);
	mlx_destroy_image(g_mlx_ptr, map->img2->ptr);

}
