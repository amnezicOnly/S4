#!/bin/bash

make
echo "Inputs"
rm output.txt && touch output.txt && ./assignment3.out input/input1.txt output.txt && diff -q output.txt input/ref1.txt && cat output.txt && echo " " && cat input/ref1.txt && echo " " && echo " "
rm output.txt && touch output.txt && ./assignment3.out input/input2.txt output.txt && diff -q output.txt input/ref2.txt && cat output.txt && echo " " && cat input/ref2.txt && echo " " && echo " "
rm output.txt && touch output.txt && ./assignment3.out input/input3.txt output.txt && diff -q output.txt input/ref3.txt && cat output.txt && echo " " && cat input/ref3.txt && echo " " && echo " "
rm output.txt && touch output.txt && ./assignment3.out input/input4.txt output.txt && diff -q output.txt input/ref4.txt && cat output.txt && echo " " && cat input/ref4.txt && echo " " && echo " "
echo "Errors"
rm output.txt && touch output.txt && ./assignment3.out input/error1.txt output.txt && diff -q output.txt outputError.txt && cat output.txt && echo " " && cat outputError.txt && echo " " && echo " "
rm output.txt && touch output.txt && ./assignment3.out input/error2.txt output.txt && diff -q output.txt outputError.txt && cat output.txt && echo " " && cat outputError.txt && echo " " && echo " "
rm output.txt && touch output.txt && ./assignment3.out input/error3.txt output.txt && diff -q output.txt outputError.txt && cat output.txt && echo " " && cat outputError.txt && echo " " && echo " "
rm output.txt && touch output.txt && ./assignment3.out input/error4.txt output.txt && diff -q output.txt outputError.txt && cat output.txt && echo " " && cat outputError.txt && echo " " && echo " "
rm output.txt && touch output.txt && ./assignment3.out input/error5.txt output.txt && diff -q output.txt outputError.txt && cat output.txt && echo " " && cat outputError.txt && echo " " && echo " "
rm output.txt && touch output.txt && ./assignment3.out input/error6.txt output.txt && diff -q output.txt outputError.txt && cat output.txt && echo " " && cat outputError.txt && echo " " && echo " "
