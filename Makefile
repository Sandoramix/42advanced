NAME=libasm.a
TESTPROG_NAME=libasm

SRC = ./ft_read.s \
	./ft_strcmp.s \
	./ft_strcpy.s \
	./ft_strdup.s \
	./ft_strlen.s \
	./ft_write.s

SRC_BONUS = ./ft_list_push_front_bonus.s \
	./ft_list_size_bonus.s

AS=nasm
ASFLAGS= -g -f elf64 $(ASDEBUGFLAGS)

OBJ=$(SRC:.s=.o)
OBJ_BONUS=$(SRC_BONUS:.s=.o)

all: $(NAME)

bonus: OBJ := $(OBJ) $(OBJ_BONUS)
bonus: $(OBJ_BONUS) $(NAME)

$(NAME): $(OBJ)
	$(AR) rcs $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
	$(RM) $(NAME) $(TESTPROG_NAME)

re: fclean all

CC=clang
CFLAGS+= -w -g
$(TESTPROG_NAME): $(NAME)
	$(CC) $(CFLAGS) -I. main.c -L. -lasm -o $(TESTPROG_NAME)

debug: ASDEBUGFLAGS=-gdwarf
debug: fclean bonus

test: debug $(TESTPROG_NAME)

.PHONY: all clean fclean re