/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:32:55 by anloisea          #+#    #+#             */
/*   Updated: 2022/10/31 19:13:49 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	int	fd;
	char	*cmd_line;
	
	fd = open("examples/var_def.txt", O_RDONLY);
	cmd_line = get_next_line(fd);
	

	t_parser	*parser = parser_init(lexer_init(cmd_line), envp);
	t_tree		*top = parser_start(parser);
	(void)top;
	free(parser);
	return (0);
}