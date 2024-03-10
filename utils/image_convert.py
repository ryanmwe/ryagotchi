from PIL import Image
import numpy as np

def image_to_c_header(image_path, output_path, array_name):
    # Open the image
    img = Image.open(image_path).convert('RGB')
    
    # Convert the image to RGB565
    width, height = img.size
    pixels = list(img.getdata())
    rgb565_pixels = [(r & 0xF8) << 8 | (g & 0xFC) << 3 | (b & 0xF8) >> 3 for r, g, b in pixels]
    
    # Create the C header file
    with open(output_path, 'w') as f:
        f.write(f'#ifndef {array_name.upper()}_H\n')
        f.write(f'#define {array_name.upper()}_H\n\n')
        f.write(f'const uint16_t {array_name}[{len(rgb565_pixels)}] = '+'{\n')
        for i, pixel in enumerate(rgb565_pixels):
            if i % 12 == 0:
                f.write("\n    ")
            f.write(f'0x{pixel:04X}, ')
        f.write('\n};\n\n#endif // ' + f'{array_name.upper()}_H\n')
    
    print(f'Converted {image_path} to {output_path} as {array_name}')

# Convert the BMP image to a C header file
image_path = './utils/files/Sprite-0002.bmp'
output_path = './include/images/Sprite-0002.h'
array_name = 'Sprite0002'

image_to_c_header(image_path, output_path, array_name)
