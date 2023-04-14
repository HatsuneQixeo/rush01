NAME		:=	rush01

CC			:=	gcc
CXXFLAGS	:=	-Wall -Wextra -Werror
CXXFLAGS	+=	-g
# CXXFLAGS	+=	-fsanitize=address
# CXXFLAGS	+=	-Wno-unused-variable -Wno-unused-parameter

SRC_DIR		:=	srcs
SRCS		:=	$(wildcard $(SRC_DIR)/*.c)

OBJ_DIR		:=	objs
OBJS		:=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

HEADER		:=	$(wildcard $(SRC_DIR)/*.h)
CFLAGS		:=	$(addprefix -I, $(dir $(HEADER)))

all: $(NAME)

$(OBJ_DIR):
	mkdir $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	$(CC) $(CXXFLAGS) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CXXFLAGS) $^ -o $@

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
