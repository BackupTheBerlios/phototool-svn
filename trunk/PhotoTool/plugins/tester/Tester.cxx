
#include <stdio.h>
#include <phototool/PluginBase.h>

extern "C"
int plugin_type()
{
    return PHOTOTOOL_SORT;
}

extern "C" 
int plugin_load()
{
    printf("Loading plugin\n");
    return 0;
}

extern "C" 
int plugin_unload()
{
    printf("Unloading plugin\n");
    return 0;
}

