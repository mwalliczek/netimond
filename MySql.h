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

#ifndef MYSQL_H
#define MYSQL_H

#include <mysql/mysql.h>

#include "Statistics.h"

class MySql {
    MYSQL *mysql_connection;
    MYSQL_STMT *mysql_stmt_bandwidth, *mysql_stmt_connections, *mysql_stmt_content, *mysql_stmt_stats;

    char* mysql_host;
    char* mysql_db;
    char* mysql_username;
    char* mysql_password;
    
    void insertConnectionAndContent(MYSQL_STMT* mysql_stmt, char* buff, short duration, const char* foreign_ip,
        int dst_port, short protocol, const char* text, long long int bytes, short inbound, short intern);
    void init();
    void destroy();
        
    
    public:
        MySql(char* mysql_host, char* mysql_db, char* mysql_username, char* mysql_password);
        ~MySql();
        
        void insertBandwidth(char* buff, short duration, long long int sum, short intern);
        void insertConnection(char* buff, short duration, const char* foreign_ip, int dst_port, short protocol,
            const char* text, long long int bytes, short inbound, short intern);
        void insertContent(char* buff, short duration, const char* foreign_ip, int dst_port, short protocol,
            const char* text, long long int bytes, short inbound, short intern);
        void insertStats(std::string timestamp, Statistics* stat);
};

#endif
