/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:24:51 by lewis             #+#    #+#             */
/*   Updated: 2019/06/21 16:13:18 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/wolf3d.h"

void	get_speed(t_var *info)
{
	if (info->map[(int)(info->posx + info->dirx
	* info->movespeed)][(int)(info->posy)] == '#' ||
	info->map[(int)(info->posx)][(int)(info->posy + info->diry
	* info->movespeed)] == '#')
	{
		info->movespeed = info->frametime * 0.8;
		info->rotspeed = info->frametime * 0.9;
	}
	else
	{
		if (info->sprint)
		{
			info->movespeed = info->frametime * 4;
			info->rotspeed = info->frametime * 1.3;
		}
		else
		{
			info->movespeed = info->frametime * 2.0;
			info->rotspeed = info->frametime * 2.8;
		}
	}
}

void	mouser(t_var *info)
{
	int y;

	SDL_GetRelativeMouseState(&(info->x_dec), &y);
	info->y_dec += y;
	if (info->y_dec > WINDOW_H + 500)
		info->y_dec = WINDOW_H + 500;
	else if (info->y_dec < -500)
		info->y_dec = -500;
}

void	rot_right(t_var *info)
{
	info->olddirx = info->dirx;
	info->dirx = info->dirx * cos(-info->rotspeed) - info->diry
	* sin(-info->rotspeed);
	info->diry = info->olddirx * sin(-info->rotspeed) + info->diry
	* cos(-info->rotspeed);
	info->oldplanex = info->planex;
	info->planex = info->planex * cos(-info->rotspeed) - info->planey
	* sin(-info->rotspeed);
	info->planey = info->oldplanex * sin(-info->rotspeed) + info->planey
	* cos(-info->rotspeed);
}

void	rot_left(t_var *info)
{
	info->olddirx = info->dirx;
	info->dirx = info->dirx * cos(info->rotspeed) - info->diry
	* sin(info->rotspeed);
	info->diry = info->olddirx * sin(info->rotspeed) + info->diry
	* cos(info->rotspeed);
	info->oldplanex = info->planex;
	info->planex = info->planex * cos(info->rotspeed) - info->planey
	* sin(info->rotspeed);
	info->planey = info->oldplanex * sin(info->rotspeed) + info->planey
	* cos(info->rotspeed);
}

void	rotate(t_var *info)
{
	if (info->mouse_in)
		mouser(info);
	if (info->x_dec > 0)
	{
		rot_right(info);
		info->x_dec = 0;
	}
	else if (info->x_dec < 0)
	{
		rot_left(info);
		info->x_dec = 0;
	}
}
