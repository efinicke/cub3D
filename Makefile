# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/21 19:40:58 by spayeur           #+#    #+#              #
#    Updated: 2022/04/13 12:35:35 by spayeur          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                 Informations                                 #
# **************************************************************************** #

CUB3D				=	cub3D
CUB3D_BONUS			=	cub3D_bonus

CC					=	gcc
#CFLAGS				=	-Wall -Wextra -Werror
SRCS_DIR			=	./srcs
#BONUS				=	./bonus
INCLUDE				=	./includes/cub3d.h
#INCLUDE_BONUS		=	./includes/cub3d_bonus.h

LIBFT				=	./libft
LIBFT_FLAGS			=	-lft -L ./libft
INCLUDE_LIBFT		=	./libft/libft.a
LIBMLX				=	./miniLibX
LIBMLX_FLAGS		=	-lmlx_Linux -lXext -lX11 -L ./miniLibX
INCLUDE_LIBMLX		=	./miniLibX/libmlx_Linux.a

# Comment/uncomment the line below to disable/enable the mute mode
MUTE				=	@

# **************************************************************************** #
#                                    C0l0r$                                    #
# **************************************************************************** #

# Regular Colors
BLACK			:= $(shell tput -Txterm setaf 0)
RED				:= $(shell tput -Txterm setaf 1)
GREEN			:= $(shell tput -Txterm setaf 2)
YELLOW			:= $(shell tput -Txterm setaf 3)
BLUE			:= $(shell tput -Txterm setaf 4)
MAGENTA			:= $(shell tput -Txterm setaf 5)
CYAN			:= $(shell tput -Txterm setaf 6)
WHITE			:= $(shell tput -Txterm setaf 7)

# Bold
BOLD			:= $(shell tput -Txterm bold)
BBLACK			= ${BOLD}${BLACK}
BRED			= ${BOLD}${RED}
BGREEN			= ${BOLD}${GREEN}
BYELLOW			= ${BOLD}${YELLOW}
BBLUE			= ${BOLD}${BLUE}
BMAGENTA		= ${BOLD}${MAGENTA}
BCYAN			= ${BOLD}${CYAN}
BWHITE			= ${BOLD}${WHITE}
END				:= $(shell tput -Txterm sgr0)

# Clear
CLEAR			:= $(shell tput -Txterm clear)
CLEAR_LINE		:= $(shell tput -Txterm el)

# **************************************************************************** #
#                                 Source files                                 #
# **************************************************************************** #

# ********************************** Cub3D *********************************** #

SRC_FILES_CUB3D			=	cub3d.c \
							game_loop.c \
							utils.c

SRCS_CUB3D				=	$(addprefix $(SRCS_DIR)/, $(SRC_FILES_CUB3D))

# ******************************** Structures ******************************** #

SRC_FILES_STRUCTURES	=	cub.c \
							minimap.c \
							player.c \
							init_and_destroy_wall_textures.c \
							img.c \
							point.c

SRCS_STRUCTURES			=	$(addprefix $(SRCS_DIR)/structures/, $(SRC_FILES_STRUCTURES))

# ********************************* Parsing ********************************** #

SRC_FILES_PARSING		=	parse_cub_file.c \
							parse_line.c \
							parse_texture.c parse_color.c \
							parse_map.c parse_player.c \
							parse_utils.c \
							normalize_map.c \
							check_missing_element.c \
							check_map.c 

SRCS_PARSING			=	$(addprefix $(SRCS_DIR)/parsing/, $(SRC_FILES_PARSING))

# ********************************* Drawing ********************************** #

SRC_FILES_DRAWING		=	rect.c \
							circ.c \
							line.c \
							draw_utils.c \
							mlx_linux_workaround.c

SRCS_DRAWING			=	$(addprefix $(SRCS_DIR)/drawing/, $(SRC_FILES_DRAWING))

# ******************************** Raycasting ******************************** #

SRC_FILES_RAYCASTING	=	raycasting.c \
							raycasting_utils.c

SRCS_RAYCASTING			=	$(addprefix $(SRCS_DIR)/raycasting/, $(SRC_FILES_RAYCASTING))

# ******************************** Rendering ********************************* #

SRC_FILES_RENDERING		=	render.c \
							generate_3d_projection.c \
							generate_wall_projection.c \
							minimap_render.c \
							rays_render.c

SRCS_RENDERING			=	$(addprefix $(SRCS_DIR)/rendering/, $(SRC_FILES_RENDERING))

# ********************************** Events ********************************** #

SRC_FILES_EVENTS		=	on_keydown.c \
							on_keyup.c \
							on_destroy.c

SRCS_EVENTS				=	$(addprefix $(SRCS_DIR)/events/, $(SRC_FILES_EVENTS))

# ********************************* Project ********************************** #

SRCS_PROJECT			=	$(SRCS_CUB3D) $(SRCS_STRUCTURES) $(SRCS_PARSING) \
							$(SRCS_DRAWING) $(SRCS_RAYCASTING) $(SRCS_RENDERING) \
							$(SRCS_EVENTS)

# **************************************************************************** #
#                                 Object files                                 #
# **************************************************************************** #

OBJS_PROJECT		=	$(SRCS_PROJECT:.c=.o)

# **************************************************************************** #
#                                    Rules                                     #
# **************************************************************************** #

%.o: %.c
					@printf "${BMAGENTA}%-35.35s\r${END}" $@
					$(MUTE)$(CC) $(CFLAGS) -c $< -o $@

all:				$(CUB3D)

$(CUB3D):			$(OBJS_PROJECT)
ifndef MUTE
					make -C $(LIBFT)
					make -C $(LIBMLX)
else
					@make -C $(LIBFT) >/dev/null
					@make -C $(LIBMLX) >/dev/null
endif
					$(MUTE)$(CC) $(CFLAGS) $(OBJS_PROJECT) -I $(INCLUDE) $(INCLUDE_LIBFT) ${INCLUDE_LIBMLX} $(LIBFT_FLAGS) ${LIBMLX_FLAGS} -lm -o $(CUB3D) 
					@echo -n "$(CLEAR_LINE)"
					@echo "${BCYAN}$(CUB3D) ${BGREEN}has been build ! ${END}"

$(CUB3D_BONUS):
					@echo "${YELLOW}No bonus for this project.$(END)"

clean:
					@echo "${BBLUE}Cleaning...${END}"
ifndef MUTE
					rm -f $(OBJS_PROJECT)
					make clean -C $(LIBFT)
					make clean -C $(LIBMLX)
					@echo "${CYAN}All object files ${BGREEN}have been removed.${END}"
else
					@make clean -C $(LIBFT) >/dev/null
					@make clean -C $(LIBMLX) >/dev/null
					@echo -n "${CYAN}"`rm -vf $(OBJS_PROJECT) | wc -l`
					@echo " object file(s) ${BGREEN}has/have been removed.${END}"
endif

fclean:				clean
ifndef MUTE
					rm -f $(CUB3D)
					make fclean -C $(LIBFT)
					make fclean -C $(LIBMLX)
					@echo "${CYAN}$(CUB3D)${END} ${BGREEN}has been removed.${END}"
else
					@make fclean -C $(LIBFT) >/dev/null
					@make fclean -C $(LIBMLX) >/dev/null
					@rm $(CUB3D) 2>/dev/null && \
					echo "${CYAN}$(CUB3D)${END} ${BGREEN}has been removed.${END}" || true
endif

re:					fclean all

bonus:				$(CUB3D_BONUS)

.PHONY:				all clean fclean re bonus
