#include "VirtualQCHttp.h"
#include "QuantumCloudHTTP.h"


VirtualQCHttp::VirtualQCHttp()
{
}


VirtualQCHttp::~VirtualQCHttp()
{
}

/*****************************************************************************************************************
Name:        createQCHttp
Description: create quantum http class
Argin:       sKeyFilePath   key file path
Argout:      None  
return:      true or false
*****************************************************************************************************************/
VirtualQCHttp * createQCHttp(std::string &sKeyFilePath)
{
    return (VirtualQCHttp *)new QuantumCloudHTTP(sKeyFilePath);
}

/*****************************************************************************************************************
Name:        destroyQCHttp
Description: destroy quantum http class
Argin:       pVQCHttp   virtual quantum http class pointer
Argout:      None  
return:      true or false
*****************************************************************************************************************/
bool destroyQCHttp(VirtualQCHttp * pVQCHttp)
{
    delete(pVQCHttp);
    return true;
}
