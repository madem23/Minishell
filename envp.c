#include "minishell.h"

/* Creates a new envp (tab of strings). */
void	update_envp(t_minishell *minishell)
{
	int		len;
	t_var	*tmp;
	int		i;
	char	*join_equal;

	if (minishell->envp)
		free_tab((void **)minishell->envp);
	tmp = minishell->var_def;
	len = 0;
	while (tmp)
	{
		if (tmp->env == true)
			len++;
		tmp = tmp->next;
	}
	minishell->envp = malloc((len + 1) * sizeof(char *));
	i = 0;
	tmp = minishell->var_def;
	while (tmp)
	{
		if (tmp->env == true)
		{
			join_equal = ft_strjoin(tmp->name, "=");
			minishell->envp[i] = ft_strjoin(join_equal, tmp->value);
			free(join_equal);
			i++;
		}
		tmp = tmp->next;
	}
	minishell->envp[i] = NULL;
}
