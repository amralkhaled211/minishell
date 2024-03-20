/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 13:34:37 by rluari            #+#    #+#             */
/*   Updated: 2024/03/08 16:28:46 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *leftov_str, char *line);
int		ft_strlen2(char *str);
char	*ft_strchr2(char *str, int c);
char	*ft_strjoin2(char *str, char *buf);
char	*ft_new(char *str);
char	*ft_helper_strhoin(char *str);

#endif