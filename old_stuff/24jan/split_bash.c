/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_bash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:00:17 by aismaili          #+#    #+#             */
/*   Updated: 2024/01/24 19:39:59 by aismaili         ###   ########.fr       */
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
	split->flag = 0;
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


int	ft_get_redir(char *input, int i, t_split *split)
{
	(void)split;
	if (input[i] == '<') // redirect input
	{
		if (input[i + 1] == '<') // Here doc
			return (2);
		return (1);
	}
	else if (input[i] == '>') // redirect output
	{
		if (input[i + 1] == '>') // Append
			return (2);
		return (1);
	}
	return (0);
}

int	is_op_special(char *input, int i, t_split *split)
{
	if (input[i] == '|')
		return (1);
	if (ft_get_redir(input, i, split) == 1)
		return (2);
	if (ft_get_redir(input, i, split) == 2)
		return (3);
	return (0);
}

void	init_start_end(t_split *split, char *input, char *delimeter)
{
	if (!split->in_quotes && split->i > 0 && !strchr(delimeter, input[split->i - 1]) && !is_op_special(input, split->i - 1, split) && !split->flag)
	{
		split->q_start = split->i;
		while (split->q_start > 0 && !strchr(delimeter, input[split->q_start]))
		{
			if (is_op_special(input, split->q_start - 1, split))
				break ;
			split->q_start--;
		}
		split->arg_start = split->q_start;
		split->q_start = split->i;
	}
	else if (!split->in_quotes && split->i > 0 && (strchr(delimeter, input[split->i - 1]) || is_op_special(input, split->i - 1, split)) && !split->flag)//delimeter before quote sign
	{
		split->q_start = split->i;
		split->arg_start = split->i;
	}
}

int	is_quote(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '"')
		return (2);
	return (0);
}

void	save_quote(t_split *split, char *input, char *delimeter)
{
	if (!split->in_quotes && (strchr(delimeter, input[split->i + 1]) || is_op_special(input, split->i + 1, split) || !input[split->i]))//only go in save_qoute if already at end of token
	{
		split->arg_end = split->i;
		split->result[split->a++] = ft_substr(input, split->arg_start, (split->arg_end - split->arg_start + 1));
		split->is_word = false;
		split->flag = 0;
	}
	else if (!split->in_quotes && is_quote(input[split->i + 1]))
		split->flag = 1;//if next quote -> no need to init_start again, set quote_char and in_quote
	else if (!split->in_quotes && (!strchr(delimeter, input[split->i + 1]) || !is_op_special(input, split->i + 1, split)))
		split->flag = 2;//if next non_deli or non_op -> no need to init_start again, dont set quote_char and in_quote again
}

void	save_word(t_split *split, char *input, char *delimeter)
{
	if (split->is_word)
	{
		split->word_end = split->i - 1;
		while (split->word_end >= 0 && (!strchr(delimeter, input[split->word_end])))
		{
			if (is_op_special(input, split->word_end, split) && (!strchr(delimeter, input[split->word_end - 1]) || !strchr(delimeter, input[split->word_end + 1])))
				break ;
			split->word_end--;
		}
		split->word_start = split->word_end + 1;
		split->word_end = split->i;
		split->result[split->a++] = ft_substr(input, split->word_start, (split->word_end - split->word_start));
		split->is_word = false;
	}
}

/* char	*ft_substr(char const *s, unsigned int start, size_t len)
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
} */

int	pipe_special(int *count, char *delimeter, char *s, int i)
{
	if (!strchr(delimeter, s[i - 1]) && !strchr(delimeter, s[i + 1]) && (!is_quote(s[i - 1]) || !is_op_special(s, i, NULL)))// && s[i - 1] != '\'' && s[i - 1] != '"'
		(*count) = (*count + 2);
	else
		(*count)++;
	i++;
	return (i);
}

int	redir_special(int *count, char *delimeter, char *s, int i)
{
	if (!strchr(delimeter, s[i - 1]) && !strchr(delimeter, s[i + 1]) && (!is_quote(s[i - 1]) || !is_op_special(s, i, NULL)))// && s[i - 1] != '\'' && s[i - 1] != '"'
		(*count) = (*count + 2);
	else
		(*count)++;
	i++;
	return (i);
}

int	appdoc_special(int *count, char *delimeter, char *s, int i)
{
	if (!strchr(delimeter, s[i - 1]) && !strchr(delimeter, s[i + 2]) && (!is_quote(s[i - 1]) || !is_op_special(s, i, NULL)))// && s[i - 1] != '\'' && s[i - 1] != '"'
		(*count) = (*count + 2);
	else if (!strchr(delimeter, s[i - 1]))
		(*count)++;
	else if (!strchr(delimeter, s[i + 2]))
		(*count)++;
	i = i + 2;
	return (i);
}

