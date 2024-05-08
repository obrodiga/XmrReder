#ifndef STRUCT_H
#define STRUCT_H

//#include <QVector>
#include <vector>
#include <QString>

using namespace std;

struct Line
{
    QString line_type;
    QString port;
    int address;
    int baudrate;
};

struct Lines
{
    vector<Line> m_lines;
};

struct Object
{
    int class_id;
    QString logical_name;
    QString data_source;
};

struct LogicalDevice
{
    int address;
    int module;
    vector<Object> m_object;
};

struct LogicalDevices
{
    vector<LogicalDevice> m_logicaldevaice;
};

struct Server
{
    Lines m_lines;
    LogicalDevices m_devaices;
};

struct Servers
{
    vector<Server> m_Servers;
};

#endif // STRUCT_H
