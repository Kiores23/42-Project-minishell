/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 18:27:23 by amery             #+#    #+#             */
/*   Updated: 2023/04/24 13:35:58 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../Includes/macro.h"
# include "../../Includes/lib.h"
# include "../../Includes/struct.h"

typedef struct s_export
{
	int		i;
	int		boolean;
	t_env	*lst;
}	t_export;

typedef struct s_echo
{
	int		n_flag;
	int		in_quote;
	int		in_apostrophe;
	int		i;
}				t_echo;

typedef struct s_unset
{
	t_env	*lst;
	int		pos;
	int		i;
	int		r;
}	t_unset;

// BUILTINS
int		ft_echo(char **line);
void	env_print(t_env *our_env);
int		ft_lstlen(t_env *lst);
void	free_at(t_env **lst, int pos);
int		unset_env_var(t_env **lst_ptr, char **names);
int		changedirectory(char **argv, t_env *env);
char	*return_to_the_old(char *pwd, int free);
char	*get_last_path(char *pwd, int act);
int		ft_exit(char **cmds, t_stack *s, t_env *env, char *line);
int		check_variable_name(char *str);
int		ft_pwd(char **argv, int infun);
int		print_unset_message(char *name);
t_env	*free_cur(t_env *ptr);
void	init_var_unset(t_unset *unset_vars, t_env **lst_ptr);
// EXPORT
int		export_env(t_env **our_env, char **strings);
char	**parse_string(char *str, char **tab);
int		print_export(t_env **our_env);
t_env	*sorted_list(t_env **our_env);
t_env	*ft_lst_cpy(t_env *lst);
void	init_var_export(t_export *export_va, t_env **our_env);
void	handle_export_conditions(char *string, t_export *e, char **tab, int *r);
void	free_tab_ptrs(char **tab);
int		handle_error(char *strings, t_export *export_va);
int		handle_underscore(char *strings, t_export *export_va);
void	handle_the_case(char **tab);

#endif