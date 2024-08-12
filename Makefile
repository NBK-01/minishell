NAME = minishell

HEADER = ./includes/

AUTHOR = nkanaan && mhabbal

LIBFT = lib/libft.a

CC = gcc

CFLAGS = -Werror -Wall -Wextra #-fsanitize=address

SRCS = main init/lexer init/shell misc/prompt_utils misc/printing

BUILTIN_SRCS = cd echo pwd env handle_builtins

LEXER_SRCS =  l_tokenize token/l_token_utils token/l_types utils/l_utils \
utils/quotes/l_quotes utils/glob/l_glob utils/glob/l_glob_utils \
utils/operators/l_ampersand utils/operators/l_pipes utils/parens/l_parens utils/parens/l_paren_utils

SRC = $(addprefix src/, $(addsuffix .c, $(SRCS)))

BUILTIN_SRC = $(addprefix src/builtins/, $(addsuffix .c, $(BUILTIN_SRCS)))

LEXER_SRC = $(addprefix src/lexer/, $(addsuffix .c, $(LEXER_SRCS)))

OBJS = $(addprefix objs/, $(addsuffix .o, $(SRCS)))
BUILTIN_OBJS = $(addprefix objs/builtins/, $(addsuffix .o, $(BUILTIN_SRCS)))
LEXER_OBJS = $(addprefix objs/lexer/, $(addsuffix .o, $(LEXER_SRCS)))

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
	@sleep 0.02
	@for i in $$(seq 1 $(CNT)); \
	do \
		printf "$(OK_COLOR)*"; \
	done
	$(eval CNT=$(shell echo $$(($(CNT) + 1))))
	@sleep 0.02
	@printf "\r$(_MUP)"


$(NAME):	$(BUILTINS_OBJS) $(LEXER_OBJS) $(OBJS) $(LIBFT) $(HEADER)
	@$(CC) $(CFLAGS)  $(BUILTINS_OBJS) $(LEXER_OBJS) $(OBJS) -o $(NAME) $(LIBFT) -lreadline
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
