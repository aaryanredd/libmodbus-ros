#include<modbus.h>
#include<iostream>
#include<stdio.h>
#include<string>
#include<bits/stdc++.h>
using namespace std;
class modbus_implementation_class
{
    public:
        modbus_implementation_class(string,vector<int>,string,int);                       
        modbus_implementation_class(string,vector<int>,string,int,char,int,int);                   
        string host,connection_type,comp_port;                                                      
        vector<int> address_list;
        int baud,bits_stop,data_bits,port;
        char parity;
        void read_modbus_fun();        
};