/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:31:00 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/16 17:49:19 by aismaili         ###   ########.fr       */
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

/*static char	*join_strs(char *str, char *add)
{
	char	*tmp;

	if (!add)
		return (str);
	if (!str)
	{
		str = ft_strdup(add);
		if (!str)
			return (NULL);
		return (str);
	}
	tmp = str;
	str = ft_strjoin(tmp, add);
	if (!str)
		return (free(tmp), NULL);
	free(tmp);
	return (str);
}

int	cmd_printf(char *detail, char *error_msg, char *command, int error_nb)
{
	char	*msg;

	msg = ft_strdup("minishell: ");
	if (!msg)
		return (-3);
	if (detail != NULL)
	{
		msg = join_strs(msg, detail);
		if (!msg)
			return (-3);
		msg = join_strs(msg, ": ");
		if (!msg)
			return (-3);
	}
	if (error_msg != NULL)
	{
		msg = join_strs(msg, error_msg);
		if (!msg)
			return (-3);
		msg = join_strs(msg, ": ");
		if (!msg)
			return (-3);
	}
	if (command != NULL)
	{
		msg = join_strs(msg, command);
		if (!msg)
			return (-3);
	}
	ft_putendl_fd(msg, 2);
	free(msg);
	return (error_nb);
}*/

static char	*join_strs(char *str, char *add)
{
	char	*tmp;

	if (!add)
		return (str);
	if (!str)
	{
		str = ft_strdup(add);
		return (str);
	}
	tmp = ft_strjoin(str, add);
	free(str);
	return (tmp);
}

static char	*create_error_message(char *msg, char *detail, char *error_msg,
	char *command)
{
	msg = join_strs(msg, detail);
	msg = join_strs(msg, ": ");
	msg = join_strs(msg, error_msg);
	msg = join_strs(msg, ": ");
	msg = join_strs(msg, command);
	return (msg);
}

int	cmd_printf(char *detail, char *error_msg, char *command, int error_nb)
{
	char	*msg;

	msg = ft_strdup("minishell: ");
	if (!msg)
		return (-3);
	if (detail || error_msg || command)
	{
		msg = create_error_message(msg, detail, error_msg, command);
		if (!msg)
			return (-3);
	}
	ft_putendl_fd(msg, 2);
	free(msg);
	return (error_nb);
}
