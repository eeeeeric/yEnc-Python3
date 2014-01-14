#ifndef _YENC_H_
#define _YENC_H_

#define YENC_DOC "Encode and decode yEnc data"

#define LINE_LENGTH 128
/* Worst case scenario buffer size for input data of size n */
#define BUF_SIZE(n) (((2*n + LINE_LENGTH - 1)/LINE_LENGTH) * (LINE_LENGTH+2))
#define CR          0x0d
#define LF          0x0a
#define ESC         0x3d
#define TAB         0x09
#define SPACE       0x20
#define DOT         0x2e
#define MAGIC       42
#define MAGIC_ESC   64

#endif
