/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 14:27:51 by lbonnete          #+#    #+#             */
/*   Updated: 2019/06/01 16:31:42 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef WOLF3D_H
# define WOLF3D_H

# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <pthread.h>
# include "../libft/libft.h"
# include "SDL.h"
# include "SDL_mixer.h"
# include "SDL_net.h"
# define WINDOW_W 1600
# define WINDOW_H 900
# define w_h WINDOW_W/2
# define NB_THREADS_MAX 1
# define BLACK 0x000000
# define SKY_BLUE 0x00BFFF
# define GRASS_GREEN 0x1FBC3F
# define SOUTH_WALL 0xd2b48c
# define NORTH_WALL 0xD28F8F
# define EAST_WALL 0xDAA520
# define WEST_WALL 0xF4A460
# define RMASK 0
# define GMASK 0
# define BMASK 0
# define AMASK 0
# define EXIT_W 1
# define NORTH	2
# define SOUTH	3
# define WEST	4
# define EAST	5

typedef struct s_input	t_input;
typedef struct s_mthrds	t_mthrds;
typedef struct s_thrd	t_thrd;
typedef	struct s_var	t_var;
typedef	struct s_text	t_text;
struct	s_thrd
{
	int			id;
	double rayDirX;
	double rayDirY;
	int mapX;
	int mapY;
	double sideDistX;
    double sideDistY;
	double deltaDistX;
    double deltaDistY;
    double perpWallDist;
	int lineheight;
	int stepX;
    int stepY;
	int hit;
	int side;
	int		x;
	int		x1;
	int		x2;
	int		y1;
	int		y2;
	double cameraX;
	t_var	*info;
	t_text	*text;
};

struct s_text
{
	int 	tex_id;
	double	wall_x;
	int 	tex_x;
	int		tex_y;
	int		texWidth;
	int		texHeight;
	Uint32	color;
};


struct	s_mthrds
{
	pthread_t	threads[NB_THREADS_MAX];
	t_thrd		thrd[NB_THREADS_MAX];
};

struct	s_var
{
	SDL_Window *window;
	SDL_Event *event;
	SDL_Renderer *renderer;
	SDL_Surface *text_tab[4];
	SDL_Surface *image;
	SDL_Texture *texture;
	int		texture_cap;
	int		mouse_in;
	int		p_x;
	int		p_y;
	float	pf_x;
	float	pf_y;
	float	c_angl;
	char	**map;
	double posX;
	double posY;
	double ori_X;
	double ori_Y;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double time;
	double oldTime;
	double time_reset;
	double moveSpeed;
    double rotSpeed;
	double oldDirX;
	double oldPlaneX;
	double frameTime;
	int sprint;
	int	x_dec;
	int y_dec;
	t_mthrds mthrds;
};


struct s_input
{
	int up;
	int down;
	int straf_left;
	int straf_right;
	int left;
	int right;
};


char				**realloc_map(char **map, int len);
void				destroy_tab(char ***tab);
int					dealer(t_var *info);
void    			*algo(void *thrds);
void  				draw_ray(t_thrd *thrd, t_var *info);
float			   	ft_fabs(float a);
int     			verti_check(char *line);
int					get_char_map(int fd, t_var *info);
int     			spawn_and_top_checker(t_var *info);
int					bottom_checker(t_var *info);
int					ft_reader(char *name, t_var *info);
int					checker(t_var *info);
void				sider(t_thrd *thrd, t_var *info, int x, int y);
void				get_speed(t_var *info);
void				ft_clock(t_var *info);
void 				rotate(t_var *info);
void				ft_multithreading(t_var *info);
void				put_pixel_to_suface(Uint32 color, int x, int y, SDL_Surface *image);
void				ft_init_pour_linstant(t_var *info);
int					tex_sider(t_thrd *thrd);
int					texturer(t_thrd *thrd, int x);

#endif