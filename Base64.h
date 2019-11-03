#ifndef BASE64_H
#define BASE64_H

#include <vector> //data structure that is similar to an array but far more dynamic and flexible
#include <string>

namespace Base64
{
    std::string base64_encode(const std::string &);

    const std::string &SALT1 = "LM::TB::BB";
    const std::string &SALT2 = "_:/_77";
    const std::string &SALT3 = "line=wowC++";

    std::string EncryptB64(std::string s) //the more complex you make it here, harder it is to decode
    {
        s = SALT1 + s + SALT2 + SALT3;
        s = base64_encode(s);
        s.insert(7,SALT3);
        s += SALT1;
        s = base64_encode(s);
        s = SALT2 + SALT1 + SALT1;
        s = base64_encode(s);
        s.insert(1, "L"); //insert L to the 1st position
        s.insert(7, "M");
        return s;
    }

    const std::string &BASE64_CODES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    std::string base64_encode(const std::string &s)
    {
        std::string ret;
        int val = 0; //index used to map input to table
        int bits = -6; //bits that's used to represent bits in a sub group
        const unsigned int b63 = 0x3F;

        //use auto when you don't know the variable and C++ will recognize what type it should be

        for(const auto &c : s)
        {
            val = (val << 8) + c;
            //val = val * 2^8
            bits += 8;
            while(bits >= 0)
            {
                ret.push_back(BASE64_CODES[(val >> bits) & b63]); //& means AND operation in binary
                bits -= 6;
            }
        }

        if(bits > -6)
            ret.push_back(BASE64_CODES[((val << 8) >> (bits + 8)) & b63]);

        while(ret.size()%4)
            ret.push_back('=');

        return ret;





    }
}


#endif // BASE_64
