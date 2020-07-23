/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blank.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 14:45:17 by trabut            #+#    #+#             */
/*   Updated: 2020/01/29 12:57:35 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/wolf3d.h"

static	int		mouse_test(t_var *info)
{
	if (info->mouse_in)
		SDL_SetRelativeMouseMode(SDL_TRUE);
	else
		SDL_SetRelativeMouseMode(SDL_FALSE);
	return (1);
}

static	void	ft_put_weapon(t_var *info)
{
	int		x;
	int		y;
	Uint32	color;

	x = 0;
	while (x < info->text_tab[5]->w)
	{
		y = 0;
		while (y < info->text_tab[5]->h)
		{
			color = get_pixel(info->text_tab[5], x, y);
			if (color != 0)
				put_pixel_to_suface(color, x + WINDOW_W / 2 - 45,
				WINDOW_H + y - 125, info->image);
			y++;
		}
		x++;
	}
}

static	void	quitter(t_var *info)
{
	ft_putendl(SDL_GetError());
	SDL_DestroyWindow(info->window);
	SDL_Quit();
}

static	void	frame_help(t_var *info)
{
	SDL_RenderPresent(info->renderer);
	SDL_DestroyTexture(info->texture);
}

int				frame(t_var *info)
{
	while (dealer(info))
	{
		mouse_test(info);
		rotate(info);
		ft_clock(info);
		ft_multithreading(info);
		if (info->weapon_cap)
			ft_put_weapon(info);
		if (!(info->texture =
		SDL_CreateTextureFromSurface(info->renderer, info->image)))
		{
			ft_putstr("Erreur CreateTextureFromSurface :\n");
			quitter(info);
			return (0);
		}
		if (SDL_RenderCopy(info->renderer, info->texture, NULL, NULL))
		{
			ft_putstr("Erreur RenderCopy :\n");
			quitter(info);
			return (0);
		}
		frame_help(info);
	}
	destroy_tab(&(info->map));
	return (1);
}
