/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 15:51:41 by lbonnete          #+#    #+#             */
/*   Updated: 2019/05/31 16:27:12 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/wolf3d.h"

void	get_speed(t_var *info)
{
	if (info->map[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)] == '#'||
		info->map[(int)(info->posX)][(int)(info->posY + info->dirY * info->moveSpeed)] == '#')
	{
		info->moveSpeed = info->frameTime * 0.8;
		info->rotSpeed = info->frameTime * 0.9;
	}
	else 
	{
		if (info->sprint)
		{
			info->moveSpeed = info->frameTime * 4;
			info->rotSpeed = info->frameTime * 1.3;
		}
		else
		{
			info->moveSpeed = info->frameTime * 2.0;
			info->rotSpeed = info->frameTime * 2.8;
		}
	}
}

void		mouser(t_var *info)
{
	int y;

	SDL_GetRelativeMouseState(&(info->x_dec),&y);
	info->y_dec += y;
	if (info->y_dec > WINDOW_H + 500)
		info->y_dec = WINDOW_H  + 500;
	else if (info->y_dec < - 500)
		info->y_dec =  - 500;
}

void	rot_right(t_var *info)
{
	info->oldDirX = info->dirX;
	info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
	info->dirY = info->oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
	info->oldPlaneX = info->planeX;
	info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
	info->planeY = info->oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
}

void	rot_left(t_var *info)
{
	info->oldDirX = info->dirX;
	info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
	info->dirY = info->oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
	info->oldPlaneX = info->planeX;
	info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
	info->planeY = info->oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
}

void 	rotate(t_var *info)
{
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

int		dealer(t_var *info)
{
	SDL_Event event;
	static t_input input;
	double straffer_x;
	double straffer_y;
	int local;

	if (SDL_PollEvent(&event) == 1)
	{
		if (event.type == SDL_QUIT && event.type == SDL_KEYDOWN)
			return (0);
		if (event.key.keysym.sym == SDLK_ESCAPE)
			return (0);
		if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP)
    	{
			if (event.key.state == SDL_PRESSED)
				input.up = 1;
			else
				input.up = 0;
		}
		if (event.key.keysym.sym == SDLK_t && event.key.state == SDL_PRESSED)
    	{
			if (info->texture_cap == 0)
				info->texture_cap = 1;
			else
				info->texture_cap = 0;
		}
		if (event.key.keysym.sym == SDLK_m && event.key.state == SDL_PRESSED)
    	{
			if (info->mouse_in == 0)
				info->mouse_in  = 1;
			else
				info->mouse_in  = 0;
		}
		if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN)
    	{
			if (event.key.state == SDL_PRESSED)
				input.down = 1;
			else
				input.down = 0;
		}
		if (event.key.keysym.sym == SDLK_a)
    	{
			if (event.key.state == SDL_PRESSED)
				input.straf_left = 1;
			else
				input.straf_left = 0;
		}
		if (event.key.keysym.sym == SDLK_d)
    	{
			if (event.key.state == SDL_PRESSED)
				input.straf_right = 1;
			else
				input.straf_right = 0;
		}
		if (event.key.keysym.sym == SDLK_LEFT)
    	{
			if (event.key.state == SDL_PRESSED)
				input.left = 1;
			else
				input.left = 0;
		}
		if (event.key.keysym.sym == SDLK_RIGHT)
    	{
			if (event.key.state == SDL_PRESSED)
				input.right = 1;
			else
				input.right = 0;
		}
		if (event.key.keysym.sym == SDLK_LSHIFT)
    	{
			if (event.key.state == SDL_PRESSED)
				info->sprint = 1;
			else
				info->sprint = 0;
		}
		if (event.key.keysym.sym == SDLK_DELETE && event.key.state == SDL_PRESSED)
		{
			info->posX = info->ori_X;
			info->posY = info->ori_Y;
			info->time_reset = info->time;
			ft_init_pour_linstant(info);
		}
		if (event.key.keysym.sym == SDLK_PAGEUP && event.key.state == SDL_PRESSED)
		{
			info->y_dec -= 8;
		}
		if (event.key.keysym.sym == SDLK_PAGEDOWN && event.key.state == SDL_PRESSED)
		{
			info->y_dec += 8;
		}
	}
	if (input.right)
	{
		rot_right(info);
	}
	else if (input.left)
	{
		rot_left(info);		
	}
	get_speed(info);
	if (input.up)
	{
		if (info->map[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)] != '#')
			info->posX += info->dirX * info->moveSpeed;
		if (info->map[(int)(info->posX)][(int)(info->posY + info->dirY * info->moveSpeed)] != '#')
			info->posY += info->dirY * info->moveSpeed;
		if (info->map[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)] == 'X')
		{
			local = info->time - info->time_reset;
			ft_putstr("YOU'VE ESCAPED THE PROGRAM IN ");
			ft_putnbr(local / 1000 / 60);
			ft_putstr(" min ");
			ft_putnbr(local / 1000 % 60);
			ft_putstr(" sec and ");
			ft_putnbr(local % 1000);
			ft_putstr(" millisec");
			ft_putendl("!");
			return(0);
		}
	}
	if (input.down)
  	{
  		if (info->map[(int)(info->posX - info->dirX * info->moveSpeed)][(int)(info->posY)] != '#')
			info->posX -= info->dirX * info->moveSpeed;
	   	if (info->map[(int)(info->posX)][(int)(info->posY - info->dirY * info->moveSpeed)] != '#')
			info->posY -= info->dirY * info->moveSpeed;
	}
	if (input.straf_right)
	{
		straffer_x = info->dirY;
		straffer_y = -info->dirX;
		if (info->map[(int)(info->posX + straffer_x * info->moveSpeed)][(int)(info->posY)] != '#')
			info->posX += straffer_x * info->moveSpeed;
		if (info->map[(int)(info->posX)][(int)(info->posY + straffer_y * info->moveSpeed)] != '#')
			info->posY += straffer_y * info->moveSpeed;
	}
	if (input.straf_left)
	{
		straffer_x = -info->dirY;
		straffer_y = info->dirX;
		if (info->map[(int)(info->posX + straffer_x * info->moveSpeed)][(int)(info->posY)] != '#')
			info->posX += straffer_x * info->moveSpeed;
		if (info->map[(int)(info->posX)][(int)(info->posY + straffer_y * info->moveSpeed)] != '#')
			info->posY += straffer_y * info->moveSpeed;
	}
	return (1);
}