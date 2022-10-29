/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:56:26 by anloisea          #+#    #+#             */
/*   Updated: 2022/10/29 11:28:41 by antoine          ###   ########.fr       */
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
//# include <readline.h>
//# include <history.h>

void	error(int errnum, char *msg);

//Utils:

int	ft_isaccepted(char c);

#endif