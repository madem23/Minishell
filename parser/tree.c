/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:24:44 by antoine           #+#    #+#             */
/*   Updated: 2022/10/31 16:09:42 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include <stdlib.h>
#include "../minishell.h"

t_tree	*tree_init(int type)
{
	t_tree	*tree;
	
	tree = malloc(sizeof(t_tree));
	if (!tree)
		error(1, "Failed to allocate tree\n");
	tree->type = type;
	tree->exec_name = NULL;
	tree->exec_args = NULL;
	tree->exec_args_size = 0;
	tree->cmd_line = NULL;
	tree->cmd_line_size = 0;
	return (tree);
}