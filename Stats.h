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

#ifndef STATS_H
#define STATS_H

#include "MySql.h"
#include "Statistics.h"

class Stats {
    std::map<std::string, Statistics*> statistics;
    std::string lastStatsTimestamp;
    MySql* mysql_connection;
    
    public:
        Stats(MySql* mysql_connection);
        void cleanup(char *statsbuff);
        void insert(char *statsbuff, int dst_port, int protocol, bool intern, bool inbound, long long int sum);
};

#endif