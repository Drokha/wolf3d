/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 17:04:55 by lbonnete          #+#    #+#             */
/*   Updated: 2018/12/20 15:36:45 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_sqrt(int nb)
{
	int i;
	int gap;
	int som;

	i = 1;
	som = 0;
	gap = 1;
	if (nb <= 0)
		return (0);
	while (som <= nb && i < 46340)
	{
		som = som + gap;
		if (som == nb)
			return (i);
		gap = gap + 2;
		i++;
	}
	return (0);
}
