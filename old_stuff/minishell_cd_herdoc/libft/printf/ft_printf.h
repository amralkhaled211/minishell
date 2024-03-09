/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 18:52:42 by aismaili          #+#    #+#             */
/*   Updated: 2023/09/28 18:54:55 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *format, ...);
void	ft_printnbr(int n, int *ct);
void	ft_printstr(char *s, int *ct);
void	ft_printchar(char c, int *ct);
void	ft_printhexas(unsigned int hd, int *ct);
void	ft_printhexab(unsigned int hd, int *ct);
void	ft_printunbr(unsigned int n, int *ct);
void	ft_printaddress(void *ptr, int *ct);

#endif
