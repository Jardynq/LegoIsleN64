import os
import re

def replace_header_guard(file_path):
    with open(file_path, 'r', encoding='utf-8') as f:
        lines = f.readlines()

    if not lines:
        return False

    # Match old header guards
    guard_start_pattern = re.compile(r'^\s*#ifndef\s+(\w+_[Hh])\s*$')
    guard_define_pattern = re.compile(r'^\s*#define\s+(\w+_[Hh])\s*$')
    guard_end_pattern = re.compile(r'^\s*#endif\s*((//|/\*).*_[Hh]\s*(\*/)?)\s*$')
    skip_pattern = re.compile(r'^\s*(//.*|/\*.*\*/)?\s*$')

    new_lines = []
    i = 0

    while i < len(lines) and skip_pattern.match(lines[i]):
        print(lines[i], end='')
        new_lines.append(lines[i])
        i += 1

    if i + 1 >= len(lines):
        print(file_path)
        print()
        return False

    m1 = guard_start_pattern.match(lines[i])
    m2 = guard_define_pattern.match(lines[i + 1])
    if not (m1 and m2 and m1.group(1) == m2.group(1)):
        print(file_path)
        print()
        return False

    print(lines[i], end='')
    print(lines[i+1], end='')
    i += 2
    new_lines.append("#pragma once\n")

    while i < len(lines):
        line = lines[i]
        if i == len(lines) - 1:
            if guard_end_pattern.match(line):
                print(line, end='')
                break
        new_lines.append(line)
        i += 1
    print()

    with open(file_path, 'w', encoding='utf-8') as f:
        f.writelines(new_lines)

    print(f"Converted: {file_path}")
    return True


def convert_headers_in_directory(directory):
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(('.h', '.hpp')):
                path = os.path.join(root, file)
                replace_header_guard(path)

if __name__ == '__main__':
    convert_headers_in_directory("./src")
