/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealers3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/03/05 15:06:35 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/wolf3d.h"

void	mouse_and_texture(t_var *info, SDL_Event event)
{
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
			info->mouse_in = 1;
		else
			info->mouse_in = 0;
	}
	if (event.key.keysym.sym == SDLK_g && event.key.state == SDL_PRESSED)
	{
		if (info->weapon_cap == 0)
			info->weapon_cap = 1;
		else
			info->weapon_cap = 0;
	}
}

void	get_move1(SDL_Event event, t_input *input)
{
	if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP
	|| event.key.keysym.sym == SDLK_z)
	{
		if (event.key.state == SDL_PRESSED)
			input->up = 1;
		else
			input->up = 0;
	}
	if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_q)
	{
		if (event.key.state == SDL_PRESSED)
			input->straf_left = 1;
		else
			input->straf_left = 0;
	}
	if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN)
	{
		if (event.key.state == SDL_PRESSED)
			input->down = 1;
		else
			input->down = 0;
	}
}

void	get_move2(SDL_Event event, t_input *input)
{
	if (event.key.keysym.sym == SDLK_d)
	{
		if (event.key.state == SDL_PRESSED)
			input->straf_right = 1;
		else
			input->straf_right = 0;
	}
	if (event.key.keysym.sym == SDLK_LEFT)
	{
		if (event.key.state == SDL_PRESSED)
			input->left = 1;
		else
			input->left = 0;
	}
	if (event.key.keysym.sym == SDLK_RIGHT)
	{
		if (event.key.state == SDL_PRESSED)
			input->right = 1;
		else
			input->right = 0;
	}
}

int		move(t_var *info, t_input input)
{
	if (input.up && input.diag == 0)
	{
		if (info->map[(int)(info->posx + info->dirx * info->movespeed)]
		[(int)(info->posy)] != '#' && hitboxx(info, info->dirx))
			info->posx += info->dirx * info->movespeed;
		if (info->map[(int)(info->posx)][(int)(info->posy + info->diry
		* info->movespeed)] != '#' && hitboxy(info, info->diry))
			info->posy += info->diry * info->movespeed;
	}
	if (input.down && input.diag == 0)
	{
		if (info->map[(int)(info->posx - info->dirx * info->movespeed)]
		[(int)(info->posy)] != '#' && hitboxx(info, (-1) * info->dirx))
			info->posx -= info->dirx * info->movespeed;
		if (info->map[(int)(info->posx)][(int)(info->posy - info->diry
		* info->movespeed)] != '#' && hitboxy(info, (-1) * info->diry))
			info->posy -= info->diry * info->movespeed;
	}
	return (1);
}

void	reset_and_head(t_var *info, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_DELETE && event.key.state == SDL_PRESSED)
	{
		info->posx = info->ori_x;
		info->posy = info->ori_y;
		info->time_reset = info->time;
		ft_init_pour_linstant(info);
	}
	if (event.key.keysym.sym == SDLK_PAGEUP && event.key.state == SDL_PRESSED)
		info->y_dec -= 8;
	if (event.key.keysym.sym == SDLK_PAGEDOWN && event.key.state == SDL_PRESSED)
		info->y_dec += 8;
}
