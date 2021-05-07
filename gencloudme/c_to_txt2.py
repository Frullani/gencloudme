#!/usr/bin/env python3
"""Copy files to the .txt extension, v.2"""

from os import path, walk, mkdir
from sys import platform
from shutil import copyfile

# Add file extension if you want such files to be copied.
# Warning! It will literally copied, byte-by-byte.
FILES_TO_COPY = ['c', 'cp', 'hpp']

# Change this to True if you want the file to be copied to the same directory.
# Else all files will be copied in /txt_copy.
COPY_TO_THE_SAME_DIRECTORY = False


def turn_to(current_dir=True):
    """Copy files to the .txt extension.

    Work with current directory and subdirectories.
    If current_dir = True (default) - copy file to the same directory.
    If not - copy to the '/txt_copy' at the root (from which the script was called) directory.
        It will be created if necessary.
    """
    dir_sep = '\\' if platform.startswith('win') else '/'
    path_to_copy = path.abspath(__file__).rpartition(dir_sep)[0] + dir_sep + 'txt_copy'

    if current_dir:
        print('The file will be copied to the same directory.\n')
    else:
        print('The file will be copied to the {} at the'.format(path_to_copy),
              'root (from which the script was called) directory.')
        print('It will be created if necessary.\n')

    if (not current_dir and not path.exists('txt_copy_h')):
        mkdir('txt_copy_h')

    for root, _, files in walk(path.abspath(__file__).rpartition(dir_sep)[0]):
        for file in files:
            if any([file.endswith('.' + x) for x in FILES_TO_COPY]):
                print('Find file {}. Coping...'.format(file))
                if current_dir:
                    path_to_copy = root

                copyfile(
                    path.join(root, file),
                    path.join(path_to_copy,
                              file.rpartition('.')[0] + '_h.txt'))
    return 'Done!'


print(turn_to(COPY_TO_THE_SAME_DIRECTORY))
