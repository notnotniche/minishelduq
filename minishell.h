/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:40:58 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/12 15:27:10 by itahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "unistd.h"
#include "stdlib.h"
#include <errno.h>
# include <termios.h>
# include <term.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
#include <readline/readline.h>		
#include <linux/limits.h>	
#include <readline/history.h>	


extern int g_status_exit_code;

# define WORD 0 // word
# define PIPE 1 // |
# define REDIR_IN 3 // <
# define REDIR_OUT 4 // >
# define HERE_DOC 5 // <<
# define APP_OUT 2 // >>
# define COMMAND_NOT_FOUND 127 // G_STATUS
# define NO_ACCESS 126// G_STATUS
# define SUCESS 0 // G_STATUS
# define ERROR 1 // NERD



// token == 0 command , token == 1 string token == 2 other  

typedef struct s_quote
{
	char quote;
	int quote_bool;
} t_quote;

typedef struct s_malloc
{
	void	*adr;
	struct 	s_malloc *next;
}	t_malloc;

typedef struct str_list
{
	char *str_list;
	char *str_list2;
	struct str_list *next;
} t_str_list;

typedef struct l_list
{
	char *word;
	int operator;
	struct l_list *next;
} t_lex_list;

typedef struct export_list
{
	char *name;
	char *value;
} t_export_list;

typedef struct env_list
{
	char *name;
	char *value;
	struct env_list *next;
} t_env_list;

typedef struct token_list
{
	t_str_list *in_file;
	int token;
	t_str_list *arguments;
	t_str_list *delimeter;
	t_str_list *out_file;
	int			i_fd;
	int			o_fd;
	struct token_list *next;
} t_token_list;

typedef struct s_exec_init
{
	int nb_command;
	int pipetmp;
	pid_t realpid;
	int mypipe[2];
	pid_t *pid;
} t_exec_init;

typedef struct s_init
{
	char *read_line;

	t_env_list *lst_env;
	t_malloc *lst_mal;
	t_lex_list *lst_lex;
	t_token_list *lst_token;
	char			*err_msg;
} t_init;


//

//utils
int	ft_atoi(const char *str);
int		ft_strcmp(char *str, char *str2);
int		ft_strlen(char *str);
char	*ft_strtrim(char *str, int i , int y);
int		ft_strsame(char *str1, char *str2);
char    **ft_split(const char *s, char c);
int		is_only_isspace(char *str);
char *ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_strjoin(char *str1, char *str2);
int		ft_isalpha(char c);
void	check_pipe(int fd);
int		ft_isalnum(char c);
void	heredoc_supp(t_token_list *token_lst);
int		is_quote(char c);
char	*ft_strcpy(char *dest, const char *src);
void	close_fds(int fd_nbr, ...);
char *ft_strcat(char *dest, const char *src);
int		ft_isitenv(char c);
int    ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(char *str);
char			*ft_itoa(int n);
char	*ft_join_str_in_init(t_init *init, char c, 	char *src);
void	ft_print_fd(char *str, int fd);
int		ft_size_token(t_token_list *list);
int		ft_size_env(t_env_list *head);
int		ft_size_str(t_str_list *head);

t_str_list	*lstnew_str(char *content, t_init *init);
t_str_list *lstlast_str(t_str_list *str_list);
void	lstaddback_str(t_str_list **str_list, t_str_list *new);
void	print_str(t_str_list *str_list, char *str);
void	print_all_str(t_init *init);

//check_error
int check_error(t_lex_list *lst_lex);
void free_s_init(t_init *init);


// utils_malloc_list

t_malloc *lstnew_malloc(void *adr);
t_malloc *lstlast_malloc(t_malloc *nodes);
void lstaddback_malloc(t_init *init, t_malloc *new);
void	free_lst_malloc(t_malloc *lst);

//lexer
int	ft_is_operator(char *read_line, t_lex_list **lex_list, t_init *init);
int	ft_isspace(char c);
int length_word(char *word);
void write_word(char *word, char **split);
void end_of_word(char **splittos);

