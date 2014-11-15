CXX	=	g++
RM	=	rm -f

CPPFLAGS +=	-Wextra -Wall -Werror
CPPFLAGS +=	-std=c++11
CPPFLAGS +=	-I.

LDFLAGS +=	-static

SRCS	=	main.cpp
OBJS	=	$(SRCS:.cpp=.o)

BIN	=	../bin/
LIB	=	libcorniflex.a
NAME	=	a.out

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CXX) $(OBJS) -o $(NAME) -l$(subst lib,,$(subst .a,,$(LIB)))

depend:		.depend

.depend:	$(SRCS)
		$(RM) ./.depend
		$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)
		$(RM) ./.depend

re:		fclean all

run:		$(NAME)
		./$(NAME)

debug:		$(NAME)
		valgrind --track-origins=yes ./$(NAME)

include .depend

.PHONY:		all clean fclean re run debug
