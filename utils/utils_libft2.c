/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:02:02 by anfouger          #+#    #+#             */
/*   Updated: 2026/03/11 11:33:01 by anfouger         ###   ########.fr       */
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

static int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**copy_tab(char **tab)
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
			while (i > 0)
				free(new_tab[--i]);
			free(new_tab);
			return (NULL);
		}
		i++;	
	}
	new_tab[i] = NULL;
	return (new_tab);
}
