# COLORS

CYAN = \033[1;96m
YEL = \033[0;33m
GRN = \033[0;32m
RESET = \033[0m

# MAIN CONFIG

FT_LS_BIN = ft_ls
CHECKER_BIN = checker

# GCC COMPILATOR PART CONF

CC = gcc
FLAGS = -Wall -Wextra -Werror
LIBRARIES = -lft -L$(PRINTF_DIR)
INCLUDES = -I$(HEADERS_DIRECTORY) -I$(PRINTF_HEADERS)ft_printf.h

# LIB SRC AND DST PART CONF

PRINTF = $(PRINTF_DIR)libftprintf.a
PRINTF_DIR = ./lib/printf/
PRINTF_HEADERS = $(PRINTF_DIR)

HEADERS_LIST = ft_ls.h
HEADERS_DIRECTORY = ./src/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

#	Функция addprefix добавляет свой первый аргумент ко всем целям, 
#	которые задает второй аргумент.

SRC_DIR = ./src/
SRC_LST = utilities.c utilities2.c output.c sorting_algs.c aux.c\
 validation.c free.c utilities3.c sorting_algs2.c aux2.c aux3.c \
 output2.c output3.c utilities4.c

SRC_FT_LS = main.c

SOURCES = $(addprefix $(SRC_DIR), $(SRC_LST))
SOURCES_FT_LS = $(addprefix $(SRC_DIR), $(SRC_FT_LS))


# 	Функция patsubsb уберет префикс ../../ у имен файлов (она заменяет шаблон, 
#	заданный первым аргументом на шаблон во втором аргументе, а % обозначает любое количество символов)

OBJ_DIR = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SRC_LST))
OBJECTS_LIST_LS = $(patsubst %.c, %.o, $(SRC_FT_LS))
OBJECTS	= $(addprefix $(OBJ_DIR), $(OBJECTS_LIST))
OBJECTS_LS = $(addprefix $(OBJ_DIR), $(OBJECTS_LIST_LS))

.PHONY: all clean fclean re

#	RULES and stuff

all: $(FT_LS_BIN)

$(FT_LS_BIN): $(PRINTF) $(OBJ_DIR) $(OBJECTS) $(OBJECTS_LS)
	@$(CC) $(FLAGS) $(PRINTF) $(INCLUDES) $(OBJECTS) $(OBJECTS_LS) -o $(FT_LS_BIN)
	@echo "\n$(FT_LS_BIN): $(CYAN)$(FT_LS_BIN) object files were created$(RESET)"
	@echo "$(FT_LS_BIN): $(GRN)$(FT_LS_BIN) was created$(RESET)"



$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(FT_LS_BIN): $(CYAN)$(OBJ_DIR) was created$(RESET)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(CYAN).$(RESET)\c"

$(PRINTF):
	@echo "$(FT_LS_BIN): $(CYAN)creating $(PRINTF)...$(RESET)"
	@$(MAKE) -sC $(PRINTF_DIR)

clean:
	@$(MAKE) -sC $(PRINTF_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "$(FT_LS_BIN): $(YEL)$(OBJ_DIR) was deleted$(RESET)"
	@echo "$(FT_LS_BIN): $(YEL)object files were deleted$(RESET)"

fclean: clean
	@rm -f $(PRINTF)
	@echo "$(FT_LS_BIN): $(YEL)$(PRINTF) was deleted$(RESET)"
	@rm -f $(FT_LS_BIN)
	@echo "$(FT_LS_BIN): $(YEL)$(FT_LS_BIN) was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all