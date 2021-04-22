#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "huffman.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void loadFile(const QString &file_name);

private slots:
    void on_pushButton_clicked();

//   void compressFinished();


    void on_compress_clicked();


    void on_decompress_clicked();

    void on_labelpic_linkActivated(const QString &link);

private:
    Ui::MainWindow *ui;
        std::chrono::time_point<std::chrono::steady_clock> m_start;

    void MakehuffmanTree();
    void getcodewords();
    void compare();
    void getfreqtable();
    bool isleaf();


};
#endif // MAINWINDOW_H
