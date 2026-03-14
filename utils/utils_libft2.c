/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:02:02 by anfouger          #+#    #+#             */
/*   Updated: 2026/03/14 12:39:00 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char)s1[i] == (unsigned char)s2[i])
			i++;
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if ((unsigned char)s1[i] == (unsigned char)s2[i])
			i++;
		else
			return (0);
	}
	return (1);
}

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**dup_tab(char **tab)
{
	char	**new_tab;
	int		i;

	new_tab = malloc(sizeof(char *) * (tab_len(tab) + 1));
	if (!new_tab)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		if (!new_tab[i])
		{
			clean_tab(tab, i);
			return (NULL);
		}
		i++;	
	}
	new_tab[i] = NULL;
	return (new_tab);
}

void	clean_tab(char **tab, int i)
{
	while (i > 0)
		free(tab[--i]);
	free(tab);
}

long	verif_max_long(char *s)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		if (result > (LONG_MAX - (s[i] - '0')) / 10)
			return (0);
		result = result * 10 + (s[i] - '0');
		i++;
	}
	if (s[i] != '\0')
		return (0);
	return (result);
}
