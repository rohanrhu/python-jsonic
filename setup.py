# -*- coding: utf-8 -*-
# Python bindings for jsonic library.
#
# https://github.com/rohanrhu/python-jsonic
# https://oguzhaneroglu.com/projects/python-jsonic/
#
# Licensed under MIT
# Copyright (C) 2019, Oğuzhan Eroğlu (https://oguzhaneroglu.com/) <rohanrhu2@gmail.com>
#

from setuptools import setup, Extension
from os import path

this_directory = path.abspath(path.dirname(__file__))
with open(path.join(this_directory, 'README.md'), encoding='utf-8') as f:
    long_description = f.read()

jsonic = Extension(
    "jsonic",
    sources = [
        "python-jsonic.c",
        "lib/jsonic/jsonic.c"
    ]
)

setup(
    name = "pyjsonic",
    version = "1.9",
    description = "Python bindings for Jsonic JSON reader library.",
    long_description = long_description,
    long_description_content_type='text/markdown',
    author = "Oğuzhan Eroğlu",
    author_email = "rohanrhu2@gmail.com",
    url = "https://github.com/rohanrhu/python-jsonic",
    ext_modules = [jsonic],
    data_files = [
        ("headers", [
            "python-jsonic.h",
            "lib/jsonic/jsonic.h"
        ])
    ]
)