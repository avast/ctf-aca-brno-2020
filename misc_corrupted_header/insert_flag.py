import io
import os
from PIL import Image
from PIL import ImageFont
from PIL import ImageDraw


path = os.path.dirname(os.path.abspath(__file__))

image = Image.open(path + '/gaben.png')
font = ImageFont.truetype(font="FreeMono.ttf", size=20)
draw = ImageDraw.Draw(image)
draw.text(
        (image.size[0] * 0.2, image.size[1] * 0.6),
        text=u"avastCTF{gl0rious_g4ben_our_l0rd_4nd_sav1our}",
        fill=(0, 0, 0),
        font=font
        )
image.save(path + "/flag_inside.png")
    