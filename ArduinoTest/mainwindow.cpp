/****************************************************************************
**
** Copyright (C) 2012 Denis Shienkov <denis.shienkov@gmail.com>
** Copyright (C) 2012 Laszlo Papp <lpapp@kde.org>
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtSerialPort module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "console.h"
#include "settingsdialog.h"
#include "graph2d.h"
#include "viz3D.h"
#include "datasaver.h"

#include <fstream>
#include <QLabel>
#include <QMessageBox>
#include <QtCharts/QChartView>


//! [0]
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow),
    m_status(new QLabel),
    m_settings(new SettingsDialog),
//! [1]
    m_serial(new QSerialPort(this))
//! [1]
{
//! [0]
    m_ui->setupUi(this);
    m_ui->m_console->setEnabled(false);

    label1=new QLabel("TEST TEST TEST");
    label1->setFixedSize(200,100);

    QVBoxLayout *mainLayout = new QVBoxLayout();

    mainLayout->addWidget(label1);


    mainWidget = new QWidget;
    mainWidget->setLayout(mainLayout);

    Graph2D *accelGraph = new Graph2D();
    accelGraph->setTitle("Accelerometer Graph");
    Graph2D *gyroGraph= new Graph2D();
    gyroGraph->setTitle("Gyroscope Graph");
    Graph2D *magGraph= new Graph2D();
    magGraph->setTitle("Magnetometer Graph");

    accelGraph->legend()->setAlignment(Qt::AlignLeft);
    accelGraph->layout()->setContentsMargins(0,0,0,0);
    gyroGraph->legend()->setAlignment(Qt::AlignLeft);
    gyroGraph->layout()->setContentsMargins(0,0,0,0);
    magGraph->legend()->setAlignment(Qt::AlignLeft);
    magGraph->layout()->setContentsMargins(0,0,0,0);

//    accelGraph->legend()->detachFromChart();
//    accelGraph->legend()->setBackgroundVisible(true);
//    accelGraph->legend()->setGeometry(QRectF(100,
//                                             100,
//                                             100,
//                                             50));
//    accelGraph->legend()->update();
////    chart->legend()->hide();
    accelGraph->setAnimationOptions(QChart::AllAnimations);
    m_ui->accelView->setChart(accelGraph);
//    m_ui->accelView->setRenderHint(QPainter::Antialiasing);

    gyroGraph->setAnimationOptions(QChart::AllAnimations);
    m_ui->gyroView->setChart(gyroGraph);
//    m_ui->gyroView->setRenderHint(QPainter::Antialiasing);

    magGraph->setAnimationOptions(QChart::AllAnimations);
    m_ui->magView->setChart(magGraph);



    m_ui->actionConnect->setEnabled(true);
    m_ui->actionDisconnect->setEnabled(false);
    m_ui->actionQuit->setEnabled(true);
    m_ui->actionConfigure->setEnabled(true);

    m_ui->statusBar->addWidget(m_status);

    initActionsConnections();

    connect(m_serial, &QSerialPort::errorOccurred, this, &MainWindow::handleError);

//! [2]
    connect(m_serial, &QSerialPort::readyRead, this, &MainWindow::readData);
//! [2]
    connect(m_ui->m_console, &Console::getData, this, &MainWindow::writeData);

    connect(m_ui->m_console, &Console::sendAllData, this, &MainWindow::writeDatatoFile);
    connect(m_ui->m_console, &Console::sendAccelData, accelGraph, &Graph2D::updateGraph);
    connect(m_ui->m_console, &Console::sendGyroData, gyroGraph, &Graph2D::updateGraph);
    connect(m_ui->m_console, &Console::sendMagData, magGraph, &Graph2D::updateGraph);
    connect(m_ui->m_console, &Console::sendRPY, m_ui->openGLWidget, &Viz3D::updateRotation);

//! [3]
}
//! [3]

MainWindow::~MainWindow()
{
    delete m_settings;
    delete m_ui;
    fileOut.close();
}

//! [4]
void MainWindow::openSerialPort()
{
    const SettingsDialog::Settings p = m_settings->settings();
    m_serial->setPortName(p.name);
    m_serial->setBaudRate(p.baudRate);
    m_serial->setDataBits(p.dataBits);
    m_serial->setParity(p.parity);
    m_serial->setStopBits(p.stopBits);
    m_serial->setFlowControl(p.flowControl);
    if (m_serial->open(QIODevice::ReadWrite)) {
        m_ui->m_console->setEnabled(true);
        m_ui->m_console->setLocalEchoEnabled(p.localEchoEnabled);
        m_ui->actionConnect->setEnabled(false);
        m_ui->actionDisconnect->setEnabled(true);
        m_ui->actionConfigure->setEnabled(false);
        showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                          .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                          .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
    } else {
        QMessageBox::critical(this, tr("Error"), m_serial->errorString());

        showStatusMessage(tr("Open error"));
    }
}
//! [4]

//! [5]
void MainWindow::closeSerialPort()
{
    if (m_serial->isOpen())
        m_serial->close();
    m_ui->m_console->setEnabled(false);
    m_ui->actionConnect->setEnabled(true);
    m_ui->actionDisconnect->setEnabled(false);
    m_ui->actionConfigure->setEnabled(true);
    fileOut.close();
    showStatusMessage(tr("Disconnected"));
}

void MainWindow::writeDatatoFile(double ax, double ay, double az,
                           double gx, double gy, double gz,
                           double mx, double my, double mz,
                           double yaw, double pitch, double roll,
                           float qw, double qx, double qy, double qz
                           ){
    if(readyToSave){
        if(saveQuaternions){
            fileOut << qw <<","<<qx<<","<<qy<<","<<qz;
        }
        if(saveRaw){
            if(saveQuaternions) fileOut<<",";
            fileOut << ax <<","<<ay<<","<<az<<",";
            fileOut << gx <<","<<gy<<","<<gz<<",";
            fileOut << mx <<","<<my<<","<<mz;
        }
        if(saveRPY){
             if(saveQuaternions || saveRaw) fileOut<<",";
             fileOut << roll <<","<<pitch<<","<<yaw;
        }
        fileOut <<std::endl;


    }


}
//! [5]

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Simple Terminal"),
                       tr("The <b>Simple Terminal</b> example demonstrates how to "
                          "use the Qt Serial Port module in modern GUI applications "
                          "using Qt, with a menu bar, toolbars, and a status bar."));
}

//! [6]
void MainWindow::writeData(const QByteArray &data)
{
    m_serial->write(data);
}
//! [6]

//! [7]
void MainWindow::readData()
{
    const QByteArray data = m_serial->readAll();
    m_ui->m_console->putData(data);
}
//! [7]

//! [8]
void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), m_serial->errorString());
        closeSerialPort();
    }
}
//! [8]

void MainWindow::initActionsConnections()
{
    connect(m_ui->actionConnect, &QAction::triggered, this, &MainWindow::openSerialPort);
    connect(m_ui->actionDisconnect, &QAction::triggered, this, &MainWindow::closeSerialPort);
    connect(m_ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
    connect(m_ui->actionConfigure, &QAction::triggered, m_settings, &SettingsDialog::show);
    connect(m_ui->actionClear, &QAction::triggered, m_ui->m_console, &Console::clear);
    connect(m_ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
    connect(m_ui->actionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
}

void MainWindow::showStatusMessage(const QString &message)
{
    m_status->setText(message);
}

void MainWindow::on_enableSavingButton_clicked()
{
    std::string pathString = m_ui->pathToFile->toPlainText().toStdString();
    std::ifstream ifile(pathString);
    // Check if file already exists (prevents overwriting after disabling logging and enabling again)
    if(ifile.good()) {
         ifile.close();
         QMessageBox warningBox;
         warningBox.setText("Warning, this file already exists");
         warningBox.setInformativeText("Do you want to overwrite it?");
         warningBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
         warningBox.setIcon(QMessageBox::Warning);
         if(warningBox.exec()==QMessageBox::No) return;
    }
    saveQuaternions = m_ui->cbQuaternions->isChecked();
    saveRaw = m_ui->cbRaw->isChecked();
    saveRPY = m_ui->cbRPY->isChecked();

    // Check if at least one checkbox is selected
    if(!(saveQuaternions || saveRaw || saveRPY)){
        QMessageBox::critical(this, "Error", "Please select at least one data type to save");
        return;

    }
    // Create file
    fileOut.open(pathString);
    // Check if opened successfully
    if(!fileOut.is_open()){
        QMessageBox::critical(this, "Error", "Failed to open file");
        return;
    }
    // Add column names to file
    if(saveQuaternions){
        fileOut << "qw," << "qx,"<<"qy,"<<"qz";

    }
    if(saveRaw){
        //Add comma if there are other columns lready
        if(saveQuaternions) fileOut<<",";
        fileOut << "ax," << "ay,"<<"az (mg),";
        fileOut << "gx," << "gy,"<<"gz (deg/s),";
        fileOut << "mx," << "my,"<<"mz (mG)";

    }
    if(saveRPY){
         if(saveQuaternions ||saveRaw) fileOut<<",";
          fileOut << "roll," << "pitch,"<<"yaw (deg),";

    }
    fileOut <<std::endl;
    // Update button status
    m_ui->enableSavingButton->setEnabled(false);
    m_ui->disableSavingButton->setEnabled(true);
    m_ui->cbQuaternions->setEnabled(false);
    m_ui->cbRaw->setEnabled(false);
    m_ui->cbRPY->setEnabled(false);
    readyToSave = true;


}


void MainWindow::on_browseButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                              QDir::homePath(),
                               tr("Data File (*.csv *.txt)"));
    m_ui->pathToFile->setText(fileName);
}



void MainWindow::on_disableSavingButton_clicked()
{
    m_ui->enableSavingButton->setEnabled(true);
    m_ui->disableSavingButton->setEnabled(false);
    m_ui->cbQuaternions->setEnabled(true);
    m_ui->cbRaw->setEnabled(true);
    m_ui->cbRPY->setEnabled(true);
    fileOut.close();
    readyToSave = false;

}

