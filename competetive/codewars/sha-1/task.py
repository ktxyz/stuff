class SHA1(object):
    def __init__(self):
        self.message = b''

    def update(self, message):
        self.message += message

    def digest(self):
        hash_int = self.sha1(self.message)
        return self.sha1_to_bytes(hash_int).hex().encode()

    def sha1_to_bytes(self, hash_int):
        return hash_int.to_bytes(20, byteorder='big')

    def leftrotate(self, i, n):
        return ((i << n) & 0xffffffff) | (i >> (32 - n))

    def process_chunk(self, chunk, h0, h1, h2, h3, h4):
        w = [int.from_bytes(chunk[i:i+4], byteorder='big') for i in range(0, 64, 4)] + [0] * 64
        
        for i in range(16, 80):
            w[i] = self.leftrotate(w[i-3] ^ w[i-8] ^ w[i-14] ^ w[i-16], 1)
        
        a, b, c, d, e = h0, h1, h2, h3, h4
        
        for i in range(80):
            if i < 20:
                f = (b & c) | ((~b) & d)
                k = 0x5A827999
            elif i < 40:
                f = b ^ c ^ d
                k = 0x6ED9EBA1
            elif i < 60:
                f = (b & c) | (b & d) | (c & d)
                k = 0x8F1BBCDC
            else:
                f = b ^ c ^ d
                k = 0xCA62C1D6

            a, b, c, d, e = ((self.leftrotate(a, 5) + f + e + k + w[i]) & 0xffffffff, 
                            a, self.leftrotate(b, 30), c, d)
        
        h0 = (h0 + a) & 0xffffffff
        h1 = (h1 + b) & 0xffffffff
        h2 = (h2 + c) & 0xffffffff
        h3 = (h3 + d) & 0xffffffff
        h4 = (h4 + e) & 0xffffffff
        
        return h0, h1, h2, h3, h4

    def sha1(self, message):
        message = bytearray(message)
        orig_len_in_bits = (8 * len(message)) & 0xffffffffffffffff
        message.append(0x80)

        while len(message) % 64 != 56:
            message.append(0)
        
        message += orig_len_in_bits.to_bytes(8, byteorder='big')
        
        h0 = 0x67452301
        h1 = 0xEFCDAB89
        h2 = 0x98BADCFE
        h3 = 0x10325476
        h4 = 0xC3D2E1F0

        for i in range(0, len(message), 64):
            h0, h1, h2, h3, h4 = self.process_chunk(message[i:i+64], h0, h1, h2, h3, h4)

        return (h0 << 128) | (h1 << 96) | (h2 << 64) | (h3 << 32) | h4