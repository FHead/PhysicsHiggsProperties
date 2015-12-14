#!/bin/sh

mkdir -p Temp

for i in `ls Source/ | grep _[12][1-9]0100.root | grep -v 110100` 
do
   echo $i
   for j in Central LeptonUp LeptonDown LeptonWide LeptonNarrow \
      BCentral BLeptonUp BLeptonDown BLeptonWide BLeptonNarrow
   # for j in BCentral BLeptonUp BLeptonDown BLeptonWide BLeptonNarrow
   do
      cat BatchSubmit/${i}/LSF*/STDOUT BatchSubmit/LSF*/STDOUT | grep "$i " | grep " $j " \
         | grep -v nan \
         | cut --delim=' ' --field=3- > Temp/SynthesizedLog_${i}_${j}.txt
   done
done


