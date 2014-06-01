#Alaa Khreis
#alaa_khreis@hotmail.com

reset
set term x11
set terminal png size 980,640 enhanced font "Helvetica,15"
set output "Comparision-IMSI-15.png"
set title "Throughput for each UE"
set xlabel "Scheduler"
set ylabel "Throughput (kbps)"
set autoscale y
set boxwidth 0.2
set style fill solid
unset key
plot "distance-15.txt" using ($0):(($3)*8/30/1024):xticlabels(1) with boxes linecolor rgb "red", \
     "distance-15.txt" using ($0):(($3)*8/30/1024)+1:(sprintf("%.2f",(($3)*8/30/1024))) with labels     