void operator_manager(char **read_line, t_lex_list **lex_list, t_init *init);
void word_manager(char *read_line, t_lex_list **lex_list, t_init *init);
t_lex_list *lexer_lexing(char *read_line, t_init *init);

//token
void token_here_doc(t_token_list **token, t_lex_list **lex_list, t_init *init);
void token_add_word(t_token_list **token, t_lex_list **lex_list, t_init *init);
void token_add_redir_in(t_token_list **token, t_lex_list **lex_list, t_init *init);
void token_add_redir_out(t_token_list **token, t_lex_list **lex_list, t_init *init);
void token_add_app_out(t_token_list **token, t_lex_list **lex_list, t_init *init);

t_token_list *lst_new_token(t_init *init);
t_token_list *lstlast_token(t_token_list *lst);
void lstaddback_token(t_token_list **lst, t_token_list *new);
void print_all_token(t_token_list *lst);


t_token_list *get_all_token(t_init *init);

//lexer_utils
t_lex_list *lstnew_lex(char *word, int operator, t_init *init);
t_lex_list *lstlast_lex(t_lex_list *list);
void lstadd_back_lex(t_lex_list **list, t_lex_list *new);
void print_lst_lex(t_lex_list *list);

////envp

//env_list_utils
void		print_lst_env(t_env_list *list);
void		lstadd_back_env(t_env_list **list, t_env_list *new);
t_env_list	*lstlast_env(t_env_list *list);
t_env_list	*lstnew_env(char *name, char *value);

//env_list
int		env_name_size(char *env);
void	end_env_name(char **str);


void		routine_start(int sig);
char	*env_name(char *env);
t_env_list	*init_env_list(char **env);
void	change_env_value(char *name, char *new_value, t_init *init);
char	*get_env_value(char *name, t_init *init);

t_env_list	*lstnew_env(char *name, char *value);
t_env_list	*lstlast_env(t_env_list *list);
void		lstadd_back_env(t_env_list **list, t_env_list *new);
void print_lst_env(t_env_list *list);


//expand
int		is_env(char *str);
int		size_double_tab(char **arguments);
int valid_first_letter(char *str, int i);
char	*env_name_expander(char *str);
void	expander_expanding(t_init *init);

//builtins
void the_real_exit(char **all_args, t_init *init);
int builtin_manage(t_init *init, char *str, char **all_args);
int is_command_builtin(char *str);
void	sh_lvl_manager(t_init *init);
void 	the_real_cd(char **path, char **envp, t_init *init);
void the_real_env(char **arguments, t_init *init);
void free_tab_tab(char **splittos);
void the_real_unset(char **arguments, t_init *init);
void    text_to_print(char    **line, t_init *init);
void printLinkedList(t_env_list *head);
int fork_builtin(char *str);
void the_real_export(char **arguments, t_init *init);
void free_env_list(t_env_list *head);

void	ft_echo(char *cmd);
int		the_real_pwd(t_init *init);


//exec
void	heredoc_sigint(int sig);
void	handle_sigint(int sig);
void    ft_heredoc(char *delimiteur, t_init *init);
void real_exec(t_init *init);
char *is_pathabs(t_init *init, char *str);
int check_outfile_fd(t_token_list *tok_list);
int check_infile_fd(t_token_list *tok_list);
int check_if_directory(char *path);
int file_exec(char *path);
char **env_to_str(t_init *init, t_env_list *env_list, int size_env);
void printalltab(char **tarb, char *arg);
int name_exist_in_env(char *str, t_init *init);
int check_file_exist(char *path);
void exec_all_pid(t_init *init, int i, t_exec_init exec_init);
char *path_maker(t_init *init, t_str_list *cmd, char *path,t_exec_init *exec_init);
void	command_manager(t_init *init, t_exec_init *exec_init,int i);
void	close_fd(int fd_nbr, int *fd_array);

//exec file_manager
void	redir_out_manager(t_token_list *token_list);
void	app_out_manager(t_token_list *token_list);
void	redir_in_manager(t_token_list *token_list);
void	redir_here_doc(t_token_list *token_list);

#endif