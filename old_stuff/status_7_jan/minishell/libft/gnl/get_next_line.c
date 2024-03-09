/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:03:11 by aismaili          #+#    #+#             */
/*   Updated: 2023/12/08 20:15:41 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *ncall)
{
	int		b_read;
	char	*buf;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
	{
		if (ncall != NULL)
			free(ncall);
		return (NULL);
	}
	b_read = 1;
	while (!ft_strchrgnl(ncall, '\n') && b_read != 0)
	{
		b_read = read(fd, buf, BUFFER_SIZE);
		if (b_read == -1)
		{
			free(buf);
			free(ncall);
			return (NULL);
		}
		buf[b_read] = '\0';
		ncall = ft_strjoingnl(ncall, buf);
	}
	free(buf);
	return (ncall);
}

char	*ft_get_line(char *ncall)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	if (!ncall[i])
		return (NULL);
	while (ncall[i] != '\0' && ncall[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	while (j < i)
	{
		line[j] = ncall[j];
		j++;
	}
	if (ncall[i] == '\n')
	{
		line[i] = ncall[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*last_read(char *ncall)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (ncall[i] && ncall[i] != '\n')
		i++;
	if (!ncall[i])
	{
		free(ncall);
		return (NULL);
	}
	temp = malloc(sizeof(char) * (ft_strlengnl(ncall) - i + 1));
	if (!temp)
		return (free(ncall), NULL);
	i++;
	while (ncall[i])
		temp[j++] = ncall[i++];
	temp[j] = '\0';
	free(ncall);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*ncall;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	errno = 0;
	ncall = read_line(fd, ncall);
	if (!ncall)
		return (NULL);
	line = ft_get_line(ncall);
	ncall = last_read(ncall);
	return (line);
}

/* int	main(void)
{
	int fd = open("text.txt", O_RDONLY);

	
	char *line = _line(fd);
	if (line == NULL)
		return (free(line), 0);
	printf("%s", line);
	free(line);
	line = _line(fd);
	if (line == NULL)
		return (free(line),0);
	printf("%s", line);
	free(line);
	line = _line(fd);
	if (line == NULL)
		return (free(line),0);
	printf("%s", line);
	free(line);
	line = _line(fd);
	if (line == NULL)
		return (free(line),0);
	printf("%s", line);
	free(line);
	line = _line(fd);
	printf("%s", line);
	free(line);
	line = _line(fd);
	printf("%s", line);
	free(line);
	line = _line(fd);
	printf("%s", line);
	free(line);
	line = _line(fd);
	printf("%s", line);
	free(line);
	line = _line(fd);
	printf("%s", line);
	free(line);
	line = _line(fd);
	printf("%s", line);
	free(line);
	line = _line(fd);
	printf("%s", line);
	free(line);
	return (0);
} */
