/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:39:35 by trabut            #+#    #+#             */
/*   Updated: 2019/05/29 15:58:24 by lbonnete         ###   ########.fr       */
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
	}
}

char	**realloc_map(char **map, int len)
{
	int		i;
	char	**ret;

	if (!(ret = (char **)malloc(sizeof(char *) * len + 1)))
		return (0);
	ret[len] = NULL;
	if (map)
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
