# My-zip

This program compresses an input using runtime compression. Compressed data will be written in binary.

## Usage

To compile the program run:

    gcc my-zip.c -o my-zip

Then run the program with one of the following commands:

Compress contents of a file/files and print result to standard output

    ./my-zip file1 [file2 file3 ...]

Compress contents of a file/files and write result to a file

    ./my-zip file1 [file2 file3 ...] > output

