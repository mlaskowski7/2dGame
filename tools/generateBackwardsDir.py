# Script used to flip horizontally images in a dir and save them to another dir, used for backwards movement

import os
import argparse

from PIL import Image

def flipImagesToDir(imagesDir, outputDir):
    os.makedirs(outputDir, exist_ok=True)
    for subdir in os.listdir(imagesDir):
        subdirPath = os.path.join(imagesDir,subdir)
        if os.path.isdir(subdirPath):
            os.makedirs(os.path.join(outputDir,subdir), exist_ok=True)
            for file in os.listdir(subdirPath):
                if file.endswith('.png'):
                    path = os.path.join(subdirPath,file)
                    flipped = Image.open(path).transpose(Image.FLIP_LEFT_RIGHT)
                    flipped.save(os.path.join(outputDir, subdir, file))

def main():
    argParser = argparse.ArgumentParser()
    argParser.add_argument('imagesDir', type=str)
    argParser.add_argument('outputDir')
    arguments = argParser.parse_args();
    flipImagesToDir(arguments.imagesDir, arguments.outputDir)

if __name__ == "__main__":
    main()


