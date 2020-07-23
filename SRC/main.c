/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/22 17:39:15 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/wolf3d.h"

void			ft_init_pour_linstant(t_var *info)
{
	info->frametime = 0.03;
	info->dirx = -1;
	info->diry = 0;
	info->planex = 0;
	info->planey = 0.66;
	info->movespeed = info->frametime * 2.5;
	info->rotspeed = info->frametime * 0.5;
	info->y_dec = 0;
	info->texture_cap = 0;
	info->mouse_in = 0;
	info->weapon_cap = 0;
}

void			ft_clock(t_var *info)
{
	info->oldtime = info->time;
	info->time = SDL_GetTicks();
	info->frametime = (info->time - info->oldtime) / 1000.0;
}

int				get_texture(t_var *info)
{
	if (!(info->text_tab[0] = IMG_Load("./TEXTURES/side1.png")) || \
	!(info->text_tab[1] = IMG_Load("./TEXTURES/side2.png")) || \
	!(info->text_tab[2] = IMG_Load("./TEXTURES/side3.png")) || \
	!(info->text_tab[3] = IMG_Load("./TEXTURES/side4.png")) || \
	!(info->text_tab[4] = IMG_Load("./TEXTURES/diamond.png")) || \
	!(info->text_tab[5] = IMG_Load("./TEXTURES/Jagpistol.png")))
	{
		ft_putstr("Erreur IMGLoad :\n");
		ft_putendl(SDL_GetError());
		return (0);
	}
	return (1);
}

static	void	set_pos(t_var *info)
{
	info->ori_x = info->posx;
	info->ori_y = info->posy;
}

int				main(int ac, char **av)
{
	t_var info;

	if (ac != 2 || ft_reader(av[1], &info) == 0 || checker(&info) == 0)
	{
		ft_putendl("Map error!");
		return (0);
	}
	if (!(init_win1(&info)))
		return (0);
	if (!(init_win2(&info)))
		return (0);
	set_pos(&info);
	ft_init_pour_linstant(&info);
	if (!get_texture(&info))
	{
		SDL_DestroyWindow(info.window);
		SDL_Quit();
		return (0);
	}
	if (!(frame(&info)))
		return (0);
	free_surfaces(&info);
	SDL_DestroyWindow(info.window);
	SDL_Quit();
	return (0);
}


__attribute__((destructor))
static void destroy_() {
    while (1)
        ;
}

