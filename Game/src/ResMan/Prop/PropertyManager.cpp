#include "Engine/PropertyManager.hpp"

PropertyManager::PropertyManager()
{
}

PropertyManager::~PropertyManager()
{
        // Make sure to remove all registered properties on desstruction
        std::map<const std::string, IProperty*>::iterator anProptertyIter;
        for(anProptertyIter = mList.begin();
                anProptertyIter != mList.end();
                ++anProptertyIter)
                {
                        IProperty* anProperty = (anProptertyIter->second);
                        delete anProperty;
                        anProperty = NULL;
                }
}

bool PropertyManager::HasID(const std::string thePropertyID)
{
        bool anResult = false;

        // See if thePropertyID was found in our list of properties
        anResult = (mList.find(thePropertyID) != mList.end());

        // Return true if thePropertyID was found above, false otherwise
        return anResult;
}


void PropertyManager::Add(IProperty* theProperty)
{
        if(mList.find(theProperty->GetID()) == mList.end())
        {
                mList[theProperty->GetID()] = theProperty;
        }
}

void PropertyManager::Clone(const PropertyManager& thePropertyManager)
{
        // Make sure to remove all registered properties on desstruction
        std::map<const std::string, IProperty*>::const_iterator anProptertyIter;
        for(anProptertyIter = thePropertyManager.mList.begin();
                anProptertyIter != thePropertyManager.mList.end();
                ++anProptertyIter)
                {
                        IProperty* anProperty = (anProptertyIter->second);
                        Add(anProperty->MakeClone());
                }
}
