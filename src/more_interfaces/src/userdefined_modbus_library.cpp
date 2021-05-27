#include "userdefined_modbus_library.hpp"

modbus_implementation_class::modbus_implementation_class(string host,vector<int> address_list,string connection_type,int port)
{
    modbus_implementation_class::host = host;
    modbus_implementation_class::port = port;
    modbus_implementation_class::address_list = address_list;
    modbus_implementation_class::connection_type = connection_type;
    init();
}

modbus_implementation_class::modbus_implementation_class(string comp_port,vector<int> address_list,string connection_type,int baud,char parity,int data_bits,int bits_stop)
{
    modbus_implementation_class::comp_port = comp_port;
    modbus_implementation_class::address_list = address_list;
    modbus_implementation_class::connection_type = connection_type;
    modbus_implementation_class::baud = baud;
    modbus_implementation_class::parity = parity;
    modbus_implementation_class::data_bits = data_bits;
    modbus_implementation_class::bits_stop = bits_stop;
    init();
}

void modbus_implementation_class::init()
{
    std::string COMMON_FMT("[%TimeStamp%]: %Message%");
    boost::log::add_file_log 
    (
        boost::log::keywords::file_name = "mylogs/%Y_%m_%d_%H_%M_%S_status.log",
        boost::log::keywords::format = COMMON_FMT,
        boost::log::keywords::auto_flush = true,
        boost::log::keywords::rotation_size = 16384
    );
    boost::log::add_common_attributes();
}

float modbus_implementation_class::fun(int addr,modbus_t *ctx)
{       
        uint16_t temporary_array[2];                                                  // temporary storage bay for storing values fetched from registers                                    
        int rc = modbus_read_registers(ctx, addr,2, temporary_array);               // reading from the registers
        float reading=modbus_get_float(temporary_array);                            // converting those values to float 
        cout<<reading<<" "; 
        return reading;   
}

void modbus_implementation_class::read_modbus_fun()
{
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
        BOOST_LOG_TRIVIAL(error) << "An error severity message";                    // terminate if connection fails
        modbus_free(ctx);
    }
    else
        BOOST_LOG_TRIVIAL(info) << "Connection Established";

    reading1=fun(address_list[0],ctx);
    BOOST_LOG_TRIVIAL(info) << "Reading 1 is: "<< reading1;
    reading2=fun(address_list[1],ctx);
    BOOST_LOG_TRIVIAL(info) << "Reading 2 is: "<<reading2;
    reading3=fun(address_list[2],ctx);
    BOOST_LOG_TRIVIAL(info) << "Reading 2 is: "<<reading3;
    
    modbus_close(ctx);                                                              // closing the established connection
    modbus_free(ctx);                                                               // deleting the context
}