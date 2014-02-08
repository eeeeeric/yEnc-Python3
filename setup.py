import os
from distutils.core import setup, Extension

setup(
    name        = '_yenc', 
    version     = '0.1.3', 
    author      = 'Eric Zheng',
    url         = 'https://github.com/eeeeeric/yEnc-Python3',
    license     = 'GPL v3',
    platforms   = ['Unix', 'Windows'],
    description = 'yEnc encoder and decoder', 
    py_modules  = ['yenc'],
    ext_modules = [Extension('_yenc', sources=[os.path.join('src', '_yenc.c')])])

