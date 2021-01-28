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
        hotkey_command = 'active=$(xdotool getactivewindow) && ' \
            'xdotool windowactivate %s && ' \
            'xdotool key --window %s %s && ' \
            'xdotool windowactivate $active'

        hotkey_apps = (
            ('Zoom', 'Zoom', 'alt-a'),
            ('Meet', 'Google Meet', 'alt-d'),
            ('Teams', 'Microsoft Teams', 'ctrl+M'),
        )
        for app in hotkey_apps:
            if app[0] in words:
                self._command = hotkey_command % (words[0], words[0], app[2])
                print('%s detected, using %s' % app[1:])
                return

        print('Window "%s" not recognized' % ' '.join(words[1:]))
        self._command = None
