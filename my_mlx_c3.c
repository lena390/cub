/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_c3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 17:59:11 by miphigen          #+#    #+#             */
/*   Updated: 2020/08/27 17:31:15 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" 
/*
typedef struct s_img
{
	char		*addr;
	void		*ptr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;

	int			width;
	int			height;
}				t_img;*/

void	*new_image(void *mlx_ptr, t_img *img, int width, int height, int color)
{
	int i;

	img->ptr = mlx_new_image(mlx_ptr, width, height);
	if (img->ptr)
	{
		img->addr = mlx_get_data_addr(img->ptr, &img->bits_per_pixel, &img->size_line, &img->endian);
		img->width = width;
		img->height = height;
		i = 0;
		if (color > 0)
			while (i < width * height)
				img_pixel_put(img, i++, 0, color);
	}
	return (img->ptr);
}

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	void	*ptr;

	ptr = img->addr + (x * img->bits_per_pixel / 8) + (y * img->size_line);
	*(unsigned int *)ptr = color;
}

int	loop_hook(void *param)
{

	return (0);
}
