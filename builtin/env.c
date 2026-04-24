/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:22:32 by anfouger          #+#    #+#             */
/*   Updated: 2026/04/24 09:52:49 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_env(t_env *env, char **argv)
{
	int	i;

	i = 0;
	if (argv[1])
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd("': No such file or directory\n", 2);
		return (127);
	}
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
