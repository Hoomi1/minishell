#include "minishell.h"

static char	*ft_search(char *tmp, size_t start, size_t end, const char *set)
{
	char		*search_word;
	char		*tmp_free;

	search_word = NULL;
	search_word = ft_substr(tmp, start, end - start + 1);
	if (search_word == NULL)
		return (NULL);
	tmp_free = search_word;
	search_word = ft_strtrim(search_word, set);
	ft_free_tmp(tmp_free);
	return (search_word);
}

char	*open_one_quotes(char *str, size_t *i, size_t end)
{
	char	*tmp;
	char	*tmp_befor;
	char	*tmp_search;
	char	*tmp_after;

	tmp = str;
	while (str[end] != '\'' && str[end] != '\0')
		end++;
	tmp_befor = ft_befor_search(str, *i);
	tmp_search = ft_search(str, *i, end, "\'");
	tmp_after = ft_after_search(str, ft_strlen(tmp_befor) + \
	ft_strlen(tmp_search) + 2);
	if (ft_error_malloc(tmp_befor, tmp_search, tmp_after))
	{
		clear_tmp(tmp, tmp_befor, tmp_search, tmp_after);
		return (NULL);
	}
	str = open_done(tmp_befor, tmp_search, tmp_after, i);
	clear_tmp(tmp, tmp_befor, tmp_search, tmp_after);
	return (str);
}
