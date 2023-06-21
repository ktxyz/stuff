from preloaded import MORSE_CODE

import numpy as np
from sklearn.cluster import KMeans

def decodeMorse(morse_code):
    if morse_code == '':
        return ''
    return ' '.join(
        ''.join(MORSE_CODE[letter] for letter in word.split(' '))
        for word in morse_code.strip().split('   ')
    )

def splitBinary(seq):
    if len(seq) == 0:
        return []
    
    groups = []
    curr = [seq[0]]
    for i in range(1, len(seq)):
        if seq[i] == curr[-1]:
            curr.append(seq[i])
        else:
            groups.append(''.join(curr))
            curr = [seq[i]]
    groups.append(''.join(curr))
    return groups
    
def decodeBitsAdvanced(bits):
    bits = bits.strip('0')
    
    zeros = [x for x in bits.split('1') if '0' in x]
    ones = [x for x in bits.split('0') if '1' in x]

    bits = splitBinary(bits)

    mean_bits = [len(x) for x in bits]
    if len(mean_bits) == 0:
        return ''
    if len(set(mean_bits)) < 2:
        if len(mean_bits) > 1:
            return '..'
        else:
            return '.'
    
    kmean = KMeans(
                init='random',
                n_clusters=2,
                n_init=100,
                max_iter=333,
                random_state=42
    )
    kmean.fit(np.array(mean_bits).reshape(-1, 1))
    dict_map = {
        np.argmin(kmean.cluster_centers_): 0,
        np.argmax(kmean.cluster_centers_): 1,
    }
    bits_list = [dict_map[label] for label in kmean.labels_]
    for i in range(len(bits)):
        if len(bits[i]) >= 5 * min(kmean.cluster_centers_):
            bits_list[i] = 2
    
    dict_labels = {
        ('0', 0): '',
        ('0', 1): ' ',
        ('0', 2): '   ',
        ('1', 0): '.',
        ('1', 1): '-',
    }

    return ''.join(dict_labels[(bit[0], label)] for bit, label in zip(bits, bits_list))