/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:23:08 by antoine           #+#    #+#             */
/*   Updated: 2022/11/25 11:25:35 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"

int	pwd(void);
int	env(char **envp, char **args);
int	echo(char **args);
int	cd(char **args, struct s_minishell *minishell);
int	export(t_tree *branch, struct s_minishell *minishell);
int	unset(char **args, struct s_minishell *minishell);
int	check_for_builtins(t_tree *branch, struct s_minishell *minishell);
int	modify_existing_var(t_tree *branch, char *token_value, int j);
int	modify_existing_string_var(t_tree *branch, char *var_name, char *var_value);

#endif