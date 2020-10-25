/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_c3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 00:53:17 by miphigen          #+#    #+#             */
/*   Updated: 2020/10/23 11:04:56 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	cub_init(void)
{
	g_map->res_width = -1;
	g_map->res_height = -1;
	g_map->ceil = -1;
	g_map->floor = -1;
	g_map->hero_direction = -1.;
	g_map->img2 = ft_malloc(sizeof(t_img));
}

void	free_map(void)
{
	puts("free_map() in a process");
}

int	set_error_and_exit(char *msg)
{
	if (msg)
		ft_printf("Error\n%s (%d)\n", msg, g_map->status);
	free_map();
	exit(0);
}

int		main(int ac, char **av)
{
	if (ac == 1)
	{
		printf("Error.\nEnter a map file path as a 1st parameter\n");
		return (0);
	}
	g_map = ft_calloc(sizeof(t_map), 1);
	if (!g_map)
		set_error_and_exit("Memory allocation failure");
	cub_init();
	parse_map(open(av[1], O_RDONLY));
	maze_is_valid();
	if (g_map->status == 6)
	{
		if (ac >= 3 && ft_strncmp(av[2], "--save", 7) == 0)
			g_map->screenshot_needed = 1;
		render_map();
	}
	else
		set_error_and_exit("Memory allocation failure");
	free_map();
}
