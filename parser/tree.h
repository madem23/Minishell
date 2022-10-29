/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:26:27 by antoine           #+#    #+#             */
/*   Updated: 2022/10/29 11:43:34 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

typedef struct s_tree
{
	enum
	{
		TREE_VARARIABLE_DEF,
		TREE_VARIABLE,
		TREE_CMD_CALL,
		TREE_STRING,
	}type;

	// TREE_VARIABLE_DEF
	char			*variable_def_name;
	char			*variable_def_value;

	//TREE_VARIABLE
	char			*variable_name;

	//TREE_CMD_CALL
	char			*cmd_name;
	struct s_tree	**cmd_args;
	int				args_size;

	//TREE_STRING
	char			*string_value;
	
}t_tree;

#endif