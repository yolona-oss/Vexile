#ifndef PROPERTY_MANAGER_HPP_INCLUDED
#define PROPERTY_MANAGER_HPP_INCLUDED

#include "./IProperty.hpp"
#include "./TProperty.hpp"
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>

/// Provides the PropertyManager class for managing IProperty classes
class PropertyManager {
public:
  /**
   * PropertyManager default constructor
   */
  PropertyManager();

  /**
   * PropertyManager deconstructor
   */
  virtual ~PropertyManager();

  /**
   * HasProperty returs true if thePropertyID specified exists in this
   * PropertyManager.
   * @param[in] thePropertyID to lookup in this PropertyManager
   * @return true if thePropertyID exists, false otherwise
   */
  bool HasID(const std::string thePropertyID);

  /**
   * GetProperty returns the property as type with the ID of thePropertyID.
   * @param[in] thePropertyID is the ID of the property to return.
   * @return the value stored in the found propery in the form of TYPE. If no
   * Property was found it returns the default value the type constructor.
   */
  template <class TYPE> TYPE Get(const std::string thePropertyID) {
    if (mList.find(thePropertyID) != mList.end()) {
      if (mList.at(thePropertyID)->GetType()->Name() == typeid(TYPE).name())
        return static_cast<TProperty<TYPE> *>(mList[thePropertyID])->GetValue();
    } else {
      std::cout << "PropertyManager:Get() returning blank property(" << thePropertyID << ") type"
                << std::endl;
    }
    TYPE anReturn = TYPE();
    return anReturn;
  }

  /**
   * SetProperty sets the property with the ID of thePropertyID to theValue.
   * @param[in] thePropertyID is the ID of the property to set.
   * @param[in] theValue is the value to set.
   */
  template <class TYPE> void Set(const std::string thePropertyID, TYPE theValue) {
    if (mList.find(thePropertyID) != mList.end()) {
      if (mList.at(thePropertyID)->GetType()->Name() == typeid(TYPE).name()) {
        static_cast<TProperty<TYPE> *>(mList[thePropertyID])->SetValue(theValue);
      }
    } else {
      std::cerr << "PropertyManager:Set() unable to find property(" << thePropertyID << ")"
                << std::endl;
    }
  }

  /**
   * AddProperty Creates a Property and addes it to this entity.
   * @param[in] thePropertyID is the ID of the property to create.
   * @param[in] theValue is the inital value to set.
   */
  template <class TYPE> void Add(const std::string thePropertyID, TYPE theValue) {
    // Only add the property if it doesn't already exist
    if (mList.find(thePropertyID) == mList.end()) {
      TProperty<TYPE> *anProperty = new (std::nothrow) TProperty<TYPE>(thePropertyID);
      anProperty->SetValue(theValue);
      mList[anProperty->GetID()] = anProperty;
    }
  }

  /**
   * AddProperty gets a premade Property and addes it to this entity.
   * @param[in] theProperty is a pointer to a pre exisiting property.
   */
  void Add(IProperty *theProperty);

  /**
   * Clone is responsible for making a clone of each property in the
   * PropertyManager provided.
   * @param[in] thePropertyManager to clone into ourselves
   */
  void Clone(const PropertyManager &thePropertyManager);

protected:
private:
  // Variables
  ///////////////////////////////////////////////////////////////////////////
  /// A map of all Properties available for this PropertyManager class
  std::map<const std::string, IProperty *> mList;
}; // PropertyManager class
#endif
