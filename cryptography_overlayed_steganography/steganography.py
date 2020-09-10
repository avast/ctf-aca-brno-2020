import os
from PIL import Image
from PIL import ImageFont
from PIL import ImageDraw


def combine_colours(original, flag):
    o = original & 0b11110000
    f = flag & 0b11110000
    f = f >> 4
    return o | f


path = os.path.dirname(os.path.abspath(__file__))

image = Image.open(path + '/image.png')
image_rgb = image.convert('RGB')

flag = Image.open(path + '/hidden.png')
flag = flag.convert('RGB')
flag = flag.resize(image.size, Image.BILINEAR)
font = ImageFont.truetype(font="FreeMono.ttf", size=20)
draw = ImageDraw.Draw(flag)
draw.text(
        (image.size[0] * 0.35, image.size[1] * 0.45),
        text=u"avastCTF{stegan0graphy_is_e4sy_peasy}",
        fill=(40, 40, 40),
        font=font
        )
flag_rgb = flag.convert('RGB')

new_image = []

for y in range(image.size[1]):
    for x in range(image.size[0]):
        orig_r, orig_g, orig_b = image_rgb.getpixel((x, y))
        flag_r, flag_g, flag_b = flag_rgb.getpixel((x, y))

        r = combine_colours(orig_r, flag_r)
        g = combine_colours(orig_g, flag_g)
        b = combine_colours(orig_b, flag_b)

        new_image.append((r, g, b, 255))

image_w_flag = Image.new(image.mode, image.size)
image_w_flag.putdata(new_image)
image_w_flag.save(path + '/image_w_flag.png')
