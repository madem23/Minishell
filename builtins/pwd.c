/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:10:57 by antoine           #+#    #+#             */
/*   Updated: 2022/12/15 15:35:28 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	pwd(t_minishell *minishell)
{
	char	*buf;

	buf = get_var_value(minishell->var_def, "PWD");
	if (!buf)
	{
		ft_putstr_fd("minishell: ", 2);
		perror("pwd: ");
		return (1);
	}
	printf("%s\n", buf);
	free(buf);
	return (0);
}
