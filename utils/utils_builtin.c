/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 09:35:18 by anfouger          #+#    #+#             */
/*   Updated: 2026/04/24 10:28:06 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_env_value(char **envp, char *str)
{
	int		i;
	int		start;
	int		end;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], str, ft_strlen(str)) == 0
			&& envp[i][ft_strlen(str)] == '=')
		{
			start = ft_strlen(str) + 1;
			end = ft_strlen(envp[i]);
			return (ft_strndup(envp[i], start, end));
		}
		i++;
	}
	return (NULL);
}

static int	copy_str_tab(char **tab, char **new_tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		if (!new_tab[i])
		{
			clean_str_tab(new_tab, i);
			return (-1);
		}
		i++;
	}
	return (i);
}

char	**add_var(t_env *env, char **tab, char *str)
{
	(void)env;
	char	**new_tab;
	int		i;

	new_tab = malloc(sizeof(char *) * (tab_str_len(tab) + 2));
	if (!new_tab)
		return (NULL);
	i = copy_str_tab(tab, new_tab);
	if (i == -1)
		return (NULL);
	new_tab[i] = ft_strdup(str);
	if (!new_tab[i])
	{
		clean_str_tab(new_tab, i);
		return (NULL);
	}
	new_tab[i + 1] = NULL;
	free_str_tab(tab);
	return (new_tab);
}

int	change_value(char **envp, char *key, char *str)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0
			&& (envp[i][ft_strlen(key)] == '='
			|| envp[i][ft_strlen(key)] == '\0'))
		{
			free(envp[i]);
			envp[i] = ft_strdup(str);
			return (1);
		}
		i++;
	}
	return (0);
}

void	print_export(char *str)
{
	int i;

	i = 0;
	printf("declare -x ");
	while (str[i] && str[i - 1] != '=')
	{
		printf("%c", str[i]);
		i++;
	}
	printf("\"");
	while (str[i])
	{
		printf("%c", str[i]);
		i++;
	}
	printf("\"\n");
}
