# COLORS

CYAN = \033[1;96m
YEL = \033[0;33m
GRN = \033[0;32m
RESET = \033[0m

# MAIN CONFIG

FT_MINISHELL = minishell

# GCC COMPILATOR PART CONF

CC = gcc
FLAGS = -Wall -Wextra -Werror
LIBRARIES = -lft -L$(PRINTF_DIR)
INCLUDES = -I$(HEADERS_DIRECTORY) -I$(PRINTF_HEADERS)ft_printf.h

# LIB SRC AND DST PART CONF

PRINTF = $(PRINTF_DIR)libftprintf.a
PRINTF_DIR = ./lib/printf/
PRINTF_HEADERS = $(PRINTF_DIR)

HEADERS_LIST = minishell.h
HEADERS_DIRECTORY = ./src/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

#	Функция addprefix добавляет свой первый аргумент ко всем целям, 
#	которые задает второй аргумент.

SRC_DIR = ./src/
SRC_LST = built_ins.c built_ins2.c cpy_func.c launch.c linked_list.c\
linked_list2.c linked_list3.c sig_handler.c split_line.c utilities.c utilities2.c


SRC_FT_MINISHELL = main.c

SOURCES = $(addprefix $(SRC_DIR), $(SRC_LST))
SOURCES_FT_MINISHELL = $(addprefix $(SRC_DIR), $(SRC_FT_MINISHELL))


# 	Функция patsubsb уберет префикс ../../ у имен файлов (она заменяет шаблон, 
#	заданный первым аргументом на шаблон во втором аргументе, а % обозначает любое количество символов)

OBJ_DIR = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SRC_LST))
OBJECTS_LIST_LS = $(patsubst %.c, %.o, $(SRC_FT_MINISHELL))
OBJECTS	= $(addprefix $(OBJ_DIR), $(OBJECTS_LIST))
OBJECTS_LS = $(addprefix $(OBJ_DIR), $(OBJECTS_LIST_LS))

.PHONY: all clean fclean re

#	RULES and stuff

all: $(FT_MINISHELL)

$(FT_MINISHELL): $(PRINTF) $(OBJ_DIR) $(OBJECTS) $(OBJECTS_LS)
	@$(CC) $(FLAGS) $(PRINTF) $(INCLUDES) $(OBJECTS) $(OBJECTS_LS) -o $(FT_MINISHELL)
	@echo "\n$(FT_MINISHELL): $(CYAN)$(FT_MINISHELL) object files were created$(RESET)"
	@echo "$(FT_MINISHELL): $(GRN)$(FT_MINISHELL) was created$(RESET)"



$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(FT_MINISHELL): $(CYAN)$(OBJ_DIR) was created$(RESET)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(CYAN).$(RESET)\c"

$(PRINTF):
	@echo "$(FT_MINISHELL): $(CYAN)creating $(PRINTF)...$(RESET)"
	@$(MAKE) -sC $(PRINTF_DIR)

clean:
	@$(MAKE) -sC $(PRINTF_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "$(FT_MINISHELL): $(YEL)$(OBJ_DIR) was deleted$(RESET)"
	@echo "$(FT_MINISHELL): $(YEL)object files were deleted$(RESET)"

fclean: clean
	@rm -f $(PRINTF)
	@echo "$(FT_MINISHELL): $(YEL)$(PRINTF) was deleted$(RESET)"
	@rm -f $(FT_MINISHELL)
	@echo "$(FT_MINISHELL): $(YEL)$(FT_MINISHELL) was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all