This project is a simulation of downlink scheduling using ns3
The code is created by me (Alaa Khreis) and is based on the LENA v8 documentation
Copy the folders scratch and lte-epc-output in addition to run-lte-epc.sh to your ns-3.19 directory
Adjust the paths used in the code to suit your environement
./run-lte-epc.sh
This will run the simulation (lte-epc.cc) 9 times, each time a different scheduler is selected
The output is saved in the lte-epc-output/<SchedulerName> folder
gnuplot is called by the script and will plot the Throughput of each UE in every simulation to generate a chart (the png image)
