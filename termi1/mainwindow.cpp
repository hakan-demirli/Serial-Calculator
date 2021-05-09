#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QtWidgets>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pic = new QSerialPort;

    this->setWindowTitle("New Title");

    //look vendor and product id to find what connected to ports

    qDebug() << "number of avaliable ports: " << QSerialPortInfo::availablePorts().length();
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        qDebug() << "Has vendor ID: " << serialPortInfo.hasVendorIdentifier();
        if(serialPortInfo.hasVendorIdentifier()){
            qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier();
        }
        qDebug() << "Has product ID: " << serialPortInfo.hasProductIdentifier();
        if(serialPortInfo.hasProductIdentifier()){
            qDebug() << "Product ID: " << serialPortInfo.productIdentifier();
        }
    }
/*
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){

        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){

            if(serialPortInfo.vendorIdentifier() == pic_vendor_id){

                if(serialPortInfo.productIdentifier() == pic_product_id){
                    pic_port_name = serialPortInfo.portName();
                    pic_is_available = true;
                }
            }
        }
    }
*/
/*
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){

        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
            pic_port_name[0] = serialPortInfo.portName();
            pic_is_available = true;
        }
    }

    if(pic_is_available){
        //open and configure the port
        pic->setPortName(pic_port_name[0]);
        pic->open(QSerialPort::ReadWrite);
        pic->setBaudRate(QSerialPort::Baud9600);
        pic->setDataBits(QSerialPort::Data8);
        pic->setParity(QSerialPort::NoParity);
        pic->setStopBits(QSerialPort::OneStop);
        pic->setFlowControl(QSerialPort::NoFlowControl);

        connect(pic, &QSerialPort::readyRead, this, &MainWindow::readData);

    }else{
        QMessageBox::warning(this, "wtf", "Wtf");
    }
    */
}

MainWindow::~MainWindow()
{
    if(pic->isOpen()){
        pic->close();
    }
    delete ui;
}

void MainWindow::readData()
{
    forever{
        if (pic->bytesAvailable()==0)
            break;

        if(ui->receive_float->isChecked()){

             t_float val;
             t_float lav;
             unsigned char operation;
             char k[1];

             pic->read(k, 1);

             bufferread[11] = bufferread[10];
             bufferread[10] = bufferread[9];
             bufferread[9] = bufferread[8];
             bufferread[8] = bufferread[7];
             bufferread[7] = bufferread[6];
             bufferread[6] = bufferread[5];
             bufferread[5] = bufferread[4];
             bufferread[4] = bufferread[3];
             bufferread[3] = bufferread[2];
             bufferread[2] = bufferread[1];
             bufferread[1] = k[0];

            if(bufferread[10] == 255 && bufferread[11] == 170){

                 val.B0 = bufferread[9];
                 val.B1 = bufferread[8];
                 val.B2 = bufferread[7];
                 val.B3 = bufferread[6];

                 lav.B0 = bufferread[5];
                 lav.B1 = bufferread[4];
                 lav.B2 = bufferread[3];
                 lav.B3 = bufferread[2];

                 operation = bufferread[1];

                 val.FV = calculator(val.FV, lav.FV, operation);

                 QString b = QString::number(val.FV);
                 ui->textBrowser->moveCursor (QTextCursor::End);
                 ui->textBrowser->insertPlainText (b);
                 ui->textBrowser->moveCursor (QTextCursor::End);

                 char ar[7];
                 qDebug("this is %f", val.FV);

                 ar[0] = 0xAA;
                 ar[1] = 0XFF;
                 ar[2] = val.B0;
                 ar[3] = val.B1;
                 ar[4] = val.B2;
                 ar[5] = val.B3;
                 pic->write(ar, 6);

            }
        }else if(ui->receive_hexa->isChecked()){

            const QByteArray data = pic->readAll();
            QString myString(data.toHex()); //constructor QString(const QByteArray &ba)
            ui->textBrowser->moveCursor (QTextCursor::End);
            ui->textBrowser->insertPlainText (myString);
            ui->textBrowser->moveCursor (QTextCursor::End);

        }else if(ui->receive_bin->isChecked()){

            const QByteArray data = pic->readAll();
            QDataStream ds(data);
            int size; // Since the size you're trying to read appears to be 2 bytes
            ds >> size;
            QString bin = QString::number( size, 16);
            ui->textBrowser->moveCursor (QTextCursor::End);
            ui->textBrowser->insertPlainText (bin);
            ui->textBrowser->moveCursor (QTextCursor::End);

        }else{

            const QByteArray data = pic->readAll();
            QString myString(data); //constructor QString(const QByteArray &ba)
            ui->textBrowser->moveCursor (QTextCursor::End);
            ui->textBrowser->insertPlainText (myString);
            ui->textBrowser->moveCursor (QTextCursor::End);
        }
    }
}

float MainWindow::calculator(float x, float y, unsigned char operation){

    if(operation == '+'){
        return x+y;
    }else if(operation == '-'){
        return x-y;
    }else if(operation == 'x'){
        return x*y;
    }else if(operation == '/'){
        return x/y;
    }
    return 0;
}

void MainWindow::on_speed_box_currentIndexChanged(const QString &arg1)
{
    int a = arg1.toInt();
    pic->setBaudRate(a);
    qDebug ("This is current baud rate %d", a);
}

void MainWindow::on_data_box_currentTextChanged(const QString &arg1)
{
    int a = arg1.toInt();
     pic->setDataBits(QSerialPort::DataBits(a));
    qDebug ("This is current data bits %d", a);
}

