#pragma once

#include <Noahh/DefaultInclude.hpp>
#include "Types.hpp"
#include <chrono>
#include <sstream>
#include <vector>
#include <fs/filesystem.hpp>
#include <ccTypes.h>

/*namespace cocos2d {
    class CCObject;
    class CCNode;
    class CCPoint;
    class CCSize;
    class CCRect;
    class CCArray;
}*/

NOAHH_DLL std::ostream& operator<<(std::ostream& os, noahh::Mod* mod);
NOAHH_DLL std::ostream& operator<<(std::ostream& os, cocos2d::CCObject* obj);
NOAHH_DLL std::ostream& operator<<(std::ostream& os, cocos2d::CCArray* obj);
NOAHH_DLL std::ostream& operator<<(std::ostream& os, cocos2d::CCPoint const& pos);
NOAHH_DLL std::ostream& operator<<(std::ostream& os, cocos2d::CCSize const& size);
NOAHH_DLL std::ostream& operator<<(std::ostream& os, cocos2d::CCRect const& rect);
NOAHH_DLL std::ostream& operator<<(std::ostream& os, cocos2d::ccColor3B const& color);
NOAHH_DLL std::ostream& operator<<(std::ostream& os, cocos2d::ccColor4B const& color);

namespace noahh {
    class Mod;
    #pragma warning(disable: 4251)

    using log_clock = std::chrono::system_clock;

    struct NOAHH_DLL LogMetadata {
        std::string m_repr;
        LogMetadata(std::string const& r) : m_repr(r) {}
        LogMetadata() {}
        virtual ~LogMetadata() {}
    };

    std::string generateLogName();

    class Log;
    class NOAHH_DLL LogPtr {
    protected:
        Mod* m_sender = nullptr;
        log_clock::time_point m_time = log_clock::now();
        std::vector<LogMetadata*> m_data;
        Severity m_severity = Severity::Debug;

        friend class Log;
    
    public:
        LogPtr(Mod* Mod) : m_sender(Mod) {}

        ~LogPtr();

        std::string toString(bool logTime = true) const;
        std::vector<LogMetadata*> getData() const;

        log_clock::time_point getTime() const;
        std::string getTimeString() const;
        Mod* getSender() const;
        Severity getSeverity() const;

    };

    using ostream_fn_type = std::ostream&(*)(std::ostream&);

    class NOAHH_DLL Log {
    protected:
        LogPtr* m_logptr = nullptr;
        std::stringstream m_stream;
        void flush();

    public:
        static Log get();
        
        inline Log(Mod* m) : m_logptr(new LogPtr(m)) {}
        inline Log() : Log(nullptr) {}

        Log& operator<<(ostream_fn_type);

        Log& operator<<(Severity::type s);
        Log& operator<<(Severity s);


        template <typename T>
        Log& operator<<(T item) {
            this->m_stream << item;
            //static_assert(!std::is_same<Severity, T>::value, "didnt work :(");
            return *this;
        }

        template <typename U, typename T>
        Log& streamMeta(T t) {
            static_assert(std::is_base_of<LogMetadata, U>::value, "Metadata class must derive from noahh::LogMetadata");

            auto md = new LogMetadata;
            md->m_repr = this->m_stream.str();
            this->m_logptr->m_data.push_back(md);
            m_stream.str("");

            md = new U(t);
            m_stream << t;
            md->m_repr = m_stream.str();
            this->m_logptr->m_data.push_back(md);
            m_stream.str("");

            return *this;
        }

        ~Log();
    };

    // noahh-defined metadata functions

    struct ModMeta : public LogMetadata {
        Mod* m_mod;
        ModMeta(Mod* m) : m_mod(m) {}
        ModMeta(std::string const& r, Mod* m) : m_mod(m), LogMetadata(r) {}
    };
    struct NOAHH_DLL CCObjectMeta : public LogMetadata {
        cocos2d::CCObject* m_obj;
        CCObjectMeta(cocos2d::CCObject* obj);
        CCObjectMeta(std::string const& r, cocos2d::CCObject* obj);
        ~CCObjectMeta();
    };
    struct NOAHH_DLL CCArrayMeta : public LogMetadata {
        cocos2d::CCArray* m_arr;
        CCArrayMeta(cocos2d::CCArray* arr);
        CCArrayMeta(std::string const& r, cocos2d::CCArray* arr);
        ~CCArrayMeta();
    };
}
NOAHH_DLL noahh::Log& operator<<(noahh::Log&, noahh::Mod*);
NOAHH_DLL noahh::Log& operator<<(noahh::Log&, cocos2d::CCObject*);
NOAHH_DLL noahh::Log& operator<<(noahh::Log&, cocos2d::CCArray*);