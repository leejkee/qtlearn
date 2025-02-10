#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QSqlDatabase>
class DatabaseManager
{
public:
    static DatabaseManager& instance()
    {
        static DatabaseManager instance;
        return instance;
    }

    QSqlDatabase& getDB()
    {
        return db;
    }

    bool openDB(const QString& name)
    {
        if (db.isOpen())
        {
            return true;
        }
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(name);
        if (!db.open())
        {
            QMessageBox::information(nullptr, "Error", QString("DB open failded: %1").arg(db.lastError().text()));
            return false;
        }
        return true;
    }

    void closeDB()
    {
        if (db.isOpen())
        {
            db.close();
        }
    }

private:
    DatabaseManager(){}
    ~DatabaseManager()
    {
        closeDB();
    }
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    QSqlDatabase db;
};
#endif // DATABASEMANAGER_H