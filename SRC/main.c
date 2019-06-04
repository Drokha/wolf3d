/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2019/05/31 16:28:07 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/wolf3d.h"



void	ft_init_pour_linstant(t_var *info)
{//WTF ca veut dire quoi tout ca
//0 si on peut pas dire hein
//ARSGSSSGSDFSFDGSDFGSDFGDSFG
	info->frameTime = 0.03;
  	info->dirX = -1, info->dirY = 0;
	info->planeX = 0, info->planeY = 0.66;
	info->moveSpeed = info->frameTime * 2.5;
    info->rotSpeed = info->frameTime * 0.5;
	info->y_dec = 0;
	info->texture_cap = 0;
	info->mouse_in = 1;
}

void	ft_clock(t_var *info)
{	
	info->oldTime = info->time;
    info->time = SDL_GetTicks();
    info->frameTime = (info->time - info->oldTime) / 1000.0;
    //printf("fps: %f  Speed %f\n",1.0 / info->frameTime, info->moveSpeed); //FPS counter
}

int		get_texture(t_var *info)
{
	if (!(info->text_tab[0] = SDL_LoadBMP("./TEXTURES/wood.bmp")))
	{
		printf("Erreur SDL_LoadBMP : %s\n", SDL_GetError());
		return (0);
	}
	return (1);
}

int main(int ac, char **av)
{
	t_var info;

	if (ac != 2 || ft_reader(av[1], &info) == 0 || checker(&info) == 0)
	{
		printf("Map error!\n");
		return (0);
	}
    if (0 != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_EVENTS))
	{
		printf("Erreur SDL_Init : %s\n", SDL_GetError());
		return (0);
	}
	if (!(info.window = SDL_CreateWindow("wolf3d", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,\
	WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN)))
	{
		printf("Erreur SDL_CreateWindow : %s\n", SDL_GetError());
		SDL_Quit();
		return (0);
	}
	if (!(info.renderer = SDL_CreateRenderer(info.window, -1, SDL_RENDERER_ACCELERATED)))
	{
		printf("Erreur SDL_CreateRenderer : %s\n", SDL_GetError());
		SDL_DestroyWindow(info.window);
		SDL_Quit();
		return (0);
	}
	if (!(info.image = SDL_CreateRGBSurface(0, WINDOW_W, WINDOW_H, 32, RMASK, GMASK, BMASK, AMASK)))
	{
		printf("Erreur SDL_CreateRGBSurface : %s\n", SDL_GetError());
		SDL_DestroyWindow(info.window);
		SDL_Quit();
		return (0);
	}
	info.ori_X = info.posX;
	info.ori_Y = info.posY;
	ft_init_pour_linstant(&info);
	if (!get_texture(&info))
	{
		SDL_DestroyWindow(info.window);
		SDL_Quit();
		return (0);
	}
	while (dealer(&info))
	{
		if (info.mouse_in)
			SDL_SetRelativeMouseMode(SDL_TRUE);
		else
			SDL_SetRelativeMouseMode(SDL_FALSE);
		rotate(&info);
		ft_clock(&info);
		ft_multithreading(&info);
		if (!(info.texture = SDL_CreateTextureFromSurface(info.renderer, info.image)))
		{
			printf("Erreur SDL_CreateRGBSurface : %s\n", SDL_GetError());
			SDL_DestroyWindow(info.window);
			SDL_Quit();
			return (0);
		}
		if (SDL_RenderCopy(info.renderer, info.texture, NULL, NULL))
		{
			printf("Erreur SDL_RenderCopy : %s\n", SDL_GetError());
			SDL_DestroyWindow(info.window);
			SDL_Quit();
			return (0);
		}
		SDL_RenderPresent(info.renderer);
		SDL_DestroyTexture(info.texture);
	}
	SDL_FreeSurface(info.image);
	SDL_DestroyWindow(info.window);
	SDL_Quit();
	return (0);
}