/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:21:54 by anfouger          #+#    #+#             */
/*   Updated: 2026/03/11 09:16:02 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_cd(char **argv)
{
	char *path;

	printf("builtin_cd\n");
	if (!argv[1])
		path = getenv("HOME");
	else
		path = argv[1];
	if (!path)
	{
		perror("cd");
		return (1);
	}
	if (!chdir(path))
	{
		perror("cd");
		return (1);
	}
	return (0);
}
