#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QPlainTextEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //void keyPressEvent(QKeyEvent *e);

    void on_speed_box_currentIndexChanged(const QString &arg1);

    void on_data_box_currentTextChanged(const QString &arg1);

    void on_parity_box_currentIndexChanged(int index);

    void on_stop_box_currentIndexChanged(int index);

    void on_ports_currentIndexChanged(int index);

    void on_refresh_clicked();

    void on_send__clicked();

    void on_clear_receive_clicked();

    void on_clear_send_clicked();

    void on_connect_clicked();

    void on_disconnect_clicked();

    void on_send_hexa_stateChanged(int arg1);

    void on_send_bin_stateChanged(int arg1);


    void on_receive_bin_stateChanged(int arg1);

    void on_receive_hexa_stateChanged(int arg1);

    void on_receive_float_stateChanged(int arg1);

    void on_send_float_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QSerialPort *pic;
    QByteArray buffer;
    static const quint16 pic_vendor_id = 1659;
    static const quint16 pic_product_id = 8963;
    QString pic_port_name[7];
    bool pic_is_available;
    void readData();
    unsigned char bufferread[13];
    int klm = 0;
    float calculator(float x, float y, unsigned char operation);

    typedef union {

        struct {
            float FV; //32 bit
        };

        struct {
            unsigned char B0;
            unsigned char B1;
            unsigned char B2;
            unsigned char B3;
        };
    } t_float;

};

#endif // MAINWINDOW_H
