NAME = minishell

SRC = $(NAME)

INC = $(NAME) 

SRCDIR = ./src/

INCDIR = ./inc/

OBJ_DST_DIR = ./obj_dst/

SRCS = $(addprefix $(SRCDIR),$(addsuffix .c,$(SRC)))
SRCS = $(addprefix $(SRCDIR),$(addsuffix .c,$(SRC)))
OBJS = $(addprefix $(OBJ_DST_DIR),$(addsuffix .o,$(SRC)))
DSTS = $(addprefix $(OBJ_DST_DIR),$(addsuffix .d,$(SRC)))
INCLUDE:= $(addprefix $(INCDIR),$(addsuffix .h, $(INC)))

#LIBFT LIBRARY
DIR_LIBFT = $(addprefix $(INCDIR),libft/)
LIBFT = $(addprefix $(DIR_LIBFT),libft.a)

CC:= gcc

FLAGS:= -Werror -Wextra -Wall -O2 -fsanitize=address -g

VISUAL = MANDAT
#-fsanitize=datarace -fsanitize=address
RM := rm -rfd

all:  $(NAME) $(LIBFT)

-include $(DSTS)

$(NAME): $(OBJS) 
	$(CC) $(FLAGS)  $(OBJS) -o $(NAME)

#-static-libsan 
$(DIR_OBJ_DST)%.o: $(DIR_SRC)%.c $(DIR_OBJ_DST)%.d
	@mkdir -p $(DIR_OBJ_DST)
	@echo "compiling" $(DIR_SRC)$*.c '\r'
	@$(CC) $(FLAGS) -D $(VISUAL) -static-libsan -c $(DIR_SRC)$*.c -o $(DIR_OBJ_DST)$*.o

$(DIR_OBJ_DST)%.d: $(DIR_SRC)%.c $(INCLUDE)
	@mkdir -p $(DIR_OBJ_DST)
	@$(CC) $(FLAGS) -MM -c $(DIR_SRC)$*.c -o $(DIR_OBJ_DST)$*.d 

libft:
	MAKE -C$(DIR_LIBFT)

clean:
	$(RM) $(DIR_OBJ_DST)
	MAKE -C$(DIR_LIBFT) clean

fclean: clean
	$(RM) $(NAME)
	MAKE -C$(DIR_LIBFT) fclean

re: fclean all

print:
	@echo INCLUDE: $(INCLUDE)
	@echo NAME: $(NAME)
	@echo SRC: $(SRCS)
	@echo OBJS: $(OBJS)
	@echo DSTS: $(DSTS)
	@echo DIR_OBJ_DST: $(DIR_OBJ_DST)
	@echo DIRLIBFT: $(DIR_LIBFT)
	@echo LIBFT: $(LIBFT)

.PHONY: all re clean fclean print
