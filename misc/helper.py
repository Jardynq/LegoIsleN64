import os
import re

extensions={'.c', '.cpp', '.h', '.hpp'}
known_prefixes = [
    "lego",
    # "mx"
]
known_ignore = [
    "legofs", 
    "isleapp", 
    "global", 
    "define", 
    "main", 
    "legomain",
    "asset_test",
]
known_words = [
    "unkown100db7f4", 
    "registration",
    "notification",
    "controller", 
    "locomotion",
    "subscriber",
    "transition",
    "background",
    "helicopter", 
    "skateboard", 
    "infocenter", 
    "collection", 
    "quaternion",
    "motorcycle", 
    "orientable",
    "stopwatch",
    "streaming",
    "container",
    "presenter", 
    "composite",
    "animation", 
    "hashtable", 
    "ambulance",
    "character",
    "parameter",
    "utilities",
    "locations", 
    "gamestate", 
    "variables", 
    "buildings", 
    "dunebuggy", 
    "renderer",
    "towtrack", 
    "streamer",
    "variable",
    "hospital",
    "building",
    "boundary", 
    "elevator", 
    "geometry", 
    "realtime", 
    "provider",
    "parallel",
    "genactor",
    "pizzeria", 
    "modeldb",
    "jukebox", 
    "station", 
    "display", 
    "surface", 
    "history", 
    "factory",
    "phoneme",
    "manager", 
    "texture",
    "looping",
    "extract", 
    "storage", 
    "unknown",
    "point32",
    "builder",
    "utility",
    "version",
    "isleapp",
    "racecar",
    "special", 
    "station", 
    "scripts",
    "plants", 
    "actors", 
    "camera", 
    "string",
    "cursor", 
    "tickle",
    "camera",
    "device",
    "jetski",
    "memory",
    "source",
    "bottom", 
    "region", 
    "size32", 
    "bitset",
    "police",
    "matrix", 
    "letter",
    "entity",
    "rect16",
    "object",
    "rect32",
    "sphere",
    "vertex",
    "action", 
    "center", 
    "jetski", 
    "struct", 
    "serial", 
    "vector",
    "stream",
    "select",
    "define",
    "create", 
    "buffer",
    "racers",
    "global",
    "legofs",
    "radio", 
    "pizza", 
    "named",
    "state", 
    "utils", 
    "event", 
    "flags", 
    "table",
    "timer",
    "queue",
    "chunk",
    "brick", 
    "build",
    "param",
    "point",
    "score",
    "audio",
    "input",
    "image", 
    "actor", 
    "world",
    "group",
    "view1",
    "media",
    "multi",
    "plant",
    "cache",
    "sound",
    "meter",
    "model",
    "doors", 
    "color",
    "still", 
    "extra", 
    "music", 
    "plane", 
    "types", 
    "point", 
    "light",
    "start", 
    "debug",
    "math", 
    "main",
    "data", 
    "impl",
    "isle", 
    "bump", 
    "bouy", 
    "edge",
    "mesh",
    "nocd",
    "ammo",
    "race",
    "sfwd",
    "disk",
    "omni",
    "atom", 
    "misc", 
    "core",
    "file",
    "midi",
    "rect",
    "size",
    "pool",
    "list",
    "book", 
    "tree", 
    "door", 
    "view", 
    "wave",
    "load",
    "anim",
    "hide",
    "path",
    "bike", 
    "info",
    "tran",
    "part",
    "skel",
    "act1",
    "act2",
    "act3",
    "nav", 
    "roi",
    "box",
    "lod",
    "flc",
    "gas", 
    "map", 
    "ram",
    "smk",
    "tgl",
    "end",
    "weg",
    "car",
    "mx", 
    "ds", 
    "we", 
    "2d",
    "3d",
    "4d",
    "mm",
    "io",
    "of", 
]


def rename_pattern(old_name):
    name, ext = os.path.splitext(os.path.basename(old_name))
    name = name.lower()

    # Ignore known files
    if name in known_ignore:
        return name + ext.lower()

    # Ignore actions files
    if name.lower().endswith("actions"):
        return name + ext.lower()

    # Remove known prefix
    for prefix in known_prefixes:
        if name.startswith(prefix):
            name = name[len(prefix):]
            break

    i = 0
    result = []
    buffer = ''
    while i < len(name):
        if name[i] == '_':
            i += 1
            continue

        match = None
        for word in known_words:
            if name[i:].startswith(word):
                match = word
                break

        if match:
            if buffer:
                result.append(buffer)
                buffer = ''
            result.append(match)
            i += len(match)
        else:
            buffer += name[i]
            i += 1

    if buffer:
        print (f"Warning: Unrecognized pattern in '{old_name}': '{buffer}'")
        result.append(buffer)

    # Join with underscores and lowercase
    return '_'.join(w.lower() for w in result) + ext.lower()


def rename_files(root_dir):
    mapping = {}
    for dirpath, _, filenames in os.walk(root_dir):
        for file in filenames:
            if not os.path.splitext(file)[1] in extensions:
                continue

            new_name = rename_pattern(file)
            old_path = os.path.join(dirpath, file)
            new_path = os.path.join(dirpath, new_name)
            if file != new_name:
                mapping[file] = new_name
                os.rename(old_path, new_path)
    return mapping

def fix_includes(root_dir, mapping):
    include_pattern = re.compile(r'#include\s+["<](.*?)[">]')

    for dirpath, _, filenames in os.walk(root_dir):
        for file in filenames:
            if not os.path.splitext(file)[1] in extensions:
                continue

            path = os.path.join(dirpath, file)
            with open(path, 'r', encoding='utf-8') as file:
                lines = file.readlines()

            changed = False
            new_lines = []
            for line in lines:
                match = include_pattern.search(line)
                if match:
                    included_file = match.group(1)
                    included_filename = os.path.basename(included_file)
                    if included_filename in mapping:
                        new_include = included_file.replace(included_filename, mapping[included_filename])
                        new_line = line.replace(included_file, new_include)
                        new_lines.append(new_line)
                        changed = True
                    else:
                        new_lines.append(line)
                else:
                    new_lines.append(line)

            if changed:
                with open(path, 'w', encoding='utf-8') as file:
                    file.writelines(new_lines)

def globalize_includes(root_dir):
    include_pattern = re.compile(r'#include\s+["<](.*?)[">]')

    for dirpath, _, filenames in os.walk(root_dir):
        for file in filenames:
            if not os.path.splitext(file)[1] in extensions:
                continue

            path = os.path.join(dirpath, file)
            with open(path, 'r', encoding='utf-8') as file:
                lines = file.readlines()

            changed = False
            new_lines = []
            for line in lines:
                match = include_pattern.search(line)
                if match:
                    included_file = match.group(1)
                    included_filename = os.path.basename(included_file)
                    new_include = included_file.replace(included_file, included_filename)
                    new_line = line.replace(included_file, new_include)
                    new_lines.append(new_line)
                    changed = True
                else:
                    new_lines.append(line)

            if changed:
                with open(path, 'w', encoding='utf-8') as file:
                    file.writelines(new_lines)

def main():
    #mapping = rename_files("./src")
    #fix_includes("./src", mapping)
    globalize_includes("./src")

if __name__ == "__main__":
    main()
