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

typedef vector<Line> Lines;

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
    vector<Object> Object;
};

typedef vector<LogicalDevice> LogicalDevices;

struct Server
{
    Lines m_lines;
    LogicalDevices Devaices;
};

typedef vector<Server> Servers;

#endif // STRUCT_H
