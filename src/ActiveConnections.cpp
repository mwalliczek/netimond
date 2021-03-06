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

#include "ActiveConnections.h"

#include "netimond.h"
#include "Logfile.h"
#include "Ipv4Addr.h"
#include "Ipv6Addr.h"

template<typename IP>
ActiveConnections<IP>::ActiveConnections(std::list<Subnet<IP>> const & interns, std::list<Subnet<IP>> const & selfs):
        interns(interns), selfs(selfs), suspiciousEvents(SuspiciousEvents<IP>::getInstance()) {
    if (LOG_CHECK_DEBUG()) {
        std::string internsString;
        for (auto &intern : this->interns ) {
            internsString += " " + intern.toString();
        }
        LOG_DEBUG("interns:%s", internsString.c_str());
        std::string selfsString;
        for (auto &self : this->selfs ) {
            selfsString += " " + self.toString(); 
        }
        LOG_DEBUG("selfs:%s", selfsString.c_str());
    }
}

template<typename IP>
bool ActiveConnections<IP>::isIntern(IP const & ip) const {
    for(auto internIter : interns) {
        if (internIter.match(ip)) {
            return true;
        }
    }
    return false;
}

template<typename IP>
bool ActiveConnections<IP>::isSelf(IP const & ip) const {
    for(const auto selfIter : selfs) {
        if (selfIter.match(ip)) {
            return true;
        }
    }
    return false;
}

template<typename IP>
Connection* ActiveConnections<IP>::createSimpleConnection(IP const & ip_src, IP const & ip_dst, u_char protocol) const {
    bool inbound = isSelf(ip_dst);
    bool intern = inbound ? isIntern(ip_src) : isIntern(ip_dst);
    return new Connection(std::shared_ptr<IpAddr>(inbound ? new IP(ip_src) : new IP(ip_dst)), protocol, inbound, intern);
}

template<typename IP>
void ActiveConnections<IP>::handlePacket(IP const & ip_src, IP const & ip_dst, uint16_t ip_len, u_char protocol) const {
    Connection* connection = createSimpleConnection(ip_src, ip_dst, protocol);
    connection->handleData(ip_len);
    connection->stop();
}

template class ActiveConnections<Ipv4Addr>;
template class ActiveConnections<Ipv6Addr>;
