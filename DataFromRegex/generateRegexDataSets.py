import re
import exrex
import os

directory = "RegexDataSets"

if not os.path.exists(directory) :
    os.makedirs(directory)

PosFileAstart = open(directory+'/'+"PosData.txt","w")

for i in range(99) :
    word = exrex.getone('[a-f]{6,7}[a-c]{1,3}[a-f]{4,7}[a-c]{1,3}')
    for i in range(len(word)) :
        PosFileAstart.write('(')
        PosFileAstart.write(word[i])
        PosFileAstart.write(')')
    PosFileAstart.write('\n')
word = exrex.getone('[a-f]{6,7}[a-c]{1,3}[a-f]{4,7}[a-c]{1,3}')
for i in range(len(word)) :
    PosFileAstart.write('(')
    PosFileAstart.write(word[i])
    PosFileAstart.write(')')

PosFileAstart.close()

PosFileBstart = open(directory+'/'+"NegData.txt","w")

for i in range(99) :
    word = exrex.getone('[a-f]{6,7}[d-f]{1,3}[a-f]{4,7}[d-f]{1,3}')
    for i in range(len(word)) :
        PosFileBstart.write('(')
        PosFileBstart.write(word[i])
        PosFileBstart.write(')')
    PosFileBstart.write('\n')
word = exrex.getone('[a-f]{6,7}[d-f]{1,3}[a-f]{4,7}[d-f]{1,3}')
for i in range(len(word)) :
    PosFileBstart.write('(')
    PosFileBstart.write(word[i])
    PosFileBstart.write(')')

PosFileBstart.close()


