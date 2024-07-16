// #include <iostream>
#include <sstream>
// #include <ctime>
#include <regex>
// #include <limits>
#include <iomanip>

using namespace std;

bool isValidDateTime(const string& date, const string& time) {
    // Regex pattern for YYYY-MM-DD
    regex date_pattern(R"(\d{4}-\d{2}-\d{2})");
    regex time_pattern(R"(\d{2}:\d{2})");
    if (regex_match(date, date_pattern) && regex_match(time, time_pattern)) {
        // Further check to validate the actual date values
        tm tm = {};
        istringstream ss(date + " " + time);
        ss >> get_time(&tm, "%Y-%m-%d %H:%M");
        return !ss.fail();
    }
    return false;
}