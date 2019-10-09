#
# Python bindings for jsonic library.
#
# https://github.com/rohanrhu/python-jsonic
# https://oguzhaneroglu.com/projects/python-jsonic/
#
# Licensed under MIT
# Copyright (C) 2019, Oğuzhan Eroğlu (https://oguzhaneroglu.com/) <rohanrhu2@gmail.com>
#

from distutils.core import setup, Extension

jsonic = Extension(
    "pyjsonic",
    sources = [
        "python-jsonic.c",
        "lib/jsonic/jsonic.c"
    ]
)

setup(
    name = "pyjsonic",
    version = "1.0",
    description = "Python bindings for Jsonic library.",
    ext_modules = [jsonic]
)