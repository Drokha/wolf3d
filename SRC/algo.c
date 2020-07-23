/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:15:23 by trabut            #+#    #+#             */
/*   Updated: 2019/06/21 16:07:18 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/wolf3d.h"

static	void	cond(t_thrd *thrd)
{
	if (thrd->raydirx < 0)
	{
		thrd->stepx = -1;
		thrd->sidedistx = (thrd->info->posx - thrd->mapx) * thrd->deltadistx;
	}
	else
	{
		thrd->stepx = 1;
		thrd->sidedistx = (thrd->mapx + 1.0 - thrd->info->posx)
		* thrd->deltadistx;
	}
	if (thrd->raydiry < 0)
	{
		thrd->stepy = -1;
		thrd->sidedisty = (thrd->info->posy - thrd->mapy) * thrd->deltadisty;
	}
	else
	{
		thrd->stepy = 1;
		thrd->sidedisty = (thrd->mapy + 1.0 - thrd->info->posy)
		* thrd->deltadisty;
	}
}

static	void	alg_dda(t_thrd *thrd)
{
	while (thrd->hit == 0)
	{
		if (thrd->sidedistx < thrd->sidedisty)
		{
			thrd->sidedistx += thrd->deltadistx;
			thrd->mapx += thrd->stepx;
			thrd->side = 0;
		}
		else
		{
			thrd->sidedisty += thrd->deltadisty;
			thrd->mapy += thrd->stepy;
			thrd->side = 1;
		}
		if (thrd->info->map[thrd->mapx][thrd->mapy] == '#'
		|| thrd->info->map[thrd->mapx][thrd->mapy] == 'X')
		{
			thrd->hit = 1;
		}
	}
}

static	void	wallh(t_thrd *thrd)
{
	int		lineheight;

	lineheight = (int)(W_H / thrd->perpwalldist);
	thrd->y1 = -lineheight / 2 + WINDOW_H / 2;
	thrd->y2 = lineheight / 2 + WINDOW_H / 2;
}

static	void	init_algo(t_thrd *thrd)
{
	thrd->camerax = 2 * thrd->x / (double)WINDOW_W - 1;
	thrd->raydirx = thrd->info->dirx + thrd->info->planex * thrd->camerax;
	thrd->raydiry = thrd->info->diry + thrd->info->planey * thrd->camerax;
	thrd->mapx = (int)thrd->info->posx;
	thrd->mapy = (int)thrd->info->posy;
	thrd->deltadistx = ft_fabs(1 / thrd->raydirx);
	thrd->deltadisty = ft_fabs(1 / thrd->raydiry);
	thrd->hit = 0;
}

void			*algo(void *thrds)
{
	t_thrd	*thrd;
	t_var	*info;

	thrd = thrds;
	info = thrd->info;
	thrd->x = thrd->id;
	while (thrd->x < WINDOW_W)
	{
		init_algo(thrd);
		cond(thrd);
		alg_dda(thrd);
		if (thrd->side == 0)
			thrd->perpwalldist = (thrd->mapx - thrd->info->posx +
			(1 - thrd->stepx) / 2) / thrd->raydirx;
		else
			thrd->perpwalldist = (thrd->mapy - thrd->info->posy +
			(1 - thrd->stepy) / 2) / thrd->raydiry;
		wallh(thrd);
		if (thrd->info->texture_cap)
			texturer(thrd, thrd->x);
		else
			draw_ray(thrd, info);
		thrd->x += NB_THREADS_MAX;
	}
	pthread_exit(NULL);
}
