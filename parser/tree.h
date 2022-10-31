/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:26:27 by antoine           #+#    #+#             */
/*   Updated: 2022/10/31 18:12:31 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

typedef struct s_tree
{
	enum
	{
		TREE_CMD_LINE,
		TREE_VARIABLE_DEF,
		TREE_EXEC_CALL,
		TREE_NULL
	}type;

	//TREE_CMD_LINE
	struct s_tree	**cmd_line;
	int				cmd_line_size;
	
	//TREE_VARIABLE_DEF
	char	*variable_name;
	char	*variable_value;
	
	//TREE_EXEC_CALL
	char			*exec_name;
	struct s_tree	**exec_args;
	char			*exec_path;
	int				exec_args_size;

	
}t_tree;

t_tree	*tree_init(int type);

#endif