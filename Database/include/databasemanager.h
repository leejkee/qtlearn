#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QSqlDatabase>
class DatabaseManager
{
public:
    DatabaseManager();
    ~DatabaseManager();

    void openDB();

    QSqlDatabase db;
};
#endif // DATABASEMANAGER_H