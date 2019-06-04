/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 17:37:57 by lbonnete          #+#    #+#             */
/*   Updated: 2019/05/29 15:56:01 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/wolf3d.h"

int		get_char_map(int fd, t_var *info)
{
	char	*line;
	int		len;
	int		i;
	size_t	width;

	len = 0;
	i = -1;
	while (get_next_line(fd, &line) == 1)
	{
		if (i == -1)
		{
			width = ft_strlen(line);
			if (width < 5)
				return (0);
		}
		else if (width != ft_strlen(line))
			return (0);
		if (verti_check(line) || !(info->map = realloc_map(info->map, ++len))
		|| !(info->map[++i] = ft_strdup(line)))
			return (0);
		ft_strdel(&line);
	}
	return (1);
}

int		ft_reader(char *name, t_var *info)
{
	int fd;

	if (-1 == (fd = open(name, O_RDONLY)))
	{
		close(fd);
		return (0);
	}
	if (get_char_map(fd, info) == 0)
	{
		close(fd);
		destroy_tab(&(info->map));
		return (0);
	}
	close(fd);
	return (1);
}
