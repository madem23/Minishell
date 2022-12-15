/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:23:08 by antoine           #+#    #+#             */
/*   Updated: 2022/12/15 16:56:31 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"

int		pwd(struct s_minishell *minishell);
int		env(t_var *list, char **args);
int		echo(char **args);
int		cd(char **args, struct s_minishell *minishell);
int		export(t_tree *branch, struct s_minishell *minishell);
int		unset(char **args, struct s_minishell *minishell);
void	ft_exit(char **args);
int		check_for_builtins(t_tree *branch, struct s_minishell *minishell);
int		modify_existing_var(t_tree *branch, char *tk_value, int j);
int		modify_existing_string_var(t_tree *branch,
			char *var_name, char *var_value);

#endif