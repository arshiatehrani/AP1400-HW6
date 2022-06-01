#ifndef Q3_H
#define Q3_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <regex>
#include <sstream>
#include <string>

namespace q3 {

struct Flight {
    Flight(std::string _flight_number, size_t _duration, size_t _connections, size_t _connection_times, size_t _price)
        : flight_number { _flight_number }
        , duration { _duration }
        , connections { _connections }
        , connection_times { _connection_times }
        , price { _price }
    {
    }

    std::string flight_number;
    size_t duration;
    size_t connections;
    size_t connection_times;
    size_t price;
};

struct compare {
    bool operator()(const Flight& flight_1, const Flight& flight_2)
    {
        return (flight_1.duration) + (flight_1.connection_times) + 3 * (flight_1.price) > (flight_2.duration) + (flight_2.connection_times) + 3 * (flight_2.price);
    }
};

inline std::priority_queue<Flight, std::vector<Flight>, compare> gather_flights(std::string filename)
{
    std::priority_queue<Flight, std::vector<Flight>, compare> flight {};
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string txt = buffer.str();

    std::regex pattern(R"((\d-\s)(flight_number)(:)(\w+)(\s-\s)(duration:)(\d+)(\w)(\d*)(\w*)(\s-\sconnections:)(\d)(\s-\sconnection_times:)(\d)(\w)(\d*)(\w*)(,*)(\d*)(h*)(\d*)(m*)(,*)(\d*)(h*)(\d*)(m*)(\s-\sprice:)(\d+))"); // using raw string
    std::smatch match;

    while (std::regex_search(txt, match, pattern)) {

        std::string flight_number { match[4].str() };
        std::istringstream iss_duration_h { match[7].str() };
        std::istringstream iss_duratioin_m { match[9].str() };
        std::istringstream iss_connections { match[12].str() };
        std::istringstream iss_connection_times_1_h { match[14].str() };
        std::istringstream iss_connection_times_1_m { match[16].str() };
        std::istringstream iss_connection_times_2_h { match[19].str() };
        std::istringstream iss_connection_times_2_m { match[21].str() };
        std::istringstream iss_connection_times_3_h { match[24].str() };
        std::istringstream iss_connection_times_3_m { match[26].str() };
        std::istringstream iss_price { match[29].str() };
        size_t duration_h {};
        size_t duratioin_m {};
        size_t connections {};
        size_t connection_times_1_h {};
        size_t connection_times_1_m {};
        size_t connection_times_2_h {};
        size_t connection_times_2_m {};
        size_t connection_times_3_h {};
        size_t connection_times_3_m {};
        size_t price {};
        iss_duration_h >> duration_h;
        iss_duratioin_m >> duratioin_m;
        iss_connections >> connections;
        iss_connection_times_1_h >> connection_times_1_h;
        iss_connection_times_1_m >> connection_times_1_m;
        iss_connection_times_2_h >> connection_times_2_h;
        iss_connection_times_2_m >> connection_times_2_m;
        iss_connection_times_3_h >> connection_times_3_h;
        iss_connection_times_3_m >> connection_times_3_m;
        iss_price >> price;
        flight.push(Flight(flight_number, (duration_h * 60) + duratioin_m, connections, (connection_times_1_h + connection_times_2_h + connection_times_3_h) * 60 + connection_times_1_m + connection_times_2_m + connection_times_3_m, price));
        txt = match.suffix().str();
    }
    return flight;
}
}

#endif // Q3_H