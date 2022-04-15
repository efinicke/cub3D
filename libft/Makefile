# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/16 13:02:00 by spayeur           #+#    #+#              #
#    Updated: 2022/04/10 22:22:48 by efinicke         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	ft_bzero.c ft_isdigit.c ft_isspace.c ft_strlen.c \
				ft_putchar_fd.c ft_putstr_fd.c \
				ft_strncmp.c \
				get_next_line.c get_next_line_utils.c

OBJS		=	${SRCS:.c=.o}

NAME		=	libft.a
 
CC			=	gcc
RM			=	rm -f

CFLAGS		=	-Wall -Wextra -Werror

all:		${NAME}

${OBJS}:	libft.h

$(NAME):	${OBJS}
			ar rc ${NAME} ${OBJS}

clean:
			${RM} ${OBJS} ${B_OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
