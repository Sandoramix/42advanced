NAME=libasm.a
TEST_NAME=libasm

SRC = ./ft_read.s \
	./ft_strcmp.s \
	./ft_strcpy.s \
	./ft_strdup.s \
	./ft_strlen.s \
	./ft_write.s

SRC_BONUS = ./ft_list_push_front_bonus.s \
	./ft_list_size_bonus.s \
	./ft_list_sort_bonus.s

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
	$(RM) $(NAME)

re: fclean all

$(TEST_NAME): $(NAME)
	$(CC) $(CFLAGS) -w -g -I. main.c -o $(TEST_NAME) -L. -lasm

debug: ASDEBUGFLAGS=-gdwarf
debug: fclean bonus

test: debug $(TEST_NAME)

.PHONY: all clean fclean re