/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces_c3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:06:30 by miphigen          #+#    #+#             */
/*   Updated: 2020/10/21 22:10:00 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*add_spaces_2_str(char *s1, int length)
{
	char	*s2;
	int		i;
	char	*temp;

	if (!(s2 = malloc(length + 1)))
		return (NULL);
	i = 0;
	temp = s1;
	while (*temp != '\0')
	{
		s2[i] = *temp;
		i++;
		temp++;
	}
	while (i < length)
		s2[i++] = ' ';
	s2[i] = '\0';
	free(s1);
	return (s2);
}

char	**add_spaces(char **array, int width, int *height)
{
	int		i;
	char	**maze;
	char	*tmp;

	while (array[*height])
		(*height)++;
	if (!(maze = malloc(sizeof(char *) * (*height + 1))))
		return (NULL);
	i = -1;
	while (array[++i])
	{
		tmp = NULL;
		if (!(tmp = add_spaces_2_str(array[i], width)))
		{
			free(tmp);
			free_2d_array(maze, *height + 1);
			return (NULL);
		}
		else
			maze[i] = tmp;
	}
	maze[i] = NULL;
	free(array);
	return (maze);
}

