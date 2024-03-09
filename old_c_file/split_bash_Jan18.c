/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_bash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:00:17 by aismaili          #+#    #+#             */
/*   Updated: 2024/01/18 21:09:51 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include "microshell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len);

void	reset_split_var(t_split *split)
{
	split->a = 0;
	split->i = 0;
	split->arg_end = 0;
	split->arg_start = 0;
	split->in_quotes = false;
	split->is_word = false;
	split->q_start = 0;
	split->quote_char = '\0';
	split->result = NULL;
	split->word_start = 0;
	split->word_end = 0;
}

/* bool	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (true);
	return (false);
} */

void	init_start_end(t_split *split, char *input, char *delimeter)
{
	if (split->in_quotes == false && split->i > 0 && !strchr(delimeter, input[split->i - 1]) && input[split->i - 1] != '|')
	{
		split->q_start = split->i;
		while (split->q_start > 0 && !strchr(delimeter, input[split->q_start]))
		{
			split->q_start--;
		}
		split->arg_start = split->q_start;
		split->q_start = split->i;
	}
	else if (split->in_quotes == false && split->i > 0 && strchr(delimeter, input[split->i - 1]) || input[split->i - 1] == '|')//delimeter before quote sign
	{
		split->q_start = split->i;
		split->arg_start = split->i;
	}
}

void	save_quote(t_split *split, char *input, char *delimeter)
{
	split->i++;
	while (input[split->i] && !strchr(delimeter, input[split->i]) && input[split->i] != '|')
		split->i++;
	split->arg_end = split->i--;
	split->result[split->a++] = ft_substr(input, split->arg_start, (split->arg_end - split->arg_start));
	split->is_word = false;
}

void	save_word(t_split *split, char *input, char *delimeter)
{
	if (split->is_word)
	{
		split->word_end = split->i - 1;
		while (split->word_end >= 0 && (!strchr(delimeter, input[split->word_end])))
		{
			if (input[split->word_end] == '|' && (!strchr(delimeter, input[split->word_end - 1]) || !strchr(delimeter, input[split->word_end + 1])))
				break ;
			split->word_end--;
		}
		split->word_start = split->word_end + 1;
		split->word_end = split->i;
		split->result[split->a++] = ft_substr(input, split->word_start, (split->word_end - split->word_start));
		split->is_word = false;
	}
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	size_t			b;
	unsigned char	*sub;

	i = 0;
	b = 0;
	if (s == NULL)
		return (NULL);
	if (len > strlen(s) - start)
		len = strlen(s) - start;
	if (start > strlen(s))
		len = 0;
	sub = malloc(((len + 1) * sizeof(char)));
	if (sub == NULL)
		return (NULL);
	while (s[i])
	{
		if (i >= start && b < len)
			sub[b++] = s[i];
		i++;
	}
	sub[b] = '\0';
	return ((char *)sub);
}

int	pipe_special(size_t *count, char *delimeter, char const *s, int i)
{
	if (!strchr(delimeter, s[i - 1]) && !strchr(delimeter, s[i + 1]))
		(*count) = (*count + 2);
	else if (!strchr(delimeter, s[i - 1]))
		(*count)++;
	else if (!strchr(delimeter, s[i + 1]))
		(*count)++;
	i++;
	return (i);
}

static size_t	count_words(char const *s, char *delimeter, t_split *split)
{
	size_t i;
	size_t count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == '"' || s[i] == '\'') && (!split->in_quotes || split->quote_char == s[i]))
		{
			if (split->in_quotes == false && i > 0 && strchr(delimeter, s[i - 1]))
				split->q_start = i;
			split->in_quotes = !split->in_quotes;
			if (split->in_quotes)
				split->quote_char = s[i];
			else
				split->quote_char = '\0';
			if (!split->in_quotes && split->q_start > 0 && strchr(delimeter, s[split->q_start - 1]))
			{
				count++;
				split->is_word = false;
			}
			i++;
		}
		else if (s[i] == '|' && (!strchr(delimeter, s[i - 1]) || !strchr(delimeter, s[i + 1])) && !split->in_quotes)//ignore if stand alone '|'
			i = pipe_special(&count, delimeter, s, i);
		else if ((strchr(delimeter, s[i])) && !split->in_quotes)
		{
			if (split->is_word)
			{
				count++;
				split->is_word = false;
			}
			i++;
		}
		else
		{
			split->is_word = true;
			i++;
		}
	}
	if (split->is_word || split->in_quotes)// If we end on a word or inside quotes
		count++;
	return (count);
}

int	ft_pipe_special(char *input, char *delimeter, t_split *split)
{
	if (!strchr(delimeter, input[split->i - 1]) && !strchr(delimeter, input[split->i + 1]))
	{
		save_word(split, input, delimeter);
		split->result[split->a++] = ft_substr(input, split->i, 1);
		split->i++;
	}
	else if (!strchr(delimeter, input[split->i - 1]))
	{
		save_word(split, input, delimeter);
		split->result[split->a++] = ft_substr(input, split->i, 1);
		split->i++;
	}
	else if (!strchr(delimeter, input[split->i + 1]))
	{
		save_word(split, input, delimeter);
		split->result[split->a++] = ft_substr(input, split->i, 1);
		split->i++;
	}
	return (split->i);
}

char	**ft_split_bash(char *input, char *delimeter)
{
	t_split	split;

	reset_split_var(&split);
	split.num_words = count_words(input, delimeter, &split);
	printf("%d\n", split.num_words);
	if (!split.num_words)
		return (NULL);
	reset_split_var(&split);
	split.result = malloc(sizeof(char *) * (split.num_words + 1));
	if (!split.result)
		return (NULL);
	while (input[split.i])
	{
		if ((input[split.i] == '"' || input[split.i] == '\'') && (!split.in_quotes || split.quote_char == input[split.i]))
		{
			init_start_end(&split, input, delimeter);
			split.in_quotes = !split.in_quotes;
			if (split.in_quotes)
				split.quote_char = input[split.i];
			else
				split.quote_char = '\0';
			if (!split.in_quotes)
				save_quote(&split, input, delimeter);
			split.i++;
		}
		else if (input[split.i] == '|' && (!strchr(delimeter, input[split.i - 1]) || !strchr(delimeter, input[split.i + 1])) && !split.in_quotes)//ignore if stand alone '|'
			split.i = ft_pipe_special(input, delimeter, &split);
		else if ((strchr(delimeter, input[split.i]) || input[split.i] == 0) && !split.in_quotes)
		{
			save_word(&split, input, delimeter);
			split.i++;
		}
		else
		{
			split.is_word = true;
			split.i++;
		}
	}
	if (split.in_quotes)
		save_quote(&split, input, delimeter);
	else if (input[split.i] == 0 && !strchr(delimeter, input[split.i - 1]) && !split.in_quotes)
		save_word(&split, input, delimeter);
	split.result[split.a] = NULL;
	return (split.result);
}

int main(int ac, char *av[])
{
	(void)ac;
	//char *input = readline("$ ");
    char **result = ft_split_bash("'ls'\"-l\"|\"wc\" | wc", " \t");
    int i = 0;
    while (result[i])
    {
        printf("%s\n", result[i]);
        free(result[i]);
        i++;
    }
    free(result);
}
