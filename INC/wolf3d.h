/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewis <lewis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 14:27:51 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/22 17:39:38 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include <SDL.h>
# include <SDL_image.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <pthread.h>
# include "../libft/libft.h"
# define WINDOW_W			1280
# define WINDOW_H			720
# define W_H 				853
# define NB_THREADS_MAX		12
# define BLACK				0x000000
# define SKY_BLUE			0x00BFFF
# define GRASS_GREEN		0x1FBC3F
# define SOUTH_WALL			0xd2b48c
# define NORTH_WALL			0xD28F8F
# define EAST_WALL			0xDAA520
# define WEST_WALL			0xF4A460
# define RMASK				0
# define GMASK				0
# define BMASK				0
# define AMASK				0
# define EXIT_W				4
# define NORTH				3
# define SOUTH				2
# define WEST				1
# define EAST				0

typedef struct s_input	t_input;
typedef struct s_mthrds	t_mthrds;
typedef struct s_thrd	t_thrd;
typedef	struct s_var	t_var;
typedef	struct s_text	t_text;

struct					s_text
{
	int					tex_id;
	double				wall_x;
	double				tex_x;
	double				tex_y;
	int					texwidth;
	int					texheight;
	Uint32				color;
};

struct					s_thrd
{
	int					id;
	double				raydirx;
	double				raydiry;
	int					mapx;
	int					mapy;
	double				sidedistx;
	double				sidedisty;
	double				deltadistx;
	double				deltadisty;
	double				perpwalldist;
	int					lineheight;
	int					stepx;
	int					stepy;
	int					hit;
	int					side;
	int					x;
	int					x1;
	int					x2;
	int					y1;
	int					y2;
	double				camerax;
	t_var				*info;
	t_text				text;
};

struct					s_mthrds
{
	pthread_t			threads[NB_THREADS_MAX];
	t_thrd				thrd[NB_THREADS_MAX];
};

struct					s_var
{
	SDL_Window			*window;
	SDL_Event			*event;
	SDL_Renderer		*renderer;
	SDL_Surface			*text_tab[6];
	SDL_Surface			*image;
	SDL_Texture			*texture;
	int					weapon_cap;
	int					texture_cap;
	int					mouse_in;
	int					p_x;
	int					p_y;
	float				pf_x;
	float				pf_y;
	float				c_angl;
	char				**map;
	double				posx;
	double				posy;
	double				ori_x;
	double				ori_y;
	double				dirx;
	double				diry;
	double				planex;
	double				planey;
	double				time;
	double				oldtime;
	double				time_reset;
	double				movespeed;
	double				rotspeed;
	double				olddirx;
	double				oldplanex;
	double				frametime;
	int					sprint;
	int					x_dec;
	int					y_dec;
	t_mthrds			mthrds;
};

struct					s_input
{
	int					up;
	int					down;
	int					straf_left;
	int					straf_right;
	int					left;
	int					right;
	double				straffer_x;
	double				straffer_y;
	double				diag_x;
	double				diag_y;
	int					diag;
};

char					**realloc_map(char **map, int len);
void					destroy_tab(char ***tab);
int						dealer(t_var *info);
void					*algo(void *thrds);
void					draw_ray(t_thrd *thrd, t_var *info);
float					ft_fabs(float a);
int						verti_check(char *line);
int						get_char_map(int fd, t_var *info);
int						spawn_and_top_checker(t_var *info);
int						bottom_checker(t_var *info);
int						ft_reader(char *name, t_var *info);
int						checker(t_var *info);
void					sider(t_thrd *thrd, t_var *info, int x, int y);
void					get_speed(t_var *info);
void					ft_clock(t_var *info);
void					rotate(t_var *info);
void					ft_multithreading(t_var *info);
void					put_pixel_to_suface(Uint32 color,
						int x, int y, SDL_Surface *image);
void					ft_init_pour_linstant(t_var *info);
int						tex_sider(t_thrd *thrd);
int						texturer(t_thrd *thrd, int x);
Uint32					get_pixel(SDL_Surface *tex, int x, int y);
void					securise_y1_y2(t_thrd *thrd);
int						init_win1(t_var *info);
int						init_win2(t_var *info);
int						frame(t_var *info);
void					rot_left(t_var *info);
void					rot_right(t_var *info);
void					mouse_and_texture(t_var *info, SDL_Event event);
void					get_move1(SDL_Event event, t_input *input);
void					get_move2(SDL_Event event, t_input *input);
int						move(t_var *info, t_input input);
void					reset_and_head(t_var *info, SDL_Event event);
int						escape(t_var *info);
int						hitboxx(t_var *info, double dirx);
int						hitboxy(t_var *info, double diry);
void					free_surfaces(t_var *info);
void					move_diag(t_input *input);
void					diag(t_var *info, t_input input);
void					diag1(t_var *info, t_input input);
void					diag2(t_var *info, t_input input);
void					diag3(t_var *info, t_input input);
void					diag4(t_var *info, t_input input);

#endif
