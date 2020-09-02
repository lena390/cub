/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 20:03:33 by miphigen          #+#    #+#             */
/*   Updated: 2020/08/31 19:12:58 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_MLX_H
# define MY_MLX_H

# include <mlx.h>
# include <stdio.h>
# include <math.h>

void	*g_mlx_ptr;
void	*g_win_ptr;

typedef struct s_img
{
	char		*addr;
	void		*ptr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;

	int			width;
	int			height;
}				t_img;

void	new_image(t_img *img, int width, int height);
void	img_pixel_put(t_img *img, int x, int y, int color);
int		key_hook(int key, void *param);
int		mouse_hook(int button, int x, int y, void *param);
int		expose_hook(void *param);
int		loop_hook(void *param);
void	put_image_to_window(t_img *img, int x, int y);

#endif
