/**
  * @file createtable.h
  * @brief create table
  * @author Kharchenko Daniil
  */

#ifndef CREATETABLE_H
#define CREATETABLE_H

#include <QDialog>

namespace Ui {
class createTable;
}

class createTable : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief constructor create Table
     * @param parent
     */
    explicit createTable(QWidget *parent = nullptr);
    /**
      * @brief destructor create Table
      */
    ~createTable();
    /**
     * @brief get Row
     * @return number of rows
     */
    int getRow();
    /**
     * @brief get column
     * @return number of rows
     */
    int getCol();
private:
    Ui::createTable *ui;
    int col=1;
    int row=1;
private slots:
    /**
     * @brief confirm
     */
    void confirm();

signals:
    /**
     * @brief send column and row
     * @param column
     * @param row
     */
    void sendCR(int col, int row);
};

#endif // CREATETABLE_H
