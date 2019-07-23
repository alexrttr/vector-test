#include <iostream>
#include <vector>

int copy = 0;
int move = 0;

struct Heavy
{
    Heavy(){};
    Heavy(int){};
    Heavy(const Heavy&)
    {
       copy++;
    }
    Heavy(Heavy&&)
    {
       move++;
    }
    Heavy& operator=(Heavy other)
    {
       swap(other);
       std::cout << "copy assign" << std::endl;
       return *this;
    }
    Heavy& operator=(Heavy&& other)
    {
       // move operations
       std::cout << "move assign" << std::endl;
       return *this;
    }
    void swap(Heavy& other) { }
};


void printGlobals()
{
    std::cout << copy << ' ' << move << std::endl;
}


int main(int argc, char** argv)
{
    std::vector<Heavy> v1;
    std::vector<Heavy> v2;
    std::vector<Heavy> v3;

    v1.reserve(50);
    v2.reserve(50);
    v3.reserve(50);

    printGlobals();

    v1.push_back(Heavy()); 

    printGlobals();

    for (int i = 0; i < 4; ++i)
    {
        v1.push_back(Heavy()); 
    }

    printGlobals();

    std::vector<Heavy> v22;
    // v22.reserve(50);
    for (int i = 0; i < 5; ++i)
    {
        v22[i] = v1[i];
    }

    printGlobals();

    for (int i = 0; i < 5; ++i)
    {
        v2.push_back(v1[i]);
    }

    printGlobals();

    for (int i = 0; i < 5; ++i)
    {
        v3.push_back(std::move(v1[i]));
    }

    printGlobals();

    std::cout << "before vE" << std::endl;

    std::vector<Heavy> vE;
    vE.reserve(50);

    for (int i = 0; i < 5; ++i)
    {
        vE.emplace_back(std::move(v3[i]));
    }

    printGlobals();

    std::cout << "decltype, move" << std::endl;
    std::vector<Heavy> vEEM;
    vEEM.reserve(50);
    for (int i = 0; i < 5; ++i)
    {
        decltype(std::move(v3[i])) ell = std::move(v3[i]);
        vEEM.emplace_back(std::move(ell));
    }

    printGlobals();

    std::cout << "decltype" << std::endl;
    std::vector<Heavy> vEE;
    vEE.reserve(50);
    for (int i = 0; i < 5; ++i)
    {
        decltype(std::move(v3[i])) ell = std::move(v3[i]);
        printGlobals();
        vEE.emplace_back(ell);
        printGlobals();
    }

    printGlobals();

    std::cout << "auto, emplace_back" << std::endl;
    std::vector<Heavy> vEEE;
    vEEE.reserve(50);
    for (int i = 0; i < 5; ++i)
    {
        auto el = std::move(v3[i]);
        printGlobals();
        vEEE.emplace_back(el);
        printGlobals();
    }

    printGlobals();

    std::cout << "auto, emplace_back moved" << std::endl;
    std::vector<Heavy> vEEEM;
    vEEEM.reserve(50);
    for (int i = 0; i < 5; ++i)
    {
        auto el = std::move(v3[i]);
        printGlobals();
        vEEEM.emplace_back(std::move(el));
        printGlobals();
    }

    printGlobals();

    std::cout << "Before vRE" << std::endl;

    std::vector<Heavy> vRE;
    vRE.reserve(50);

    for (int i = 0; i < 5; ++i)
    {
        vRE.emplace_back(45);
    }

    printGlobals();

    decltype(std::move(v3)) v4 = std::move(v3);

    printGlobals();

    auto v8 = std::move(vEEE);

    printGlobals();

    auto v9 = std::move(v4);

    printGlobals();

    auto v10 = v8;
    printGlobals();

    return 0;
}

