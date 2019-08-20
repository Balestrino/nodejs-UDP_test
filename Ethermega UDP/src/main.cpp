#include <Arduino.h>
#include <SPI.h>        
#include <EthernetUdp.h>

byte mac[] = { 0xAE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress ip(192, 168, 0, 88);
unsigned int localPort = 8888;

IPAddress remote(192, 168, 0, 90);
unsigned int remotePort = 8888;

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];  // buffer to hold incoming packet,

EthernetUDP Udp;

void setup() 
{
  Serial.begin(9600);
  Serial.println("UDP Server starting...");
  pinMode(49,INPUT_PULLUP);
  pinMode(48,OUTPUT);

  Ethernet.begin(mac,ip);
  // Ethernet.setRetransmissionCount(0); // default 8
  // Ethernet.setRetransmissionTimeout(0); // milliseconds

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  Udp.begin(localPort);
  
}

void loop() {
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    // Serial.print("Received packet of size ");
    // Serial.println(packetSize);
    // Serial.print("From ");
    IPAddress remote = Udp.remoteIP();

    // Serial.print(", port ");
    // Serial.println(Udp.remotePort());

    // read the packet into packetBufffer
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    // Serial.println("Contents:");
    // Serial.println(packetBuffer);

    // send a reply to the IP address and port that sent us the packet we received
    // Serial.print("sending packet to: "); 
    // Serial.print(Udp.remoteIP());
    // Serial.print(" port: ");
    // Serial.println(remotePort);
    //Udp.beginPacket(Udp.remoteIP(), remotePort);
    Udp.beginPacket(remote, remotePort);

    Udp.write("1234567890123456789012345678901234567890");
    delay(1);
    if(!Udp.endPacket()) {
      Serial.println("send error!");
    }

  }
}