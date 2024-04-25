import sys
import os

MAX_LINE_LENGTH = 80


def format_byte(byte):
    hex_str = hex(byte)[2:]
    return f"0x{hex_str.zfill(2)}"


def file_to_c_array(input_file, output_file, array_name):
    with open(input_file, 'rb') as file:
        file_content = file.read()

    with open(output_file, 'w') as output:
        output.write("#include <stdint.h>\n\n")
        output.write(f"const uint8_t {array_name}[] = {{\n    ")

        line_length = 0

        for byte in file_content:
            byte_str = format_byte(byte) + ", "
            output.write(byte_str)
            line_length += len(byte_str)

            # New line
            if line_length >= MAX_LINE_LENGTH:
                output.write("\n    ")
                line_length = 0

        output.write("\n};\n")
        # output.write(
        #     f"const size_t {array_name}_size = sizeof({array_name});\n")


if __name__ == "__main__":
    if len(sys.argv) != 2 or sys.argv[1] == '-h':
        print("Usage: python {} vlw_file".format(
            sys.argv[0]))
        sys.exit(1)

    input_file_path = sys.argv[1]

    # Get array name
    array_name = os.path.basename(input_file_path)
    array_name = array_name.lower().replace('-', '_')
    array_name = array_name[:array_name.rfind('.')]

    # Get output file name
    output_file_path = array_name + ".h"

    print("convert {} to {}".format(input_file_path, output_file_path))
    file_to_c_array(input_file_path, output_file_path, array_name)
