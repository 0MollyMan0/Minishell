/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 09:02:06 by anfouger          #+#    #+#             */
/*   Updated: 2026/04/24 09:17:01 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*init_envp(char **tab)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->envp = dup_tab(tab);
	if (env)
	{
		/* code */
	}
	
	
}
