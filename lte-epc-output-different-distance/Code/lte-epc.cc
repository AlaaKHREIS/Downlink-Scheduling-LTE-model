//Alaa Khreis
//alaa_khreis@hotmail.com
//My code is based on the LENA v8 documentation

//Run this code using ./waf --run scratch/lte-epc --cwd TracesPath
//or use ./run-lte-epc.sh  to run all the schedulers and generate output

#include <ns3/object.h>
#include <ns3/spectrum-interference.h>
#include <ns3/spectrum-error-model.h>
#include <ns3/log.h>
#include <ns3/packet.h>
#include <ns3/ptr.h>

#include "ns3/radio-bearer-stats-calculator.h"
#include <ns3/constant-position-mobility-model.h>
#include <ns3/eps-bearer.h>
#include <ns3/node-container.h>
#include <ns3/mobility-helper.h>
#include <ns3/net-device-container.h>
#include <ns3/lte-ue-net-device.h>
#include <ns3/lte-enb-net-device.h>
#include <ns3/lte-ue-rrc.h>
#include <ns3/lte-helper.h>
#include "ns3/string.h"
#include "ns3/double.h"
#include <ns3/lte-enb-phy.h>
#include <ns3/lte-ue-phy.h>
#include <ns3/boolean.h>
#include <ns3/enum.h>

#include <ns3/epc-helper.h>
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/internet-module.h"
#include "ns3/lte-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-helper.h"

//Add for input-defaults.txt file
#include "ns3/config-store.h"
#include "ns3/core-module.h"


//FlowMonitor
#include "ns3/flow-monitor-module.h"

//to debug the program:

using namespace ns3;
using namespace std;

