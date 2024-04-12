#!/bin/bash

make
rm output.txt ; touch output.txt
./lab7.out inputs/input1.txt output.txt ; diff -q output.txt inputs/ref1.txt
rm output.txt ; touch output.txt
./lab7.out inputs/input2.txt output.txt ; diff -q output.txt inputs/ref2.txt
rm output.txt ; touch output.txt
./lab7.out inputs/input3.txt output.txt ; diff -q output.txt inputs/ref3.txt
rm output.txt ; touch output.txt
./lab7.out inputs/input4.txt output.txt ; diff -q output.txt inputs/ref4.txt
rm output.txt ; touch output.txt
./lab7.out inputs/input5.txt output.txt ; diff -q output.txt inputs/ref5.txt
