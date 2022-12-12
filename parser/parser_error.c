/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpolpa <elpolpa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:22:03 by elpolpa           #+#    #+#             */
/*   Updated: 2022/12/09 16:22:05 by elpolpa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../minishell.h"
#include "../libft/libft.h"

void	error_syntax(char *value)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putstr_fd(value, 2);
	ft_putstr_fd("'\n", 2);
	g_global.error_parsing = true;
	g_global.exit_status = 2;
}
