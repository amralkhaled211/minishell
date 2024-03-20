/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:57:35 by amalkhal          #+#    #+#             */
/*   Updated: 2024/03/20 21:54:39 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

bool	is_spertor(char c)
{
	if (c == '$' || c == ' ' || c == '=' || c == '\0')
		return (true);
	return (false);
}

bool	range_quotes(char *str, int j)// 'hi'$A$USER$A -> 'hi''$USER$A'asdf asdf'"$USER"
{
	int		len;
	bool	in_squote;
	bool	in_dquote;

	len = ft_strlen(str) - 1;
	in_squote = false;
	in_dquote = false;
	if (str[j] != '$')
		return (true);
	while (len >= 0)
	{
		if (str[len] == '"' && !in_squote)
			in_dquote = !in_dquote;
		else if (str[len] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (str[len] == '$' && len == j)
		{
			if (in_squote)
				return (true);
		}
		len--;
	}
	return (false);
}

bool	is_only_spaces(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (!ft_strchr(" \t", value[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	is_multiple_words(char *trmd)
{
	int		i;

	i = 0;
	while (trmd[i])
	{
		if (ft_strchr(" \t", trmd[i]))
			return (true);
		i++;
	}
	return (false);
}

bool	check_amb_rules(t_shell *shell, char *value)
{
	char	*trmd;

	//edge_case: only spaces
	if (is_only_spaces(value))
		return (true);
	trmd = ft_strtrim(value, " \t");
	if (!trmd)
		free_after_malloc_fail(shell, -1, 2);
	if (is_multiple_words(trmd))
		return (free(trmd), true);
	return (free(trmd), false);
}

void	check_amb(t_shell *shell, t_token *token)//must get the value of the var beforehand
{
	char	*var;
	char	*value;

	var = get_the_var(token->value);//also adds '=' at the end
	if (!var)
		free_after_malloc_fail(shell, -1, 2);
	if (!is_var_val(var, shell))//is unset
	{
		token->amb_redir = true;
		free(var);
		return ;
	}
	value = get_value_from_var(var, shell);
	if (!value)
		free_after_malloc_fail(shell, -1, 2);
	if (check_amb_rules(shell, value))//set, so check the rules
	{
		token->amb_redir = true;
		free(value);
		free(var);
		return ;
	}
	free(value);
	free(var);
}

void	expander(t_shell *shell, t_token *token)
{
	int	i;
	int	j;

	i = 0;
	while (token[i].type != TOKEN_END && token[i].type != TOKEN_DEFAULT)
	{
		if (token[i].type == TOKEN_WORD)
		{
			j = 0;
			if (i > 0 && token[i - 1].type == TOKEN_HEREDOC)
			{
				i++;
				continue ;
			}
			if (i > 0 && token[i].value[j] == '$' && is_redir(token[i - 1]))//must include VARs that include space as delimeter & only_space//get_the_var
				check_amb(shell, &token[i]);
			expand_checker(shell, token, i);
		}
		i++;
	}
}

void	expand_checker(t_shell *shell, t_token *token, int i)
{
	int		j;

	j = 0;
	errno = 0;
	token[i].orig_input = ft_strdup(token[i].value);
	if (!token[i].orig_input && errno != 0)
		free_after_malloc_fail(shell, -1, 2);
	while (token[i].value && token[i].type != TOKEN_END
		&& token[i].value[j] && token[i].amb_redir == false)
	{
		if (token[i].value[j] == '$'
			&& is_spertor(token[i].value[j + 1]) == false
			&& range_quotes(token[i].value, j) == false
			&& inside_dquote(shell, token[i].value, j) == false)
		{
			if (change_var_to_val(token,
					valid_var(token[i].value + j, shell), j, i) == 1)
			{
				free_after_malloc_fail(shell, -1, 2);
			}
			j = -1;
		}
		j++;
	}
}

char	*get_var_only(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
			break ;
		i++;
	}
	return (ft_substr(str, 0, i));
}


/*
bool	range_quotes(char *str, int j)
{
	int		i;
	bool	in_squote;
	bool	in_dquote;

	i = -1;
	in_squote = false;
	in_dquote = false;
	if (str[j] != '$')
		return (true);
	while (str[++i])
	{
		if (str[i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		else if (str[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (str[i] == '$' && i == j)
		{
			if (in_squote)
				return (true);
		}
	}
	return (false);
}*/