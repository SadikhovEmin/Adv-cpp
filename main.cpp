// Name: Emin Sadikhov
#include <iostream>
#include <vector>
template<typename ...> struct TD; // your compile time debug helper (TypeDisplayer)



// WRITE YOUR CODE HERE (STARTS)

template<typename T>
concept AnyContainer = requires(T t)
{
    t.size();
    t.begin();
    t.end();
};

//template<typename ... Ts> auto print(Ts... ts) { ((std::cout << ts << std::endl), ...); }
template<typename First, typename ... Rest>
inline void print(First first, Rest ... rest)
{
    if constexpr(AnyContainer<First>)
    {
        for(const auto& i: first)
            std::cout << i << " ";
        std::cout << std::endl << std::endl;
//        std::cout << std::endl;
    }
    else
        std::cout << first << std::endl;

    if constexpr(sizeof...(rest) != 0)
        print(rest...);
    else
        std::cout << std::endl;
}

template<typename T> concept One    = requires(T t) { t(int{});  t(double{}); t(float{}); };
template<typename T> concept Two    = requires(T t) { t(int{},int{}); t(double{},double{}); t(float{},float{}); };
template<typename T> concept Three  = requires(T t) { t(int{},int{},int{}); t(double{},double{},double{}); t(float{},float{},float{}); };



struct $ {
    auto operator()(auto value) const { return value; }
};
auto $1 = $();
auto $2 = $();
auto $3 = $();


template<typename T1, typename T2>
auto operator+(T1 t1, T2 t2) {
    // lambda, lambda
    if constexpr(One<T1> && One<T2>)
        return [=](auto l1, auto l2) { return t1(l1) + t2(l2); };
    else if constexpr(One<T1> && Two<T2>)
        return [=](auto l1, auto l2, auto l3) { return t1(l1) + t2(l2, l3); };
    else if constexpr(Two<T1> && One<T2>)
        return [=](auto l1, auto l2, auto l3) { return t1(l1, l2) + t2(l3); };
    // lambda, value
    else if constexpr(Three<T1> || Two<T1> || One<T1>)
        return [=]<typename ... Ts>(Ts...ts) { return t1(ts...) + t2; };
    // value, lambda
    else if constexpr(Three<T2> || Two<T2> || One<T2>)
        return [=]<typename ... Ts>(Ts...ts){ return t1 + t2(ts...); };
}

template<typename T1, typename T2>
auto operator-(T1 t1, T2 t2) {
    // lambda, lambda
    if constexpr(One<T1> && One<T2>)
        return [=](auto l1, auto l2) { return t1(l1) - t2(l2); };
    else if constexpr(One<T1> && Two<T2>)
        return [=](auto l1, auto l2, auto l3) { return t1(l1) - t2(l2, l3); };
    else if constexpr(Two<T1> && One<T2>)
        return [=](auto l1, auto l2, auto l3) { return t1(l1, l2) - t2(l3); };
    // lambda, value
    else if constexpr(Three<T1> || Two<T1> || One<T1>)
        return [=]<typename ... Ts>(Ts...ts) { return t1(ts...) - t2; };
    // value, lambda
    else if constexpr(Three<T2> || Two<T2> || One<T2>)
        return [=]<typename ... Ts>(Ts...ts){ return t1 - t2(ts...); };
}



template<typename T1, typename T2>
auto operator/(T1 t1, T2 t2) {
    // lambda, lambda
    if constexpr(One<T1> && One<T2>)
        return [=](auto l1, auto l2){ return t1(l1) / t2(l2); };
    else if constexpr(One<T1> && Two<T2>)
        return [=](auto l1, auto l2, auto l3){ return t1(l1) / t2(l2, l3); };
    else if constexpr(Two<T1> && One<T2>)
        return [=](auto l1, auto l2, auto l3){ return t1(l1, l2) / t2(l3); };
    // lambda, value
    else if constexpr(Three<T1> || Two<T1> || One<T1>)
        return [=]<typename ... Ts>(Ts...ts){ return t1(ts...) / t2; };
    // value, lambda
    else if constexpr(Three<T2> || Two<T2> || One<T2>)
        return [=]<typename ... Ts>(Ts...ts){ return t1 / t2(ts...); };
}

template<typename T1, typename T2>
auto operator*(T1 t1, T2 t2) {
    // lambda, lambda
    if constexpr(One<T1> && One<T2>)
        return [=](auto l1, auto l2){ return t1(l1) * t2(l2); };
    else if constexpr(One<T1> && Two<T2>)
        return [=](auto l1, auto l2, auto l3){ return t1(l3) * t2(l1, l2); };
    else if constexpr(Two<T1> && One<T2>)
        return [=](auto l1, auto l2, auto l3){ return t1(l1, l2) * t2(l3); };
    // lambda, value
    else if constexpr(Three<T1> || Two<T1> || One<T1>)
        return [=]<typename ... Ts>(Ts...ts){ return t1(ts...) * t2; };
    // value, lambda
    else if constexpr(Three<T2> || Two<T2> || One<T2>)
        return [=]<typename ... Ts>(Ts...ts){ return t1 * t2(ts...); };
}

template<typename T1, typename T2>
auto operator>(T1 t1, T2 t2) {
    // lambda, lambda
    if constexpr(One<T1> && One<T2>)
        return [=](auto l1, auto l2){ return t1(l1) > t2(l2); };
    else if constexpr(One<T1> && Two<T2>)
        return [=](auto l1, auto l2, auto l3){ return t1(l3) > t2(l1, l2); };
    else if constexpr(Two<T1> && One<T2>)
        return [=](auto l1, auto l2, auto l3){ return t1(l1, l2) > t2(l3); };
    // lambda, value
    else if constexpr(Three<T1> || Two<T1> || One<T1>)
        return [=]<typename ... Ts>(Ts...ts){ return t1(ts...) > t2; };
    // value, lambda
    else if constexpr(Three<T2> || Two<T2> || One<T2>)
        return [=]<typename ... Ts>(Ts...ts){ return t1 > t2(ts...); };
}

template<typename T>
auto operator++(T t, int) {
    return [=](auto value) {
        auto result = t(value);     // 10 20 30
        auto temp = result++;       // 11 21 31
//        std::cout << "my : " << result << std::endl;
        return temp;
    };
}



template<typename T>
struct Vector : std::vector<T> {

    using std::vector<T>::vector;

    auto operator[](auto func) {
        if constexpr(std::is_same_v<decltype (func(1)), bool>) {
            auto v = std::vector<bool>{};
            for(auto& i: *this)
                v.push_back(func(i));
            return v;
        }
        else {
            auto v = std::vector<int>{};
            for(auto& i: *this)
                v.push_back(func(i));
            return v;
        }
    }

    auto operator[](std::vector<bool> v) {
        auto result = std::vector<int>{};
        for(auto i = 0; i < v.size(); i++)
            if(v.at(i))
                result.push_back(this->at(i));
        return result;
    }

    auto operator[](int i) {
        if(i < 0)
            return this->at(i + this->size());
        return this->at(i);
    }

};

template<typename T>
Vector(T) -> Vector<T>;

template<typename First, typename ...Rest>
Vector(First,Rest...) -> Vector<First>;


// WRITE YOUR CODE HERE (ENDS)


int main()
{
    // design a print overload-set or a single print function that can generically print any number of
    // containers and strings and other values in a single call to print. check the below usage of print.

    // design a math expression system that lazily represents an operation over values that will be later provided
    // use $1, $2, $3 as special variables of this math expression toolkit
    // $1 means the first value, $2 means the second, $3 means the third value supplied to a function/lambda
    // (yes, using $ is valid for variables!)
    // for instance; auto e=$3-$1+$2 creates an expression via composing 3 different lambdas
    // when later called with (10, 20, 30, 40, 50, ...) evaluates to 30-10+20
    // your design shall take care of at least +, -, *, /, ++, > operators
    // note that ++i and i++ are different overloads. How to overload both of them? Check the internet.
    // > will create a lazy boolean expression
    // ++ will also touch and change the item itself
    // (for instance running $1++ over a vector will increment all elements by one after the evaluation is done)
    // operator precedence is the same as the precedences that are defined in the C++ language
    // if you do compose two lambdas from left to right, there shall be no problem with the precedence
    // language will take care of it for you

    // create a Vector<...> class that inherits from vector<...> and extends it so that after auto v = Vector{...};
    // v[boolean expression] outputs a mask of vector<bool>
    // v[other expression] creates a new vector that contains transformed items according to the expression
    // v[vector<bool>] selects only the elements that correspond to boolean true locations of the vector<bool> mask
    // v[index] works as before
    // v[-index] selects the item starting from the end of the vector. For instance, -1 is the last element.

    // Q1 (15 pts) - print overload-set working correctly as used below in all questions
    // Q2 (30 pts) â€“ below and all expressions that can be written with $1, $2, $3 and +, -, *, / works correctly
    auto l1 = (1.1 + $3) * ($1 + $2 / 2.0);
    print("l1(5, 10, 15)", l1(5, 10, 15));

    // Q3 (5 pts) - deduction guide for below line
    // you can change below line to Vector<int>{10, 20, 30} if you want to skip this question
    auto v = Vector{10, 20, 30}; // not written Vector<int>{10, 20, 30} especially.

    // Q4 (5 pts) - $1>10 works as expected
    // Q5 (10 pts) - masking of a Vector works
    auto mask_gt_10 = v[$1 > 10];
//    std::cout << mask_gt_10.at(0) << std::endl;
//    std::cout << mask_gt_10.at(1) << std::endl;
//    std::cout << mask_gt_10.at(2) << std::endl;

    // Q6 (10 pts) - selection of Vector elements by means of a mask
    auto v_selected = v[mask_gt_10];
    print("v", v, "Mask of $1>10", mask_gt_10, "v_selected", v_selected);

//    // Q7 (10 pts) - accessing elements of a Vector in standard way and in reverse direction
    print("First element of v", v[0], "Last Element of v", v[-1]);
    print("v", v);

//    // Q8 (only for CS409) (15 pts) - item++ operator works on Vector<int>
    print("v applied with $1++ * 3", v[$1++ * 3]);


    print("v", v); // note that v's items are now incremented by one due to $1++ above


//    // Q8 (only for CS509) (15 pts) - ++item operator works on Vector<double>
//    // you can change below line to Vector<double>{1.1, 2.2, 3.3} if you don't want points from Q3
////    auto v2 = Vector{1.1, 2.2, 3.3};
////    print("v2", v2);
////    print("v2 applied with ++$1 - 1", v2[++$1 - 1]);
////    print("v2", v2); // note that v's items are now incremented by one due to $1++ above
    return 0;
}


