import sys
import os
from PIL import Image


def halftone(image_path, output_path=None, width=128):
    # Open the image
    img = Image.open(image_path)

    # Convert image to grayscale
    img = img.convert('L')

    # Resize image to desired width while maintaining aspect ratio
    wpercent = (width / float(img.size[0]))
    hsize = int((float(img.size[1]) * float(wpercent)))
    img = img.resize((width, hsize))

    # Convert image to halftone
    # Convert to 1-bit monochrome image (black and white)
    img = img.convert('1')

    if output_path is None:
        output_dir = os.path.dirname(image_path)
        filename, ext = os.path.splitext(os.path.basename(image_path))
        output_path = os.path.join(output_dir, filename + "_halftone" + ext)

    img.save(output_path)
    print(f"Image converted and saved as {output_path}")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        script_name = os.path.basename(sys.argv[0])
        print(
            f"Usage: python {script_name} input_image_path [output_image_path]")
        sys.exit(1)

    input_image = sys.argv[1]
    output_image = sys.argv[2] if len(sys.argv) == 3 else None

    halftone(input_image, output_image)
