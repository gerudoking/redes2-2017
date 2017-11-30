#include <fstream>
#include "ns3/netanim-module.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("base");

int main (int argc, char *argv[]){

	Time::SetResolution (Time::NS);
	LogComponentEnable("UdpEchoClientApplication",LOG_LEVEL_INFO);
	LogComponentEnable("UdpEchoServerApplication",LOG_LEVEL_INFO);

	bool useV6 = false;

	//Cria os nós da rede
	NS_LOG_INFO("Creating nodes...");
	NodeContainer nodes, nodesRede1, nodesRede2, nodesRede3;
	nodes.Create(11);

	//Seta os nós para cada rede

	//Rede 1
	nodesRede1.Add(nodes.Get(0));
	nodesRede1.Add(nodes.Get(1));
	nodesRede1.Add(nodes.Get(2));
	nodesRede1.Add(nodes.Get(3));
	nodesRede1.Add(nodes.Get(4));//Nó roteador da rede 1

	//Rede 2
	nodesRede2.Add(nodes.Get(6));//Nó roteador da rede 2
	nodesRede2.Add(nodes.Get(7));
	nodesRede2.Add(nodes.Get(8));
	nodesRede2.Add(nodes.Get(9));
	nodesRede2.Add(nodes.Get(10));

	//Rede entre roteadores e nó intermediário
	nodesRede3.Add(nodes.Get(5));

	InternetStackHelper stackHelper;
	stackHelper.Install(nodes);


	//Cria os canais requeridos pela topologia
	NS_LOG_INFO("Creating channels...");

	PointToPointHelper pointHelper;
	//pointHelper.SetChannelAttribute("DataRate", DataRateValue(DataRate (5000000)));
	pointHelper.SetChannelAttribute("Delay", TimeValue(MilliSeconds(2)));
	//pointHelper.SetDeviceAttribute("Mtu", UintegerValue(1400));

	NetDeviceContainer netInterface1 ,netInterface2 ,netInterface3 ,netInterface4;

	netInterface1.Add(pointHelper.Install(nodesRede1.Get(0),nodesRede1.Get(4)));
	netInterface1.Add(pointHelper.Install(nodesRede1.Get(1),nodesRede1.Get(4)));
	netInterface1.Add(pointHelper.Install(nodesRede1.Get(2),nodesRede1.Get(4)));
	netInterface1.Add(pointHelper.Install(nodesRede1.Get(3),nodesRede1.Get(4)));

	netInterface2.Add(pointHelper.Install(nodesRede1.Get(4),nodesRede3.Get(0)));

	netInterface3.Add(pointHelper.Install(nodesRede3.Get(0),nodesRede2.Get(0)));

	netInterface4.Add(pointHelper.Install(nodesRede2.Get(0),nodesRede2.Get(1)));
	netInterface4.Add(pointHelper.Install(nodesRede2.Get(0),nodesRede2.Get(2)));
	netInterface4.Add(pointHelper.Install(nodesRede2.Get(0),nodesRede2.Get(3)));
	netInterface4.Add(pointHelper.Install(nodesRede2.Get(0),nodesRede2.Get(4)));

	NS_LOG_INFO ("Assign IP Addresses.");
  	if (useV6 == false){
	Ipv4InterfaceContainer interfaceRede1,interfaceRede2,interfaceRede3,interfaceRede4;
      	Ipv4AddressHelper ipv4;
      	ipv4.SetBase ("10.1.1.0", "255.255.255.0");
      	interfaceRede1 = ipv4.Assign (netInterface1);
	ipv4.NewNetwork();

	ipv4.SetBase("10.1.2.0","255.255.255.0");
	interfaceRede2 = ipv4.Assign(netInterface2);
	ipv4.NewNetwork();

	ipv4.SetBase("10.1.3.0","255.255.255.0");
	interfaceRede3 = ipv4.Assign(netInterface3);
	ipv4.NewNetwork();

	ipv4.SetBase("10.1.4.0","255.255.255.0");
	interfaceRede4 = ipv4.Assign(netInterface4);
	ipv4.NewNetwork();   

	Ipv4GlobalRoutingHelper::PopulateRoutingTables();
}	

    NS_LOG_INFO("Create Applications.");
	
	uint16_t port = 4000;
  	ApplicationContainer client,server,p2pClient1,p2pClient2,p2pServer1,p2pServer2;
	UdpEchoServerHelper echoServerHelper(port);
	server = echoServerHelper.Install(nodesRede1.Get(2));

	UdpEchoClientHelper echoClientHelper(nodesRede1.Get(2)->GetObject<Ipv4>()->GetAddress(1,0).GetLocal(),port);
	client = echoClientHelper.Install(nodesRede2.Get(2));

	p2pServer1 = echoServerHelper.Install(nodesRede2.Get(1));
	p2pServer2 = echoServerHelper.Install(nodesRede1.Get(1));
  	
	UdpEchoClientHelper echoClientHelper2(nodesRede1.Get(1)->GetObject<Ipv4>()->GetAddress(1,0).GetLocal(),port);
	p2pClient1 = echoClientHelper2.Install(nodesRede2.Get(1));

	UdpEchoClientHelper echoClientHelper3(nodesRede2.Get(1)->GetObject<Ipv4>()->GetAddress(1,0).GetLocal(),port);
	p2pClient2 = echoClientHelper3.Install(nodesRede1.Get(1));	

	server.Start(Seconds(1));
	server.Stop(Seconds(50));
	client.Start(Seconds(2));
	client.Stop(Seconds(49));
	p2pClient1.Start(Seconds(2));
	p2pServer1.Start(Seconds(1));
	p2pClient1.Stop(Seconds(49));
	p2pServer1.Stop(Seconds(50));
	p2pClient2.Start(Seconds(2));
	p2pServer2.Start(Seconds(1));
	p2pClient2.Stop(Seconds(49));
	p2pServer2.Stop(Seconds(50));

	

  	/*uint32_t MaxPacketSize = 1024;
  	Time interPacketInterval = Seconds (0.05);
  	uint32_t maxPacketCount = 320;
  	client.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
  	client.SetAttribute ("Interval", TimeValue (interPacketInterval));
  	client.SetAttribute ("PacketSize", UintegerValue (MaxPacketSize));*/
  	


	AnimationInterface anima ("base.xml");
	anima.SetConstantPosition (nodes.Get(0),0.0,0.0);
	anima.SetConstantPosition (nodes.Get(1),0.0,20.0);
	anima.SetConstantPosition (nodes.Get(2),0.0,40.0);
	anima.SetConstantPosition (nodes.Get(3),0.0,60.0);
	anima.SetConstantPosition (nodes.Get(4),30.0,30.0);
	anima.SetConstantPosition (nodes.Get(5),60.0,0.0);
	anima.SetConstantPosition (nodes.Get(6),90.0,30.0);
	anima.SetConstantPosition (nodes.Get(7),120.0,0.0);
	anima.SetConstantPosition (nodes.Get(8),120.0,20.0);
	anima.SetConstantPosition (nodes.Get(9),120.0,40.0);
	anima.SetConstantPosition (nodes.Get(10),120.0,60.0);

	Simulator::Stop(Seconds(50));
	Simulator::Run();
	Simulator::Destroy();

	return 0;
	
}
