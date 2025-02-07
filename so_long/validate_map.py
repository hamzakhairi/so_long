def validate_map(file):
    with open(file, 'r') as f:
        lines = f.readlines()
        width = len(lines[0].strip())
        for i, line in enumerate(lines):
            line = line.strip()
            if len(line) != width:
                print(f"Error: Line {i + 1} has length {len(line)}. Expected {width}.")
                return False
    print("Map is rectangular.")
    return True

if __name__ == "__main__":
    import sys
    if len(sys.argv) != 2:
        print("Usage: python validate_map.py <map_file>")
        sys.exit(1)
    validate_map(sys.argv[1])