import zlib
import _yenc

def encode(data):
    """Encode the input data to yEnc

    Arguments:
    data -- the data to encode

    Returns:
    (size, crc32, encoded)
    size    -- the size of the input data
    crc32   -- the crc32 of the input data
    encoded -- the encoded data itself, without any headers/trailer
    """
    return len(data), hex(zlib.crc32(data) & 0xffffffff)[-8:], _yenc.encode(data)

def decode(data):
    """Decode the input data from yEnc back to its original format
    
    Arguments:
    data -- the yEncoded data, this should not contain any headers 
          (=ybegin, =ypart) or the trailer (=yend)
    
    Returns:
    (size, crc32, decoded)
    size    -- the size of the decoded data
    crc32   -- the crc32 of the decoded data
    decoded -- the decoded data itself
    """
    decoded = _yenc.decode(data)
    return len(decoded), hex(zlib.crc32(decoded) & 0xffffffff)[-8:], decoded
