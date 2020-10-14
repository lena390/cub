/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_c3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 19:17:14 by miphigen          #+#    #+#             */
/*   Updated: 2020/10/14 18:41:10 by miphigen         ###   ########.fr       */
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
}

void	apply_texture(int x, int delete_later, t_wall *wall)
{
	double			scale_y;
	int				y;
	int				j;
	int				y_start;
	int	y_end;

	if (wall->type == 'N') 
		g_map->texture_ptr = g_map->NO;
	else if (wall->type == 'S')
		g_map->texture_ptr = g_map->SO;
	else if (wall->type == 'W')
		g_map->texture_ptr = g_map->WE;
	else
		g_map->texture_ptr = g_map->EA;
	if (g_map->texture_ptr != g_map->previous_texture_ptr)
		g_map->column_number = 0;
	y_start = (g_map->img2->height - wall->height) / 2;
	y_end = y_start + wall->height;
	scale_y = floor(wall->height / g_map->texture_ptr->height);
	y = -1;
	j = -1;
	while (++j < g_map->texture_ptr->height)
	{
		int xx = g_map->column_number * g_map->texture_ptr->bits_per_pixel / 8;
		int yy = j * g_map->texture_ptr->size_line;
		void *ptr = g_map->texture_ptr->addr + xx + yy;
		
		int k = -1;
		while (++k < scale_y && y_start < y_end)
		{
			img_pixel_put(g_map->img2, x, y_start++, *(unsigned int *)ptr);
			
			int piska = (wall->height - (scale_y * g_map->texture_ptr->height));
			int	a = wall->height / piska;
			if (k % a == 0)
				img_pixel_put(g_map->img2, x, y_start++, *(unsigned int *)ptr);
		}
	}
	g_map->previous_texture_ptr = g_map->texture_ptr;
	if (++g_map->column_counter >= scale_y)
	{	
		g_map->column_number++;
		g_map->column_counter = 0;
	}
}
//	ptr = img->addr + (x * img->bits_per_pixel / 8) + (y * img->size_line);
//unsigned int	mlx_get_color_value(void *mlx_ptr, int color);
