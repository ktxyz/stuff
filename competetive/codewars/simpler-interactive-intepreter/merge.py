import os
import re

def get_included_files(header_content):
    """Return a list of local header files included in the given content."""
    # Regex to match #include "filename.h"
    pattern = re.compile(r'#include "(.*?\.h)"')
    return pattern.findall(header_content)

def get_sorted_files(directory):
    """Return header files sorted based on their dependencies."""
    headers = {}
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith('.h'):
                with open(os.path.join(root, file), 'r') as f:
                    content = f.read()
                    headers[file] = {
                        'content': content,
                        'includes': get_included_files(content)
                    }

    sorted_files = []
    while headers:
        for file, data in dict(headers).items():
            # If a file doesn't have dependencies or all its dependencies
            # are already in the sorted list, it's safe to append it.
            if not data['includes'] or all(inc in sorted_files for inc in data['includes']):
                sorted_files.append(file)
                del headers[file]

    return sorted_files


def generate_merged_file(directory, sorted_files):
    """Generate the merged.h file."""
    merged_content = ["#pragma once\n\n"]  # Start with pragma once
    added_files = set()  # To keep track of files already added

    # Add the content of each file, excluding its #include directives
    for file in sorted_files:
        if file not in added_files:
            with open(os.path.join(directory, file), 'r') as f:
                for line in f:
                    # Exclude local includes
                    if not (line.startswith("#include \"") or line.startswith("#pragma once")):
                        merged_content.append(line)
            added_files.add(file)
            merged_content.append("\n")  # Add a newline for clarity

    # remove old merged.h file
    if os.path.exists('merged.h'):
        os.remove('merged.h', dir_fd=None)
    with open('merged.h', 'w+', encoding='utf-8') as f:
        f.writelines(merged_content)



if __name__ == "__main__":
    directory = input("Enter the directory path: ")
    sorted_files = get_sorted_files(directory)
    generate_merged_file(directory, sorted_files)
    print("merged.h has been generated!")
