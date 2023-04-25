NAME = minishell

LIB_PATH = ./libft/

LIB = -L ./libft -lft

SRCS =	srcs/readline.c \
    	srcs/builtins/ft_echo.c \
		srcs/builtins/builtins_env.c \
		srcs/builtins/builtins_export.c \
		srcs/builtins/builtins_export_help.c \
		srcs/builtins/builtins_export_help2.c \
		srcs/builtins/builtin_print_export.c \
		srcs/builtins/builtins_cd.c \
		srcs/builtins/builtins_cd_utils.c \
		srcs/builtins/builtins_pwd.c \
		srcs/builtins/builtins_exit.c \
		srcs/builtins/builtins_env_utils.c \
    	srcs/parsing/linked_list_management.c \
    	srcs/parsing/linked_list_management2.c \
    	srcs/parsing/parsing_first_part.c \
    	srcs/parsing/parsing_second_part.c \
		srcs/parsing/parsing_third_part.c \
    	srcs/parsing/redirections_mangement.c \
		srcs/parsing/redirections_mangemment_out.c \
		srcs/parsing/redirections_utils.c \
		srcs/parsing/split_for_command.c \
		srcs/parsing/split_for_command2.c \
		srcs/parsing/parsing_environnement.c \
		srcs/parsing/parsing_envrionnement_utils.c \
		srcs/parsing/replace_env_var_utils.c \
		srcs/parsing/remplace_env_var.c \
		srcs/parsing/remplace_env_var2.c \
		srcs/parsing/verif_string.c \
		srcs/parsing/free_all.c \
		srcs/execution/get_path.c \
		srcs/execution/execution.c \
		srcs/execution/execution_2.c \
		srcs/execution/final_execution.c \
		srcs/execution/redir.c \
		srcs/execution/get_tab_env.c \
		srcs/execution/env_execution.c \
		srcs/execution/env_execution_redir.c \
		srcs/execution/redir_utils.c \
    	srcs/signals/signals.c \
		srcs/signals/sign_error.c \
		srcs/signals/signals_fun.c

HEADERS = -I ./Includes/minishell.h

OBJ_PATH = ./obj/
OBJS = ${addprefix $(OBJ_PATH), ${SRCS:.c=.o}}

CC = gcc

CFLAGS = -Wall -Werror -Wextra

$(OBJ_PATH)%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(HEADER) $(OBJS)
	make -C $(LIB_PATH)
	$(CC) $(CFLAGS) $(HEADERS) $(LIB) -o $(NAME) $(OBJS) -lreadline -L ~/.brew/Cellar/readline/8.2.1/lib/

all: $(NAME)

clean:
	@rm -f *.out
	@rm -f *.o
	@rm -rf $(OBJ_PATH)
	make clean -C $(LIB_PATH)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIB_PATH)

re: fclean all

.PHONY : all clean fclean bonus
