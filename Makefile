SRCS	= \
			main.c \
			srcs/ft_list_at.c \
			srcs/ft_list_pop.c \
			srcs/ft_list_push.c \
			srcs/ft_list_size.c \
			srcs/ft_list_free.c \
			srcs/ft_json_parse.c \
			srcs/ft_json_free.c \
			srcs/ft_json_strerror.c \
			srcs/next_token.c \
			srcs/parse_object.c \
			srcs/parse_member.c \
			srcs/parse_string.c \
			srcs/parse_array.c \
			srcs/parse_value.c \
			srcs/parse_number.c \

LIBS	=	-lft \

HEADERS	=	includes/

LIB_NAMES	= $(subst -l,lib,$(LIBS))
LIB_LD		= $(foreach lib,$(LIB_NAMES),-L$(lib))
LIB_PATHS	= $(foreach lib,$(LIB_NAMES),$(lib)/$(lib).a)
LIB_HEADERS	= $(foreach lib,$(LIB_NAMES),-I$(lib)/includes/)

OBJS		= ${SRCS:.c=.o}
DEPS		= ${SRCS:.c=.d}
CC			= gcc
CCFLAGS		= -Wall -Wextra -g
DEPSFLAGS	= -MMD -MP
NAME		= libftjson
RM			= rm -f
MAKE		= make -C

.PHONY: all clean fclean re

$(NAME) : $(LIB_PATHS) $(OBJS)
		$(CC) $(CCFLAGS) -I$(HEADERS) $(LIB_HEADERS) -o $@ $(OBJS) $(LIB_LD) $(LIBS)

$(LIB_PATHS) :
		$(MAKE) $(notdir $(basename $@))

all : $(NAME)

clean :
		-$(RM) $(OBJS) $(DEPS)

fclean : clean
		$(foreach lib, $(LIB_NAMES), \
			make -C $(lib) fclean; \
		)
		-$(RM) $(NAME)

re : fclean all

-include $(DEPS)

%.o : %.c Makefile
		$(CC) $(CCFLAGS) $(DEPSFLAGS) -I$(HEADERS) $(LIB_HEADERS) -c $< -o $@ $(LIB_LD) $(LIBS)
