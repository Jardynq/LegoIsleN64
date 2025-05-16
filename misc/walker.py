import os
import re
from collections import defaultdict

INCLUDE_REGEX = re.compile(r'^\s*#include\s*[<"]([^">]+)[">]')

class IncludeNode:
    def __init__(self, path):
        self.path = path
        self.children = []
        self.size = 0
        self.depth = 0

    def add_child(self, node):
        if all(child.path != node.path for child in self.children):
            self.children.append(node)

    def compute_size(self, visited=None):
        if visited is None:
            visited = set()
        if self.path in visited:
            return 0
        visited.add(self.path)

        child_sizes = []
        child_depths = []

        for child in self.children:
            child_sizes.append(child.compute_size(visited))
            child_depths.append(child.depth)

        self.size = 1 + sum(child_sizes)
        self.depth = 1 + (max(child_depths) if len(child_depths) > 0 else 0)
        return self.size

def build_filename_path_map(root_dir):
    filename_map = defaultdict(list)
    for dirpath, _, filenames in os.walk(root_dir):
        for filename in filenames:
            full_path = os.path.abspath(os.path.join(dirpath, filename))
            filename_map[filename].append(full_path)
    return filename_map

def assign_preferred_parents(all_nodes):
    preferred = {}

    for node in all_nodes.values():
        for child in node.children:
            current = preferred.get(child.path)
            if not current or node.size > current.size:
                preferred[child.path] = node

    return preferred

def get_subtree_depth(node, depth_cache, visited=None):
    if visited is None:
        visited = set()
    if node.path in visited:
        return 0
    if node.path in depth_cache:
        return depth_cache[node.path]

    visited.add(node.path)

    if not node.children:
        depth = 1
    else:
        depth = 1 + max(
            get_subtree_depth(child, depth_cache, visited.copy())
            for child in node.children
        )

    depth_cache[node.path] = depth
    return depth

def parse_includes(file_path, filename_map, all_nodes, visited):
    base_name, ext = os.path.splitext(file_path)
    if ext not in (".h", ".cpp"):
        print(f"Unsupported file type: {file_path}")
        return None

    header_path = os.path.abspath(base_name + ".h")
    source_path = os.path.abspath(base_name + ".cpp")

    node_key = header_path
    if node_key in visited:
        return all_nodes.get(node_key)

    visited.add(node_key)

    if node_key in all_nodes:
        node = all_nodes[node_key]
    else:
        node = IncludeNode(node_key)
        all_nodes[node_key] = node

    lines = []

    try:
        with open(header_path, 'r', encoding='utf-8') as f:
            lines.extend(f.readlines())
    except Exception:
        pass

    try:
        with open(source_path, 'r', encoding='utf-8') as f:
            lines.extend(f.readlines())
    except Exception:
        pass

    includes = []
    for line in lines:
        match = INCLUDE_REGEX.match(line)
        if match:
            includes.append(os.path.basename(match.group(1)))

    for include_name in includes:
        candidates = filename_map.get(include_name, [])
        if candidates:
            child_path = candidates[0]
            child_node = parse_includes(child_path, filename_map, all_nodes, visited)
            if child_node:
                node.add_child(child_node)
        else:
            child_node = IncludeNode("!! " + include_name + " !!")
            node.add_child(child_node)

    return node

def write_graphviz(all_nodes, output_path):
    def trim_path(path):
        norm = os.path.normpath(path)
        parts = norm.split(os.sep)
        if "src" in parts:
            idx = parts.index("src")
            return "/".join(parts[idx+1:])
        return os.path.basename(path)  # fallback: just show file name

    with open(output_path, "w") as f:
        f.write("digraph IncludeGraph {\n")
        f.write("    node [shape=box, style=filled, fillcolor=lightgrey];\n")

        added_edges = set()

        for node in all_nodes.values():
            label = trim_path(node.path)
            f.write(f'    "{label}" [label="{label}"];\n')

            for child in node.children:
                child_label = trim_path(child.path)
                edge = (label, child_label)
                if edge not in added_edges:
                    f.write(f'    "{label}" -> "{child_label}";\n')
                    added_edges.add(edge)

        f.write("}\n")


def print_tree(node, indent=0, visited=None, preferred=None, depth_cache=None):
    if visited is None:
        visited = set()
    if depth_cache is None:
        depth_cache = {}

    if node.path in visited:
        return
    visited.add(node.path)

    print(' ' * indent + os.path.basename(node.path))

    sorted_children = sorted(
        [c for c in node.children if preferred.get(c.path) == node],
        key=lambda c: get_subtree_depth(c, depth_cache)
    )

    for child in sorted_children:
        print_tree(child, indent + 2, visited, preferred, depth_cache)

if __name__ == "__main__":
    import sys

    if len(sys.argv) != 3:
        print("Usage: walker.py <root_dir> <root_file>")
        sys.exit(1)

    root_dir = os.path.abspath(sys.argv[1])
    root_file = os.path.abspath(sys.argv[2])

    if not os.path.isfile(root_file):
        print(f"File not found: {root_file}")
        sys.exit(1)

    filename_map = build_filename_path_map(root_dir)
    all_nodes = {}
    visited = set()

    root = parse_includes(root_file, filename_map, all_nodes, visited)
    if root:
        for node in all_nodes.values():
            node.compute_size(set())
        preferred_parents = assign_preferred_parents(all_nodes)
        print_tree(root, preferred=preferred_parents)
        write_graphviz(all_nodes, "graph.dot")
