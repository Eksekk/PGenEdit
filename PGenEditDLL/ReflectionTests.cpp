#include "pch.h"
#include "ReflectionTests.h"
#include "Utility.h"
#include "Reflection.h"
#include "LuaWrapper.h"
#include "Asserter.h"

namespace
{
    using VectorType = std::vector<int>;
    using ArrayType = std::array<int, 5>;
    using MapType = std::unordered_map<std::string, int>;
}
struct ReflectionSampleStruct
{
    int i;
    std::string str;
    std::vector<int> vec;
    std::array<int, 5> arr;
    std::unordered_map<std::string, int> map;

    void setArrayWithDefaultArgs(int a, int b, int c = 12, int d = 33, int e = -5)
    {
        arr[0] = a;
        arr[1] = b;
        arr[2] = c;
        arr[3] = d;
        arr[4] = e;
    }
    union UnionSample
    {
        qword_t i;
        float fArray[2];
        double d;
        bool firstByteBool;
        byte_t firstByte;

        // this union and all other reflection test structs will have operators to modify it based on int argument
        // this will allow to modify it generically (for change, then equality testing) with simple int addition
        UnionSample& operator+=(int val)
        {
            i += val;
            return *this;
        }

        UnionSample operator+(int val) const
        {
            UnionSample u2(*this);
            u2.i += val;
            return u2;
        }

        friend std::string to_string(const UnionSample& u);

        // comparison operator for all fields
        bool operator==(const UnionSample& other) const
        {
            return i == other.i && fArray[0] == other.fArray[0] && fArray[1] == other.fArray[1] && d == other.d && firstByteBool == other.firstByteBool && firstByte == other.firstByte;
        }
    } u;
protected:
    int protectedInt;
    void* protectedPtr;
private:
    int privateInt;
    void* privatePtr;
public:
    inline int get5() const
    {
        return 5;
    }

    inline void setInt(int val)
    {
        i = val;
    }

    void modifyMultiple(int val, std::string str, std::vector<int> vec)
    {
        i = val;
        this->str = str;
        this->vec = vec;
    }

    // this method should modify variables by for example adding to them
    void modifyMultipleByOperation(int val, std::string str, std::vector<int> vec)
    {
        i += val;
        this->str += str;
        this->vec.insert(this->vec.end(), vec.begin(), vec.end());
    }

    struct InnerStruct
    {
        bool b, bb, bbb;
        std::string str;
        void allTrue()
        {
            b = true, bb = true, bbb = true;
        }
        void allFalse()
        {
            b = false, bb = false, bbb = false;
        }

        InnerStruct() : b(false), bb(false), bbb(false), str("default") {}
        // default copy ctor
        InnerStruct(const InnerStruct&) = default;
        InnerStruct(InnerStruct&&) = default;
        InnerStruct& operator=(const InnerStruct&) = default;
        InnerStruct& operator=(InnerStruct&&) = default;

        // virtual methods
        virtual int returnSizeof() const
        {
            return sizeof(InnerStruct);
        }

        // in derived class will return double the value
        virtual int addAllArguments(int a, int b, int c, int d) const
        {
            return a + b + c + d;
        }

        // an operator which modifies the struct based on int argument passed to it
        InnerStruct& operator+=(int val)
        {
            str += std::to_string(val);
            return *this;
        }

        InnerStruct operator+(int val) const
        {
            InnerStruct u2(*this);
            u2.str += std::to_string(val);
            return u2;
        }

        friend std::string to_string(const InnerStruct& u);

        // comparison operator for all fields
        bool operator==(const InnerStruct& other) const
        {
            return b == other.b && bb == other.bb && bbb == other.bbb && str == other.str;
        }

        RTTR_ENABLE()
    };

    struct InnerStruct2 : public InnerStruct
    {
        char ch;
        int i;

        virtual int returnSizeof() const override
        {
            return sizeof(InnerStruct2);
        }

        virtual int addAllArguments(int a, int b, int c, int d) const override
        {
            return 2 * (a + b + c + d);
        }

        // an operator += which modifies the struct based on int argument passed to it
        InnerStruct2& operator+=(int val)
        {
            i += val;
            return *this;
        }

        InnerStruct2 operator+(int val) const
        {
            InnerStruct2 u2(*this);
            u2.i += val;
            return u2;
        }

        friend std::string to_string(const InnerStruct2& u);

        // comparison operator for all fields
        bool operator==(const InnerStruct2& other) const
        {
            return ch == other.ch && i == other.i && InnerStruct::operator==(other);
        }

        RTTR_ENABLE(InnerStruct)
    };
    // safeguard
    static_assert(sizeof(InnerStruct) != sizeof(InnerStruct2), "Inner struct sizes are equal, this will break reflection tests");

    InnerStruct inner;
    InnerStruct2 inner2;

    // add constructors like in registration code below
    ReflectionSampleStruct(int i = 0, std::string str = "default", std::vector<int> vec = { 1, 2, 3 }, std::array<int, 5> arr = { 1, 2, 3, 4, 5 }, std::unordered_map<std::string, int> map = { {"a", 1}, {"b", 2}, {"c", 3} }, UnionSample u = { 0 }) : i(i), str(str), vec(vec), arr(arr), map(map), u(u) {}

    // few constructors with default arguments
    ReflectionSampleStruct(bool b, int i = 20, char ch = 'a') : ReflectionSampleStruct() // this call also initializes other fields with default values
    {
        this->i = i + b;
        str = std::string(1, ch);
        vec = { 1, 2, 3 };
        arr = { 1, 2, 3, 4, 5 };
        map = { {"a", 1}, {"b", 2}, {"c", 3} };
        u = { 0 };
    }

    ReflectionSampleStruct(int a, int b, int c = 5, int d = 20) : ReflectionSampleStruct()
    {
        i = a + b + c + d;
        str = "default";
        vec = { 1, 2, 3 };
        arr = { 1, 2, 3, 4, 5 };
        map = { {"a", 1}, {"b", 2}, {"c", 3} };
        u = { 0 };
    }

    // copy ctor
    ReflectionSampleStruct(const ReflectionSampleStruct&) = default;
    
    // a operator += which modifies the struct based on int argument passed to it
    ReflectionSampleStruct& operator+=(int val)
    {
        i += val;
        return *this;
    }

    ReflectionSampleStruct operator+(int val) const
    {
        ReflectionSampleStruct u2(*this);
        u2.i += val;
        return u2;
    }

    // comparison operator for all fields
    bool operator==(const ReflectionSampleStruct& other) const
    {
        return i == other.i && str == other.str && vec == other.vec && arr == other.arr && map == other.map && u == other.u;
    }

    friend std::string to_string(const ReflectionSampleStruct& u);
};

// returns 0 for success, 1 and above for failure (specific error codes)
static int __declspec(naked) __fastcall fastcallGlobalFunctionTest(int argEcx, int argEdx, int argEsp)
{
    __asm
    {
        mov eax, 1
        cmp ecx, 0x77777777
        jne $fail
        inc eax
        cmp edx, 0x3333333
        jne $fail
        inc eax
        cmp dword ptr[esp + 4], 0x88888888
        jne $fail
        mov eax, 0
        ret 4

        $fail:
        ret 4
    }
}

std::string to_string(const ReflectionSampleStruct::UnionSample& u)
{
    // join all fields separated by ;, like this: i=5;
    return wxString::Format("i=%lld;fArray[0]=%f;fArray[1]=%f;d=%f;firstByteBool=%d;firstByte=%d", u.i, u.fArray[0], u.fArray[1], u.d, u.firstByteBool, u.firstByte).ToStdString();
}

std::string to_string(const ReflectionSampleStruct::InnerStruct& u)
{
    // join all fields separated by ;, like this: b=true;bb=false;bbb=true;str=abc;
    return wxString::Format("b=%d;bb=%d;bbb=%d;str=%s", u.b, u.bb, u.bbb, u.str).ToStdString();
}

std::string to_string(const ReflectionSampleStruct::InnerStruct2& u)
{
    // join all fields separated by ;, like this: ch=a;i=5;b=true;bb=false;bbb=true;str=abc;
    return wxString::Format("ch=%c;i=%d;%s", u.ch, u.i, to_string(static_cast<const ReflectionSampleStruct::InnerStruct&>(u)).c_str()).ToStdString();
}

std::string to_string(const ReflectionSampleStruct& u)
{
    // join all fields separated by ;, like this: i=5;str=abc;vec=1,2,3;arr=1,2,3,4,5;map=a:1,b:2,c:3;u=i=5;fArray[0]=1.000000;fArray[1]=2.000000;d=0.000000;firstByteBool=0;firstByte=0;
    return wxString::Format("i=%d;str=%s;vec=%s;arr=%s;map=%s;u=%s", u.i, u.str, containerToString(u.vec), containerToString(u.arr), containerToString(u.map), to_string(u.u)).ToStdString();
}

RTTR_REGISTRATION
{
    using namespace rttr;
    using Inner2 = ReflectionSampleStruct::InnerStruct2;
    using Inner = ReflectionSampleStruct::InnerStruct;
using UnionSample = ReflectionSampleStruct::UnionSample;

    registration::class_<UnionSample>("UnionSample")
.property("i", &UnionSample::i)
        .property("fArray", &UnionSample::fArray)
        .property("d", &UnionSample::d)
        .property("firstByteBool", &UnionSample::firstByteBool)
        .property("firstByte", &UnionSample::firstByte)
        .constructor<>()
.constructor<const UnionSample&>()

        .method("operator+=", static_cast<UnionSample& (UnionSample::*)(int)>(&UnionSample::operator+=))
        .method("operator+", static_cast<UnionSample(UnionSample::*)(int) const>(&UnionSample::operator+))
        .method("operator==", &UnionSample::operator==)
        ;
    registerExtra<UnionSample>();

    registration::class_<Inner2>("InnerStruct2")
        .property("ch", &Inner2::ch)
        .property("i", &Inner2::i)
        .method("returnSizeof", &Inner2::returnSizeof)
        .method("addAllArguments", &Inner2::addAllArguments)
        
        .constructor<>();
registerExtra<Inner2>();

    registration::class_<Inner>("InnerStruct")
        .property("b", &Inner::b)
        .property("bb", &Inner::bb)
        .property("bbb", &Inner::bbb)
        .property("str", &Inner::str)
        .method("allTrue", &Inner::allTrue)
        .method("allFalse", &Inner::allFalse)
        .method("returnSizeof", &Inner::returnSizeof)
        .method("addAllArguments", &Inner::addAllArguments)
        .constructor<>();
registerExtra<Inner>();

    registration::class_<ReflectionSampleStruct>("ReflectionSampleStruct")
        .property("i", &ReflectionSampleStruct::i)
        .property("str", &ReflectionSampleStruct::str)
        .property("vec", &ReflectionSampleStruct::vec)
        .property("arr", &ReflectionSampleStruct::arr)
        .property("map", &ReflectionSampleStruct::map)
        .property("u", &ReflectionSampleStruct::u)
        .property("inner", &ReflectionSampleStruct::inner)
        .property("inner2", &ReflectionSampleStruct::inner2)
        .method("get5", &ReflectionSampleStruct::get5)
        .method("setInt", &ReflectionSampleStruct::setInt)
        .method("modifyMultiple", &ReflectionSampleStruct::modifyMultiple)
        .method("modifyMultipleByOperation", &ReflectionSampleStruct::modifyMultipleByOperation)
        .method("operator+=", static_cast<ReflectionSampleStruct& (ReflectionSampleStruct::*)(int)>(&ReflectionSampleStruct::operator+=))
        .method("operator+", static_cast<ReflectionSampleStruct(ReflectionSampleStruct::*)(int) const>(&ReflectionSampleStruct::operator+))
        .method("operator==", &ReflectionSampleStruct::operator==)
        .method("setArrayWithDefaultArgs", &ReflectionSampleStruct::setArrayWithDefaultArgs)
        .constructor<int, std::string, std::vector<int>, std::array<int, 5>, std::unordered_map<std::string, int>, ReflectionSampleStruct::UnionSample>()(default_arguments(0, std::string("default"), std::vector<int>{ 1, 2, 3 }, std::array<int, 5>{ 1, 2, 3, 4, 5 }, std::unordered_map<std::string, int>{ {"a", 1}, {"b", 2}, {"c", 3} }, ReflectionSampleStruct::UnionSample{ 0 }))
        .constructor<bool, int, char>()(default_arguments(20, 'a'))
        .constructor<int, int, int, int>()(default_arguments(5, 20))
        ;
registerExtra<ReflectionSampleStruct>();
}

template<typename Type>
Type& getPropertyValue(const rttr::type& t, const std::string& name)
{
    return t.get_property(name).get_value().get_value<Type>();
}

// changes provided value by addition operator, works for strings too (concatenates)
template<typename T>
auto increaseBy(const T& val, int by)
{
    if constexpr (SAME_BASE_TYPE(val, std::string))
    {
        return val + std::to_string(by);
    }
    else if constexpr (SAME_BASE_TYPE(val, wxString))
    {
        return val + std::to_string(by);
    }
    else if constexpr (SAME_BASE_TYPE(val, VectorType))
    {
        VectorType vec = val;
        for (auto& i : vec)
        {
            i += by;
        }
        return vec;
    }
    else if constexpr (SAME_BASE_TYPE(val, ArrayType))
    {
        ArrayType arr = val;
        for (auto& i : arr)
        {
            i += by;
        }
        return arr;
    }
    else if constexpr (SAME_BASE_TYPE(val, MapType))
    {
        MapType map = val;
        for (auto& [key, value] : map)
        {
            value += by;
        }
        return map;
    }
    else
    {
        return val + by;
    }
}

template<typename PropType, typename Struct>
void testPropertyGetSet(Asserter& myasserter, Struct& stru, PropType Struct::* propPtr, const std::string& name, int testIndex)
{
    auto prop = rttr::type::get<Struct>().get_property(name);
    auto val = prop.get_value(stru).get_value<PropType>();
    PropType newVal = increaseBy(val, 1);

    constexpr auto tryToString = [](const auto& val) -> std::string
        {
            if constexpr (SAME(decay_fully<decltype(val)>, std::string))
            {
                return val;
            }
            else if constexpr (SAME_BASE_TYPE(val, VectorType) || SAME_BASE_TYPE(val, ArrayType) || SAME_BASE_TYPE(val, MapType))
            {
                return containerToString(val);
            }
            else
            {
                using std::to_string; // allow ADL to work
                return to_string(val);
            }
        };

    // set with reflection
    prop.set_value(stru, newVal);
    //// get with reflection
    PropType val2 = prop.get_value(stru).get_value<PropType>();
    myassertf(val2 == newVal, "[Property '%s' get/set; test #%d] values changed using reflection and obtained with reflection don't match (expected: '%s', actual: '%s')", name, testIndex, tryToString(newVal), tryToString(val2));
    // now do the same, but get property value directly from the struct
    //// get directly
    PropType val3 = stru.*propPtr;
    myassertf(val3 == newVal, "[Property '%s' get/set; test #%d] values changed using reflection and obtained directly don't match (expected: '%s', actual: '%s')", testIndex, name, tryToString(newVal), tryToString(val3));
    // now do the same as above two, but set value with provided pointer
    // set directly
    PropType newVal2 = increaseBy(newVal, 1);
    stru.*propPtr = newVal2;
    //// get with reflection
    PropType val4 = prop.get_value(stru).get_value<PropType>();
    myassertf(val4 == newVal2, "[Property '%s' get/set; test #%d] values changed directly and obtained with reflection don't match (expected: '%s', actual: '%s')", testIndex, name, tryToString(newVal2), tryToString(val4));
    //// get directly
    PropType val5 = stru.*propPtr;
    myassertf(val5 == newVal2, "[Property '%s' get/set; test #%d] values changed directly and obtained directly don't match (expected: '%s', actual: '%s')", testIndex, name, tryToString(newVal2), tryToString(val5));
}

