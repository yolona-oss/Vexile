#ifndef IPROPERTY_HPP_INCLUDED
#define IPROPERTY_HPP_INCLUDED

#include <string>

/// Provides the interface for all IEntity properties
class IProperty {
public:
  /// Class that represents the type for this class
  class Type_t {
  private:
    std::string mName;

  public:
    explicit Type_t(std::string theName) : mName(theName) {}
    std::string Name() const { return mName; };
  };

  /**
   * IProperty default constructor
   * @param[in] theType of property this property represents
   * @param[in] thePropertyID to use for this property
   */
  IProperty(std::string theType, const std::string thePropertyID);

  /**
   * IProperty destructor
   */
  virtual ~IProperty();

  /**
   * GetType will return the Type_t type for this property
   * @return the Type_t class for this property
   */
  Type_t *GetType(void);

  /**
   * GetID will return the Property ID used for this property.
   * @return the property ID for this property
   */
  const std::string GetID(void) const;

  /**
   * Update will be called for each IProperty registered with IEntity and
   * enable each IProperty derived class to perform Update related tasks
   * (e.g. frame counter, timer update, decreate in shields, etc).
   */
  virtual void Update() = 0;

  /**
   * MakeClone is responsible for creating a clone of this IProperty
   * derived class and returning it as part of the Prototype and Instance
   * system. The value of the Property will also be copied into the clone.
   * @return pointer to the IProperty derived class clone that was created
   */
  virtual IProperty *MakeClone() = 0;

protected:
  /**
   * SetType is responsible for setting the type of class this IProperty
   * class represents and is usually called by the IProperty derived class
   * to set theType.
   * @param[in] theType to set for this IProperty derived class
   */
  void SetType(std::string theType);

private:
  // Variables
  ///////////////////////////////////////////////////////////////////////////
  /// The type that represents this class
  Type_t mType;
  /// The property ID assigned to this IProperty derived class
  const std::string mPropertyID;
};

#endif // IPROPERTY_HPP_INCLUDED
