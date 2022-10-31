/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:56:26 by anloisea          #+#    #+#             */
/*   Updated: 2022/10/31 16:53:34 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include "libft/libft.h"
# include "lexer/token.h"
# include "lexer/lexer.h"
# include "parser/parser.h"
# include "parser/tree.h"
# include <stdio.h>

//open
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

void	error(int errnum, char *msg);

//PATHS:

char	**get_paths(char *envp[]);
char	*check_exec_paths(char **paths, char *exec_called);

//Utils:

int	ft_isaccepted(char c);

#endif