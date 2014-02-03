#!/bin/bash
find src/ -name "*.cxx.in" -o -name "*.cxx" -o -name "*.hxx" -o -name "*.c" -o -name "*.h" -o -name "*.hxx.in" > fileList.txt
uncrustify -c uncrustify.config -F fileList.txt --replace
find src/ -name "*.unc-backup~" -o -name "*.unc-backup.md5~" > fileList.txt
xargs -I{} sh -c 'rm {}' < fileList.txt
rm fileList.txt
