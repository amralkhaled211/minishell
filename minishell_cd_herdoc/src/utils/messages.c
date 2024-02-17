/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:31:00 by aismaili          #+#    #+#             */
/*   Updated: 2024/01/31 15:18:01 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void my_sprintf(char *buffer, const char *format, const char *insert)//in combination with perror
{
	const char *p = format;
	char *buf_ptr = buffer;

	while (*p)
	{
		if (*p == '%' && *(p + 1) == 's')
		{
			// Copy the insert string
			ft_memcpy(buf_ptr, insert, ft_strlen(insert));
			buf_ptr += strlen(insert);
			p += 2; // Skip over the "%s"
		}
		else
			*buf_ptr++ = *p++;
	}
	*buf_ptr = '\0'; // Null-terminate the buffer
}
