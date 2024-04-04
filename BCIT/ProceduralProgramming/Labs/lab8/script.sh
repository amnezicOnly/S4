#!/bin/bash

make

for i in {1..5}; do 
    cp "inputs/input$i.txt" input.txt
    cp "inputs/ref$i.txt" ref.txt
    make convert_input > /dev/null
    make run > /dev/null
    echo "$i => $(make check)"
    rm input.txt
    rm ref.txt
done
