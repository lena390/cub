/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 23:49:42 by miphigen          #+#    #+#             */
/*   Updated: 2020/08/31 00:57:40 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	make_grid(t_img *img, int side_length, int width, int height)
{
	int i;
	int j;

	i = side_length - 1;
	while (i < height)
	{
		j = -1;
		while (++j < width)
			img_pixel_put(img, i, j, 0xffffff);
		i += side_length;
	}
	while (i < img->width)
	{
		j = -1;
		while (++j < height)
			img_pixel_put(img, j, i, 0xffffff);
		i += side_length;
	}
}

void	add_1(t_img *img, int side_length, int x, int y)
{
	int i;
	int j;
	int x1;
	int color;

	x = x1 * side_length;
	y = y * side_length;
	i = -1;
	while (++i < side_length)
	{
		j = -1;
		while (++j < side_length)
			img_pixel_put(img, x + j, y + i, 0xffffff);
	}
	j = -1;
	while (++j < )

}