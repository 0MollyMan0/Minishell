/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:22:21 by anfouger          #+#    #+#             */
/*   Updated: 2026/03/12 11:19:26 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static	char **dup_tab_less_i(char **tab, int index)
{
	char	**new_tab;
	int		i;
	int		j;

	new_tab = malloc(sizeof(char *) * (tab_len(tab)));
	if (!new_tab)
		return (NULL);
	i = 0;
	j = 0;
	while (tab[j])
	{
		if (i == index)
			j++;
		new_tab[i] = ft_strdup(tab[j]);
		if (!new_tab[i])
		{
			clean_tab(new_tab, i);
			return (NULL);
		}
		i++;
		j++;
	}
	new_tab[i] = NULL;
	free_tab(tab);
	return (new_tab);
}

static int	get_index(char **tab, char *key)
{
	int	i;

	i = 0;
	while (ft_strncmp(tab[i], key, ft_strlen(key)) != 0)
		i++;
	return (i);
}

int	builtin_unset(t_minish *minish, char **argv)
{
	int		i;

	i = get_index(minish->envp, argv[1]);
	minish->envp = dup_tab_less_i(minish->envp, i);
	return (0);
}
