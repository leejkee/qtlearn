#ifndef TFORMDOC_H
#define TFORMDOC_H

#include <QWidget>

class QPlainTextEdit;
class QToolBar;
class TFormDoc : public QWidget
{
    Q_OBJECT

public:
    explicit TFormDoc(QWidget *parent = nullptr);
    ~TFormDoc();
    void loadFromFile(QString &FileName);

private:
    QAction *actionOpen;
    QAction *actionFont;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionCut;
    QAction *actionRedo;
    QAction *actionUndo;
    QAction *actionClose;
    QToolBar *localToolBar;

    QPlainTextEdit *plainTextEdit;

signals:
    void titleChanged(QString title);

private slots:
    void onActionOpenTriggered();
    void onActionFontTriggered();
};

#endif // TFORMDOC_H