static size_t	count_words(char *s, char *delimeter, t_split *split)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == '"' || s[i] == '\'') && (!split->in_quotes || split->quote_char == s[i]))
		{
			if (!split->in_quotes && strchr(delimeter, s[i - 1]) && i > 0)
				split->q_start = i;
			split->in_quotes = !split->in_quotes;
			if (split->in_quotes)
				split->quote_char = s[i];
			else
				split->quote_char = '\0';
			if (!split->in_quotes && (strchr(delimeter, s[i + 1]) || is_op_special(s, i + 1, split)))// && (strchr(delimeter, s[split->q_start - 1]) || ) && split->q_start >= 0 
			{
				count++;
				split->is_word = false;
			}
			i++;
		}
		else if (s[i] == '|' && (!strchr(delimeter, s[i - 1]) || !strchr(delimeter, s[i + 1])) && !split->in_quotes)//ignore if stand alone '|'
			i = pipe_special(&count, delimeter, s, i);
		else if (ft_get_redir(s, i, split) == 1 && (!strchr(delimeter, s[i - 1]) || !strchr(delimeter, s[i + 1])) && !split->in_quotes)//ignore if stand alone '>'
			i = redir_special(&count, delimeter, s, i);
		else if (ft_get_redir(s, i, split) == 2 && (!strchr(delimeter, s[i - 1]) || !strchr(delimeter, s[i + 2])) && !split->in_quotes)//ignore if stand alone '>>'
			i = appdoc_special(&count, delimeter, s, i);
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
	if (!strchr(delimeter, input[split->i - 1]) || !strchr(delimeter, input[split->i + 1]))
	{
		save_word(split, input, delimeter);
		split->result[split->a++] = ft_substr(input, split->i, 1);
		split->i++;
	}
	return (split->i);
}

int	ft_redir_special(char *input, char *delimeter, t_split *split)
{
	if (!strchr(delimeter, input[split->i - 1]) || !strchr(delimeter, input[split->i + 1]))
	{
		save_word(split, input, delimeter);
		split->result[split->a++] = ft_substr(input, split->i, 1);
		split->i++;
	}
	return (split->i);
}

int	ft_appdoc_special(char *input, char *delimeter, t_split *split)
{
	if (!strchr(delimeter, input[split->i - 1]) || !strchr(delimeter, input[split->i + 2]))
	{
		save_word(split, input, delimeter);
		split->result[split->a++] = ft_substr(input, split->i, 2);
		split->i = split->i + 2;
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
	split.result = malloc(sizeof(char *) * (split.num_words + 7 + 1));
	if (!split.result)
		return (NULL);
	while (input[split.i])
	{
		if ((input[split.i] == '"' || input[split.i] == '\'' || split.flag == 2) && (!split.in_quotes || split.quote_char == input[split.i] || split.flag))
		{
			init_start_end(&split, input, delimeter); //flag == 0
			if (split.flag != 2)
			{
				if (split.flag == 1)
					split.flag = 0;
				split.in_quotes = !split.in_quotes;
				if (split.in_quotes)
					split.quote_char = input[split.i];
				else
					split.quote_char = '\0';
			}
			save_quote(&split, input, delimeter);
			split.i++;
		}
		else if (input[split.i] == '|' && (!strchr(delimeter, input[split.i - 1]) || !strchr(delimeter, input[split.i + 1])) && !split.in_quotes)//ignore if stand alone '|'
			split.i = ft_pipe_special(input, delimeter, &split);
		else if ((ft_get_redir(input, split.i, &split) == 1) && (!strchr(delimeter, input[split.i - 1]) || !strchr(delimeter, input[split.i + 1])) && !split.in_quotes)//ignore the stand alone '<'
			split.i = ft_redir_special(input, delimeter, &split);
		else if ((ft_get_redir(input, split.i, &split) == 2) && (!strchr(delimeter, input[split.i - 1]) || !strchr(delimeter, input[split.i + 2])) && !split.in_quotes)
			split.i = ft_appdoc_special(input, delimeter, &split);
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

/* int main(int ac, char *av[])
{
	(void)ac;
	//char *input = readline("$ ");
	char input[] = "'-l'|><'wc'|'<'wc";//"'l''-'1|'file'2"
	printf("%s\n", input);
    char **result = ft_split_bash(input, " \t");
    int i = 0;
    while (result[i])
    {
        printf("%s\n", result[i]);
        free(result[i]);
        i++;
    }
    free(result);
} */

/*
	"'ls'\"-l\"|\"wc\" | wc" // 5
	'ls''a' 'l'<'file'
	'ls''|'|'l'<'file'
*/