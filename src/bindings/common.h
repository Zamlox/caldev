/**
 * Author: 		Iosif Haidu
 * Description: Common types for bindings
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __BIND_COMMON_H__
#define __BIND_COMMON_H__

namespace Bind
{

class Param0
{
public:
};

template <typename T1>
class Param1
{
public:
    Param1()
        : pValue1{nullptr}
    {}
    Param1(Param1 const& rValP)
    {
        *this = rValP;
    }
    Param1(T1 const& rValP)
    {
        setValue1(rValP);
    }
    Param1& operator=(Param1 const& rOpP)
    {
        if (rOpP.pValue1 == nullptr)
            reset();
        else
            setValue1(rOpP.value1);
        return *this;
    }
    Param1& operator=(T1 const& rOpP)
    {
        setValue1(rOpP);
        return *this;
    }
    Param1& operator=(void*)
    {
        reset();
        return *this;
    }
    bool operator==(Param1<T1> const& rOpP)
    { return value1 == rOpP.value1; }
    bool operator!=(Param1<T1> const& rOpP)
    { return value1 != rOpP.value1; }

    void reset()
    { pValue1 = nullptr; }
    T1* getValue1() const
    { return pValue1; }
    void setValue1(T1 const& rValueP)
    {
        value1 = rValueP;
        pValue1 = &value1;
    }

private:
    T1  value1, *pValue1;
};

template <typename T1, typename T2>
class Param2
{
public:
    Param2()
        : pValue1{nullptr}
        , pValue2{nullptr}
    {}
    void reset()
    { pValue1 = nullptr; pValue2 = nullptr; }
    T1* getValue1()
    { return pValue1; }
    T2* getValue2()
    { return pValue2; }
    void setValue1(T1 const& rValueP)
    { value1 = rValueP; pValue1 = &value1; }
    void setValue2(T2 const& rValueP)
    { value2 = rValueP; pValue2 = &value2; }

private:
    T1  value1, *pValue1;
    T2  value2, *pValue2;
};

template <typename T1, typename T2, typename T3>
class Param3
{
public:
    Param3()
        : pValue1{nullptr}
        , pValue2{nullptr}
        , pValue3{nullptr}
    {}
    void reset()
    { pValue1 = nullptr; pValue2 = nullptr; pValue3 = nullptr; }
    T1* getValue1()
    { return pValue1; }
    T2* getValue2()
    { return pValue2; }
    T3* getValue3()
    { return pValue3; }
    void setValue1(T1 const& rValueP)
    { value1 = rValueP; pValue1 = &value1; }
    void setValue2(T2 const& rValueP)
    { value2 = rValueP; pValue2 = &value2; }
    void setValue3(T3 const& rValueP)
    { value3 = rValueP; pValue3 = &value3; }

private:
    T1  value1, *pValue1;
    T2  value2, *pValue2;
    T3  value3, *pValue3;
};

template <typename T1, typename T2, typename T3, typename T4>
class Param4
{
public:
    Param4()
        : pValue1{nullptr}
        , pValue2{nullptr}
        , pValue3{nullptr}
        , pValue4{nullptr}
    {}
    void reset()
    { pValue1 = nullptr; pValue2 = nullptr; pValue3 = nullptr; pValue4 = nullptr; }
    T1* getValue1()
    { return pValue1; }
    T2* getValue2()
    { return pValue2; }
    T3* getValue3()
    { return pValue3; }
    T4* getValue4()
    { return pValue4; }
    void setValue1(T1 const& rValueP)
    { value1 = rValueP; pValue1 = &value1; }
    void setValue2(T2 const& rValueP)
    { value2 = rValueP; pValue2 = &value2; }
    void setValue3(T3 const& rValueP)
    { value3 = rValueP; pValue3 = &value3; }
    void setValue4(T4 const& rValueP)
    { value4 = rValueP; pValue4 = &value4; }

private:
    T1  value1, *pValue1;
    T2  value2, *pValue2;
    T3  value3, *pValue3;
    T4  value4, *pValue4;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5>
class Param5
{
public:
    Param5()
        : pValue1{nullptr}
        , pValue2{nullptr}
        , pValue3{nullptr}
        , pValue4{nullptr}
        , pValue5{nullptr}
    {}
    void reset()
    { pValue1 = nullptr; pValue2 = nullptr; pValue3 = nullptr; pValue4 = nullptr; pValue5 = nullptr; }
    T1* getValue1()
    { return pValue1; }
    T2* getValue2()
    { return pValue2; }
    T3* getValue3()
    { return pValue3; }
    T4* getValue4()
    { return pValue4; }
    T5* getValue5()
    { return pValue5; }
    void setValue1(T1 const& rValueP)
    { value1 = rValueP; pValue1 = &value1; }
    void setValue2(T2 const& rValueP)
    { value2 = rValueP; pValue2 = &value2; }
    void setValue3(T3 const& rValueP)
    { value3 = rValueP; pValue3 = &value3; }
    void setValue4(T4 const& rValueP)
    { value4 = rValueP; pValue4 = &value4; }
    void setValue5(T5 const& rValueP)
    { value5 = rValueP; pValue5 = &value5; }

private:
    T1  value1, *pValue1;
    T2  value2, *pValue2;
    T3  value3, *pValue3;
    T4  value4, *pValue4;
    T5  value5, *pValue5;
};

} // namespace Bind

#endif // __BIND_COMMON_H__
