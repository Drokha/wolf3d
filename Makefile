# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/18 15:34:09 by trabut            #+#    #+#              #
#    Updated: 2019/05/29 16:36:34 by lbonnete         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3D

FLAGS       = -Wall -Wextra -Werror -O3
SDL2		= -framework SDL2
SDL2_MIXER	= -framework SDL2_mixer
SDL2_NET	= -framework SDL2_net

SDL2_HEADER			= -I Frameworks/SDL2.framework/Headers/
SDL2_HEADER_MIXER	= -I Frameworks/SDL2_mixer.framework/Headers/
SDL2_HEADER_NET	    = -I Frameworks/SDL2_net.framework/Headers/

SDL			= -F Frameworks $(SDL2) $(SDL2_MIXER) $(SDL2_NET)
SDL_HEADER	= -F Frameworks $(SDL2_HEADER) $(SDL2_HEADER_MIXER) $(SDL2_HEADER_NET)

LIBFT = libft/libft.a

CC = gcc

HEAD_DIR = INC
SRC_DIR	 = SRC
OBJ_DIR	 = OBJ

SRC =	main.c\
		dealers.c\
		testaffichage3d.c\
		tools.c\
		algo.c\
		tools2.c\
		checker.c\
		mapper.c\
		ft_multi.c

INC = graphic_bibl.h wolf3d.h
OBJ	= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

$(shell mkdir -p $(OBJ_DIR))

all: $(NAME)
	echo "wolf3D ready"

$(NAME): $(OBJ) $(LIBFT)
	$(CC) -I $(HEAD_DIR) -o $@ $(OBJ) $(SDL) $(LIBFT) $(FLAGS) 


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -I $(HEAD_DIR) -o $@ $(SDL_HEADER) -c $< $(FLAGS)

$(LIBFT):
	make -C libft/ libft.a

p: all clean

clean:
	make clean -C libft
	/bin/rm -f $(OBJ)
	echo "Objects Destroyed"

fclean:	clean
	make fclean -C libft
	/bin/rm -f $(NAME)
	echo "Project Destroyed"

re:	fclean all

norm:
	$(NORMINETTE) $(SRC_DIR)/ $(HEAD_DIR)/

sdl:

.PHONY:	all clean fclean re norm p

.SILENT: