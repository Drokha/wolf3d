/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:03:46 by lbonnete          #+#    #+#             */
/*   Updated: 2019/05/29 16:04:08 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/wolf3d.h"

void			ft_multithreading(t_var *info)
{
	t_mthrds	*mthrds;
	int			i;

	mthrds = &info->mthrds;
	i = -1;
	while (++i < NB_THREADS_MAX)
	{
		mthrds->thrd[i].id = i;
		mthrds->thrd[i].info = info;
		pthread_create(&mthrds->threads[i], NULL, algo, &mthrds->thrd[i]);
	}
	i = -1;
	while (++i < NB_THREADS_MAX)
	{
		pthread_join(mthrds->threads[i], NULL);
	}
}
