// /////////////////////////////////////////////////////////////////
// Generated by axel-plugin wizard
// /////////////////////////////////////////////////////////////////

/* (C) MyCompany */


/* Put a short description of your plugin here */

/* MyCompany-contact@mycompany.com-http://www.mycompany.com */

#include "MyPluginDefaultData.h"

#include <dtkCore/dtkAbstractDataFactory.h>

// /////////////////////////////////////////////////////////////////
// MyPluginDefaultDataPrivate
// /////////////////////////////////////////////////////////////////

class MyPluginDefaultDataPrivate
{
    
};


// /////////////////////////////////////////////////////////////////
// MyPluginDefaultData
// /////////////////////////////////////////////////////////////////

MyPluginDefaultData::MyPluginDefaultData(void) : axlAbstractData(), d(new MyPluginDefaultDataPrivate)
{
    
}

MyPluginDefaultData::~MyPluginDefaultData(void)
{
    delete d;
    
    d = NULL;
}


bool MyPluginDefaultData::registered(void)
{
    return MyPluginPlugin::dataFactSingleton->registerDataType("MyPluginDefaultData", createMyPluginDefaultData);
}

QString MyPluginDefaultData::description(void) const
{
    QString result = "MyPluginDefaultData : Description...";
    
    return result;
}

QString MyPluginDefaultData::identifier(void) const
{
    return "MyPluginDefaultData";
}

QString MyPluginDefaultData::objectType(void) const
{
    return "axlAbstractData";
}

// /////////////////////////////////////////////////////////////////
// Type instanciation
// /////////////////////////////////////////////////////////////////

dtkAbstractData *createMyPluginDefaultData(void)
{
    return new MyPluginDefaultData;
}

