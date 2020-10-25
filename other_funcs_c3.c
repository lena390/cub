/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_funcs_c3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 15:10:19 by miphigen          #+#    #+#             */
/*   Updated: 2020/10/21 15:11:25 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		set_error_and_exit("Memory allocation failure");
	else
		return (ptr);
}

void	free_2d_array(char **s, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		free(s[i]);
	free(s);
}
