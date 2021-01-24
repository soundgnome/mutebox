#!/usr/bin/env python3

import os

from http.server import HTTPServer

from handlers import MuteboxHandler
import config


def serve():
    window_handler = config.WINDOW_HANDLER()
    MuteboxHandler.mute = window_handler.mute
    HTTPServer(
        (config.HOST, config.PORT),
        MuteboxHandler
    ).serve_forever()


if __name__ == '__main__':
    serve()
