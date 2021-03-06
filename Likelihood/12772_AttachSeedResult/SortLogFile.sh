#!/bin/sh

mkdir -p Temp

for i in `ls BatchResult/ | tr -d '\\'`
do
   for j in Central BCentral
   do
      cat BatchResult/$i/*txt \
         | grep " $j " \
         | grep ".root" \
         | cut --delim=' ' --field=3- > Temp/SynthesizedLog_${i}_${j}.txt
   done
done

exit

for i in `ls Source/ | grep 6110`
do
   echo $i
   for j in Central LeptonUp LeptonDown LeptonWide LeptonNarrow \
      BCentral BLeptonUp BLeptonDown BLeptonWide BLeptonNarrow \
      SpectrumHard SpectrumSoft SpectrumCentral SpectrumForward \
      BSpectrumHard BSpectrumSoft BSpectrumCentral BSpectrumForward \
      HMassA HMassB HMassC HMassD
   do
      cat BatchSubmit/${i}/LSF*/STDOUT BatchSubmit/LSF*/STDOUT BatchSubmit/$i/*/Result*txt \
         BatchSubmit/$i/Output*txt \
         | grep "$i " | grep " $j " \
         | grep -v nan \
         | cut --delim=' ' --field=3- > Temp/SynthesizedLog_${i}_${j}.txt
   done
done


