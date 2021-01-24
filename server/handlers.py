from http.server import BaseHTTPRequestHandler
from os import popen


class MuteboxHandler(BaseHTTPRequestHandler):

    def do_GET(self, *args, **kwargs):
        self.mute()
        self.send_response_only(200)
        self.end_headers()


class X11Handler:

    def __init__(self) -> None:
        wininfo = popen('xwininfo |grep "Window id:"')
        words = wininfo.read().strip().replace('"', '').split(' ')
        self._set_command(words[3:])


    def mute(self) -> None:
        if self._command is None:
            print('toggle mute')
        else:
            popen(self._command)


    def _set_command(self, words: list) -> None:
        if 'Zoom' in words:
            self._command = 'xdotool windowactivate %s && xdotool key --window %s alt+a' \
                % (words[0], words[0])
        else:
            print('Window "%s" not recognized' % ' '.join(words[1:]))
            self._command = None
