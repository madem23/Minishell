/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:10:57 by antoine           #+#    #+#             */
/*   Updated: 2022/12/22 10:50:35 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	pwd(t_minishell *minishell)
{
	char	*buf;

	buf = get_var_value(minishell->var_def, "PWD");
	if (!buf)
	{
		var_add_back(&minishell->var_def,
			var_init(ft_strdup("PWD"), getcwd(NULL, 0), true));
		buf = get_var_value(minishell->var_def, "PWD");
		if (!buf)
			buf = ft_strdup(".");
	}
	printf("%s\n", buf);
	free(buf);
	return (0);
}
