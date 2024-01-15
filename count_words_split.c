#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>

 size_t count_words(char const *s, char *delimeter)
{
	size_t i = 0;
	size_t count = 0;
	size_t q_start = 0;
	bool in_quotes = false;
	char quote_char = '\0';
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

int main()
{
   printf("%zu\n", count_words("        \"   \"  ", " "));
}
