import numpy as np
from PIL import Image

dimensions, data = open('data.txt', 'r').read().split('\n\n')
H, W = tuple(map(int, dimensions.split(',')))
data = data[1:-1].split('),(')
data = list(map(lambda x: tuple(map(int, x.split(', '))), data))
image = np.array(data)

image = np.clip(image, 0, 255).astype(np.uint8)
Image.fromarray(image.reshape(H, W, 3), 'RGB')