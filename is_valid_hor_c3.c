/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_hor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:09:36 by miphigen          #+#    #+#             */
/*   Updated: 2020/10/21 16:09:51 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_hero(char c, double x, double y)
{
	g_map->hero_x = y;
	g_map->hero_y = x;
	c == 'E' ? g_map->hero_direction = 0 : 0;
	c == 'N' ? g_map->hero_direction = M_PI_2 : 0;
	c == 'W' ? g_map->hero_direction = M_PI : 0;
	c == 'S' ? g_map->hero_direction = M_PI + M_PI_2 : 0;
}

int		check_line(char *s)
{
	while (*s != '\0' && (*s == '1' || *s == ' '))
		s++;
	return (*s == '\0' ? 1 : 0);
}

int		is_valid_hor(char **array)
{
	int		ret_value;
	char	c;
	char	*set;
	char	*s;
	int		i;

	g_map->status = 5;
	set = "012 NSWE";
	ret_value = 1;
	s = array[0];
	i = 1;
	while (array[i] && ret_value == 1)
	{
		s = array[i];
		while (*s != '\0' && (ret_value = ft_is_in_set(set, *s)) == 1)
		{
			c = *(s + 1);
			if (*s == '1')
				;
			else if (*s == '0' || *s == '2')
				ret_value = (c == ' ' || c == '\0') ? 0 : 1;
			else if (*s == ' ')
				ret_value = c != ' ' && c != '1' && c != '\0' ? 0 : 1;
			else
			{
				if (c != '1' && c != '0' && c != '2')
					ret_value = 0;
				set_hero(*s, i, s - array[i]);
				set = "012 ";
				*s = '0';
			}
			s++;
		}
		i++;
	}
	ret_value = g_map->hero_direction == -1 ? 0 : ret_value;
	return (ret_value & (check_line(array[i - 1]) & (check_line(array[0]))));
}
