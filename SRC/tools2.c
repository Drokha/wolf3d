/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 17:24:15 by trabut            #+#    #+#             */
/*   Updated: 2019/06/01 15:20:30 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/wolf3d.h"

float	ft_fabs(float a)
{
	if (a < 0)
		return (-1 * a);
	return (a);
}

void	sider(t_thrd *thrd, t_var *info, int x, int y)
{
	if ((thrd->info->map)[thrd->mapX][thrd->mapY] == 'X')
		put_pixel_to_suface(BLACK, x, y, info->image);
	else if (thrd->side)
	{
		if (thrd->info->posY < thrd->mapY)
			put_pixel_to_suface(SOUTH_WALL, x, y, info->image);
		else
			put_pixel_to_suface(NORTH_WALL, x, y, info->image);
	}
	else
	{
		if (thrd->info->posX > thrd->mapX)
			put_pixel_to_suface(WEST_WALL, x, y, info->image);
		else
			put_pixel_to_suface(EAST_WALL, x, y, info->image);
	}
}

void	put_pixel_to_suface(Uint32 color, int x, int y, SDL_Surface *image)
{
	Uint32 *pixels;

	pixels = image->pixels;
	if (x >= 0 && y >= 0 && x < image->w && y < image->h)
		pixels[y * image->w + x] = color;
}

int        tex_sider(t_thrd *thrd)
{
    if ((thrd->info->map)[thrd->mapX][thrd->mapY] == 'X')
        return (EXIT_W);
    else if (thrd->side)
    {
        if (thrd->info->posY < thrd->mapY)
            return (SOUTH);
        else
            return (NORTH);
    }
    else
    {
        if (thrd->info->posX > thrd->mapX)
            return (WEST);
        else
            return (EAST);
    }
}
