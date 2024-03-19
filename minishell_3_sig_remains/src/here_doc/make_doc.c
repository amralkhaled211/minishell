/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:58:07 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/17 15:31:45 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int	check_heredoc_line(t_shell *shell, char **line, t_redirection *io, int *ret)
{
	if (*line == NULL)
	{
		perror("warning heredoc end-of-file: wanted\n");
		*ret = 1;
		return (1);
	}
	if (ft_strcmp(*line, io->file) == 0)
	{
		*ret = 1;
		return (1);
	}
	if (ft_strchr(*line, '$') && !io->with_quotes)
	{
		errno = 0;
		*line = doc_expand(shell, *line);
		if (!(*line) && errno != 0)
		{
			*ret = -2;
			return (1);
		}
	}
	return (0);
}

static void	signal_handler(int sig)
{
	(void)sig;
	g_exit = 130;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

int	fill_heredoc(t_shell *shell, t_redirection *io, int fd)
{
	struct sigaction	act_here_doc;
	char				*line;
	int					ret;

	ret = 1;
	line = NULL;
	act_here_doc.sa_handler = &signal_handler;
	sigemptyset(&act_here_doc.sa_mask);
	act_here_doc.sa_flags = 0;
	sigaction(SIGINT, &act_here_doc, NULL);
	while (1)
	{
		if (g_exit == 130)
		{
			unlink(io->docfl);
			return (free(line), 2);
		}
		free(line);
		line = readline(">");
		if (check_heredoc_line(shell, &line, io, &ret) == 1)
			break ;
		ft_putendl_fd(line, fd);
	}
	free(line);
	return (ret);
}

int	open_heredoc(t_shell *shell, t_redirection	*io)
{
	int		tmp_fd;
	int		ret;

	tmp_fd = open(io->docfl, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmp_fd == -1)
		free_after_malloc_fail(shell, -1, 4);
	ret = fill_heredoc(shell, io, tmp_fd);
	close(tmp_fd);
	if (ret == -2)
		free_after_malloc_fail(shell, -1, 4);
	return (ret);
}

char	*delete_and_replace_for_doc(char *str, char *value, int ind)
{
	int		len;
	char	*new;

	len = (ft_strlen(str) - var_len(str + ind) + ft_strlen(value));
	new = get_value_to_str(str, value, len, ind);
	return (new);
}
