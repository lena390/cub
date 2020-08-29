/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_c3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 16:24:19 by miphigen          #+#    #+#             */
/*   Updated: 2020/08/29 19:25:38 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_max_width(char **array)
{
	int	max;
	int	current;

	max = 0;
	while (*array)
	{
		current = ft_strlen(*array);
		max = current > max ? current : max;
		array++;
	}
	return (max);
}

char	*add_spaces_2_str(char *s1, int length)
{
	char	*s2;
	int		i;
	char	*temp;
	
	if (!(s2 = malloc(length + 1)))
		return (NULL);
	i = 0;
	if (s1)
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

	while (array[*height])//get maze height
		(*height)++;
	if (!(maze = malloc(sizeof(char *) * (*height + 1))))
		return (NULL);
	i = -1;
	while (array[++i])
	{
		tmp = NULL;
		if (!(tmp = add_spaces_2_str(array[i], width)))
			return (NULL);
		else
			maze[i] = tmp;
	}
	maze[i] = NULL;
	free(array);
	return (maze);
}

void	set_hero(t_map *map, char c, int x, int y)
{
	map->hero.x = x;
	map->hero.y = y;
	map->hero.orient = c;
}

int		check_line(char *s)
{
	while (*s != '\0' && (*s == '1' || *s == ' '))
		s++;
	return (*s == '\0' ? 1 : 0);
}

int		is_valid_hor(char **array, t_map *map)
{
	int		ret_value;
	char	c;
	char	*set;
	char	*s;
	int		i;

	set = "012 NSWE";
	ret_value = 1;
	s = array[0];
	i = 1;
	while (array[i] && ret_value > 0)
	{
		s = array[i];
		while (*s != '\0' && ret_value > 0 && (ret_value = ft_is_in_set(set, *s)) == 1)
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
				set_hero(map, *s, i, s - array[i]);
				set = "012 ";
			}
			s++;
		}
		i++;
	}
	ret_value = ret_value == map->hero.orient == 0 ? 0 : ret_value;
	return (ret_value && check_line(array[i - 1] && check_line(array[0])));
}

int		is_valid_vert(char **array1, t_map *map, char hero_char)
{
	int		ret_value;
	int		i;
	int		j;
	char	c1;
	char	c2;

	char **array = map->maze;
	ret_value = 2;
	i = 0;
	while (i < map->maze_height && (array[i][0] == ' ' || array[i][0] == '1'))
		i++;
	ret_value = i == map->maze_height ? 2 : 1;
	while (i < map->maze_width && ret_value == 2)
	{
		j = 0;
		while (j < map->maze_height - 1 && ret_value == 2)
		{	
			c1 = array[j][i];
			c2 = array[++j][i];
			if (c1 == '1')
				;
			else if (c1 == '0' || c1 == '2' || c1 == hero_char)
				ret_value = (c2 == ' ' || c2 == '\0') ? -5 : 2;
			else if (c1 == ' ')
				ret_value = c2 != ' ' && c2 != '1' && c2 != '\0' ? -6 : 2;
			else
				ret_value = -7;
		}
		i++;
	}
	return (map->status = ret_value);
}

int	maze_is_valid(t_map *map)
{
	int ret_value;;

	map->maze_width = get_max_width(map->maze) + 1;
	if (!(map->maze = add_spaces(map->maze, map->maze_width, &map->maze_height)))
		return (-1);
	if ((ret_value = is_valid_hor(map->maze, map)) == 1)
		return (is_valid_vert(map->maze, map, map->hero.orient));
	else
		return (-1);
}