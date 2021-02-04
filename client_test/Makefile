NAME		=	client

#GTKFLAGS	=	`pkg-config --cflags --libs gtk+-3.0`
GTKFLAGS	=   -L resource/gtk3/lib -lgtk-3.0 -L resource/gtk3/lib -lgdk-3.0

GLIBFLAGS   =   -L resource/glib/lib -lglib-2.0.0 -lgobject-2.0.0
GIOFLAGS	=	-L resource/glib/lib -lgio-2.0.0 
PANGOFLAGS 	=	-L resource/pango/lib -lpango-1.0.0 -lpangocairo-1.0.0
CAIROFLAGS	=	-L resource/cairo/lib -lcairo-gobject.2 -lcairo.2
PBUFFFLAGS	=	-L resource/gdkpixbuf/lib -lgdk_pixbuf-2.0.0
ATKFLAGS	=	-L resource/atk/lib -latk-1.0.0	
HBUZZFLAGS	=	-L resource/harfbuzz/lib -lharfbuzz.0		
GTEXTFLAGS	=	-L resource/gettext/lib -lintl.8

ORACLE		=	-std=c11 -Wall -Wextra -Werror -Wpedantic
CFLAGS		=	$(ORACLE)
GTK 		= 	$(GTKFLAGS) $(GLIBFLAGS) $(GIOFLAGS) $(PANGOFLAGS) $(CAIROFLAGS) $(PBUFFFLAGS) $(ATKFLAGS) $(HBUZZFLAGS) $(GTEXTFLAGS)

SRC_DIR = src

OBJ_DIR = obj

INC_DIR = inc

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILES:%.c=%.o)))

