#!/usr/bin/python

"""
Output lines selected randomly from a file

Copyright 2005, 2007 Paul Eggert.
Copyright 2010 Darrell Benjamin Carbajal.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Please see <http://www.gnu.org/licenses/> for a copy of the license.

$Id: randline.py,v 1.4 2010/04/05 20:04:43 eggert Exp $
"""

import sys, locale, string
from optparse import OptionParser

class commline:
    def __init__(self, file1, file2):
        if(file1 == "-"):
            self.file1=sys.stdin.readlines()
        else:
            f = open(file1, 'r')
            self.file1 = f.readlines()
            f.close()
        if(file2 == "-"):
            self.file2=sys.stdin.readlines()
        else:
            g = open(file2, 'r')
            self.file2 = g.readlines();
            g.close()
        for i in range(len(self.file1)):
            self.file1[i] = self.file1[i].rstrip("\n")
        for j in range(len(self.file2)):
            self.file2[j] = self.file2[j].rstrip("\n")
                                            
    def printCols(self, isSorted, suppressOne, suppressTwo, suppressThree):
        if(isSorted):
            printable=""
            firstSize=len(self.file1)
            secondSize=len(self.file2)
            firstIndex=0
            secondIndex=0
            while (firstIndex < firstSize and secondIndex < secondSize):
                if(self.file1[firstIndex] == self.file2[secondIndex]):
                    if(not suppressThree):
                        printable += (" "*16 + self.file1[firstIndex]+"\n")
                    firstIndex += 1
                    secondIndex += 1
                elif(self.file1[firstIndex] < self.file2[secondIndex]):
                    if(not suppressOne):
                        printable += (self.file1[firstIndex] + "\n")
                    firstIndex += 1
                else:
                    if(not suppressTwo):
                        printable += (" "*8 + self.file2[secondIndex] + "\n")
                    secondIndex += 1
            else:
                while(firstIndex != firstSize):
                    if(not suppressOne):
                        printable += (self.file1[firstIndex] + "\n")
                    firstIndex += 1
                while(secondIndex != secondSize):
                    if(not suppressTwo):
                        printable += (" "*8 + self.file2[secondIndex] + "\n")
                    secondIndex += 1
            sys.stdout.write(printable)
        else:
            printable=""
            copy1 = self.file1[:]
            copy2 = self.file2[:]
            for i in range(len(copy1)):
                for j in range(len(copy2)):
                    if(copy1[i] == copy2[j]):
                        temp = copy2.pop(j)
                        if(not suppressThree):
                            printable += (" "*16 + temp +"\n")
                        break
                else:
                    if(not suppressOne):
                        printable += (copy1[i]+"\n")
            for k in copy2:
                if(not suppressTwo):
                    printable += (" "*8 + k + "\n")
            sys.stdout.write(printable)
    
def main():
    
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE1 FILE2

outputs the differences between FILE1 and FILE2."""

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-u", "--unsorted",
                      action="store_true", dest="unsorted", default=False,
                      help="accepts unsorted lists(default false)")
    parser.add_option("-1", "--one",
                      action="store_true", dest="one", default=False,
                      help="Suppresses first column (lines unique to FILE1)")
    parser.add_option("-2", "--two",
                      action="store_true", dest="two", default=False,
                      help="Suppresses second column (lines unique to FILE2)")
    parser.add_option("-3", "--three",
                      action="store_true", dest="three", default=False,
                      help="Suppresses third column (lines that appear in both files)")
    (options, args) = parser.parse_args(sys.argv[1:])

    if len(args) != 2:
        parser.error("wrong number of operands")
    file1 = args[0]
    file2 = args[1]

    output = commline(file1, file2)
    output.printCols(not options.unsorted, options.one, options.two, options.three)

if __name__ == "__main__":
    main()
