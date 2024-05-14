import os
import csv
# 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$%^&*()_-+={}[]\:;"'<,>.?/
# 🧊🍅👴！翻译的神


def generate_cpp_files(csv_file, output_folder):
    # 创建文件夹
    os.makedirs(output_folder, exist_ok=True)

    # 生成 LocalTextPoolMap_t 结构体
    local_text_pool_map_code = "#pragma once\n\n"
    local_text_pool_map_code += "struct LocalTextPoolMap_t\n{\n"

    # 读取CSV文件并生成结构体成员变量
    with open(csv_file, newline='', encoding='utf-8-sig') as csvfile:
        reader = csv.DictReader(csvfile)
        # next(reader)  # 跳过标题行
        for row in reader:
            # print(row)
            key = row['key']
            # print(key)
            local_text_pool_map_code += f"    char* {key} = nullptr;\n"
    local_text_pool_map_code += "};\n"

    # 写入 LocalTextPoolMap_t 到单独的文件
    with open(os.path.join(output_folder, "text_pool_map.h"), "w", encoding='utf-8') as f:
        f.write(local_text_pool_map_code)

    # 生成各语言的结构体
    with open(csv_file, newline='', encoding='utf-8-sig') as csvfile:
        reader = csv.DictReader(csvfile)
        headers = reader.fieldnames  # 获取CSV文件的标题

        for lang in headers[1:]:  # 从第二列开始，每一列对应一种语言
            struct_name = f"TextPool_{lang}_t"  # 结构体名称
            cpp_code = f"#pragma once\n"
            cpp_code += f"#include \"text_pool_map.h\"\n\n"
            cpp_code += f"struct {struct_name}\n{{\n"

            # 生成结构体成员变量
            with open(csv_file, newline='', encoding='utf-8-sig') as csvfile:
                reader = csv.DictReader(csvfile)
                # next(reader)  # 跳过标题行
                for row in reader:
                    key = row['key']
                    text = row[lang]
                    byte_count = len(text.encode('utf-8'))  # 字符串的字节长度
                    array_size = byte_count + 1  # 字符串的字节长度加上null终止符的大小
                    cpp_code += f"    char {key}[{array_size}] = \"{text}\";\n"

            # 添加 getMap 函数
            cpp_code += f"\n"
            cpp_code += f"    void getMap(LocalTextPoolMap_t& map)\n"
            cpp_code += f"    {{\n"
            with open(csv_file, newline='', encoding='utf-8-sig') as csvfile:
                reader = csv.DictReader(csvfile)
                # next(reader)  # 跳过标题行
                for row in reader:
                    key = row['key']
                    cpp_code += f"        map.{key} = {key};\n"
            cpp_code += f"    }}\n"

            cpp_code += "};\n"

            # 写入到单独的文件
            output_path = os.path.join(output_folder, f"text_pool_{lang}.h")
            with open(output_path, "w", encoding='utf-8') as f:
                f.write(cpp_code)


# 示例用法
# generate_cpp_files("localization.csv", "text_pool")
current_dir = os.path.dirname(os.path.abspath(__file__))
csv_file_path = os.path.join(current_dir, "localization.csv")
text_pool_folder_path = os.path.join(current_dir, "text_pool")
generate_cpp_files(csv_file_path, text_pool_folder_path)
