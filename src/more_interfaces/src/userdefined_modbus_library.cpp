// include our custom made library
#include "userdefined_modbus_library.hpp"

// constructor for our modbus implementation class in TCP mode
modbus_implementation_class::modbus_implementation_class(string host,vector<int> address_list,string connection_type,int port)
{
    modbus_implementation_class::host = host;
    modbus_implementation_class::port = port;
    modbus_implementation_class::address_list = address_list;
    modbus_implementation_class::connection_type = connection_type;
}

// constructor for our modbus implementation class in RTU mode
modbus_implementation_class::modbus_implementation_class(string comp_port,vector<int> address_list,string connection_type,int baud,char parity,int data_bits,int bits_stop)
{
    modbus_implementation_class::comp_port = comp_port;
    modbus_implementation_class::address_list = address_list;
    modbus_implementation_class::connection_type = connection_type;
    modbus_implementation_class::baud = baud;
    modbus_implementation_class::parity = parity;
    modbus_implementation_class::data_bits = data_bits;
    modbus_implementation_class::bits_stop = bits_stop;
}

// class definition
void modbus_implementation_class::read_modbus_fun()
{
    uint16_t temporary_array[2];                                                    // temporary storage bay for storing values fetched from registers                                    
    modbus_t *ctx;                                                                  // modbus pointer that will contain the context
    char *ptr;                                                                      // pointer to string
    cout<<"connection type is "<<connection_type;                                   
    if(connection_type=="TCP")                                                      
    {   
        ptr= &host[0];                                                              // setting pointer to point to the host address string for TCP  
        ctx = modbus_new_tcp(ptr, port);                                            // declaring about the connection
    }
    else
    {
        ptr= &comp_port[0];                                                         // setting pointer to point to the host address string for RTU
        ctx= modbus_new_rtu(ptr,baud,parity,data_bits,bits_stop);                   // decalring the connection 
    }
    modbus_set_debug(ctx,1);                                                        // setting debug flag on                    
    modbus_set_slave(ctx,1);                                                        // setting slave id to read from

    if (modbus_connect(ctx) == -1) 
    {
        cout<<"Connection Failed"<<"\n";                                            // terminate if connection fails
        modbus_free(ctx);
    }
     
    for(int i=0;i<address_list.size();i++)
    {   
        int rc = modbus_read_registers(ctx, address_list[i], 2, temporary_array);   // reading from the registers
        float reading=modbus_get_float(temporary_array);                            // converting those values to float 
        cout<<reading<<" ";                                                         // displaying the read values
    }

    modbus_close(ctx);                                                              // closing the established connection
    modbus_free(ctx);                                                               // deleting the context
}