#!/bin/bash

#Alaa Khreis
#alaa_khreis@hotmail.com

#Go to the scratch folder / environement dependant
#Change this to your ns-3.19 directory
cd "/root/workspace/ns-allinone-3.19/ns-3.19"


#Run the simulation with all the schedulers
echo 1 | ./waf --run scratch/lte-epc --cwd lte-epc-output/FdMtFfMacScheduler 
echo 2 | ./waf --run scratch/lte-epc --cwd lte-epc-output/TdMtFfMacScheduler 
echo 3 | ./waf --run scratch/lte-epc --cwd lte-epc-output/TtaFfMacScheduler 
echo 4 | ./waf --run scratch/lte-epc --cwd lte-epc-output/FdBetFfMacScheduler 
echo 5 | ./waf --run scratch/lte-epc --cwd lte-epc-output/TdBetFfMacScheduler 
echo 6 | ./waf --run scratch/lte-epc --cwd lte-epc-output/RrFfMacScheduler 
echo 7 | ./waf --run scratch/lte-epc --cwd lte-epc-output/FdTbfqFfMacScheduler 
echo 8 | ./waf --run scratch/lte-epc --cwd lte-epc-output/TdTbfqFfMacScheduler 
echo 9 | ./waf --run scratch/lte-epc --cwd lte-epc-output/PssFfMacScheduler 
echo 10 | ./waf --run scratch/lte-epc --cwd lte-epc-output/PfMacScheduler

#Gnuplot the Throughput for all the UEs
cd lte-epc-output/FdMtFfMacScheduler
gnuplot throughput_plot_script.gnuplot
cd ..
cd ..
cd lte-epc-output/TdMtFfMacScheduler
gnuplot throughput_plot_script.gnuplot
cd ..
cd ..
cd lte-epc-output/TtaFfMacScheduler
gnuplot throughput_plot_script.gnuplot
cd ..
cd ..
cd lte-epc-output/FdBetFfMacScheduler
gnuplot throughput_plot_script.gnuplot
cd ..
cd ..
cd lte-epc-output/TdBetFfMacScheduler
gnuplot throughput_plot_script.gnuplot
cd ..
cd ..
cd lte-epc-output/RrFfMacScheduler
gnuplot throughput_plot_script.gnuplot
cd ..
cd ..
cd lte-epc-output/FdTbfqFfMacScheduler
gnuplot throughput_plot_script.gnuplot
cd ..
cd ..
cd lte-epc-output/TdTbfqFfMacScheduler
gnuplot throughput_plot_script.gnuplot
cd ..
cd ..
cd lte-epc-output/PssFfMacScheduler
gnuplot throughput_plot_script.gnuplot
cd ..
cd ..
cd lte-epc-output/PfMacScheduler
gnuplot throughput_plot_script.gnuplot
cd ..
cd ..
