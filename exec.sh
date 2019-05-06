#!/bin/bash
if [ -z "$1" ]; then
nb=20
else
nb=$1
fi
c=0
r=0
h=0
for ((i=1; i <= $nb; i++)); do
./generator --big-superposition > b$i
cat b$i | ./lem-in > f$i
if ((`echo $?` != 0)); then
exit
fi
printf "%-9s: " "expected"
e=`cat f$i | grep -m 1 "required:" | grep -o "[0-9][0-9]*"`
echo $e
printf "%-9s: " "got"
g=`cat f$i | grep "^L" | wc -l`
echo $g
if ((g > e)); then
let h++
fi
if ((g > e + 2)); then
let c++
fi
if ((g > e + 10)); then
let r++
fi
echo $i
sleep 1
done
echo "nbr of high : $h/$nb"
echo "nbr of too high : $c/$nb"
echo "nbr of way too high : $r/$nb"
