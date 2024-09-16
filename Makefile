NAME = minishell

HEADER = ./includes/

AUTHOR = nkanaan && mhabbal

LIBFT = lib/libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

SRCS = main misc/prompt init/lexer init/shell init/parser init/execute misc/printing misc/env/env_ll misc/env/env_utils misc/memory signals

BUILTIN_SRCS = exec/builtins/echo exec/builtins/pwd exec/builtins/exit exec/builtins/env exec/builtins/cd \
exec/builtins/unset exec/builtins/export exec/builtins/export_utils

LEXER_SRCS =  l_tokenize token/l_token_utils token/l_types utils/l_utils utils/l_syntax utils/l_syntax_utils\
utils/quotes/l_quotes utils/glob/l_glob utils/glob/l_glob_utils \
utils/operators/l_ampersand utils/operators/l_pipes utils/operators/l_redirect \
utils/parens/l_parens utils/parens/l_paren_utils utils/expand/l_expand utils/expand/l_expand_utils

PARSER_SRCS = p_build_tree p_build_pipeline utils/p_utils utils/nodes/p_build_nodes utils/nodes/p_parse_nodes utils/nodes/p_node_util

EXEC_SRCS = e_execution utils/e_utils utils/pipeline/e_pipeline utils/e_helpers utils/e_redir utils/e_array_copy utils/get_next_line

SRC = $(addprefix src/, $(addsuffix .c, $(SRCS)))

BUILTIN_SRC = $(addprefix src/, $(addsuffix .c, $(BUILTIN_SRCS)))

LEXER_SRC = $(addprefix src/lexer/, $(addsuffix .c, $(LEXER_SRCS)))

PARSER_SRC = $(addprefix src/parser/, $(addsuffix .c, $(PARSER_SRCS)))

EXEC_SRC = $(addprefix src/exec/, $(addsuffix .c, $(EXEC_SRCS)))

OBJS = $(addprefix objs/, $(addsuffix .o, $(SRCS)))
BUILTIN_OBJS = $(addprefix objs/, $(addsuffix .o, $(BUILTIN_SRCS)))
LEXER_OBJS = $(addprefix objs/lexer/, $(addsuffix .o, $(LEXER_SRCS)))
PARSER_OBJS = $(addprefix objs/parser/, $(addsuffix .o, $(PARSER_SRCS)))
EXEC_OBJS = $(addprefix objs/exec/, $(addsuffix .o, $(EXEC_SRCS)))

SHELL := /bin/bash

COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m
OK_COLOR    	= \033[0;32m
_END		=	\e[0m
_GREEN		=	\e[32m
_WHITE		=	\e[37m
_MUP		=	\e[1A
_ERASE		=	\e[K


all: header $(NAME)

	@printf "\033[?25h"
header:
	@printf "%b" "$(OK_COLOR)"
	@echo ".------..------."
	@echo "|4.--. ||2.--. |"
	@echo "| :/\: || (\/) |"
	@echo "| :\/: || :\/: |"
	@echo "| '--'4|| '--'2|"
	@echo "'------''------'"
	@echo "THE DREAM TEAM"

	@printf "%b" "$(OBJ_COLOR)Author:	$(WARN_COLOR)$(AUTHOR)$(NO_COLOR)\n"
	@echo

objs/%.o:	src/%.c
	@mkdir -p $(dir $@)
	@${CC} ${CFLAGS} -c $< -o $@
	@printf "\033[?25l"
	@printf "$(_ERASE)\r"
	@printf "$<$(_END)\n"
	@for i in $$(seq 1 $(CNT)); \
	do \
		printf "$(OK_COLOR)*"; \
	done
	$(eval CNT=$(shell echo $$(($(CNT) + 1))))
	@printf "\r$(_MUP)"


$(NAME):	$(BUILTIN_OBJS) $(LEXER_OBJS) $(PARSER_OBJS) $(EXEC_OBJS) $(OBJS) $(LIBFT) $(HEADER)
	@$(CC) $(CFLAGS)  $(BUILTIN_OBJS) $(PARSER_OBJS) $(LEXER_OBJS) $(EXEC_OBJS) $(OBJS) -o $(NAME) $(LIBFT) -lreadline
	@printf "%-53b%b" "$(COM_COLOR)Project Compiled:" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

$(LIBFT):
			@make -C ./lib
			@printf "%-53b%b" "$(COM_COLOR)LIBFT Compiled:" "$(OK_COLOR)[✓]$(NO_COLOR)\n"


clean:
			rm -rf $(OBJS) ./objs
			@make clean -C ./lib
			@printf "%-53b%b" "$(COM_COLOR)OBJECT FILES DELETED:" "$(ERROR_COLOR)[✓]$(NO_COLOR)\n"


fclean:		clean
				rm $(NAME)
				rm ./lib/libft.a
				@printf "%-53b%b" "$(COM_COLOR)ALL CLEAN:" "$(ERROR_COLOR)[✓]$(NO_COLOR)\n"

re:			fclean all

.PHONY: 	all clean fclean re

.SILENT: 	clean fclean re all
