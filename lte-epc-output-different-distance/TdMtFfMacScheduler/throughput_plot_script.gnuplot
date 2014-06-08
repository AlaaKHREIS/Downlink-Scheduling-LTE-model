#Alaa Khreis
#alaa_khreis@hotmail.com

reset
set term x11
set terminal png size 980,640 enhanced font "Helvetica,15"
set output "ThroughputIMSI.png"
set title "Throughput for each UE"
set xlabel "UE (IMSI)"
set ylabel "Throughput (kbps)"
set xrange [1:10]
set xtics 1
set autoscale y
set boxwidth 0.2
set style fill solid
unset key
plot "DlRlcStats.txt" using 4:(($10)*8/300/1024) with boxes linecolor rgb "red", \
     "DlRlcStats.txt" using 4:(($10)*8/300/1024):(sprintf("%.2f",(($10)*8/300/1024))) with labels     



