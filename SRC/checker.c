/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 14:48:43 by lbonnete          #+#    #+#             */
/*   Updated: 2019/05/29 15:50:32 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/wolf3d.h"

int		checker(t_var *info)
{
	if (spawn_and_top_checker(info) == 0 || (bottom_checker(info) == 0))
	{
		destroy_tab(&(info->map));
		return (0);
	}
	return (1);
}

int		bottom_checker(t_var *info)
{
	int i;
	int j;

	i = 0;
	while ((info->map)[i])
		i++;
	j = 0;
	--i;
	while ((info->map)[i][j])
	{
		if ((info->map)[i][j] != '#')
			return (0);
		j++;
	}
	return (1);
}

int		spawn_and_top_checker(t_var *info)
{
	int i;
	int j;

	i = -1;
	while ((info->map)[++i])
	{
		j = -1;
		while ((info->map)[i][++j])
		{
			if ((i == 0) && (info->map)[i][j] != '#')
				return (0);
			if ((info->map)[i][j] == 'S' && (info->map)[i + 1][j] == 'W'
			&& (info->map)[i + 2][j] == 'E'
			&& (info->map)[i][j + 1] == 'P' && (info->map)[i + 1][j + 1] == 'N'
			&& (info->map)[i + 2][j + 1] == 'R'
			&& (info->map)[i][j + 2] == 'A' && (info->map)[i + 1][j + 2] == 'H'
			&& (info->map)[i + 2][j + 2] == 'E')
			{
				info->posX = i + 1;
				info->posY = j + 1;
				return (1);
			}
		}
	}
	return (0);
}

int		verti_check(char *line)
{
	int i;

	if (line[0] != '#')
		return (1);
	i = 0;
	while (line[i])
		i++;
	if (line[--i] != '#')
		return (1);
	return (0);
}
