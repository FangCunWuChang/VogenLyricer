#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Version.h"
#include <QMessageBox>
#include <QFile>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QHash>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void solveDictionaryList();

    QHash<QString,QHash<QString,QString>> tranl;

    void solvetran();

private slots:
    void on_aboutQt_clicked();

    void on_source_textChanged();

    void on_dics_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
