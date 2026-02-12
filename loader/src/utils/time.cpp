#include <Noahh/utils/general.hpp>

#ifdef NOAHH_IS_WINDOWS
#define NOAHH_CTIME() ctime_s(buf, sizeof buf, &t);
#else
#define NOAHH_CTIME() strcpy(buf, ctime(&t));
#endif

std::string noahh::utils::timePointAsString(const std::chrono::system_clock::time_point& tp) {
    auto t = std::chrono::system_clock::to_time_t(tp);
    char buf[128];
    NOAHH_CTIME();
    std::string res = buf;
    res.pop_back();
    return res;
}
