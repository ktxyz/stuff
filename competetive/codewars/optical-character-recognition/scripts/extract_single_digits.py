from pathlib import Path
from queue import Queue

from PIL import Image
import numpy as np


DATA_PATH = Path('data')
IMAGE_PATH = DATA_PATH / 'digits.png'
EXTRACTED_PATH = DATA_PATH / 'extracted_digits'
OUTPUT_PATH = 'digits.h'

def extract_single_digits(image_path, output_path):
    img = Image.open(image_path)
    img = img.convert('L')

    boxes = find_bounding_boxes(img)

    with open(OUTPUT_PATH, 'w+', encoding='utf-8') as f:
        f.write('#include "image.h"\n\n')
        f.write('Image digits[10] = {\n')
        for i in range(len(boxes)):
            box = boxes[i]
            digit = img.crop(box)

            f.write(f'Image({digit.size[0]}, {digit.size[1]}')
            f.write(', {\n')
            for y in range(digit.size[1]):
                f.write('\t')
                for x in range(digit.size[0]):
                    f.write(f'{1 if digit.getpixel((x, y)) > 100 else 0}, ')
                f.write('\n')
            f.write('}),')

            digit.convert('1').save(EXTRACTED_PATH / Path(f'{i}.png'))
        f.write('};\n')


def find_bounding_boxes(image):
    visited = [[False for _ in range(image.size[0])] for _ in range(image.size[1])]
    bounding_boxes = []

    for y in range(image.size[1]):
        for x in range(image.size[0]):
            if image.getpixel((x, y)) < 200 and not visited[y][x]:
                q = Queue()
                q.put((x, y))
                visited[y][x] = True
                bounding_box = [x, y, x, y]

                while(not q.empty()):
                    x, y = q.get()

                    image.putpixel((x, y), 0)

                    bounding_box[0] = min(bounding_box[0], x)
                    bounding_box[1] = min(bounding_box[1], y)
                    bounding_box[2] = max(bounding_box[2], x)
                    bounding_box[3] = max(bounding_box[3], y)

                    for dx in range(-1, 2):
                        for dy in range(-1, 2):
                            nx = x + dx
                            ny = y + dy

                            if nx < 0 or nx >= image.size[0] or ny < 0 or ny >= image.size[1]:
                                continue

                            if image.getpixel((nx, ny)) < 200 and not visited[ny][nx]:
                                q.put((nx, ny))
                                visited[ny][nx] = True
                bounding_boxes.append(bounding_box)
    return bounding_boxes


extract_single_digits(IMAGE_PATH, OUTPUT_PATH)
