/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_bash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:00:17 by aismaili          #+#    #+#             */
/*   Updated: 2024/01/15 18:28:20 by aismaili         ###   ########.fr       */
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

 static size_t count_words(char const *s, char *delimeter)
{
	size_t i = 0;
	size_t count = 0;
	size_t q_start = 0;
	char quote_char = '\0';
	bool in_quotes = false;
	bool is_word = false; // Tracks if we're inside a word

	while (s[i] != '\0')
	{
		if ((s[i] == '"' || s[i] == '\'') && (!in_quotes || quote_char == s[i]))
		{
			if (in_quotes == false && i > 0 && strchr(delimeter, s[i - 1]))//s[i - 1] != c
				q_start = i;
			in_quotes = !in_quotes;
			if (in_quotes)
				quote_char = s[i];
			else
				quote_char = '\0';
			//quote_char = in_quotes ? s[i] : '\0';
			if (!in_quotes && q_start > 0 && strchr(delimeter, s[q_start - 1]))
			{
				count++; // Count the quoted string as one word
				is_word = false;
			}
			i++;
		}
		else if (strchr(delimeter, s[i]) && !in_quotes)//s[i] == c
		{
			if (is_word)
			{
				count++; // Count as a word
				is_word = false;
			}
			i++;
		}
		else
		{
			is_word = true;
			i++;
		}
	}
	if (is_word || in_quotes)// If we end on a word or inside quotes
		count++;
	return (count);
}

/* int main()
{
   printf("%zu\n", count_words("        \"   \"  ", " "));
} */

char	**ft_split_bash(char *input, char *delimeter)
{
	//variables
	char	**result;
	size_t	a = 0;
	size_t	i = 0;
	size_t	num_words;
	size_t	q_start = 0;
	size_t	arg_start = 0;
	size_t	arg_end = 0;
	size_t  word_start = 0;
	size_t	word_end = 0;
	char quote_char = '\0';
	bool in_quotes = false;
	bool is_word = false; // Tracks if we're inside a word

	num_words = count_words(input, delimeter);
	if (!num_words)
		return (NULL);
	result = malloc(sizeof(char *) * (num_words + 1));
	if (!result)
		return (NULL);
	while (input[i])
	{
		if ((input[i] == '"' || input[i] == '\'') && (!in_quotes || quote_char == input[i]))
		{
			if (in_quotes == false && i > 0 && !strchr(delimeter, input[i - 1]))
			{
				//get q_start and arg_start
				q_start = i;
				while (q_start >= 0 && !strchr(delimeter, input[q_start]))
				{
					q_start--;
				}
				arg_start = q_start;
				q_start = i;
			}	
			in_quotes = !in_quotes;
			if (in_quotes)
				quote_char = input[i];
			else
				quote_char = '\0';
			if (!in_quotes)
			{
				while (input[i] && !strchr(delimeter, input[i]))
					i++;
				arg_end = i--;
				result[a++] = ft_substr(input, arg_start, (arg_end - arg_start));
				is_word = false;
			}
			i++;
		}
		else if (strchr(delimeter, input[i]) && !in_quotes)
		{
			if (is_word)
			{
				word_end = i - 1;
				while (word_end >= 0 && !strchr(delimeter, input[word_end]))
					word_end--;
				word_start = word_end + 1;
				word_end = i;
				result[a++] = ft_substr(input, word_start, (word_end - word_start));
				//printf("%s\nword_start: %zu\nword_end: %zu\n", result[a-1], word_start, word_end);
				is_word = false;
			}
			i++;
		}
		else
		{
			is_word = true;
			i++;
		}
	}
	result[a] = NULL;
	return (result);
}

int main()
{
    char **result = ft_split_bash("ls -l", " ");
    int i = 0;
    while (result[i])
    {
        printf("%s\n", result[i]);
        free(result[i]);
        i++;
    }
    free(result);
}
