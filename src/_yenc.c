#include <Python.h>
#include "_yenc.h"

static PyObject* encode(PyObject* self, PyObject* args)
{
    /* Declare all vars now to support MSVC */
    const Py_buffer data;
    char *encoded, *in;
    Py_ssize_t i, encoded_length;
    int column;
    PyObject* retval;

    /* Get input data */
    if (!PyArg_ParseTuple(args, "y*", &data))
        return NULL;

    /* Get output buffer */
    encoded = (char*) malloc(BUF_SIZE(data.len));
    if (NULL == encoded)
        return PyErr_NoMemory();

    /* Encoding */
    in = (char*) data.buf;
    encoded_length = 0;
    column = 0;
    for (i = 0; i < data.len; ++i)
    {
        int escape = 0;
        char c = in[i];
        c += MAGIC;
        switch (c)
        {
            case 0:
            case CR:
            case LF:
            case ESC:
                escape = 1;
                break;
            case TAB:
            case SPACE:
                if (column == 0 || column == LINE_LENGTH-1)
                {
                    escape = 1;
                    break;
                }
            case DOT:
                if (column == 0)
                {
                    escape = 1;
                    break;
                }
            default:
                break;
        }

        if (escape)
        {
            c += MAGIC_ESC;
            encoded[encoded_length++] = ESC;
            column++;
        }

        encoded[encoded_length++] = c;
        column++;

        if (column >= LINE_LENGTH)
        {
            encoded[encoded_length++] = CR;
            encoded[encoded_length++] = LF;
            column = 0;
        }
    }

    /* Create bytes object to return */
    retval = PyBytes_FromStringAndSize(encoded, encoded_length);
    free(encoded);
    return retval;
}

static PyObject* decode(PyObject* self, PyObject* args)
{
    /* Declare all vars now to support MSVC */
    const Py_buffer data;
    char *decoded, *in;
    Py_ssize_t i, decoded_length;
    PyObject* retval;

    /* Get input data */
    if (!PyArg_ParseTuple(args, "y*", &data))
        return NULL;

    /* Get output buffer - the decoded data can only be smaller */
    decoded = (char*) malloc(data.len);
    if (NULL == decoded)
        return PyErr_NoMemory();

    /* Decoding */
    in  = (char*) data.buf;
    decoded_length = 0;
    for (i = 0; i < data.len; ++i)
    {
        int escape = 0;
        char c = in[i];
        if (ESC == c)
        {
            escape = 1;
            c = in[++i];
        }
        else if (CR == c || LF == c)
        {
            continue;
        }
        
        if (escape)
            c -= (MAGIC_ESC + MAGIC);
        else
            c -= MAGIC;

        decoded[decoded_length++] = c;
    }

    /* Create bytes object to return */
    retval = PyBytes_FromStringAndSize(decoded, decoded_length);
    free(decoded);
    return retval;
}

static PyMethodDef _YencMethods[] = {
    {
        "encode", encode, METH_VARARGS,
        "Encode data to yEnc."
    },
    {
        "decode", decode, METH_VARARGS,
        "Decode yEnc data."
    },
    {
        NULL, NULL, 0, NULL
    }
};

static struct PyModuleDef _yenc_module = {
    PyModuleDef_HEAD_INIT,
    "_yenc",
    YENC_DOC,
    -1,
    _YencMethods
};

PyMODINIT_FUNC
PyInit__yenc(void)
{
    return PyModule_Create(&_yenc_module);
}
