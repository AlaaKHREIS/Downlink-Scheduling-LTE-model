This project is a simulation of downlink scheduling using ns3.
It is based on the LENA v8 documentation

The simulated schedulers are:
1-Maximum Throughput scheduler
The maximum throughput (MT) scheduler aims to maximize the overall throughput of an eNB. It allocates each RBG to the UE that can achieve the maximum expected data rate in the current TTI.

2-Throughput To Average scheduler
Different from MT, the throughput to average (TTA) scheduler can be considered as the tradeoff between efficiency and fairness.

3-Time Domain Blind Average Throughput scheduler
4-Frequency Domain Blind Average Throughput scheduler 
The blind equal throughput (BET) scheduler aims to provide an equal throughput to all UEs associated with the same eNB. Unlike MT and TTA, BET is channel-unaware in the sense that both FD-BET and TD-BET use wideband cqi in packet scheduling.

5-Frequency Domain Token Band Fair Queue scheduler
6-Time Domain Token Band Fair Queue scheduler
The Token bank fair queue (TBFQ) is a QoS aware scheduler which derives from the leaky-bucket mechanism.

7-Priority Set scheduler
The Priority set scheduler (PSS) is another QoS aware scheduler which combines time domain (TD) and frequency domain (FD) packet scheduling operations into one scheduler. It controls the fairness among UEs by defining a specified target bit rate (TBR).

8-Proportional Fair scheduler
The idea is that the past average throughput can act as a weighting factor of the expected data rate, so that users in bad conditions will be surely served within a certain amount of time.

9-Round Robin scheduler
The concept of fairness is related to the amount of time in which the channel is occupied by users. Of course, this approach is not fair in terms of user throughput.

