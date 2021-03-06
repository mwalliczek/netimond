/*
 * Copyright (c) 2019 Matthias Walliczek
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *  http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef IP_H
#define IP_H

#include "ConfigfileParser.h"
#include "ActiveTcpConnections.h"
#include "ActiveUdpConnections.h"
#include "ICMP.h"
#include "ICMPv6.h"
#include "Ipv4Addr.h"
#include "Ipv6Addr.h"

class Ip {
    ActiveConnections<Ipv4Addr> *otherv4;
    ActiveConnections<Ipv6Addr> *otherv6;
    ICMP *icmpv4;
    ICMPv6 *icmpv6;
    void handleV4(const u_char *packet);
    void handleV6(const u_char *packet);
protected:
    ActiveTcpConnections<Ipv4Addr> *activev4TcpConnections;
    ActiveTcpConnections<Ipv6Addr> *activev6TcpConnections;
    ActiveUdpConnections<Ipv4Addr> *activev4UdpConnections;
    ActiveUdpConnections<Ipv6Addr> *activev6UdpConnections;
    Ip(ActiveTcpConnections<Ipv4Addr> *activev4TcpConnections, ActiveTcpConnections<Ipv6Addr> *activev6TcpConnections,
            ActiveUdpConnections<Ipv4Addr> *activev4UdpConnections, 
            ActiveUdpConnections<Ipv6Addr> *activev6UdpConnections);

public:
    explicit Ip(ConfigfileParser *configFile);
    virtual ~Ip();
    Ip(const Ip&) = delete;
    virtual void checkTimeout();
    static void got_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);
};

#endif
