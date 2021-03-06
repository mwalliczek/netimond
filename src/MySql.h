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

#include <vector>

#include <mysql/mysql.h>

#include "Statistics.h"

class MySql {
    MYSQL *mysql_connection;
    MYSQL_STMT *mysql_stmt_bandwidth;
    MYSQL_STMT *mysql_stmt_connections;
    MYSQL_STMT *mysql_stmt_insert_stats;
    MYSQL_STMT *mysql_stmt_select_stats;
    MYSQL_STMT *mysql_stmt_number_stats;
    MYSQL_STMT *mysql_stmt_cleanup_connections;
    MYSQL_STMT *mysql_stmt_cleanup_stats;

    const char* mysql_host;
    const char* mysql_db;
    const char* mysql_username;
    const char* mysql_password;
    
    static void mapProtocol(short protocol, unsigned long *str_length, MYSQL_BIND* bind);
    
    void init();
    void destroy();
    
    MYSQL_STMT* initStmt(const char* stmt);
    void bindAndExecute(MYSQL_STMT* stmt, MYSQL_BIND* bind);
    
    public:
        explicit MySql(const char* mysql_host, const char* mysql_db, const char* mysql_username, 
                const char* mysql_password);
        MySql(const MySql&) = delete;
        ~MySql();
        
        void insertBandwidth(char* buff, short duration, long long int sum, short intern);
        void insertConnection(char* buff, short duration, const char* foreign_ip, int dst_port, short protocol,
            const char* process, const char* content, long long int bytes, short inbound, short intern);
        void insertStats(char* buff, Statistics* stat);
        std::vector<long long int>* lookupStats(char* buff, int dst_port, int protocol, bool intern, bool inbound);
        int lookupNumberStats(char* buff);
        void cleanupConnections(int days);
        void cleanupStats(int months);
        static const char* protocolName(short protocol);
};

#endif
