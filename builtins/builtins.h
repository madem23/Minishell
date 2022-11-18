/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:23:08 by antoine           #+#    #+#             */
/*   Updated: 2022/11/18 14:24:46 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"

void	pwd(void);
void	env(char **envp, char **args);
void	echo(char **args);
void	cd(char **args, char **envp);
void	export(t_tree *branch, struct s_minishell *minishell);
void	unset(char **args, struct s_minishell *minishell);
int		check_for_builtins(t_tree *branch, struct s_minishell *minishell);

#endif