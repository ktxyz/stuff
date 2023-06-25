import random
import argparse
from enum import Enum
from pathlib import Path

from PIL import Image, ImageFont, ImageDraw, ImageFilter


class ContrastType(Enum):
    VERY_LOW = 'very_low'
    LOW = 'low'
    HIGH = 'high'
    VERY_HIGH = 'very_high'

DATA_PATH = Path('data')
FONT_PATH = DATA_PATH / 'ocra_font.ttf'
OUTPUT_IMG_PATH = DATA_PATH / 'test_image.png'
OUTPUT_TEST_PATH = DATA_PATH / 'test_input.txt'

class Contrast:
    def __init__(self, type):
        self.type = type

        if self.type == ContrastType.LOW:
            self._init_low()
        elif self.type == ContrastType.HIGH:
            self._init_high()
        else:
            self.bg_color = 120
            self.fg_color = 100

    def _init_low(self):
        self.bg_color = random.randint(170, 220)
        self.fg_color = random.randint(80, self.bg_color - 60)
    
    def _init_high(self):
        self.bg_color = 240
        self.fg_color = 0


def generate_image(text, size, contrast):
    img = Image.new('1' if contrast.type == ContrastType.VERY_HIGH else 'L', size, color=contrast.bg_color)
    draw = ImageDraw.Draw(img)

    if contrast.type == ContrastType.LOW or contrast.type == ContrastType.VERY_LOW:
        num_spots = 10  # Adjust the number of spots as desired
        for _ in range(num_spots):
            x = random.randint(0, size[0])
            y = random.randint(0, size[1])
            spot_size = random.randint(min(size) // 5, min(size) // 2)
            spot_color = random.randint(contrast.bg_color - 30, contrast.bg_color + 30)
            draw.ellipse([(x, y), (x + spot_size, y + spot_size)], fill=spot_color)
        img = img.filter(ImageFilter.GaussianBlur(radius=1))
        draw = ImageDraw.Draw(img)

    size_ratio = 0.8

    font_size = int(min(size[0] * size_ratio * (1 if len(text) == 1 else 2/len(text)), size[1] * size_ratio))
    font_size -= font_size % 2
    font = ImageFont.truetype(str(FONT_PATH), size=font_size)
    text_width = draw.textlength('1', font=font)

    offset = random.randint(-2, 2)
    for i, char in enumerate(text):
        draw.text((i * text_width + offset + 2, offset), char, font=font, fill=contrast.fg_color)
        offset += random.randint(-2, 2)
    
    return img

def generate_test_input(text, image, contrast):
    print(f'Generating test input for {text}...')
    with open(OUTPUT_TEST_PATH, 'w+', encoding='utf-8') as f:
        f.write(f'{text}\n')
        f.write(f'{image.size[0]} {image.size[0]}\n')

        for row in range(image.size[1]):
            for col in range(image.size[0]):
                if contrast.type == ContrastType.VERY_HIGH:
                    f.write(f'{0 if image.getpixel((col, row)) == 0 else 1} ')
                else:
                    f.write(f'{image.getpixel((col, row))} ')
            f.write('\n')
        

def create_test(text, size, contrast_type):
    contrast = Contrast(contrast_type)

    image = generate_image(text, size, contrast)
    image.save(str(OUTPUT_IMG_PATH))

    generate_test_input(text, image, contrast)


def main():
    parser = argparse.ArgumentParser(description='Generate test image.')
    parser.add_argument('text', type=str, help='Text for the image')
    parser.add_argument('width', type=int, help='Width of the image')
    parser.add_argument('height', type=int, help='Height of the image')
    parser.add_argument(
        'contrast',
        type=str,
        choices=[contrast_type.value for contrast_type in ContrastType],
        help='Contrast type (VERY_LOW or LOW or HIGH or VERY_HIGH)',
    )

    args = parser.parse_args()
    text = args.text
    size = (args.width, args.height)
    contrast_type = ContrastType(args.contrast.lower())
    create_test(text, size, contrast_type)


if __name__ == '__main__':
    main()
