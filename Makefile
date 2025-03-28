CC = cc
NAME = philos

#FLAGS
CFLAGS = -g -Wall -Wextra -Werror -I$(INC_DIR)

# Color variables
RED = \033[0;31m
GRN = \033[0;32m
YEL = \033[0;33m
BLU = \033[0;34m
MAG = \033[0;35m
CYN = \033[0;36m
WHT = \033[0;37m
RES = \033[0m

# PATHS
INC_DIR = include/
SRC_DIR = src/
OBJ_DIR = obj/

# FILES
MAIN_FILE = main.c

SRC_FILES := src/errors.c src/parsing.c src/init.c \
			src/utils.c src/utils2.c src/meal.c src/philos.c

OBJ_FILES := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC_FILES))

#PHONY TARGETS
.PHONY: all clean fclean re

#RULES
all: ${NAME}

${NAME}: ${MAIN_FILE} $(OBJ_FILES) | $(OBJ_DIR)
	@${CC} ${CFLAGS} ${MAIN_FILE} $(OBJ_FILES) -o $(NAME)
	@echo "$(GRN)[ ${NAME} ] compiled successfully.$(RES)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
		@rm -rf ${OBJ_DIR}
		@echo "$(WHT)Clean command executed.$(RES)"

fclean: clean
		@rm -f ${NAME}

re: fclean all
