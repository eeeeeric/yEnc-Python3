yEnc-Python3
============

Basic yEnc encoder and decoder for python3.

This module does not parse nor generate the required header(s) or trailer.
It only provides a pair of encode and decode functions, which also return
the size of the ORIGINAL data (input for encode, output for decode) and
the crc32 of the original data.

This module is written in C (yenc) and python (wrapper, crc32). It is written
for use by eeeeeric/anchorman, but is available as a separate package as
there exists no C yenc module for python3 as of writing.

Installation
------------

    python setup.py build
    python setup.py install

Usage
-----

    import yenc

    size, crc32, encoded = yenc.encode(b'data')
    size, crc32, decoded = yenc.decode(encoded)

Use help(yenc) for more information.

Testing
-------

You can run tests with

    py.test test/test.py

Notes
-----

The returned crc32 value is in hex, without any leading "0x"