INC_FILES = $(wildcard $(INC_DIR)/*.h)

AR = ar

AFLAGS = rcs

MKDIR = mkdir -p
RM = rm -rf

USER_NAMES = irazumeyko $$USER

PREFIX_NAME = $(addprefix ./, $(NAME))
QUARTZ_PATH = $$HOME/.brew/Cellar/gtk+3/3.24.24/lib/gtk-3.0/3.0.0/immodules/im-quartz.so

PIXBUFFLOADER_PNG_PATH = $$HOME/.brew/lib/gdk-pixbuf-2.0/2.10.0/loaders/libpixbufloader-png.so
PIXBUFFLOADER_JPEG_PATH = $$HOME/.brew/lib/gdk-pixbuf-2.0/2.10.0/loaders/libpixbufloader-jpeg.so


all: perms install changeFromBrew clean

perms:
	@chmod -R 700 $$HOME/.brew
	@chmod -R 700 $$HOME/Desktop/Chat

install: $(OBJ_FILES)
	@$(CC) $(CFLAGS) $^ -o $(NAME) -I $(INC_DIR) $(GTK)
	@printf "\r\33[2K$@\t \033[32;1mcreated\033[0m\n"

changeFromBrew: $(USER_NAMES)
$(USER_NAMES):
	@install_name_tool -change /Users/$@/.brew/Cellar/gtk+3/3.24.24/lib/libgdk-3.0.dylib $$HOME/Desktop/Chat/client_test/resource/gtk3/lib/libgdk-3.0.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/gdk-pixbuf/lib/libgdk_pixbuf-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/glib/lib/libgmodule-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgmodule-2.0.0.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/glib/lib/libglib-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/glib/lib/libgobject-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/glib/lib/libgio-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgio-2.0.0.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/pango/lib/libpangocairo-1.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/pango/lib/libpangocairo-1.0.0.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/pango/lib/libpangoft2-1.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/pango/lib/libpangoft2-1.0.0.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/cairo/lib/libcairo.2.dylib $$HOME/Desktop/Chat/client_test/resource/cairo/lib/libcairo.2.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/cairo/lib/libcairo-gobject.2.dylib $$HOME/Desktop/Chat/client_test/resource/cairo/lib/libcairo-gobject.2.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/atk/lib/libatk-1.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/atk/lib/libatk-1.0.0.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/harfbuzz/lib/libharfbuzz.0.dylib $$HOME/Desktop/Chat/client_test/resource/harfbuzz/lib/libharfbuzz.0.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/gettext/lib/libintl.8.dylib $$HOME/Desktop/Chat/client_test/resource/gettext/lib/libintl.8.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/freetype/lib/libfreetype.6.dylib $$HOME/.brew/opt/freetype/lib/libfreetype.6.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/fribidi/lib/libfribidi.0.dylib $$HOME/.brew/opt/fribidi/lib/libfribidi.0.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/libepoxy/lib/libepoxy.0.dylib $$HOME/.brew/opt/libepoxy/lib/libepoxy.0.dylib resource/gtk3/lib/libgtk-3.0.dylib

	@install_name_tool -change /Users/$@/.brew/opt/gdk-pixbuf/lib/libgdk_pixbuf-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib resource/gtk3/lib/libgdk-3.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/glib/lib/libgmodule-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgmodule-2.0.0.dylib resource/gtk3/lib/libgdk-3.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/glib/lib/libglib-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib resource/gtk3/lib/libgdk-3.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/glib/lib/libgobject-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib resource/gtk3/lib/libgdk-3.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/glib/lib/libgio-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgio-2.0.0.dylib resource/gtk3/lib/libgdk-3.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/pango/lib/libpango-1.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/pango/lib/libpango-1.0.0.dylib resource/gtk3/lib/libgdk-3.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/pango/lib/libpangocairo-1.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/pango/lib/libpangocairo-1.0.0.dylib resource/gtk3/lib/libgdk-3.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/cairo/lib/libcairo.2.dylib $$HOME/Desktop/Chat/client_test/resource/cairo/lib/libcairo.2.dylib resource/gtk3/lib/libgdk-3.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/cairo/lib/libcairo-gobject.2.dylib $$HOME/Desktop/Chat/client_test/resource/cairo/lib/libcairo-gobject.2.dylib resource/gtk3/lib/libgdk-3.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/atk/lib/libatk-1.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/atk/lib/libatk-1.0.0.dylib resource/gtk3/lib/libgdk-3.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/gettext/lib/libintl.8.dylib $$HOME/Desktop/Chat/client_test/resource/gettext/lib/libintl.8.dylib resource/gtk3/lib/libgdk-3.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/fribidi/lib/libfribidi.0.dylib $$HOME/.brew/opt/fribidi/lib/libfribidi.0.dylib resource/gtk3/lib/libgdk-3.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/libepoxy/lib/libepoxy.0.dylib $$HOME/.brew/opt/libepoxy/lib/libepoxy.0.dylib resource/gtk3/lib/libgdk-3.0.dylib

	@install_name_tool -change /Users/$@/.brew/opt/glib/lib/libglib-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/glib/lib/libgobject-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/glib/lib/libgio-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgio-2.0.0.dylib resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/gettext/lib/libintl.8.dylib $$HOME/Desktop/Chat/client_test/resource/gettext/lib/libintl.8.dylib resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/gdk-pixbuf/lib/libgdk_pixbuf-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib	

	@install_name_tool -change /Users/$@/.brew/Cellar/glib/2.66.4_1/lib/libglib-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib resource/glib/lib/libgio-2.0.0.dylib
	@install_name_tool -change /Users/$@/.brew/Cellar/glib/2.66.4_1/lib/libgobject-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib resource/glib/lib/libgio-2.0.0.dylib
	@install_name_tool -change /Users/$@/.brew/Cellar/glib/2.66.4_1/lib/libgmodule-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgmodule-2.0.0.dylib resource/glib/lib/libgio-2.0.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/gettext/lib/libintl.8.dylib $$HOME/Desktop/Chat/client_test/resource/gettext/lib/libintl.8.dylib resource/glib/lib/libgio-2.0.0.dylib

	@install_name_tool -change /Users/$@/.brew/opt/gettext/lib/libintl.8.dylib $$HOME/Desktop/Chat/client_test/resource/gettext/lib/libintl.8.dylib resource/glib/lib/libglib-2.0.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/pcre/lib/libpcre.1.dylib $$HOME/.brew/opt/pcre/lib/libpcre.1.dylib resource/glib/lib/libglib-2.0.0.dylib

	@install_name_tool -change /Users/$@/.brew/Cellar/glib/2.66.4_1/lib/libglib-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib resource/glib/lib/libgobject-2.0.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/libffi/lib/libffi.7.dylib $$HOME/.brew/opt/libffi/lib/libffi.7.dylib resource/glib/lib/libgobject-2.0.0.dylib

	@install_name_tool -change /Users/$@/.brew/opt/glib/lib/libglib-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib resource/pango/lib/libpango-1.0.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/glib/lib/libgobject-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib resource/pango/lib/libpango-1.0.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/glib/lib/libgio-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgio-2.0.0.dylib resource/pango/lib/libpango-1.0.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/harfbuzz/lib/libharfbuzz.0.dylib $$HOME/Desktop/Chat/client_test/resource/harfbuzz/lib/libharfbuzz.0.dylib resource/pango/lib/libpango-1.0.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/fribidi/lib/libfribidi.0.dylib $$HOME/.brew/opt/fribidi/lib/libfribidi.0.dylib resource/pango/lib/libpango-1.0.0.dylib

	@install_name_tool -change /Users/$@/.brew/opt/glib/lib/libglib-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib resource/pango/lib/libpangocairo-1.0.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/glib/lib/libgobject-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib resource/pango/lib/libpangocairo-1.0.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/glib/lib/libgio-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgio-2.0.0.dylib resource/pango/lib/libpangocairo-1.0.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/harfbuzz/lib/libharfbuzz.0.dylib $$HOME/Desktop/Chat/client_test/resource/harfbuzz/lib/libharfbuzz.0.dylib resource/pango/lib/libpangocairo-1.0.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/cairo/lib/libcairo.2.dylib $$HOME/Desktop/Chat/client_test/resource/cairo/lib/libcairo.2.dylib resource/pango/lib/libpangocairo-1.0.0.dylib
	@install_name_tool -change /Users/$@/.brew/Cellar/pango/1.48.1/lib/libpango-1.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/pango/lib/libpango-1.0.0.dylib resource/pango/lib/libpangocairo-1.0.0.dylib
	@install_name_tool -change /Users/$@/.brew/Cellar/pango/1.48.1/lib/libpangoft2-1.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/pango/lib/libpangoft2-1.0.0.dylib resource/pango/lib/libpangocairo-1.0.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/fontconfig/lib/libfontconfig.1.dylib $$HOME/.brew/opt/fontconfig/lib/libfontconfig.1.dylib resource/pango/lib/libpangocairo-1.0.0.dylib

	@#install_name_tool -change /Users/$@/.brew/opt/glib/lib/libglib-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib resource/pango/lib/libpangoft2-1.0.0.dylib
	@#install_name_tool -change /Users/$@/.brew/opt/glib/lib/libgobject-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib resource/pango/lib/libpangoft2-1.0.0.dylib
	@#install_name_tool -change /Users/$@/.brew/opt/glib/lib/libgio-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgio-2.0.0.dylib resource/pango/lib/libpangoft2-1.0.0.dylib
	@#install_name_tool -change /Users/$@/.brew/opt/harfbuzz/lib/libharfbuzz.0.dylib $$HOME/Desktop/Chat/client_test/resource/harfbuzz/lib/libharfbuzz.0.dylib resource/pango/lib/libpangoft2-1.0.0.dylib
	@#install_name_tool -change /Users/$@/.brew/opt/cairo/lib/libcairo.2.dylib $$HOME/Desktop/Chat/client_test/resource/cairo/lib/libcairo.2.dylib resource/pango/lib/libpangoft2-1.0.0.dylib

	@install_name_tool -change /Users/$@/.brew/Cellar/cairo/1.16.0_4/lib/libcairo.2.dylib $$HOME/Desktop/Chat/client_test/resource/cairo/lib/libcairo.2.dylib resource/cairo/lib/libcairo-gobject.2.dylib
	@install_name_tool -change /Users/$@/.brew/opt/pixman/lib/libpixman-1.0.dylib $$HOME/.brew/opt/pixman/lib/libpixman-1.0.dylib resource/cairo/lib/libcairo-gobject.2.dylib
	@install_name_tool -change /Users/$@/.brew/opt/fontconfig/lib/libfontconfig.1.dylib $$HOME/.brew/opt/fontconfig/lib/libfontconfig.1.dylib resource/cairo/lib/libcairo-gobject.2.dylib
	@install_name_tool -change /Users/$@/.brew/opt/freetype/lib/libfreetype.6.dylib $$HOME/.brew/opt/freetype/lib/libfreetype.6.dylib resource/cairo/lib/libcairo-gobject.2.dylib
	@install_name_tool -change /Users/$@/.brew/opt/libpng/lib/libpng16.16.dylib $$HOME/.brew/opt/libpng/lib/libpng16.16.dylib resource/cairo/lib/libcairo-gobject.2.dylib
	@install_name_tool -change /Users/$@/.brew/opt/glib/lib/libglib-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib resource/cairo/lib/libcairo-gobject.2.dylib
	@install_name_tool -change /Users/$@/.brew/opt/glib/lib/libgobject-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib resource/cairo/lib/libcairo-gobject.2.dylib
	@install_name_tool -change /Users/$@/.brew/opt/gettext/lib/libintl.8.dylib $$HOME/Desktop/Chat/client_test/resource/gettext/lib/libintl.8.dylib resource/cairo/lib/libcairo-gobject.2.dylib

	@install_name_tool -change /Users/$@/.brew/Cellar/cairo/1.16.0_4/lib/libcairo.2.dylib $$HOME/Desktop/Chat/client_test/resource/cairo/lib/libcairo.2.dylib resource/cairo/lib/libcairo.2.dylib
	@install_name_tool -change /Users/$@/.brew/opt/pixman/lib/libpixman-1.0.dylib $$HOME/.brew/opt/pixman/lib/libpixman-1.0.dylib resource/cairo/lib/libcairo.2.dylib
	@install_name_tool -change /Users/$@/.brew/opt/fontconfig/lib/libfontconfig.1.dylib $$HOME/.brew/opt/fontconfig/lib/libfontconfig.1.dylib resource/cairo/lib/libcairo.2.dylib
	@install_name_tool -change /Users/$@/.brew/opt/freetype/lib/libfreetype.6.dylib $$HOME/.brew/opt/freetype/lib/libfreetype.6.dylib resource/cairo/lib/libcairo.2.dylib
	@install_name_tool -change /Users/$@/.brew/opt/libpng/lib/libpng16.16.dylib $$HOME/.brew/opt/libpng/lib/libpng16.16.dylib resource/cairo/lib/libcairo.2.dylib

	@install_name_tool -change /Users/$@/.brew/opt/glib/lib/libglib-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib resource/atk/lib/libatk-1.0.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/glib/lib/libgobject-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib resource/atk/lib/libatk-1.0.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/gettext/lib/libintl.8.dylib $$HOME/Desktop/Chat/client_test/resource/gettext/lib/libintl.8.dylib resource/atk/lib/libatk-1.0.0.dylib

	@install_name_tool -change /Users/$@/.brew/opt/glib/lib/libglib-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib resource/harfbuzz/lib/libharfbuzz.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/freetype/lib/libfreetype.6.dylib $$HOME/.brew/opt/freetype/lib/libfreetype.6.dylib resource/harfbuzz/lib/libharfbuzz.0.dylib
	@install_name_tool -change /Users/$@/.brew/opt/graphite2/lib/libgraphite2.3.dylib $$HOME/.brew/opt/graphite2/lib/libgraphite2.3.dylib resource/harfbuzz/lib/libharfbuzz.0.dylib

	@install_name_tool -change /Users/$@/.brew/Cellar/gtk+3/3.24.24/lib/lib/libgtk-3.0.dylib $$HOME/Desktop/Chat/client_test/resource/gtk3/lib/libgtk-3.0.dylib $(QUARTZ_PATH)
	@install_name_tool -change /Users/$@/.brew/Cellar/gtk+3/3.24.24/lib/libgdk-3.0.dylib $$HOME/Desktop/Chat/client_test/resource/gtk3/lib/libgdk-3.0.dylib $(QUARTZ_PATH)
	@install_name_tool -change /Users/$@/.brew/opt/glib/lib/libglib-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib $(QUARTZ_PATH)
	@install_name_tool -change /Users/$@/.brew/opt/glib/lib/libgobject-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib $(QUARTZ_PATH)
	@install_name_tool -change /Users/$@/.brew/opt/pango/lib/libpango-1.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/pango/lib/libpango-1.0.0.dylib $(QUARTZ_PATH)

	@install_name_tool -change /Users/$@/.brew/opt/libpng/lib/libpng16.16.dylib $$HOME/.brew/opt/libpng/lib/libpng16.16.dylib $(PIXBUFFLOADER_PNG_PATH)
	@install_name_tool -change /Users/$@/.brew/opt/glib/lib/libglib-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib $(PIXBUFFLOADER_PNG_PATH)
	@install_name_tool -change /Users/$@/.brew/opt/glib/lib/libgobject-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib $(PIXBUFFLOADER_PNG_PATH)
	@install_name_tool -change /Users/$@/.brew/Cellar/gdk-pixbuf/2.42.2/lib/libgdk_pixbuf-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib $(PIXBUFFLOADER_PNG_PATH)

	@install_name_tool -change /Users/$@/.brew/opt/jpeg/lib/libjpeg.9.dylib $$HOME/.brew/opt/jpeg/lib/libjpeg.9.dylib $(PIXBUFFLOADER_JPEG_PATH)
	@install_name_tool -change /Users/$@/.brew/opt/glib/lib/libglib-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib $(PIXBUFFLOADER_JPEG_PATH)
	@install_name_tool -change /Users/$@/.brew/opt/glib/lib/libgobject-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib $(PIXBUFFLOADER_JPEG_PATH)
	@install_name_tool -change /Users/$@/.brew/Cellar/gdk-pixbuf/2.42.2/lib/libgdk_pixbuf-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib $(PIXBUFFLOADER_JPEG_PATH)

	@install_name_tool -change /Users/$@/.brew/opt/gtk+3/lib/libgtk-3.0.dylib $$HOME/Desktop/Chat/client_test/resource/gtk3/lib/libgtk-3.0.dylib $(PREFIX_NAME)
	@install_name_tool -change /Users/$@/.brew/opt/gtk+3/lib/libgdk-3.0.dylib $$HOME/Desktop/Chat/client_test/resource/gtk3/lib/libgdk-3.0.dylib $(PREFIX_NAME)
	@install_name_tool -change /Users/$@/.brew/opt/gdk-pixbuf/lib/libgdk_pixbuf-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib $(PREFIX_NAME)
	@install_name_tool -change /Users/$@/.brew/opt/glib/lib/libgio-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgio-2.0.0.dylib $(PREFIX_NAME)
	@install_name_tool -change /Users/$@/.brew/opt/glib/lib/libglib-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib $(PREFIX_NAME)
	@install_name_tool -change /Users/$@/.brew/opt/glib/lib/libgobject-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib $(PREFIX_NAME)
	@install_name_tool -change /Users/$@/.brew/opt/pango/lib/libpango-1.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/pango/lib/libpango-1.0.0.dylib $(PREFIX_NAME)
	@install_name_tool -change /Users/$@/.brew/opt/pango/lib/libpangocairo-1.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/pango/lib/libpangocairo-1.0.0.dylib $(PREFIX_NAME)
	@install_name_tool -change /Users/$@/.brew/opt/cairo/lib/libcairo-gobject.2.dylib $$HOME/Desktop/Chat/client_test/resource/cairo/lib/libcairo-gobject.2.dylib $(PREFIX_NAME)
	@install_name_tool -change /Users/$@/.brew/opt/cairo/lib/libcairo.2.dylib $$HOME/Desktop/Chat/client_test/resource/cairo/lib/libcairo.2.dylib $(PREFIX_NAME)
	@install_name_tool -change /Users/$@/.brew/opt/atk/lib/libatk-1.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/atk/lib/libatk-1.0.0.dylib $(PREFIX_NAME)
	@install_name_tool -change /Users/$@/.brew/opt/harfbuzz/lib/libharfbuzz.0.dylib $$HOME/Desktop/Chat/client_test/resource/harfbuzz/lib/libharfbuzz.0.dylib $(PREFIX_NAME)
	@install_name_tool -change /Users/$@/.brew/opt/gettext/lib/libintl.8.dylib $$HOME/Desktop/Chat/client_test/resource/gettext/lib/libintl.8.dylib $(PREFIX_NAME)

#changeFromDesktop: 
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/gtk3/lib/libgdk-3.0.dylib $$HOME/Desktop/Chat/client_test/resource/gtk3/lib/libgdk-3.0.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libgmodule-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgmodule-2.0.0.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libgio-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgio-2.0.0.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/pango/lib/libpangocairo-1.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/pango/lib/libpangocairo-1.0.0.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/pango/lib/libpangoft2-1.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/pango/lib/libpangoft2-1.0.0.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/cairo/lib/libcairo.2.dylib $$HOME/Desktop/Chat/client_test/resource/cairo/lib/libcairo.2.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/cairo/lib/libcairo-gobject.2.dylib $$HOME/Desktop/Chat/client_test/resource/cairo/lib/libcairo-gobject.2.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/atk/lib/libatk-1.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/atk/lib/libatk-1.0.0.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/harfbuzz/lib/libharfbuzz.0.dylib $$HOME/Desktop/Chat/client_test/resource/harfbuzz/lib/libharfbuzz.0.dylib resource/gtk3/lib/libgtk-3.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/gettext/lib/libintl.8.dylib $$HOME/Desktop/Chat/client_test/resource/gettext/lib/libintl.8.dylib resource/gtk3/lib/libgtk-3.0.dylib

	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib resource/gtk3/lib/libgdk-3.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libgmodule-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgmodule-2.0.0.dylib resource/gtk3/lib/libgdk-3.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib resource/gtk3/lib/libgdk-3.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib resource/gtk3/lib/libgdk-3.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libgio-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgio-2.0.0.dylib resource/gtk3/lib/libgdk-3.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/pango/lib/libpango-1.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/pango/lib/libpango-1.0.0.dylib resource/gtk3/lib/libgdk-3.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/pango/lib/libpangocairo-1.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/pango/lib/libpangocairo-1.0.0.dylib resource/gtk3/lib/libgdk-3.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/cairo/lib/libcairo.2.dylib $$HOME/Desktop/Chat/client_test/resource/cairo/lib/libcairo.2.dylib resource/gtk3/lib/libgdk-3.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/cairo/lib/libcairo-gobject.2.dylib $$HOME/Desktop/Chat/client_test/resource/cairo/lib/libcairo-gobject.2.dylib resource/gtk3/lib/libgdk-3.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/atk/lib/libatk-1.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/atk/lib/libatk-1.0.0.dylib resource/gtk3/lib/libgdk-3.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/gettext/lib/libintl.8.dylib $$HOME/Desktop/Chat/client_test/resource/gettext/lib/libintl.8.dylib resource/gtk3/lib/libgdk-3.0.dylib

	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libgio-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgio-2.0.0.dylib resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/gettext/lib/libintl.8.dylib $$HOME/Desktop/Chat/client_test/resource/gettext/lib/libintl.8.dylib resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib	

	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib resource/glib/lib/libgio-2.0.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib resource/glib/lib/libgio-2.0.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libgmodule-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgmodule-2.0.0.dylib resource/glib/lib/libgio-2.0.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/gettext/lib/libintl.8.dylib $$HOME/Desktop/Chat/client_test/resource/gettext/lib/libintl.8.dylib resource/glib/lib/libgio-2.0.0.dylib

	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/gettext/lib/libintl.8.dylib $$HOME/Desktop/Chat/client_test/resource/gettext/lib/libintl.8.dylib resource/glib/lib/libglib-2.0.0.dylib

	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib resource/glib/lib/libgobject-2.0.0.dylib

	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib resource/pango/lib/libpango-1.0.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib resource/pango/lib/libpango-1.0.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libgio-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgio-2.0.0.dylib resource/pango/lib/libpango-1.0.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/harfbuzz/lib/libharfbuzz.0.dylib $$HOME/Desktop/Chat/client_test/resource/harfbuzz/lib/libharfbuzz.0.dylib resource/pango/lib/libpango-1.0.0.dylib

	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib resource/pango/lib/libpangocairo-1.0.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib resource/pango/lib/libpangocairo-1.0.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libgio-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgio-2.0.0.dylib resource/pango/lib/libpangocairo-1.0.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/harfbuzz/lib/libharfbuzz.0.dylib $$HOME/Desktop/Chat/client_test/resource/harfbuzz/lib/libharfbuzz.0.dylib resource/pango/lib/libpangocairo-1.0.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/cairo/lib/libcairo.2.dylib $$HOME/Desktop/Chat/client_test/resource/cairo/lib/libcairo.2.dylib resource/pango/lib/libpangocairo-1.0.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/pango/lib/libpango-1.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/pango/lib/libpango-1.0.0.dylib resource/pango/lib/libpangocairo-1.0.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/pango/lib/libpangoft2-1.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/pango/lib/libpangoft2-1.0.0.dylib resource/pango/lib/libpangocairo-1.0.0.dylib

	@#install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib resource/pango/lib/libpangoft2-1.0.0.dylib
	@#install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib resource/pango/lib/libpangoft2-1.0.0.dylib
	@#install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libgio-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgio-2.0.0.dylib resource/pango/lib/libpangoft2-1.0.0.dylib
	@#install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/harfbuzz/lib/libharfbuzz.0.dylib $$HOME/Desktop/Chat/client_test/resource/harfbuzz/lib/libharfbuzz.0.dylib resource/pango/lib/libpangoft2-1.0.0.dylib
	@#install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/cairo/lib/libcairo.2.dylib $$HOME/Desktop/Chat/client_test/resource/cairo/lib/libcairo.2.dylib resource/pango/lib/libpangoft2-1.0.0.dylib

	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/cairo/lib/libcairo.2.dylib $$HOME/Desktop/Chat/client_test/resource/cairo/lib/libcairo.2.dylib resource/cairo/lib/libcairo-gobject.2.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib resource/cairo/lib/libcairo-gobject.2.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib resource/cairo/lib/libcairo-gobject.2.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/gettext/lib/libintl.8.dylib $$HOME/Desktop/Chat/client_test/resource/gettext/lib/libintl.8.dylib resource/cairo/lib/libcairo-gobject.2.dylib

	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/cairo/lib/libcairo.2.dylib $$HOME/Desktop/Chat/client_test/resource/cairo/lib/libcairo.2.dylib resource/cairo/lib/libcairo.2.dylib

	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib resource/atk/lib/libatk-1.0.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib resource/atk/lib/libatk-1.0.0.dylib
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/gettext/lib/libintl.8.dylib $$HOME/Desktop/Chat/client_test/resource/gettext/lib/libintl.8.dylib resource/atk/lib/libatk-1.0.0.dylib

	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib resource/harfbuzz/lib/libharfbuzz.0.dylib

	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/gtk3/lib/libgtk-3.0.dylib $$HOME/Desktop/Chat/client_test/resource/gtk3/lib/libgtk-3.0.dylib $(QUARTZ_PATH)
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/gtk3/lib/libgdk-3.0.dylib $$HOME/Desktop/Chat/client_test/resource/gtk3/lib/libgdk-3.0.dylib $(QUARTZ_PATH)
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib $(QUARTZ_PATH)
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib $(QUARTZ_PATH)
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/pango/lib/libpango-1.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/pango/lib/libpango-1.0.0.dylib $(QUARTZ_PATH)

	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib $(PIXBUFFLOADER_PNG_PATH)
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib $(PIXBUFFLOADER_PNG_PATH)
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib $(PIXBUFFLOADER_PNG_PATH)

	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libglib-2.0.0.dylib $(PIXBUFFLOADER_JPEG_PATH)
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/glib/lib/libgobject-2.0.0.dylib $(PIXBUFFLOADER_JPEG_PATH)
	@install_name_tool -change /Users/$@/Desktop/Chat/client_test/resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib $$HOME/Desktop/Chat/client_test/resource/gdkpixbuf/lib/libgdk_pixbuf-2.0.0.dylib $(PIXBUFFLOADER_JPEG_PATH)
$(OBJ_FILES): | $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_FILES)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)
	@printf "\r\33[2K$(NAME)\033[33;1m\t compile \033[0m$(<:$(SRC_DIR)/%.c=%)\r"

$(OBJ_DIR):
	@$(MKDIR) $@

clean:
	@$(RM) $(OBJ_DIR)
	@printf "$(OBJ_DIR) in $(NAME)\t \033[31;1mdeleted\033[0m\n"

uninstall: clean
	@$(RM) $(OBJ_DIR)
	@$(RM) $(NAME)
	@@printf "$(NAME)\t \033[31;1muninstalled\033[0m\n"
	
reinstall: uninstall install clean
