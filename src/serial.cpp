#include <iostream>
#include <string>
#include <fstream>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#ifndef CONF_XML_PATH
#define CONF_XML_PATH "../conf/serializer.xml"
#endif

using namespace std;

class connParams
{
    public:
        connParams() { std::cout << "ConnParams CTOR" << std::endl; }
        std::string mAddress, mConnType;
        int mPort;

    private:
        friend class boost::serialization::access;
        template<class archive>
        void serialize(archive& ar, const unsigned int version)
        {
            using boost::serialization::make_nvp;
            ar & make_nvp("Address", mAddress);
            ar & make_nvp("Port", mPort);
            ar & make_nvp("ConnType", mConnType);
        }
};

void local_assert(bool expression, std::string MsgHelp)
{
    if(!expression) {
        std::cout << MsgHelp << std::endl;
        abort();
    }
}


void saveConnParams(const connParams& cp, const string& file_name)
{
    std::ofstream ofs(file_name, std::ofstream::trunc | std::ofstream::out);
    local_assert(ofs.good(), "output xml configuration file not found");
    try {
        boost::archive::xml_oarchive xml(ofs);
        xml << boost::serialization::make_nvp("Connection", cp);
    }catch (exception e) {
        std::cerr << "Saving Conn Params failed: " << e.what() << std::endl;
    }
}



connParams loadConnParams(const string& file_name)
{
    connParams cp;
    std::ifstream ifs(file_name, std::ifstream::binary | std::ifstream::in);
    local_assert(ifs.good(), "input xml configuration file not found");
    try {
         boost::archive::xml_iarchive xml(ifs);
         xml >> boost::serialization::make_nvp("Connection", cp);
    }catch (exception e) {
         std::cerr << "Loading Comm Params Failed: " << e.what() << std::endl;
    }
    return cp;
}

void load_configuration(const char * cpucConfPath)
{
    local_assert(cpucConfPath != NULL, "Configuration File Not found");
    connParams PrgParams = loadConnParams(std::string(cpucConfPath));
    cout << "Conn Address : " << PrgParams.mAddress << std::endl;
    cout << "Conn Port : " << PrgParams.mPort << std::endl;
    cout << "Conn Type : " << PrgParams.mConnType << std::endl;
}

int main()
{
    load_configuration(CONF_XML_PATH);

    connParams PrgParams;
    PrgParams.mAddress = "10.102.252.8";
    PrgParams.mPort = 7777;
    PrgParams.mConnType = "UDP";
    (void)saveConnParams(PrgParams, CONF_XML_PATH);
    return 0;
}
