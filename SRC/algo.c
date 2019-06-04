/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:15:23 by trabut            #+#    #+#             */
/*   Updated: 2019/06/01 16:38:45 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/wolf3d.h"

static	void	cond(t_thrd *thrd)
{
	if (thrd->rayDirX < 0)
	{
		thrd->stepX = -1;
		thrd->sideDistX = (thrd->info->posX - thrd->mapX) * thrd->deltaDistX;
	}
	else
	{
		thrd->stepX = 1;
		thrd->sideDistX = (thrd->mapX + 1.0 - thrd->info->posX)\
		* thrd->deltaDistX;
	}
	if (thrd->rayDirY < 0)
	{
		thrd->stepY = -1;
		thrd->sideDistY = (thrd->info->posY - thrd->mapY) * thrd->deltaDistY;
	}
	else
	{
		thrd->stepY = 1;
		thrd->sideDistY = (thrd->mapY + 1.0 - thrd->info->posY)\
		* thrd->deltaDistY;
	}
}

static	void	alg_dda(t_thrd *thrd)
{
	while (thrd->hit == 0)
	{
		if (thrd->sideDistX < thrd->sideDistY)
		{
			thrd->sideDistX += thrd->deltaDistX;
			thrd->mapX += thrd->stepX;
			thrd->side = 0;
		}
		else
		{
			thrd->sideDistY += thrd->deltaDistY;
			thrd->mapY += thrd->stepY;
			thrd->side = 1;
		}
		if (thrd->info->map[thrd->mapX][thrd->mapY] == '#'
		|| thrd->info->map[thrd->mapX][thrd->mapY] == 'X')
		{
			thrd->hit = 1;
		}
	}
}

static	void	wallh(t_thrd *thrd)
{
	int		lineheight;

	lineheight = (int)(w_h / thrd->perpWallDist);
	thrd->y1 = -lineheight / 2 + WINDOW_H / 2;
	thrd->y2 = lineheight / 2 + WINDOW_H / 2;
}

static	void	init_algo(t_thrd *thrd)
{
	thrd->cameraX = 2 * thrd->x / (double)WINDOW_W - 1;
	thrd->rayDirX = thrd->info->dirX + thrd->info->planeX * thrd->cameraX;
	thrd->rayDirY = thrd->info->dirY + thrd->info->planeY * thrd->cameraX;
	thrd->mapX = (int)thrd->info->posX;
	thrd->mapY = (int)thrd->info->posY;
	thrd->deltaDistX = ft_fabs(1 / thrd->rayDirX);
	thrd->deltaDistY = ft_fabs(1 / thrd->rayDirY);
	thrd->hit = 0;
}

void			*algo(void *thrds)
{
	t_thrd	*thrd;
	t_var	*info;

	thrd = thrds;
	info = thrd->info;
	thrd->x = (WINDOW_W * thrd->id) / (NB_THREADS_MAX);
	while (thrd->x < ((WINDOW_W * (thrd->id + 1) / NB_THREADS_MAX)))
	{
		init_algo(thrd);
		cond(thrd);
		alg_dda(thrd);
		if (thrd->side == 0)
			thrd->perpWallDist = (thrd->mapX - thrd->info->posX +
			(1 - thrd->stepX) / 2) / thrd->rayDirX;
		else
			thrd->perpWallDist = (thrd->mapY - thrd->info->posY +
			(1 - thrd->stepY) / 2) / thrd->rayDirY;
		wallh(thrd);
		if (thrd->info->texture_cap)			
			texturer(thrd, thrd->x);
		else
			draw_ray(thrd, info);
		thrd->x++;
	}
	pthread_exit(NULL);
}
