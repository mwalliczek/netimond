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

#include "ActiveStateConnections.h"
#include "bumon.h"
#include "Ipv4Addr.h"
#include "Ipv6Addr.h"

template<typename IP>
ActiveStateConnections<IP>::ActiveStateConnections(std::list<InternNet<IP>> interns, std::list<IP> selfs):
    ActiveConnections<IP>(interns, selfs) { }

template<typename IP>
Connection* ActiveStateConnections<IP>::createConnection(IP ip_src, int sport, IP ip_dst, int dport, u_char protocol, 
        const char *logMessage) {
    Connection* connection = this->createSimpleConnection(ip_src, ip_dst, protocol);
    connection->dst_port = dport;
    
    ConnectionIdentifier<IP> identifier = ConnectionIdentifier<IP>(ip_src, sport, ip_dst, dport);
    map[identifier] = connection->id;
    
    if (logfile->checkLevel(6)) {
	logfile->log(6, "%s: %s = %d", logMessage, identifier.toString().c_str(), connection->id);
    }
    return connection;
}

template class ActiveStateConnections<Ipv4Addr>;
template class ActiveStateConnections<Ipv6Addr>;