NAME:=ft_nm

CC=cc
INCLUDES=-I./includes
LIBS=
CFLAGS=-Wall -Wextra -Werror $(INCLUDES) -g

SRC_COMMON=./src/main.c \
	./src/nm/parsing/identify_option.c \
	./src/nm/parsing/parse_argv.c \
	./src/nm/get_known_options.c \
	./src/nm/getfilestat.c \
	./src/nm/identify_elf_format.c \
	./src/nm/nm_cycle.c \
	./src/utils/ft_strcmp.c \
	./src/utils/ft_strlen.c

SRC_MANDATORY=./src/mandatory/nm.c \
	./src/mandatory/help_message.c

SRC_BONUS=./src/bonus/nm_bonus.c \
	./src/bonus/help_message_bonus.c

SRC=$(SRC_COMMON)

all: MODE=mandatory
all: SRC:=$(SRC) $(SRC_MANDATORY)
all: $(NAME)

bonus: MODE=bonus
bonus: SRC:=$(SRC) $(SRC_BONUS)
bonus: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(LIBS)
	@echo "\e[1;33m$(NAME) \e[1;32mcompiled successfully \e[1;35m($(MODE))\e[0m"

clean:

fclean: clean
	rm -f $(NAME)

re: fclean all
re-bonus: fclean bonus

test: re
	./$(NAME) $(NAME)

.PHONY: all clean fclean re
# .SILENT: