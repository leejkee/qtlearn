#ifndef TFORMDOC_H
#define TFORMDOC_H

#include <QWidget>


class QPlainTextEdit;
class TFormDoc : public QWidget
{
    Q_OBJECT
public:
    explicit TFormDoc(QWidget *parent = nullptr);

private:
    QString m_fileName;
    bool m_fileOpened = false;
    QPlainTextEdit *plainTextEdit;

public:
    void loadFormFile(QString &fileName);
    void saveToFile();
    QString currentFileName();
    bool isFileOpened();
    void setEditFont();
    void textCut();
    void textCopy();
    void textPaste();
};

#endif // TFORMDOC_H
