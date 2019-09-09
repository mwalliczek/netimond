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

#ifndef INTERN_NET_H
#define INTERN_NET_H

#include <string>

template<typename IP>
class InternNet {
    IP ip, mask;
    IP calcMask(std::string bits);
    
    public:
        InternNet(std::string ip, std::string mask);
        bool match(IP ip) const;
        bool valid;
        std::string toString();
};

template<typename IP>
std::string InternNet<IP>::toString() {
    return ip.toString() + "/" + mask.toString();
}

template<typename IP>
InternNet<IP>::InternNet(std::string ip, std::string mask): ip(IP(ip)), mask(IP(mask)) {
    if (this->ip.empty()) {
        valid = false;
    } else {
        if (!this->mask.empty()) {
            valid = true;
        } else {
            this->mask = calcMask(mask);
            valid = !this->mask.empty();
        }
    }
}

template<typename IP>
bool InternNet<IP>::match(IP ip) const {
    return (ip & this->mask) == this->ip;
}

#endif