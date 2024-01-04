import numpy as np
from PIL import Image

data = open('data.txt', 'r').read().splitlines()
H, W = tuple(map(int, data[0].split()))
image = list(map(lambda x: tuple(map(float, x.split())) ,data[1:]))
image = np.array(image)

image = np.clip(image, 0, 255).astype(np.uint8)
image = Image.fromarray(image.reshape(H, W, 3), 'RGB')
image.show()