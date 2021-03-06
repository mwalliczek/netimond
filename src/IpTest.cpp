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

#include <arpa/inet.h>

#include <cppunit/extensions/HelperMacros.h>

#include "netimond.h"

#include "Ip.h"

class ipTest : public CPPUNIT_NS::TestFixture
{
 CPPUNIT_TEST_SUITE( ipTest );
 CPPUNIT_TEST( testPing );
 CPPUNIT_TEST( testSyn );
 CPPUNIT_TEST( testUdp );
 CPPUNIT_TEST( testPing6 );
 CPPUNIT_TEST( testSyn6 );
 CPPUNIT_TEST_SUITE_END();

 public:
  void testPing();
  void testSyn();
  void testUdp();
  void testPing6();
  void testSyn6();
};

CPPUNIT_TEST_SUITE_REGISTRATION( ipTest );

const unsigned char ping[] = { 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x45, 0x00,
    0x00, 0x54, 0x10, 0xa4, 0x40, 0x00, 0x40, 0x01, 0x2c, 0x03, 0x7f, 0x00, 0x00, 0x01, 0x7f, 0x00,
    0x00, 0x01, 0x08, 0x00, 0xc5, 0x02, 0x4c, 0x44, 0x00, 0x01, 0x56, 0xd9, 0x46, 0x5d, 0x00, 0x00,
    0x00, 0x00, 0x8a, 0xae, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
    0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25,
    0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35,
    0x36, 0x37 };

const unsigned char syn[] = { 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x45, 0x10,
    0x00, 0x3c, 0xcb, 0x9a, 0x40, 0x00, 0x40, 0x06, 0x71, 0x0f, 0x0a, 0x1f, 0x01, 0x64, 0x0a, 0x45,
    0x01, 0x01, 0x89, 0x88, 0x00, 0x19, 0x31, 0xf6, 0x1e, 0x43, 0x00, 0x00, 0x00, 0x00, 0xa0, 0x02,
    0xaa, 0xaa, 0xfe, 0x30, 0x00, 0x00, 0x02, 0x04, 0xff, 0xd7, 0x04, 0x02, 0x08, 0x0a, 0x0b, 0xb1,
    0xa1, 0x49, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x07 };

// 10.31.1.100.53795 > 10.69.1.1.53: 41416+ [1au] A? www.google.de. (54)
const unsigned char udp[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x45, 0x00,
    0x00, 0x52, 0xe9, 0x06, 0x00, 0x00, 0x40, 0x11, 0xaa, 0x27, 0x0a, 0x1f, 0x01, 0x64, 0x0a, 0x45,
    0x01, 0x01, 0xd2, 0x23, 0x00, 0x35, 0x00, 0x3e, 0xe7, 0xbc, 0xa1, 0xc8, 0x01, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x77, 0x77, 0x77, 0x06, 0x67, 0x6f, 0x6f, 0x67, 0x6c,
    0x65, 0x02, 0x64, 0x65, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x29, 0x05, 0x98, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x0c, 0x00, 0x0a, 0x00, 0x08, 0xc4, 0x5f, 0x34, 0xdd, 0x5f, 0xad, 0x28, 0xbe };
    
const unsigned char ping6[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x86, 0xdd, 0x60, 0x06,
    0x7e, 0x88, 0x00, 0x40, 0x3a, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x22, 0xdc, 0x20, 0xc3, 0x00, 0x01, 0xc4, 0xf7,
    0x46, 0x5d, 0x00, 0x00, 0x00, 0x00, 0x6a, 0xbb, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x11,
    0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21,
    0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31,
    0x32, 0x33, 0x34, 0x35, 0x36, 0x37 };

const unsigned char syn6[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x86, 0xdd, 0x60, 0x09,
    0x6f, 0x49, 0x00, 0x28, 0x06, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xcb, 0x3a, 0x00, 0x19, 0x1c, 0x3b, 0x30, 0x23, 0x00, 0x00,
    0x00, 0x00, 0xa0, 0x02, 0xaa, 0xaa, 0x00, 0x30, 0x00, 0x00, 0x02, 0x04, 0xff, 0xc4, 0x04, 0x02,
    0x08, 0x0a, 0x12, 0xf0, 0xa5, 0xa2, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x07 };

void ipTest::testPing() {
    ConfigfileParser* config = new ConfigfileParser("testConfigMock.conf");
    ip = new Ip(config);
    Ip::got_packet((u_char*) ip, NULL, ping);
    CPPUNIT_ASSERT(allConnections.size() == 1);
    Connection* con = allConnections.begin()->second;
    CPPUNIT_ASSERT(con->protocol == 1);
    CPPUNIT_ASSERT(con->ip->toString() == "127.0.0.1");
    delete con;
    allConnections.clear();
    delete ip;
    delete config;
}

void ipTest::testSyn() {
    ConfigfileParser* config = new ConfigfileParser("testConfigMock.conf");
    ip = new Ip(config);
    Ip::got_packet((u_char*) ip, NULL, syn);
    CPPUNIT_ASSERT(allConnections.size() == 1);
    Connection* con = allConnections.begin()->second;
    CPPUNIT_ASSERT(con->protocol == 6);
    CPPUNIT_ASSERT(con->ip->toString() == "10.69.1.1");
    CPPUNIT_ASSERT(con->intern == true);
    CPPUNIT_ASSERT(con->inbound == false);
    delete con;
    allConnections.clear();
    delete ip;
    delete config;
}

void ipTest::testUdp() {
    ConfigfileParser* config = new ConfigfileParser("testConfigMock.conf");
    ip = new Ip(config);
    Ip::got_packet((u_char*) ip, NULL, udp);
    CPPUNIT_ASSERT(allConnections.size() == 1);
    Connection* con = allConnections.begin()->second;
    CPPUNIT_ASSERT(con->protocol == 17);
    CPPUNIT_ASSERT(con->ip->toString() == "10.69.1.1");
    CPPUNIT_ASSERT(con->intern == true);
    CPPUNIT_ASSERT(con->inbound == false);
    CPPUNIT_ASSERT(con->dst_port == 53);
    delete con;
    allConnections.clear();
    delete ip;
    delete config;
}

void ipTest::testPing6() {
    ConfigfileParser* config = new ConfigfileParser("testConfigMock.conf");
    ip = new Ip(config);
    Ip::got_packet((u_char*) ip, NULL, ping6);
    CPPUNIT_ASSERT(allConnections.size() == 1);
    Connection* con = allConnections.begin()->second;
    CPPUNIT_ASSERT(con->protocol == 58);
    CPPUNIT_ASSERT(con->ip->toString() == "::1");
    delete con;
    allConnections.clear();
    delete ip;
    delete config;
}

void ipTest::testSyn6() {
    ConfigfileParser* config = new ConfigfileParser("testConfigMock.conf");
    ip = new Ip(config);
    Ip::got_packet((u_char*) ip, NULL, syn6);
    CPPUNIT_ASSERT(allConnections.size() == 1);
    Connection* con = allConnections.begin()->second;
    CPPUNIT_ASSERT(con->protocol == 6);
    CPPUNIT_ASSERT(con->ip->toString() == "::1");
    CPPUNIT_ASSERT(con->intern == false);
    CPPUNIT_ASSERT(con->inbound == false);
    delete con;
    allConnections.clear();
    delete ip;
    delete config;
}

