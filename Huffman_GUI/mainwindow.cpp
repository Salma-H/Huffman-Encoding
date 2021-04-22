#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QPixmap>
#include <iostream>
#include <fstream>
#include <vector>
#include "compress.h"
#include "huffman.h"

#include <string>        //for using the pop_back
#include <bits/stdc++.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    int w=ui->labelpic->width();
//    int h=ui->labelpic->height();
//    ui->labelpic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    QString filter = "Images(*.pgm) ;; All Files (*.*)";
    QString file_name = QFileDialog::getOpenFileName(this,"Choose PGM Image","",filter);


    if (!file_name.isEmpty()) {                                                     //display path
        if (ui->comboBox->findText(file_name) == -1)
            ui->comboBox->addItem(file_name);
        ui->comboBox->setCurrentIndex(ui->comboBox->findText(file_name));
    }

    if (QString::compare(file_name, QString()) !=0)

    {
        QImage image;
        bool valid = image.load(file_name);

        if (valid) {
            image = image.scaledToWidth(ui->labelpic->width(), Qt::SmoothTransformation);
       ui->labelpic->setPixmap(QPixmap::fromImage(image)); }

}


}

void MainWindow::on_compress_clicked() {
      QString file_name = QFileDialog::getOpenFileName(this,"Choose PGM Image","home://");
//    ui->outputtextEdit->append("Compressing, please wait... ");
//    auto end = std::chrono::steady_clock::now();
//    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - m_start).count();
//    ui->outputtextEdit->insertPlainText("Done\n");

 if (QString::compare(file_name, QString()) !=0)
 {
        std::string newfile = file_name. toStdString();
        image file;

        std::map<int, int> frequency;
                GetFreqTable(file.ipixels, frequency);

                Heap *huff;
                huff = MakeHuffmanTree(frequency);

                std::string S = "";
                std::map<int, std::string> encodingTable;
                GetCodewords(huff, S, encodingTable);

                std::string encoded = "";
                Mapping(file, encodingTable, encoded);
                // serialization & deserialization
                std::vector<char> bytesvector;


                compressing(bytesvector, encoded);
                writeCompImage(bytesvector, file);
                writeFreqTable(frequency);
            }

}




void MainWindow::on_decompress_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Choose PGM Image","home://");
    if (QString::compare(file_name, QString()) !=0)
    {
        std::string newfile = file_name. toStdString();
        image file;
        std::string freqfile;
               freqfile = result["file"].as<std::string>();
               image file2;
               std::vector<int> received_bytesvector;
               int num_paddingBits = 0;
               std::map <int,int> received_FreqTable;
               std::string Binary = "";
               readcompImage(file_name, received_bytesvector, num_paddingBits, file2);

               readFreqTable (freqfile, received_FreqTable);

               Decompressing (received_bytesvector , num_paddingBits , Binary );


               Heap *H;
               H = MakeHuffmanTree(received_FreqTable);


               std::string S ="";
               std::map<int, std::string> encodingTable2;
               GetCodewords(H, S, encodingTable2);

               GetPixels( Binary, encodingTable2, file2);

               WritePGM(file2);
   }
}
