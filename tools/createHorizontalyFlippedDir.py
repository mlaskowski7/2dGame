# Script used to flip horizontally images in a dir and save them to another dir, used for backwards movement

import os
import argparse

from PIL import Image

def flipImagesToDir(imagesDir, outputDir):
    os.makedirs(outputDir)
    for file in os.listdir(imagesDir):
        if file.endswith('.png'):
            path = os.path.join(imagesDir,file)
            flipped = Image.open(path).transpose(Image.FLIP_LEFT_RIGHT)
            flipped.save(os.path.join(outputDir, file))

def main():
    argParser = argparse.ArgumentParser()
    argParser.add_argument('imagesDir', type=str)
    argParser.add_argument('outputDir')
    arguments = argParser.parse_args();
    flipImagesToDir(arguments.imagesDir, arguments.outputDir)

if __name__ == "__main__":
    main()


