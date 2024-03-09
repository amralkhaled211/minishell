/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:58:07 by aismaili          #+#    #+#             */
/*   Updated: 2024/02/11 18:53:04 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

/* 	Generates a unique name for the current heredoc.
*	Returns the new heredoc name. */

char	*get_heredoc_name(void)
{
	static int	i;
	char		*name;
	char		*number;

	number = ft_itoa(i);
	if (!number)
		return (NULL);
	name = ft_strjoin(HEREDOC_NAME, number);
	free(number);
	i++;
	return (name);
}

int		check_heredoc_line(t_shell *shell, char **line, t_redirection *io, int *ret)
{
	if (*line == NULL)
	{
		printf("warning heredoc end-of-file: wanted\n");
		*ret = 1;
		return (1);
	}
	if (ft_strcmp(*line, io->file) == 0) // I implmented the strcmp function on  the libft 
	{
		*ret = 1;
		return (1);
	}
	if (ft_strchr(*line,  '$'))
	{
		*line = doc_expand(shell, *line);
		if (!(*line))
		{
			free (line);
			*ret = 0;
			return(1);
		}
	}
	return (0);
}

int		fill_heredoc(t_shell *shell, t_redirection *io, int fd)
{
	char	*line;
	int		ret;

	ret = 1;
	line = NULL;
	while (1)
	{
		line = readline(">");
		if (check_heredoc_line(shell, &line, io, &ret) == 1)
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(line);
	return (ret);
}

int		open_heredoc(t_shell *shell, t_redirection	*io)
{
	int		tmp_fd;
	int		ret;

	ret = 0;
	tmp_fd = open(io->docfl, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ret = fill_heredoc(shell, io, tmp_fd);
	close(tmp_fd);
	return (ret);
}

char	*delete_and_replace_for_doc(char *value, char *str, int ind)
{
	int	len;
	char *new;

	len = (ft_strlen(str) - var_len(str + ind) + ft_strlen(value));
	new = get_value_to_str(str, value, len, ind);
	return (new);
}
