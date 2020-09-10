import os
import random

from PIL import Image
from PIL import ImageFont
from PIL import ImageDraw
from string import ascii_lowercase


FLAG = "to0_spo0py_for_m0i"
FIBONACCI = [0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597]
FRAMES = 2030
WIDTH = 1920
HEIGHT = 1080


RANDOM = list(ascii_lowercase)
for x in range(10):
    RANDOM.append(str(x))
RANDOM.append('_')


os.system("mkdir frames")
os.system("ffmpeg -i video.mp4 -qscale 0 frames/%04d.jpg")
os.system("mkdir new_frames")


path = os.path.dirname(os.path.abspath(__file__))
big_font = ImageFont.truetype(font="FreeMono.ttf", size=64)
small_font = ImageFont.truetype(font="FreeMono.ttf", size=16)
color = (200, 200, 200)


for x in range(0, FRAMES):
    image = Image.open(f"{path}/frames/{(x+1):04d}.jpg")
    image = image.convert('RGB')
    draw = ImageDraw.Draw(image)

    if x == 1:
        draw.text(
                (random.randint(WIDTH / 2, WIDTH / 5 * 4), random.randint(HEIGHT / 5, HEIGHT / 2)),
                text=FLAG[:2],
                fill=color,
                font=small_font
                )
        FLAG = FLAG[2:]
    elif x in FIBONACCI:
        draw.text(
                (random.randint(WIDTH / 2, WIDTH / 5 * 4), random.randint(HEIGHT / 5, HEIGHT / 5 * 4)),
                text=FLAG[:1],
                fill=color,
                font=small_font
                )
        FLAG = FLAG[1:]
    else:
        draw.text(
                (random.randint(WIDTH / 2, WIDTH / 5 * 4), random.randint(HEIGHT / 5, HEIGHT / 5 * 4)),
                text=random.choice(RANDOM),
                fill=color,
                font=small_font
                )

    image.save(f"{path}/new_frames/{(x+1):04d}.jpg")

os.system("ffmpeg -framerate 25 -i new_frames/%04d.jpg -c:v libx264 -profile:v high -crf 20 -pix_fmt yuv420p newvideo.mp4")
os.system("rm -rf frames/ new_frames/")