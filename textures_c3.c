/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_c3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 19:17:14 by miphigen          #+#    #+#             */
/*   Updated: 2020/10/26 21:15:45 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*get_texture(char *filename)
{
	t_img	*img;
	
	img = malloc(sizeof(t_img));
	if (!img)
		set_error_and_exit("Не выделена память для текстур");
	img->ptr = mlx_xpm_file_to_image(g_mlx_ptr, filename, &img->width, &img->height);
	img->addr = mlx_get_data_addr(img->ptr, &img->bits_per_pixel,
			   &img->size_line, &img->endian);
	if (!img)
		set_error_and_exit("Ошибка чтения файла"); return (img);
}

void	dl_textures()
{
	g_map->NO = get_texture(g_map->path_NO);
	g_map->SO = get_texture(g_map->path_SO);
	g_map->EA = get_texture(g_map->path_EA);
	g_map->WE = get_texture(g_map->path_WE);
	g_map->S = get_texture(g_map->path_S);
}

double		get_column_number(t_wall *wall)
{
	double i = wall->y / g_map->scale;
	i = i - floor(i);
	i = i * wall->texture_ptr->width;
	
	double j = wall->x / g_map->scale;
	j = j - floor(j);
	j = j * wall->texture_ptr->width;
	
	return (wall->type == 'S' || wall->type == 'N' ? j : i);
}

double		get_sprite_column_number(t_sprite *wall)
{
	double d = wall->d;
	const int width_coef = 2;
	double sprite_width = g_map->scale / width_coef;
    d = d / sprite_width * wall->texture_ptr->width;
	return d;
}

void	apply_texture(int x, int delete_later, t_wall *wall)
{
	int				y_start;
	int				y_end;
	int				yy;
	if (wall->type == 'N') 
		wall->texture_ptr = g_map->NO;
	else if (wall->type == 'S')
		wall->texture_ptr = g_map->SO;
	else if (wall->type == 'W')
		wall->texture_ptr = g_map->WE;
	else if (wall->type == 'E')
		wall->texture_ptr = g_map->EA;
	else
		wall->texture_ptr = g_map->S;
	int column_number = (int)floor(get_column_number(wall));
	y_start = (g_map->img2->height - wall->height) / 2;
	y_end = y_start + wall->height;
	int i = -1;
	while (++i < wall->height)
	{
		int xx = column_number * wall->texture_ptr->bits_per_pixel / 8;
			yy = floor((double)(i + (wall->actual_height - wall->height)/2) / wall->actual_height * wall->texture_ptr->height) * wall->texture_ptr->size_line;//
		void *ptr = wall->texture_ptr->addr + xx + yy;
		if (*(unsigned int*)ptr != 0)
			img_pixel_put(g_map->img2, x, i + y_start, *(unsigned int*)ptr);
//		printf("xx: %d, yy: %d, i: %d, y_start: %d, *ptr = %x\n", xx,yy,i,y_start,*(unsigned int*)ptr);
	}

	if (wall->next->x >= 0) {
		// sprite
		t_img* texture_ptr = g_map->S;
		wall->next->texture_ptr = texture_ptr;
		y_start = (g_map->img2->height - wall->next->height) / 2;

		i = -1;
		column_number = (int)floor(get_sprite_column_number(wall->next));
		//printf("%d\n", column_number);
		while (++i < wall->next->height)
		{
			int xx = column_number * texture_ptr->bits_per_pixel / 8;
				yy = floor((double)(i + (wall->next->actual_height - wall->next->height)/2) / wall->next->actual_height * texture_ptr->height) * texture_ptr->size_line;//
			void *ptr = texture_ptr->addr + xx + yy;
			if (*(unsigned int*)ptr != 0)
				img_pixel_put(g_map->img2, x, i + y_start, *(unsigned int*)ptr);
		}
	}
}
