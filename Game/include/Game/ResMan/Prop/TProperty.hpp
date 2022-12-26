#ifndef TPROPERTY_HPP_INCLUDED
#define TPROPERTY_HPP_INCLUDED

#include "./IProperty.hpp"
#include <typeinfo>

/// The Template version of the IProperty class for custom property values
template <class TYPE = unsigned int> class TProperty : public IProperty {
public:
  /**
   * TProperty default constructor
   * @param[in] thePropertyID to use for this property
   */
  TProperty(const std::string thePropertyID) : IProperty(typeid(TYPE).name(), thePropertyID) {}

  /**
   * GetValue will return the property value
   * @return the property value
   */
  TYPE GetValue() { return mValue; }

  /**
   * SetValue will set the property value to the value
   * provided.
   */
  void SetValue(TYPE theValue) { mValue = theValue; }

  /**
   * Update will be called giving each property a chance to change itself
   * during the Update phase of the GameLoop (see IEntity::UpdateFixed)
   */
  void Update() {}

  /**
   * MakeClone is responsible for creating a clone of this IProperty
   * derived class and returning it as part of the Prototype and Instance
   * system. The value of the Property will also be copied into the clone.
   * @return pointer to the IProperty derived class clone that was created
   */
  IProperty *MakeClone() {
    TProperty<TYPE> *anProperty = new (std::nothrow) TProperty<TYPE>(GetID());

    // Make sure new didn't fail before setting the value for this property
    if (NULL != anProperty) {
      anProperty->SetValue(mValue);
    }

    // Return cloned anProperty or NULL if none was created
    return anProperty;
  }

private:
  TYPE mValue;
};
#endif // TPROPERTY_HPP_INCLUDED
