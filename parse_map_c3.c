/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_c3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 16:18:03 by miphigen          #+#    #+#             */
/*   Updated: 2020/10/14 15:22:46 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		g_map_config_is_complete()
{
	if (g_map->res_width == -1 || g_map->res_height == -1)
		set_error_and_exit("Missing resolution configuration");
	else if (!g_map->path_NO)
		set_error_and_exit("Missing north walls texture address");
	else if (!g_map->path_SO)
		set_error_and_exit("Missing south walls texture address");
	else if (!g_map->path_WE)
		set_error_and_exit("Missing west walls texture address");
	else if (!g_map->path_EA)
		set_error_and_exit("Missing east walls texture address");
	else if (!g_map->path_S)
		set_error_and_exit("Missing sprite texture address");
	else if (g_map->floor == -1)
		set_error_and_exit("Missing floor color value");
	else if (g_map->ceil == -1)
		set_error_and_exit("Missing ceil color value");
	else
		return (1);
	return (0);
}

void	parse_resolution(char *line)
{
	if (g_map->res_height != -1)
	{
		set_error_and_exit("Repeated resolution configuration");
		return ;
	}
	g_map->res_width = ft_atoi(++line);
	line = ft_skip_characters(line, " \t");
	line = ft_skip_characters(line, "0123456789");
	g_map->res_height = ft_atoi(line);
	if (g_map->res_height <= 0 || g_map->res_width <= 0)
		set_error_and_exit("Invalid resolution value");
}

void	parse_texture_addr(char *line)
{
	char	*id;

	id = line;
	line = ft_strchr(line, ' ');
	line = ft_strtrim(line, " ");
	if (*id == 'N' && id[1] == 'O' && !g_map->path_NO)
		g_map->path_NO = line;
	else if (*id == 'S' && id[1] == 'O' && !g_map->path_SO)
		g_map->path_SO = line;
	else if (*id == 'W' && id[1] == 'E' && !g_map->path_WE)
		g_map->path_WE = line;
	else if (*id == 'E' && id[1] == 'A' && !g_map->path_EA)
		g_map->path_EA = line;
	else if (*id == 'S' && ft_is_in_set(" \t", *++id) == 1 && !g_map->path_S)
		g_map->path_S = line;
	else
	{
		set_error_and_exit("Invalid identifier name or repeated texture configuration");
		free(line);
	}
}

void	parse_rgb(char *line)
{
	char			*id;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	id = line;
	r = ft_atoi(++line);
	line = ft_strchr(line, ',');
	g = ft_atoi(++line);
	line = ft_strchr(line, ',');
	b = ft_atoi(++line);
	if (*id == 'F' && ft_is_in_set(" \t", *(id + 1)) == 1 && g_map->floor == -1)
		g_map->floor = (r << 16 | g << 8 | b);
	else if (*id == 'C' && ft_is_in_set(" \t", *++id) == 1 && g_map->ceil == -1)
		g_map->ceil = (r << 16 | g << 8 | b);
	else
		set_error_and_exit("Invalid color value or repeated color configuration");
}

void	parse_line(char *line, int fd)
{
	char *ptr;

	g_map->status = 2;
	ptr = line;
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == '\0')
		return ;
	if (*line == 'R')
		parse_resolution(line);
	else if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
		parse_texture_addr(line);
	else if (*line == 'F' || *line == 'C')
		parse_rgb(line);
	else if (*line == '1')
	{
		if ((g_map->status = g_map_config_is_complete(g_map)) == 1)
			parse_maze(fd, ft_strdup(ptr));
	}
	else
		set_error_and_exit("Invalid character in g_map configuration");
}

void	parse_map(int fd)
{
	char		*line;
	int			ret_value;

	g_map->status = 1;
	while ((ret_value = get_next_line(fd, &line)) > 0 && g_map->msg == NULL)
	{
		parse_line(line, fd);
		free(line);
	}
	if (ret_value == -1)
		set_error_and_exit("Error occurred while reading or opening file");
}