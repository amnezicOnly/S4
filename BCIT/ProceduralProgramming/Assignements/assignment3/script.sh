#!/bin/bash

make
echo "Inputs"
rm output.txt ; touch output.txt ; ./assignment3.out input/input1.txt output.txt ; diff -q output.txt input/ref1.txt
rm output.txt ; touch output.txt ; ./assignment3.out input/input2.txt output.txt ; diff -q output.txt input/ref2.txt
rm output.txt ; touch output.txt ; ./assignment3.out input/input3.txt output.txt ; diff -q output.txt input/ref3.txt
rm output.txt ; touch output.txt ; ./assignment3.out input/input4.txt output.txt ; diff -q output.txt input/ref4.txt
echo "Errors"
rm output.txt ; touch output.txt ; ./assignment3.out input/error1.txt output.txt ; echo "1" ; diff -q output.txt outputError.txt
rm output.txt ; touch output.txt ; ./assignment3.out input/error2.txt output.txt ; echo "2" ; diff -q output.txt outputError.txt
rm output.txt ; touch output.txt ; ./assignment3.out input/error3.txt output.txt ; echo "3" ; diff -q output.txt outputError.txt
rm output.txt ; touch output.txt ; ./assignment3.out input/error4.txt output.txt ; echo "4" ; diff -q output.txt outputError.txt
rm output.txt ; touch output.txt ; ./assignment3.out input/error5.txt output.txt ; echo "5" ; diff -q output.txt outputError.txt
rm output.txt ; touch output.txt ; ./assignment3.out input/error6.txt output.txt ; echo "6" ; diff -q output.txt outputError.txt
