/**
  * @file mainwindow.h
  * @brief main window with table
  * @author Kharchenko Daniil
  */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ActiveQt\QAxObject>
#include "createtable.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    /**
     * @brief constructor MainWindow
     * @param parent
     */
    MainWindow(QWidget *parent = nullptr);
    /**
       * @brief destructor MainWindow
       */
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    createTable* conf;

private slots:
    /**
     * @brief save data in book.xlsx
     */
    void save();
    /**
     * @brief create table
     */
    void createtable();
};
#endif // MAINWINDOW_H
