from preloaded import MORSE_CODE

def decode_morse(morse_code):
    return ' '.join(
        ''.join(MORSE_CODE[letter] for letter in word.split(' '))
        for word in morse_code.strip().split('   ')
    )

def decode_bits(bits):
    bits = bits.strip('0')
    unit = len(bits)

    try:
        if '1' in bits:
            unit = min(unit, min(len(s) for s in bits.split('1') if '0' in s))
    except ValueError:
        pass
    try:
        if '0' in bits:
            unit = min(unit, min(len(s) for s in bits.split('0') if '1' in s))
    except ValueError:
        pass

    bits = bits.replace('0' * 7 * unit, '   ')
    bits = bits.replace('0' * 3 * unit, ' ')
    bits = bits.replace('1' * 3 * unit, '-')
    bits = bits.replace('1' * 1 * unit, '.')
    bits = bits.replace('0' * 1 * unit, '')
    return bits