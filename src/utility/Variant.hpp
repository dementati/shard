#pragma once

#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Weffc++"

#include <cassert>
#include <functional>
#include <memory>
#include <typeindex>

#include "Assert.hpp"

class Variant
{
    public:
        Variant();
        Variant(Variant&& other);
        Variant& operator=(Variant&& other);
        Variant(const Variant& other);
        Variant& operator=(const Variant& other);

        template<typename Type>
        Variant(const Type& data);

        template<typename Type>
        const Type& get() const;

        template<typename Type>
        Type& get();

        template<typename Type>
        void set(const Type& data);

        template<typename Type>
        bool isOfType() const;

        bool isSameTypeAs(const Variant& other) const;
    private:
        std::type_index mStoredType;
        std::shared_ptr<void> mStoredData;
        std::function<std::shared_ptr<void>(std::shared_ptr<void>)> mCopier;
};

template<typename Type>
Variant::Variant(const Type& data) :
    mStoredType(typeid(data))
{
    mStoredData = std::static_pointer_cast<void>(std::make_shared<Type>(data));

    // LCOV_EXCL_START
    mCopier = [](std::shared_ptr<void> data)
    {
        std::shared_ptr<Type> toCopy = std::static_pointer_cast<Type>(data);
        std::shared_ptr<Type> copy = std::make_shared<Type>(*toCopy);
        return std::static_pointer_cast<void>(copy);
    };
    // LCOV_EXCL_STOP
}

template<typename Type>
Type& Variant::get()
{
    ASSERT(mStoredType == typeid(Type), "Trying to get variant as the type " << typeid(Type).name() << " when it is of type " << mStoredType.name());
    ASSERT(mStoredData != nullptr, "Trying to get uninitialised variant");

    return *std::static_pointer_cast<Type>(mStoredData);
}

template<typename Type>
const Type& Variant::get() const
{
    ASSERT(mStoredType == typeid(Type), "Trying to get variant as the type " << typeid(Type).name() << " when it is of type " << mStoredType.name());
    ASSERT(mStoredData != nullptr, "Trying to set uninitialised variant");

    return *std::static_pointer_cast<Type>(mStoredData);
}

template<typename Type>
void Variant::set(const Type& data)
{
    ASSERT(mStoredType == typeid(Type), "Trying to set variant as the type " << typeid(Type).name() << " when it is of type " << mStoredType.name());

    *std::static_pointer_cast<Type>(mStoredData) = data;
}

template<typename Type>
bool Variant::isOfType() const
{
    return mStoredType == typeid(Type);
}
