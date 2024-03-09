/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:19:32 by aismaili          #+#    #+#             */
/*   Updated: 2023/12/08 20:12:16 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

char	*get_next_line(int fd);
size_t	ft_strlengnl(char *s);
char	*ft_strchrgnl(char *s, int c);
char	*ft_strjoingnl(char *s1, char *s2);

#endif
