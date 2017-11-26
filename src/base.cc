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

	NodeContainer nodes;
        nodes.Create(11);

	InternetStackHelper stack;
	stack.Install(nodes);

	PointToPointHelper p2p1;
	p2p1.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
	p2p1.SetChannelAttribute ("Delay", StringValue ("1ms"));

        PointToPointHelper p2p2;
        p2p2.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
        p2p2.SetChannelAttribute("Delay", StringValue("5ms"));

        PointToPointHelper p2p3;
        p2p3.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
        p2p3.SetChannelAttribute("Delay", StringValue("5ms"));

        PointToPointHelper p2p4;
        p2p4.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
        p2p4.SetChannelAttribute("Delay", StringValue("5ms"));

        PointToPointHelper p2p5;
        p2p5.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
        p2p5.SetChannelAttribute("Delay", StringValue("5ms"));

        PointToPointHelper p2p6;
        p2p6.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
        p2p6.SetChannelAttribute("Delay", StringValue("5ms"));

        PointToPointHelper p2p7;
        p2p7.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
        p2p7.SetChannelAttribute("Delay", StringValue("5ms"));

        PointToPointHelper p2p8;
        p2p8.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
        p2p8.SetChannelAttribute("Delay", StringValue("5ms"));

        PointToPointHelper p2p9;
        p2p9.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
        p2p9.SetChannelAttribute("Delay", StringValue("5ms"));

        PointToPointHelper p2p10;
        p2p10.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
        p2p10.SetChannelAttribute("Delay", StringValue("5ms"));

	Ipv4AddressHelper address;
	address.SetBase("10.1.1.0", "255.255.255.0");
	NetDeviceContainer devices;
	devices = p2p1.Install(nodes.Get(0), nodes.Get(4));
	Ipv4InterfaceContainer interfaces = address.Assign (devices);

	devices = p2p2.Install(nodes.Get(1),nodes.Get(4));
	address.SetBase("10.1.2.0","255.255.255.0");
	interfaces = address.Assign(devices);

	devices = p2p3.Install(nodes.Get(2),nodes.Get(4));
	address.SetBase("10.1.3.0","255.255.255.0");
	interfaces = address.Assign(devices);
	
	devices = p2p4.Install(nodes.Get(3),nodes.Get(4));
	address.SetBase("10.1.4.0","255.255.255.0");
	interfaces = address.Assign(devices);

	devices = p2p5.Install(nodes.Get(4),nodes.Get(5));
	address.SetBase("10.1.5.0","255.255.255.0");
	interfaces = address.Assign(devices);

	devices = p2p6.Install(nodes.Get(5),nodes.Get(6));
	address.SetBase("10.1.6.0","255.255.255.0");
	interfaces = address.Assign(devices);

	devices = p2p7.Install(nodes.Get(6),nodes.Get(7));
	address.SetBase("10.1.7.0","255.255.255.0");
	interfaces = address.Assign(devices);

	devices = p2p8.Install(nodes.Get(6),nodes.Get(8));
	address.SetBase("10.1.8.0","255.255.255.0");
	interfaces = address.Assign(devices);

	devices = p2p9.Install(nodes.Get(6),nodes.Get(9));
	address.SetBase("10.1.9.0","255.255.255.0");
	interfaces = address.Assign(devices);

	devices = p2p10.Install(nodes.Get(6),nodes.Get(10));
	address.SetBase("10.1.10.0","255.255.255.0");
	interfaces = address.Assign(devices);

	Ipv4GlobalRoutingHelper::PopulateRoutingTables();	

	UdpEchoServerHelper echoServer(9);
	
	ApplicationContainer serverApps = echoServer.Install(nodes.Get(2));
	serverApps.Start(Seconds(1.0));
	serverApps.Stop(Seconds(10.0));
	
	UdpEchoClientHelper echoClient (interfaces.GetAddress(1),9);
	echoClient.SetAttribute("MaxPackets",UintegerValue(1));
	echoClient.SetAttribute("Interval",TimeValue(Seconds(1.0)));
	echoClient.SetAttribute("PacketSize",UintegerValue(1024));

	ApplicationContainer clientApps = echoClient.Install (nodes.Get(0));
	clientApps.Start(Seconds(2.0));
	clientApps.Stop(Seconds(10.0));

	AnimationInterface anima ("base.xml");
	anima.SetConstantPosition (nodes.Get(0),0.0,0.0);
	anima.SetConstantPosition (nodes.Get(1),2.0,2.0);
	anima.SetConstantPosition (nodes.Get(2),3.0,3.0);
	anima.SetConstantPosition (nodes.Get(3),4.0,4.0);
	anima.SetConstantPosition (nodes.Get(4),5.0,5.0);
	anima.SetConstantPosition (nodes.Get(5),6.0,6.0);
	anima.SetConstantPosition (nodes.Get(6),7.0,7.0);
	anima.SetConstantPosition (nodes.Get(7),8.0,8.0);
	anima.SetConstantPosition (nodes.Get(8),9.0,9.0);
	anima.SetConstantPosition (nodes.Get(9),10.0,10.0);
	anima.SetConstantPosition (nodes.Get(10),11.0,11.0);

	Simulator::Run();
	Simulator::Destroy();

	return 0;
	
}
