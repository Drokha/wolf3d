/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testaffichage3d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:49:37 by trabut            #+#    #+#             */
/*   Updated: 2020/01/22 15:59:53 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/wolf3d.h"

static void		draw_sky_grd(t_thrd *thrd, t_var *info)
{
	int y;
	int top_wall;

	y = 0;
	while (y < thrd->y1 - info->y_dec)
	{
		put_pixel_to_suface(SKY_BLUE, thrd->x, y, info->image);
		y++;
	}
	top_wall = thrd->y2 - info->y_dec;
	if (top_wall > WINDOW_H)
		top_wall = WINDOW_H;
	y = top_wall;
	while (y < WINDOW_H)
	{
		put_pixel_to_suface(GRASS_GREEN, thrd->x, y, info->image);
		y++;
	}
	put_pixel_to_suface(BLACK, thrd->x, thrd->y1 - info->y_dec, info->image);
	put_pixel_to_suface(BLACK, thrd->x, thrd->y2 - info->y_dec, info->image);
}

Uint32			get_pixel(SDL_Surface *tex, int x, int y)
{
	Uint32 color;
	Uint32 *pixels;

	color = 0;
	pixels = tex->pixels;
	if (x >= 0 && y >= 0 && x < tex->w && y < tex->h)
	{
		color = pixels[tex->w * y + x];
	}
	return (color);
}

static	int		put_text_to_wall(t_thrd *thrd, int x)
{
	int		y;
	Uint32	color;

	y = thrd->y1;
	while (y < thrd->y2)
	{
		thrd->text.tex_y = (y - thrd->y1) * thrd->text.texheight;
		thrd->text.tex_y /= thrd->y2 - thrd->y1;
		if (thrd->text.tex_y > thrd->text.texheight)
			thrd->text.tex_y = thrd->text.texheight;
		if (thrd->text.tex_y < 0)
			thrd->text.tex_y = 0;
		if (thrd->text.tex_x > thrd->text.texwidth)
			thrd->text.tex_x = thrd->text.texwidth;
		if (thrd->text.tex_x < 0)
			thrd->text.tex_x = 0;
		color = get_pixel(thrd->info->text_tab[thrd->text.tex_id],
		thrd->text.tex_x, (int)thrd->text.tex_y);
		put_pixel_to_suface(color, x,
		y - thrd->info->y_dec, thrd->info->image);
		y++;
	}
	draw_sky_grd(thrd, thrd->info);
	return (1);
}

int				texturer(t_thrd *thrd, int x)
{
	thrd->text.tex_id = tex_sider(thrd);
	thrd->text.texheight = thrd->info->text_tab[thrd->text.tex_id]->h;
	thrd->text.texwidth = thrd->info->text_tab[thrd->text.tex_id]->w;
	if (thrd->side == 0)
		thrd->text.wall_x = thrd->info->posy +
		thrd->perpwalldist * thrd->raydiry;
	else
		thrd->text.wall_x = thrd->info->posx +
		thrd->perpwalldist * thrd->raydirx;
	thrd->text.wall_x -= floor(thrd->text.wall_x);
	thrd->text.tex_x = (thrd->text.wall_x * thrd->text.texwidth);
	securise_y1_y2(thrd);
	put_text_to_wall(thrd, x);
	return (1);
}

void			draw_ray(t_thrd *thrd, t_var *info)
{
	int y;
	int top_wall;

	top_wall = thrd->y2 - info->y_dec;
	y = thrd->y1 - info->y_dec;
	if (y < 0)
		y = 0;
	if (top_wall > WINDOW_H)
		top_wall = WINDOW_H;
	while (y <= top_wall)
	{
		sider(thrd, info, thrd->x, y);
		y++;
	}
	draw_sky_grd(thrd, info);
}
