/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:39:35 by trabut            #+#    #+#             */
/*   Updated: 2020/03/05 15:04:48 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/wolf3d.h"

void	destroy_tab(char ***tab)
{
	int i;

	i = 0;
	if (tab)
	{
		if (*tab)
		{
			while ((*tab)[i])
			{
				free((*tab)[i]);
				(*tab)[i] = 0;
				i++;
			}
			free(*tab);
			*tab = 0;
		}
		tab = NULL;
	}
}

char	**realloc_map(char **map, int len)
{
	int		i;
	char	**ret;

	if (!(ret = (char **)malloc(sizeof(char *) * len + 1)))
		return (0);
	ret[len] = NULL;
	if (len > 1)
	{
		i = 0;
		while (i < len)
		{
			if (!(ret[i] = ft_strdup(map[i])))
				return (0);
			i++;
		}
		free(ret[i - 1]);
		destroy_tab(&map);
	}
	return (ret);
}

int		hitboxx(t_var *info, double dirx)
{
	double x;
	double y;

	x = -0.2;
	y = -0.2;
	while (x < 0.2)
	{
		y = -0.2;
		while (y < 0.2)
		{
			if (x * x + y * y  <= 0.17 * 0.17 && info->map[(int)(info->posx + x)][(int)(info->posy)] == '#')
			{
				if(dirx >= 0 && x >= 0)
					return (0);
				if(dirx <= 0 && x <= 0)
					return (0);
			}
			y += 0.01;
		}
		x += 0.01;
	}
	return(1);
}

int		hitboxy(t_var *info, double diry)
{
	double x;
	double y;

	x = -0.2;
	y = -0.2;
	while (x < 0.2)
	{
		y = -0.2;
		while (y < 0.2)
		{
			if (x * x + y * y  <= 0.17 * 0.17 && info->map[(int)(info->posx)][(int)(info->posy + y)] == '#')
			{
				if(diry >= 0 && y >= 0)
					return (0);
				if(diry <= 0 && y <= 0)
					return (0);
			}
			y += 0.01;
		}
		x += 0.01;
	}
	return(1);
}