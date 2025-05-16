import os

def is_text_file(filepath):
    try:
        with open(filepath, 'r', encoding='utf-8') as f:
            f.read(1024)
        return True
    except:
        return False

def count_non_empty_lines_in_file(filepath):
    try:
        with open(filepath, 'r', encoding='utf-8') as file:
            return sum(1 for line in file if line.strip())
    except Exception as e:
        print(f"Skipping {filepath} due to error: {e}")
        return 0

def count_non_empty_lines_in_dir(root_dir):
    total_lines = 0
    for dirpath, _, filenames in os.walk(root_dir):
        for filename in filenames:
            filepath = os.path.join(dirpath, filename)
            if is_text_file(filepath):
                lines = count_non_empty_lines_in_file(filepath)
                total_lines += lines
    return total_lines

if __name__ == "__main__":
    import sys
    if len(sys.argv) != 2:
        print("Usage: python count_lines.py <root_directory>")
    else:
        root_directory = sys.argv[1]
        total = count_non_empty_lines_in_dir(root_directory)
        print(f"Total non-empty lines: {total}")