void MainWindow::on_parity_box_currentIndexChanged(int index)
{
    if(index == 0){
        pic->setParity(QSerialPort::NoParity);
    }else if(index == 1){
        pic->setParity(QSerialPort::EvenParity);
    }else if(index == 2){
        pic->setParity(QSerialPort::OddParity);
    }else if(index == 3){
        pic->setParity(QSerialPort::SpaceParity);
    }else if(index == 4){
        pic->setParity(QSerialPort::MarkParity);
    }
    qDebug ("This is current parity index %d", index);
}

void MainWindow::on_stop_box_currentIndexChanged(int index)
{
    if(index == 0){
        pic->setStopBits(QSerialPort::OneStop);
    }else if(index == 1){
        pic->setStopBits(QSerialPort::OneAndHalfStop);
    }else if(index == 2){
        pic->setStopBits(QSerialPort::TwoStop);
    }
    qDebug ("This is current stop bits index %d", index);
}

void MainWindow::on_ports_currentIndexChanged(int index)
{
     pic->setPortName(pic_port_name[index]);
}

void MainWindow::on_refresh_clicked()
{
    int i = 0;
    pic->close();
    ui->ports->clear();

    QList<QSerialPortInfo> com_ports = QSerialPortInfo::availablePorts();
    QSerialPortInfo port;

    foreach(port, com_ports)
    {
        pic_port_name[i] = port.portName();
        ui->ports->addItem(port.portName());
        i++;
    }
}

void MainWindow::on_send__clicked()
{
    if(ui->send_float->isChecked()){

        t_float lo;
        char ar[7];
        QString hex = ui->textEdit_3->toPlainText();
        lo.FV = hex.toFloat();
        qDebug("this is %f", lo.FV);

        ar[0] = 0xAA;
        ar[1] = 0XFF;
        ar[2] = lo.B0;
        ar[3] = lo.B1;
        ar[4] = lo.B2;
        ar[5] = lo.B3;

        pic->write(ar, 6);

    }else if(ui->send_hexa->isChecked()){

        QString hex = ui->textEdit_3->toPlainText();
        QByteArray array = QByteArray::fromHex(hex.toLatin1());
        pic->write(array);

    }else if(ui->send_bin->isChecked()){

        QString binary = ui->textEdit_3->toPlainText();
        bool fOk;
        int iValue = binary.toInt(&fOk, 2);
        QString bin = QString::number( iValue, 16);
        QByteArray array = QByteArray::fromHex(bin.toLatin1());
        pic->write(array);

    }else {

        QString text = ui->textEdit_3->toPlainText();
        QByteArray ba = text.toLocal8Bit();
        pic->write(ba);

    }
}


void MainWindow::on_clear_receive_clicked()
{
    ui->textBrowser->clear();
}

void MainWindow::on_clear_send_clicked()
{
    ui->textEdit_3->clear();
}

void MainWindow::on_connect_clicked()
{
    pic->open(QSerialPort::ReadWrite);
    pic->setBaudRate(QSerialPort::Baud9600);
    pic->setDataBits(QSerialPort::Data8);
    pic->setParity(QSerialPort::NoParity);
    pic->setStopBits(QSerialPort::OneStop);
    pic->setFlowControl(QSerialPort::NoFlowControl);
    connect(pic, &QSerialPort::readyRead, this, &MainWindow::readData);
    ui->data_box->setCurrentIndex(0);
    ui->stop_box->setCurrentIndex(0);
    ui->parity_box->setCurrentIndex(0);
    ui->speed_box->setCurrentIndex(0);
}

void MainWindow::on_disconnect_clicked()
{
    pic->close();
}

void MainWindow::on_send_hexa_stateChanged(int arg1)
{
    if(ui->send_hexa->isChecked() && (ui->send_bin->isChecked() || ui->send_float->isChecked())){
         ui->send_bin->setChecked(false);
         ui->send_float->setChecked(false);
     }
}

void MainWindow::on_send_bin_stateChanged(int arg1)
{
    if(ui->send_bin->isChecked() && (ui->send_hexa->isChecked() || ui->send_float->isChecked())){
        ui->send_hexa->setChecked(false);
        ui->send_float->setChecked(false);
    }
}
void MainWindow::on_send_float_stateChanged(int arg1)
{
    if(ui->send_float->isChecked() && (ui->send_bin->isChecked() || ui->send_hexa->isChecked())){
         ui->send_hexa->setChecked(false);
         ui->send_bin->setChecked(false);
     }
}

void MainWindow::on_receive_bin_stateChanged(int arg1)
{
    if(ui->receive_bin->isChecked() && (ui->receive_hexa->isChecked() || ui->receive_float->isChecked())){
        ui->receive_hexa->setChecked(false);
        ui->receive_float->setChecked(false);
    }
}

void MainWindow::on_receive_hexa_stateChanged(int arg1)
{
   if(ui->receive_hexa->isChecked() && (ui->receive_bin->isChecked() || ui->receive_float->isChecked())){
        ui->receive_bin->setChecked(false);
        ui->receive_float->setChecked(false);
    }
}

void MainWindow::on_receive_float_stateChanged(int arg1)
{
    if(ui->receive_float->isChecked() && (ui->receive_bin->isChecked() || ui->receive_hexa->isChecked())){
         ui->receive_hexa->setChecked(false);
         ui->receive_bin->setChecked(false);
     }
}
