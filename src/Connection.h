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

#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>
#include <ctime>
#include <memory>

#include "IpAddr.h"

class Connection {
    bool payload;
    
    public:
        Connection(std::shared_ptr<IpAddr> ip, u_short dst_port, u_char protocol, std::string process, bool inbound, bool intern);
        Connection(std::shared_ptr<IpAddr> ip, u_char protocol, bool inbound, bool intern);
        void stop();
        void handleData(unsigned int len);
        void handleData(unsigned int len, const u_char *payload, unsigned int size_payload);
        int id;
        bool ack;
        time_t lastAct;
        time_t end;
        bool alreadyRunning;
        std::string content;
        std::shared_ptr<IpAddr> ip;
        u_short dst_port;
        time_t begin;
        u_char protocol;
        std::string process;
        bool inbound;
        bool intern;
        long long unsigned int dataLength;
};

#endif
