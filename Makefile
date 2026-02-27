NAME:=ft_nm

CC=cc
INCLUDES=-I./includes
LIBS=
CFLAGS=-Wall -Wextra -Werror $(INCLUDES) -g

SRC_COMMON= ./src/main.c \
	./src/nm/elf32/nm32_run.c \
	./src/nm/elf32/nm32_symbols.c \
	./src/nm/elf64/nm64_run.c \
	./src/nm/elf64/nm64_symbols.c \
	./src/nm/help_options.c \
	./src/nm/nm_run.c \
	./src/nm/nm_utils.c \
	./src/nm/parsing/identify_option.c \
	./src/nm/parsing/nm_symbol.c \
	./src/nm/parsing/parse_argv.c \
	./src/utils/elf_utils.c \
	./src/utils/file_utils.c \
	./src/utils/ft_strchr.c \
	./src/utils/ft_strcmp.c \
	./src/utils/ft_strlen.c \
	./src/utils/ft_tolower.c \
	./src/utils/print_utils.c


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
	@echo "\e[1;30mTry it out, run:\e[0m \e[1;36mdiff <(nm $(NAME)) <(./$(NAME) $(NAME))\e[0m"

clean:

fclean: clean
	rm -f $(NAME)

re: fclean all
re-bonus: fclean bonus

test: re
	./$(NAME) $(NAME)

.PHONY: all clean fclean re
# .SILENT: