#!/bin/bash

mv input/error.txt . && ./assignment3.out error.txt && diff -q output.txt errorTest.txt &>> result.txt; mv error.txt input/.
mv input/error1.txt . && ./assignment3.out error1.txt && diff -q output.txt errorTest.txt &>> result.txt; mv error1.txt input/.
mv input/error2.txt . && ./assignment3.out error2.txt && diff -q output.txt errorTest.txt &>> result.txt; mv error2.txt input/.
mv input/error3.txt . && ./assignment3.out error3.txt && diff -q output.txt errorTest.txt &>> result.txt; mv error3.txt input/.
mv input/error4.txt . && ./assignment3.out error4.txt && diff -q output.txt errorTest.txt &>> result.txt; mv error4.txt input/.
mv input/error4.txt . && ./assignment3.out error5.txt && diff -q output.txt errorTest.txt &>> result.txt; mv error5.txt input/.
mv input/error5.txt . && ./assignment3.out error6.txt && diff -q output.txt errorTest.txt &>> result.txt; mv error6.txt input/.
mv input/input.txt . && ./assignment3.out input.txt && diff -q output.txt input/ref.txt &>> result.txt; mv input.txt input/.
mv input/input1.txt . && ./assignment3.out input1.txt && diff -q output.txt input/ref1.txt &>> result.txt; mv input1.txt input/.
mv input/input2.txt . && ./assignment3.out input2.txt && diff -q output.txt input/ref2.txt &>> result.txt; mv input2.txt input/.
mv input/input3.txt . && ./assignment3.out input3.txt && diff -q output.txt input/ref3.txt &>> result.txt; mv input3.txt input/.
mv input/input4.txt . && ./assignment3.out input4.txt && diff -q output.txt input/ref4.txt &>> result.txt; mv input4.txt input/.
