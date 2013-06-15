#ifndef YHSCRIPT_MODULES_ALL_H_
#define YHSCRIPT_MODULES_ALL_H_

#include "../Module.h"

#include "Constants.h"
#include "Natives.h"
#include "Script.h"
#include "Person.h"

#define MODULES_MODULE_ITEM(name) &name##::s_moduleData

NS_YHSCRIPT_MODULES_BEGIN

static Module* moduleList[]={
    MODULES_MODULE_ITEM(Constants),
    MODULES_MODULE_ITEM(Natives),
    MODULES_MODULE_ITEM(Script),
    MODULES_MODULE_ITEM(PersonModule),
    NULL
};

NS_YHSCRIPT_MODULES_END

#endif //YHSCRIPT_MODULES_ALL_H_