NAME:=ft_nm

CC=cc
INCLUDES=-I./includes
LIBS=
CFLAGS=-Wall -Wextra -Werror $(INCLUDES)

SRC_MAIN=./src/main.c
SRC_COMMON=

SRC_MANDATORY=./src/mandatory/nm.c
SRC_BONUS=./src/bonus/nm_bonus.c

SRC=$(SRC_COMMON)

all: MODE=mandatory
all: SRC:=$(SRC) $(SRC_MANDATORY)
all: $(NAME)

bonus: MODE=bonus
bonus: SRC:=$(SRC) $(SRC_BONUS)
bonus: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC_MAIN) $(SRC) $(LIBS)
	@echo "\e[1;33m$(NAME) \e[1;32mcompiled successfully \e[1;35m($(MODE))\e[0m"

clean:

fclean: clean
	rm -f $(NAME)

re: fclean all


.PHONY: all clean fclean re
# .SILENT: