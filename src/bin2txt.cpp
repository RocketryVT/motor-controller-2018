#include <iostream>
#include <iomanip>
#include <transmission.h>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "usage: bin2txt \"log/LOG-01.bin\"" << std::endl;
        return 1;
    }

    bool binary = false;
    if (argc == 3 && std::string(argv[2]) == "--binary")
    {
        binary = true;
    }

    auto packets = transmission::fromFile(argv[1]);

    std::map<uint8_t, std::function<
        std::string(std::vector<uint8_t>)>> translations{
    
    { 130, [] (std::vector<uint8_t> data)
    {
        uint64_t millis;
        uint8_t status;
        float o2p, o2t, cp, ct, nh, thrust;
        data >> millis >> status >> o2p
            >> o2t >> cp >> ct >> nh >> thrust;
        std::stringstream ss;
        ss << millis << " " << (int) status << " " << o2p << " " << o2t
            << " " << cp << " " << ct << " " << nh << " " << thrust;
        return ss.str();
    }},

    { 131, [] (std::vector<uint8_t> data)
    {
        uint64_t millis;
        data >> millis;
        std::stringstream ss;
        ss << millis;
        return ss.str();
    }}};


    int count = 0;
    for (auto p : packets)
    {
        std::string s = transmission::packet2str(p, translations);
        if (binary) s = transmission::packet2str(p);
        std::cout << std::hex << std::setfill('0')
            << std::setw(4) << count << "    " << s << std::endl;
        ++count;
    }

    return 0;
}
