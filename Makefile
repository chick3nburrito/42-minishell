CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = minishell

SRC_PATH = .
OBJ_PATH = obj
LIB_PATH = libft

LIB_NAME = libft.a
LIB = $(LIB_PATH)/$(LIB_NAME)

SRC_NAME = parser/aquidoc.c \
	   parser/aquidoc_helper.c \
           parser/build_cards.c \
           parser/environment.c \
           parser/main.c \
           parser/parser.c \
 	   parser/parser_utils.c \
 	   parser/parser_helper.c \
           parser/parser_token_utils.c \
           parser/parser_quote_utils.c \
           parser/shell_utils.c \
           parser/redirections.c \
	   parser/redir_helper.c  \
           parser/syntex_checker.c \
           parser/utils.c \
           parser/tools.c \
           parser/valide_input.c \
           execution/exec_one.c \
           execution/execution.c \
           execution/execution_utils.c \
           execution/exec_helpers.c \
           execution/exec_helpers2.c \
           execution/helper.c \
           blts/cd_blt.c \
           blts/echo_blt.c \
           blts/env_blt.c \
           blts/exit_blt.c \
           blts/export_blt.c \
           blts/pwd_blt.c \
           blts/unset_blt.c \
	   execution/tokens_to_cmd.c \
	   parser/expander.c \
	   parser/expander_helper.c \
           parser/expander_str.c \
	   parser/expander_utils.c


OBJ_NAME = $(SRC_NAME:.c=.o)

INC = includes/minishell.h
INC_FLAGS = -Iincludes -Ilibft

OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ) $(LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -lreadline -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INC)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_FLAGS)

$(LIB):
	$(MAKE) -C $(LIB_PATH)

clean:
	$(MAKE) -C $(LIB_PATH) clean
	rm -rf $(OBJ_PATH)

fclean: clean
	$(MAKE) -C $(LIB_PATH) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
