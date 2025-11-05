#!/bin/bash

for N in {1..80}
do
    x=$((($N%5)+1))
    ruby client.rb "${x}"&
    sleep 0.05   # give the server breathing room
done
wait
