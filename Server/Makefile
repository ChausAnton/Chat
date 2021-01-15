NAME		=	server

GTKFLAGS	=	`pkg-config --cflags --libs gtk+-3.0`
# GTKFLAGS	=	-I resource/GTK/include -L resource/GTK/lib \
# 				-lgtk-3 -lgdk-3 -Wl,-framework,Cocoa -Wl,-framework,Carbon \
# 				-Wl,-framework,CoreGraphics -lpangocairo-1.0 -lpango-1.0 \
# 				-lharfbuzz -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 \
# 				-lgio-2.0 -lgobject-2.0 -lglib-2.0 -lintl

ORACLE		=	-std=c11 -Wall -Wextra -Werror -Wpedantic
CFLAGS		=	$(GTKFLAGS)

INC 		=	inc/*.h
SRC 		= 	src/*.c

all: install clean

install:
	@cp $(SRC) .
	@cp $(INC) .
	@clang $(CFLAGS) -o $(NAME) *.c

clean:
	@rm -rf *.h
	@rm -rf *.c

uninstall: clean
	@rm -rf $(NAME)
	
reinstall: uninstall install clean
