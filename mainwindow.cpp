/**
  * @file mainwindow.cpp
  * @brief main window with table
  * @author Kharchenko Daniil
  */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QUrl>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    conf = new createTable();
    this->createtable();
    ui->table->setColumnCount(conf->getCol());
    ui->table->setRowCount(conf->getRow());
    ui->table->resizeRowsToContents();
    ui->table->resizeColumnsToContents();
    connect(ui->save, &QPushButton::clicked, this, &MainWindow::save);
}

MainWindow::~MainWindow(){delete ui;}

void MainWindow::save(){
    QAxObject *mExcel = new QAxObject( "Excel.Application", this);
    QAxObject *workbooks = mExcel->querySubObject( "Workbooks" );
    QAxObject *workbook = workbooks->querySubObject( "Open(const QString&)", QUrl::fromLocalFile("C:\\Users\\Acer\\Desktop\\WorkWithMSExcel\\book.xlsx"));
    QAxObject *mSheets = workbook->querySubObject( "Sheets" );
    int count = mSheets->dynamicCall("Count()").toInt();
    QString name;
    for (int i=1; i<=count; i++){
        QAxObject* sheet = mSheets->querySubObject( "Item( int )", i );
        name = sheet->dynamicCall("Name()").toString();
    }
    QAxObject *StatSheet = mSheets->querySubObject( "Item(const QVariant&)", QVariant(name) );
    StatSheet->setProperty("Name", "My List");
    QAxObject* Cell1 = StatSheet->querySubObject("Cells(QVariant&,QVariant&)", 1, 1);
    QAxObject* Cell2 = StatSheet->querySubObject("Cells(QVariant&,QVariant&)", conf->getRow(), conf->getCol());
    QAxObject* range = StatSheet->querySubObject("Range(const QVariant&,const QVariant&)", Cell1->asVariant(), Cell2->asVariant() );
    QList<QVariant> cellsList;
    QList<QVariant> rowsList;
    for (int i = 0; i < conf->getRow(); i++)
    {
        cellsList.clear();
        for (int j = 0; j < conf->getCol(); j++){
            QVariant myData;
            QModelIndex myIndex;
            myIndex = ui->table->model()->index(i, j, QModelIndex());
            myData = ui->table->model()->data(myIndex, Qt::DisplayRole);
            cellsList << myData;
        }
        rowsList << QVariant(cellsList);
    }
    range->setProperty("Value", QVariant(rowsList));
    workbook->dynamicCall("Save()");
    workbook->dynamicCall("Close()");
    mExcel->dynamicCall("Quit()");
    QMessageBox::information(NULL,QObject::tr("Information"), tr("Saving completed successfully!"));
}

void MainWindow::createtable(){
    conf->exec();
    this->close();
}
