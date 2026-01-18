NAME=libasm.a
TEST_NAME=libasm

SRC= ./ft_strlen.s
AS=nasm
ASFLAGS= -g -f elf64 $(ASDEBUGFLAGS)

OBJ=$(SRC:.s=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) rcs $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

$(TEST_NAME): $(NAME)
	$(CC) $(CFLAGS) -g -I. main.c -o $(TEST_NAME) -L. -lasm

debug: ASDEBUGFLAGS=-gdwarf
debug: re

test: debug $(TEST_NAME)


.PHONY: all clean fclean re