std::vector<wxString> ReflectionTests::run()
{
    Asserter myasserter("Reflection");
    using namespace rttr;
    int testIndex = 0;
    // property iteration

    auto reflType = type::get("ReflectionSampleStruct");
    using Inner = ReflectionSampleStruct::InnerStruct;
    using Inner2 = ReflectionSampleStruct::InnerStruct2;
    ReflectionSampleStruct rss;
    // call testPropertyGetSet for all properties of 'rss', without using a loop
    testPropertyGetSet(myasserter, rss, &ReflectionSampleStruct::i, "i", testIndex++);
    testPropertyGetSet(myasserter, rss, &ReflectionSampleStruct::str, "str", testIndex++);
    testPropertyGetSet(myasserter, rss, &ReflectionSampleStruct::vec, "vec", testIndex++);
    testPropertyGetSet(myasserter, rss, &ReflectionSampleStruct::arr, "arr", testIndex++);
    testPropertyGetSet(myasserter, rss, &ReflectionSampleStruct::map, "map", testIndex++);
    testPropertyGetSet(myasserter, rss, &ReflectionSampleStruct::u, "u", testIndex++);
    testPropertyGetSet(myasserter, rss, &ReflectionSampleStruct::inner, "inner", testIndex++);
    testPropertyGetSet(myasserter, rss, &ReflectionSampleStruct::inner2, "inner2", testIndex++);

    // methods, in particular using Reflection class for tests
// 	auto unpackParamsFromLuaTableToStack = [](const LuaTable& t)
// 		{
// 			int stack = luaWrapper.gettop();
// 			luaWrapper.getglobal("unpack");
// 		};

    // test calling methods with reflection

    static const wxString callMethodIntCheckFormat = "[call methods with reflection; test #%d] incorrect result (expected: %d, actual: %d)";
    testIndex = 0;
    auto result = Reflection::callInstanceMethodWithLuaParams(&rss, "get5", 0);
    myassertf(result == 5, callMethodIntCheckFormat, testIndex++, 5, result.get_value<int>());
    luaWrapper.pushnumber(10.0); // also test implicit conversion to int
    result = Reflection::callInstanceMethodWithLuaParams(&rss, "setInt", 1);
    myassertf(rss.i == 10, callMethodIntCheckFormat, testIndex++, 10, rss.i);
    luaWrapper.pushnumber(-2);
    Reflection::callInstanceMethodWithLuaParams(&rss, "setInt", 1);
    myassertf(rss.i == -2, callMethodIntCheckFormat, testIndex++, -2, rss.i);
    //result = Reflection::callInstanceMethodWithLuaParams(&rss, 

    // test constructors
    testIndex = 0;
    static const wxString constructorCheckFormat = "[constructors; test #%d] incorrect result (expected: %s, actual: %s)";
    // helper to avoid null pointer problems when accessing the created instance (constructor could not be found)
    auto checkNonNull = [&](const std::shared_ptr<ReflectionSampleStruct>& p)
        {
            myassertf(p != nullptr, constructorCheckFormat, testIndex, "not null", "null");
            return p != nullptr;
        };
    auto checkVariantValid = [&](const rttr::variant& var)
        {
            myassertf(var.is_valid(), constructorCheckFormat, testIndex, "valid", "invalid");
            return var.is_valid();
        };
    // skip fully reflective object creation for now, because I don't know how to convert arbitrary rttr variant to string, and don't want to write a lot of code for this/accept that something I made is not working fully :)
    luaWrapper.pushnumber(5).pushstring("abc");
    std::shared_ptr<ReflectionSampleStruct> pValue(Reflection::createInstanceByConstructorFromLuaStack<ReflectionSampleStruct>(2));
    if (checkNonNull(pValue))
    {
        myassertf(pValue->i == 5 && pValue->str == "abc", constructorCheckFormat, testIndex, "i = 5; str = abc;", to_string(*pValue).c_str());
    }
    ++testIndex;
    luaWrapper.pushnumber(5).pushnumber(3);
    pValue = Reflection::createInstanceByConstructorFromLuaStack<ReflectionSampleStruct>(2);
    if (checkNonNull(pValue))
    {
        myassertf(pValue->i == 5 + 3 + 20 + 5, constructorCheckFormat, testIndex, "i = 5 + 3 + 20 + 5", to_string(*pValue).c_str());
    }
    ++testIndex;
    luaWrapper.pushboolean(true);
    pValue = Reflection::createInstanceByConstructorFromLuaStack<ReflectionSampleStruct>(1);
    if (checkNonNull(pValue))
    {
        myassertf(pValue->i == 21 && pValue->str == "a", constructorCheckFormat, testIndex, "i = 21; str = a;", to_string(*pValue).c_str());
    }
    ++testIndex;
    luaWrapper.pushboolean(true);
    rttr::variant var = Reflection::createInstanceByConstructorFromLuaStack("ReflectionSampleStruct", 1);
    if (checkVariantValid(var))
    {
        pValue = var.get_value<std::shared_ptr<ReflectionSampleStruct>>();
        myassertf(pValue->i == 21 && pValue->str == "a", constructorCheckFormat, testIndex, "i = 21; str = a;", to_string(*pValue).c_str());
        // now similar to above, but get all fields reflectively
        auto type = var.get_type();
        auto reflI = type.get_property_value("i", var);
        int i = -1;
        auto reflStr = type.get_property_value("str", var);
        std::string str;
        // check that variant is correct and set variable to value
        if (reflI.is_type<int>())
        {
            i = reflI.get_value<int>();
        }
        else
        {
           myasserter.failFormat("[constructors; test #%d] couldn't get proper value of 'i' reflectively (got '%s', expected '%s')", testIndex, reflI.get_type().get_name().data(), "int");
        }

        if (reflStr.is_type<std::string>())
        {
            str = reflStr.get_value<std::string>();
        }
        else
        {
            myasserter.failFormat("[constructors; test #%d] couldn't get proper value of 'str' reflectively (got '%s', expected '%s')", testIndex, reflStr.get_type().get_name().data(), "std::string");
        }

        
        myassertf(i == 21 && str == "a", constructorCheckFormat, testIndex, "i = 21; str = a;", std::format("i = {}, str = {};", i, str));
    }
    ++testIndex;
    // provide custom int, string, vector
    luaWrapper.pushnumber(55).pushstring("ddde");
    LuaTable::constructFromValuesWithArray({ 2, 3, 5 }).pushToLuaStack();
    pValue = Reflection::createInstanceByConstructorFromLuaStack<ReflectionSampleStruct>(3);
    if (checkNonNull(pValue))
    {
        // extra parentheses to avoid commas inside initializer list, which break the macro
        myassertf((pValue->i == 55 && pValue->str == "ddde" && pValue->vec == VectorType{ 2, 3, 5 }), constructorCheckFormat, testIndex, "i = 55; str = ddde; vec = {2,3,5};", to_string(*pValue).c_str());
        Inner* inner = &pValue->inner2;
        myassertf(Reflection::callInstanceMethodWithLuaParams(inner, "returnSizeof", 0).get_value<int>() == sizeof(Inner2), "[constructors; test #%d] virtual method call with reflection failed", testIndex);
    }
    ++testIndex;

    // manipulate LuaTable class 100% reflectively

    return myasserter.errors;
}