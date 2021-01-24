import os

from handlers import *

HOST = os.getenv('MUTEBOX_SERVER', '')
PORT = int(os.getenv('MUTEBOX_PORT', 1701))
WINDOW_HANDLER = X11Handler
