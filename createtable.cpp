/**
  * @file createtable.cpp
  * @brief create table
  * @author Kharchenko Daniil
  */

#include "createtable.h"
#include "ui_createtable.h"
#include <QDebug>

createTable::createTable(QWidget *parent) :
    QDialog(parent), ui(new Ui::createTable)
{
    ui->setupUi(this);
    connect(ui->confirm, &QPushButton::clicked, this, &createTable::confirm);
}

createTable::~createTable() {delete ui;}

void createTable::confirm(){
    col = ui->col->value();
    row = ui->row->value();
    this->close();
    emit sendCR(col, row);
}

int createTable::getRow(){
    return row;
}

int createTable::getCol(){
    return col;
}
