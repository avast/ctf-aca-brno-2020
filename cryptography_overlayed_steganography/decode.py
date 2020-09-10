import os
from PIL import Image

path = os.path.dirname(os.path.abspath(__file__))

flagged = Image.open(path + '/image_w_flag.png')
pixels = flagged.getdata()

new_pixels = []

for pixel in pixels:
    r, g, b = pixel

    r = r & 0b1111
    r = r << 4

    g = g & 0b1111
    g = g << 4

    b = b & 0b1111
    b = b << 4

    new_pixels.append((r, g, b))

decoded = Image.new(flagged.mode, flagged.size)
decoded.putdata(new_pixels)
decoded.save(path + '/decoded_flag.png')
