/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d_image_c3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:11:05 by miphigen          #+#    #+#             */
/*   Updated: 2020/10/11 18:59:54 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int dbg = 0;

char	check_intersect(t_map *map, double x, double y, int scale, double xshift, double yshift)
{
	char c;
	x = x + xshift;
	y = y + yshift;
	double y1 = y - 2 * yshift;
	double x1 = x - 2 * xshift;

	if (y >= map->maze_height * scale || x >= map->maze_width * scale)
	{
		y >= map->img2->height - 1 ? y = map->img2->height : 0 ; 
		x >= map->img2->width - 1 ? x = map->img2->width : 0;
		return ('1');
	}
	else if (y1 < 0 || x1 < 0)
		return ('1');
	int y_coord = (int)floor(y / scale);
	int x_coord = (int)floor(x / scale);
	c = map->maze[y_coord][x_coord];
	if (c == '1' || c == ' ')
		return ('1');
	y_coord = (int)floor(y1 / scale);
	x_coord = (int)floor(x1 / scale);
	c = map->maze[y_coord][x_coord];
	if (c == '1' || c == ' ')
		return ('1');
	return (c);
}

void	vertical_cross(t_map *map, t_wall *wall, double angle)
{
	double	x;
	double	y;
	double	step;
	double	tg;

	step = map->scale;
	tg = tan(angle - M_PI / 2);
	if ((angle <= M_PI_2 * 3 && angle >= M_PI_2)) {
		x = floor(map->hero_x / step + 1) * step;
		step *= -1;
	}
	else
		x = floor(map->hero_x / step) * step;
	y = (x / tg) + map->hero_y - (map->hero_x / tg);
	double step_y = step / tg;//
	if (dbg) printf("@vertical_cross: initial x = %f, y = %f, step_y = %f, step_x = %f\n", x, y, step_y, step);
	while (x < map->img2->width)
	{
		x += step;
		y += step_y;
		wall->type = check_intersect(map, x, y, map->scale, 0.5, 0.5);
		if (wall->type == '1')
			break;
		if (wall->type == '2');//add sprite
	}
	if (dbg) printf("@vertical_cross: crosss x = %f, y = %f\n", x, y);
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
	double	step;
	double	tg;

	step = map->scale;
	tg = tan(M_PI - angle);
	if (angle >= M_PI && angle < M_PI * 2)
		y = floor(map->hero_y / step) * step;
	else
	{
		y = floor(map->hero_y / step + 1) * step;
		step *= -1;
	}
	x = (y / tg) + map->hero_x - (map->hero_y / tg);
	double step_x = step / tg;//
	if (dbg) printf("@horizontal_cross: initial x = %f, y = %f, step = %f, step_x = %f\n", x, y, step, step_x);
	while (y < map->img2->height)
	{
		y += step;
		x += step_x;
		wall->type = check_intersect(map, x, y, map->scale, 0.5, 0.5);
		if (wall->type == '1')
			break;
		if (wall->type == '2');//add sprite
	}
	if (dbg) printf("@horizontal_cross: crosss x = %f, y = %f\n", x, y);
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
	horizontal_cross(map, &wall1, angle);
	vertical_cross(map, &wall2, angle);
	if (dbg) printf("wall1 dist: %f. wall2 dist: %f\n", wall1.dist, wall2.dist);
	if (wall1.dist > wall2.dist)
		 wall1 = wall2;
	if (dbg) printf("xh = %f, yh = %f;   wall1 %c dist: %f\n", map->hero_x, map->hero_y, wall1.type, wall1.dist);
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
	if (dbg) printf("dist: %f wall_h: %u\n", wall.dist, wall_h);
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
	map->status = 11;
	new_image(map->img2, map->res_width, map->res_height);
	rays_number = map->img2->width / PPR;
	map->section_width = map->img2->width / rays_number;
	r_min = (map->hero_direction - ANGLE_OV / 2);
	r_max = (map->hero_direction + ANGLE_OV / 2);
	add_sprite(map, 0, 0, 1);
	i = 0;
	if (dbg) printf("================================\n");
	while (i < map->img2->width)
	{	
	if (dbg) printf(" --- ");
		draw_section(map, i, i + map->section_width,
			get_wall_inf_and_collect_sprite_loc(map, r_max, (M_PI / 3) / rays_number));
		i += map->section_width;
		r_max -= (M_PI / 3) / rays_number;
	}
	//2put_sprites_to_image(map);
	put_image_to_window(map->img2, 0, 0);
	mlx_destroy_image(g_mlx_ptr, map->img2->ptr);

}
