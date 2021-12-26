from sys import stdin 

key = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;\'ZXCVBNM,./"

while True:

    src_str = stdin.readline().rstrip()

    if src_str == '': 
        break 

    dst_src = ""

    for c in src_str:
        if c == ' ':
            dst_src += ' '
        elif c in key:
            idx = key.index(c)
            dst_src += key[idx-1]
        else:
            raise ValueError('Cannot Find Char in KeyString')

    print(dst_src)