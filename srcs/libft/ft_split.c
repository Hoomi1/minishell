/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scanary <scanary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 18:17:08 by scanary           #+#    #+#             */
/*   Updated: 2021/04/10 03:45:06 by scanary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_clean(char **arr, int len)
{
	int	i;

	i = 0;
	while (i <= len)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

static int	ft_len_w(const char *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i++])
		len++;
	return (len);
}

static int	ft_cound_w(const char *s, char c)
{
	int	nb_w;
	int	i;

	i = 0;
	nb_w = 0;
	if (!s)
		return (nb_w);
	while (s[i] && s[i] != '\0')
	{
		if ((i == 0 && s[i] != c) || (i != 0 && s[i - 1] == c && s[i] != c))
			++nb_w;
		i++;
	}
	return (nb_w);
}

static char	**get_ar(const char *s, char c)
{
	int		c_w;
	char	**arr;

	c_w = ft_cound_w(s, c);
	arr = (char **)malloc(sizeof(char *) * (c_w + 1));
	if (!s || !(arr))
		return (NULL);
	arr[c_w] = NULL;
	return (arr);
}

char	**ft_split(const char *s, char c)
{
	char	**ar;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	j = 0;
	ar = get_ar(s, c);
	if (!ar)
		return (NULL);
	while (*s && ar && i < ft_cound_w(s, c))
	{
		j = 0;
		while (s[k] == c)
			k++;
		ar[i] = (char *)malloc(sizeof(char) * (ft_len_w(&s[k], c) + 1));
		if (!(ar[i]))
			return (ft_clean(ar, i));
		while (s[k] && s[k] != c)
			ar[i][j++] = s[k++];
		ar[i++][j] = '\0';
	}
	return (ar);
}
