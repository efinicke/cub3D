/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>		    +#+  +:+	   +#+	      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 15:01:14 by spayeur           #+#    #+#             */
/*   Updated: 2022/04/06 23:13:49 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>

void    ft_bzero(void *ptr, size_t size);
int		ft_isdigit(const char c);
int		ft_isspace(const char c);
size_t	ft_strlen(const char *s);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(const char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

int		get_next_line(int fd, char **line, int stop);
int		ft_mallocprotect(char **p1, char **p2, int ret);
int		ft_strlcatbuffermanager(char **line, char *buffer, \
		unsigned int size);

#endif
