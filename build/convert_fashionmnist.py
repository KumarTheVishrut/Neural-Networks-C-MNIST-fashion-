import numpy as np
from PIL import Image
import os
import csv

def convert(csv_path, output_dir):
    os.makedirs(output_dir, exist_ok=True)
    with open(csv_path) as f:
        reader = csv.reader(f)
        next(reader)  # skip header
        for i, row in enumerate(reader):
            label = row[0]
            pixels = np.array(row[1:], dtype=np.uint8).reshape(28, 28)
            img = Image.fromarray(pixels)
            class_dir = os.path.join(output_dir, label)
            os.makedirs(class_dir, exist_ok=True)
            img.save(os.path.join(class_dir, f"{i}.png"))

convert("fashion-mnist_train.csv", "train_images")
convert("fashion-mnist_test.csv", "test_images")
