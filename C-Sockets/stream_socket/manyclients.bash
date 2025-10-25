#!/bin/bash

for N in {1..150}
do
    x=$((($N%5)+1))
    ruby client.rb "${x}"&
done
wait
