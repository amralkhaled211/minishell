/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:31:00 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/05 13:04:14 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	my_sprintf(char *buffer, const char *format, const char *insert)
{
	const char	*p;
	char		*buf_ptr;

	p = format;
	buf_ptr = buffer;
	while (*p)
	{
		if (*p == '%' && *(p + 1) == 's')
		{
			ft_memcpy(buf_ptr, insert, ft_strlen(insert));
			buf_ptr += ft_strlen(insert);
			p += 2;
		}
		else
			*buf_ptr++ = *p++;
	}
	*buf_ptr = '\0';
}

static char	*join_strs(char *str, char *add)
{
	char	*tmp;

	if (!add)
		return (str);
	if (!str)
		return (ft_strdup(add));
	tmp = str;
	str = ft_strjoin(tmp, add);
	free(tmp);
	return (str);
}

int	cmd_printf(char *detail, char *error_msg, char *command, int error_nb)
{
	char	*msg;

	msg = ft_strdup("minishell: ");
	if (detail != NULL)
	{
		msg = join_strs(msg, detail);
		msg = join_strs(msg, ": ");
	}
	if (error_msg != NULL)
	{
		msg = join_strs(msg, error_msg);
		msg = join_strs(msg, ": ");
	}
	if (command != NULL)
		msg = join_strs(msg, command);
	ft_putendl_fd(msg, 2);
	free(msg);
	return (error_nb);
}
