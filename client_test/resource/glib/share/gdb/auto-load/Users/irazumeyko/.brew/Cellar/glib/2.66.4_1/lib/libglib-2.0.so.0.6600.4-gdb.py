import sys
import gdb

# Update module path.
dir_ = '/Users/irazumeyko/.brew/Cellar/glib/2.66.4_1/share/glib-2.0/gdb'
if not dir_ in sys.path:
    sys.path.insert(0, dir_)

from glib_gdb import register
register (gdb.current_objfile ())