int
main (int argc, char *argv[])
{

//Number of Users
uint16_t m_nUser = 10;
//Distance
double distance = 60;

double interPacketInterval = 20;

//Set the simulation time
double simTime = 300.0;

// Command line arguments
CommandLine cmd;
cmd.AddValue("numberOfNodes", "Number of eNodeBs + UE pairs", m_nUser);
cmd.AddValue("simTime", "Total duration of the simulation [s])", simTime);
cmd.AddValue("distance", "Distance between eNBs [m]", distance);
cmd.AddValue("interPacketInterval", "Inter packet interval [ms])", interPacketInterval);
cmd.Parse (argc, argv);

//Input the parameters from the config txt file
ConfigStore inputConfig;
inputConfig.ConfigureDefaults ();

// parse again so you can override default values from the command line
cmd.Parse (argc, argv);

//Run the input-defaults.txt document
// ./waf --command-template="%s --ns3::ConfigStore::Filename=input-defaults.txt --ns3::ConfigStore::Mode=Load --ns3::ConfigStore::FileFormat=RawText" --run scratch/firstprogram

//Comment?
RngSeedManager::SetSeed (6);
RngSeedManager::SetRun (4);


//Set some of the Bit Error Stuff
double ber = 0.000001;
Config::SetDefault ("ns3::LteAmc::AmcModel", EnumValue (LteAmc::PiroEW2010));
Config::SetDefault ("ns3::LteAmc::Ber", DoubleValue (ber));
//The next 2 commands disable the usage of the phy error model
//Config::SetDefault ("ns3::LteSpectrumPhy::CtrlErrorModelEnabled", BooleanValue (false));
//Config::SetDefault ("ns3::LteSpectrumPhy::DataErrorModelEnabled", BooleanValue (false));
Config::SetDefault ("ns3::LteEnbRrc::EpsBearerToRlcMapping",EnumValue(LteHelper::RLC_UM_ALWAYS));


//Set LTE Helper and EPC Helper
Ptr<LteHelper> lteHelper = CreateObject<LteHelper> ();
Ptr<PointToPointEpcHelper> epcHelper = CreateObject<PointToPointEpcHelper> ();
lteHelper->SetEpcHelper (epcHelper);

//Have not set the antenna model type  
lteHelper->SetEnbAntennaModelType ("ns3::IsotropicAntennaModel");
//default ns3::LteEnbNetDevice::UlBandwidth "25"
//default ns3::LteEnbNetDevice::DlBandwidth "25"
//default ns3::LteEnbNetDevice::DlEarfcn "100"
//default ns3::LteEnbNetDevice::UlEarfcn "18100"

//Set LTE Scheduler
//Configure LTE MAC Scheduler - your choice
int choice;
cout << "Choose one of the following schedulers" << endl;
cout << "1-FdMtFfMacScheduler"<< endl;
cout << "2-TdMtFfMacScheduler"<< endl;
cout << "3-TtaFfMacScheduler"<< endl;
cout << "4-FdBetFfMacScheduler"<< endl;
cout << "5-TdBetFfMacScheduler"<< endl;
cout << "6-RrFfMacScheduler"<< endl;
cout << "7-FdTbfqFfMacScheduler"<< endl;
cout << "8-TdTbfqFfMacScheduler"<< endl;
cout << "9-PssFfMacScheduler"<< endl;
cout << "Default: PfMacScheduler" << endl;
cout << "Scheduler choice: ";
cin  >> choice;
switch (choice){
  case (1):
    lteHelper -> SetSchedulerType ("ns3::FdMtFfMacScheduler");//FD-MT
    break;
  case (2):
	lteHelper -> SetSchedulerType ("ns3::TdMtFfMacScheduler");//TD-MT
	break;
  case (3):
    lteHelper -> SetSchedulerType ("ns3::TtaFfMacScheduler");//TTA
	break;
  case (4):
	lteHelper -> SetSchedulerType ("ns3::FdBetFfMacScheduler");//FD-BET
    break;
  case (5):
    lteHelper -> SetSchedulerType ("ns3::TdBetFfMacScheduler");//TD-BET			    
    break;
  case(6):
	lteHelper->SetSchedulerType ("ns3::RrFfMacScheduler"); //RR
	break;
  case (7):
    lteHelper -> SetSchedulerType ("ns3::FdTbfqFfMacScheduler");//FD-TBFQ		   
     //Parameters for TBFQ scheduler 
	lteHelper->SetSchedulerAttribute("DebtLimit", IntegerValue(-625000)); // default value -625000 bytes (-5Mb)
	lteHelper->SetSchedulerAttribute("CreditLimit", UintegerValue(625000)); // default value 625000 bytes (5Mb)
	lteHelper->SetSchedulerAttribute("TokenPoolSize", UintegerValue(1)); // default value 1 byte
	lteHelper->SetSchedulerAttribute("CreditableThreshold", UintegerValue(0)); // default value 0			    
	break;
  case (8):
	lteHelper -> SetSchedulerType ("ns3::TdTbfqFfMacScheduler");//TD-TBFQ	     		    
    //Parameters for TBFQ scheduler
	lteHelper->SetSchedulerAttribute("DebtLimit", IntegerValue(-625000)); // default value -625000 bytes (-5Mb)
	lteHelper->SetSchedulerAttribute("CreditLimit", UintegerValue(625000)); // default value 625000 bytes (5Mb)
	lteHelper->SetSchedulerAttribute("TokenPoolSize", UintegerValue(1)); // default value 1 byte
	lteHelper->SetSchedulerAttribute("CreditableThreshold", UintegerValue(0)); // default value 0
    break;
  case (9):
    lteHelper -> SetSchedulerType ("ns3::PssFfMacScheduler");//PSS		     
    //Parameters for PSS scheduler
	//lteHelper->SetSchedulerAttribute("nMux", UIntegerValue(10)); // the maximum number of UE selected by TD scheduler
	lteHelper->SetSchedulerAttribute("PssFdSchedulerType", StringValue("CoItA")); // PF scheduler type in PSS
    break;
  default:
	//PF scheduler
	break;	
};
	
	
//Can also set the CQI filters, this changes for different schedulers
//Also possible to turn HARQ on and off
//lteHelper->SetSchedulerAttribute ("UlcqiFilter", EnumValue (FfMacScheduler::PUSH_UL_CQI));


//Pathloss/Fading Model
lteHelper->SetAttribute ("PathlossModel", StringValue ("ns3::FriisSpectrumPropagationLossModel"));


//Create the Packet Gateway
Ptr<Node> pgw = epcHelper->GetPgwNode ();

// Create a single RemoteHost
NodeContainer remoteHostContainer;
remoteHostContainer.Create (1);
Ptr<Node> remoteHost = remoteHostContainer.Get (0);
InternetStackHelper internet;
internet.Install (remoteHostContainer);

// Create the Internet
PointToPointHelper p2ph;
p2ph.SetDeviceAttribute ("DataRate", DataRateValue (DataRate ("100Gb/s")));
p2ph.SetDeviceAttribute ("Mtu", UintegerValue (1500));
p2ph.SetChannelAttribute ("Delay", TimeValue (Seconds (0.010)));
NetDeviceContainer internetDevices = p2ph.Install (pgw, remoteHost);
Ipv4AddressHelper ipv4h;
ipv4h.SetBase ("1.0.0.0", "255.0.0.0");
Ipv4InterfaceContainer internetIpIfaces = ipv4h.Assign (internetDevices);
// interface 0 is localhost, 1 is the p2p device
//Ipv4Address remoteHostAddr = internetIpIfaces.GetAddress (1);

Ipv4StaticRoutingHelper ipv4RoutingHelper;
Ptr<Ipv4StaticRouting> remoteHostStaticRouting = ipv4RoutingHelper.GetStaticRouting (remoteHost->GetObject<Ipv4> ());
remoteHostStaticRouting->AddNetworkRouteTo (Ipv4Address ("7.0.0.0"), Ipv4Mask ("255.0.0.0"), 1);
 
//Create Nodes: eNodeB and UE
NodeContainer enbNodes;
NodeContainer ueNodes;
enbNodes.Create (1);
ueNodes.Create (m_nUser);


//Set UEs position
Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
for (int i=0; i < m_nUser; i++)
        {
	  positionAlloc->Add (Vector(distance * 50 * i, 0, 0));  //scenario 2: different distance
	  //positionAlloc->Add (Vector(distance * i, 0, 0));  //scenario 1: same distance
      //Ptr<ConstantPositionMobilityModel> mm = ueNodes.Get (i)->GetObject<ConstantPositionMobilityModel> ();
	  //if(i<= (m_nUser / 2) ) mm->SetPosition (Vector (distance, 0.0, 0.0));
	  //else 		mm->SetPosition (Vector (distance+ 2 * i, 0.0, 0.0));
        }
        
// Install Mobility Model
MobilityHelper mobility;
mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
mobility.Install (enbNodes);
mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
mobility.SetPositionAllocator(positionAlloc);
mobility.Install (ueNodes);

//Create Devices and install them in the Nodes (eNB and UE)
NetDeviceContainer enbDevs;
NetDeviceContainer ueDevs;
enbDevs = lteHelper->InstallEnbDevice (enbNodes);
ueDevs = lteHelper->InstallUeDevice (ueNodes);

//Set UEs power
for (int i=0; i < m_nUser; i++)
        {
      Ptr<LteUeNetDevice> lteUeDev = ueDevs.Get (i)->GetObject<LteUeNetDevice> ();
      Ptr<LteUePhy> uePhy = lteUeDev->GetPhy ();
      uePhy->SetAttribute ("TxPower", DoubleValue (23.0));
      uePhy->SetAttribute ("NoiseFigure", DoubleValue (5.0 ));
		}

//Set eNBs power		
Ptr<LteEnbNetDevice> lteEnbDev = enbDevs.Get (0)->GetObject<LteEnbNetDevice> ();
Ptr<LteEnbPhy> enbPhy = lteEnbDev->GetPhy ();
enbPhy->SetAttribute ("TxPower", DoubleValue (30.0));
enbPhy->SetAttribute ("NoiseFigure", DoubleValue (5.0));


// Install the IP stack on the UEs
internet.Install (ueNodes);
Ipv4InterfaceContainer ueIpIface;
ueIpIface = epcHelper->AssignUeIpv4Address (NetDeviceContainer (ueDevs));

// Assign IP address to UEs, and install applications
for (uint32_t u = 0; u < ueNodes.GetN (); ++u)
    {
      Ptr<Node> ueNode = ueNodes.Get (u);
      // Set the default gateway for the UE
      Ptr<Ipv4StaticRouting> ueStaticRouting = ipv4RoutingHelper.GetStaticRouting (ueNode->GetObject<Ipv4> ());
      ueStaticRouting->SetDefaultRoute (epcHelper->GetUeDefaultGatewayAddress (), 1);
    }


//Attach a UEs to the eNodeB
for (uint16_t i = 0; i < m_nUser; i++)
        {
         lteHelper->Attach (ueDevs.Get(i), enbDevs.Get(0));
         //Side effect: the default EPS bearer will be activated
        }

//Activate an EPS bearer
enum EpsBearer::Qci q = EpsBearer::GBR_CONV_VOICE;
EpsBearer bearer (q);
//The DataRadioBearer was activated automatically in a previous step
//The following command would give an error if uncommented
//lteHelper->ActivateDataRadioBearer (ueDevs, bearer);
//Side effect: the default EPS bearer will be activated


// UDP connection from remote to UEnodes
  uint16_t dlPort = 1234;

  ApplicationContainer clientApps;
  ApplicationContainer serverApps;
  for (uint32_t u = 0; u < ueNodes.GetN (); ++u)
    {
      dlPort++;
      PacketSinkHelper dlPacketSinkHelper ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), dlPort));

      serverApps.Add (dlPacketSinkHelper.Install (ueNodes.Get(u)));

      UdpClientHelper dlClient (ueIpIface.GetAddress (u), dlPort);
      dlClient.SetAttribute ("Interval", TimeValue (MilliSeconds(interPacketInterval)));
      dlClient.SetAttribute ("MaxPackets", UintegerValue(1000000));

      clientApps.Add (dlClient.Install (remoteHost));

    }

  serverApps.Start (Seconds (0.01));
  clientApps.Start (Seconds (0.01));

  lteHelper->EnableMacTraces ();
  lteHelper->EnableRlcTraces ();


  FlowMonitorHelper flowmon;
  Ptr<FlowMonitor> monitor = flowmon.Install(ueNodes);
  flowmon.Install(enbNodes.Get(1));

  Simulator::Stop(Seconds(simTime));

  Ptr<RadioBearerStatsCalculator> rlcStats = lteHelper->GetRlcStats ();
  rlcStats->SetAttribute ("EpochDuration", TimeValue (Seconds (simTime)));

  Simulator::Run();
  cout << "Start Simulation" << endl;

  monitor->CheckForLostPackets (); 

  Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowmon.GetClassifier ());
  map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats ();

  double Throughput=0.0;

  for (map<FlowId, FlowMonitor::FlowStats>::const_iterator i = stats.begin (); i != stats.end (); ++i)
    {
    Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow (i->first);

      cout << "Flow ID: " << i->first << " Src Addr " <<  t.sourceAddress << " Dst Addr " << t.destinationAddress << endl;
      cout << "Tx Packets = " << i->second.txPackets << endl;
      cout << "Rx Packets = " << i->second.rxPackets << endl;
      Throughput=i->second.rxBytes * 8.0 /(i->second.timeLastRxPacket.GetSeconds()-i->second.timeFirstTxPacket.GetSeconds())/ 1024;
      cout << "Throughput: " <<  Throughput << " Kbps" << endl;
    }

  NS_LOG_UNCOND("Done");

  cout << "Simulation End" << endl;
  
  Simulator::Destroy();
  return 0;

}






