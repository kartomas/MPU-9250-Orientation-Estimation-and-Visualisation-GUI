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
#include "viz3D.h"

#include <math.h>
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

    setupGraphs();



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
    connect(m_ui->m_console, &Console::sendGraphData, this, &MainWindow::updateGraphs);

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
// Initialise 2D graphs
void MainWindow::setupGraphs(){
    // Accelerometer Graph
    // Set graphs
    m_ui->accelGraph->addGraph(); // x
    m_ui->accelGraph->graph(0)->setPen(QPen(QColor(214,39,40),2));
    m_ui->accelGraph->graph(0)->setName("X");
    m_ui->accelGraph->addGraph(); // y
    m_ui->accelGraph->graph(1)->setPen(QPen(QColor(44,160,44),2));
    m_ui->accelGraph->graph(1)->setName("Y");
    m_ui->accelGraph->addGraph(); // z
    m_ui->accelGraph->graph(2)->setPen(QPen(QColor(31,119,180),2));
    m_ui->accelGraph->graph(2)->setName("Z");
    // Set legend, title and axis names
    m_ui->accelGraph->legend->setVisible(true);
    m_ui->accelGraph->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
    QFont legendFont = QFont("Helvetica", 7);
    m_ui->accelGraph->legend->setFont(legendFont);
    m_ui->accelGraph->legend->setSelectedFont(legendFont);
    m_ui->accelGraph->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);
    m_ui->accelGraph->yAxis->setLabel("mg");
    m_ui->accelGraph->xAxis->setTickLabels(false);
    m_ui->accelGraph->plotLayout()->insertRow(0);
    QCPTextElement *titleAccel = new QCPTextElement(m_ui->accelGraph, "Accelerometer Data", QFont("sans", 8, QFont::Bold));
    m_ui->accelGraph->plotLayout()->addElement(0, 0, titleAccel);
    m_ui->accelGraph->plotLayout()->setAutoMargins(QCP::MarginSide(0x00)); //Disable auto margin
    m_ui->accelGraph->plotLayout()->setRowSpacing(0);
    m_ui->accelGraph->plotLayout()->setRowStretchFactor(0,0.001);
    m_ui->accelGraph->plotLayout()->setMargins(QMargins(0,0,0,0));
    m_ui->accelGraph->legend->setFillOrder(QCPLegend::foColumnsFirst);
    // Set range
    m_ui->accelGraph->xAxis->setRange(0, 40);
    m_ui->accelGraph->yAxis->setRange(-1, 1);

    // Gyroscope Graph
    // Set graphs
    m_ui->gyroGraph->addGraph(); // x
    m_ui->gyroGraph->graph(0)->setPen(QPen(QColor(214,39,40),2));
    m_ui->gyroGraph->graph(0)->setName("X");
    m_ui->gyroGraph->addGraph(); // y
    m_ui->gyroGraph->graph(1)->setPen(QPen(QColor(44,160,44),2));
    m_ui->gyroGraph->graph(1)->setName("Y");
    m_ui->gyroGraph->addGraph(); // z
    m_ui->gyroGraph->graph(2)->setPen(QPen(QColor(31,119,180),2));
    m_ui->gyroGraph->graph(2)->setName("Z");
    // Set legend, title and axis names
    m_ui->gyroGraph->legend->setVisible(true);
    m_ui->gyroGraph->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
    m_ui->gyroGraph->legend->setFont(legendFont);
    m_ui->gyroGraph->legend->setSelectedFont(legendFont);
    m_ui->gyroGraph->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);
    m_ui->gyroGraph->yAxis->setLabel("deg/s");
    m_ui->gyroGraph->xAxis->setTickLabels(false);
    m_ui->gyroGraph->plotLayout()->insertRow(0);
    QCPTextElement *titleGyro = new QCPTextElement(m_ui->gyroGraph, "Gyroscope Data", QFont("sans", 8, QFont::Bold));
    m_ui->gyroGraph->plotLayout()->addElement(0, 0, titleGyro);
    m_ui->gyroGraph->plotLayout()->setAutoMargins(QCP::MarginSide(0x00));
    m_ui->gyroGraph->plotLayout()->setRowSpacing(0);
    m_ui->gyroGraph->plotLayout()->setMargins(QMargins(0,0,0,0));
    m_ui->gyroGraph->legend->setFillOrder(QCPLegend::foColumnsFirst);
    // Set range
    m_ui->gyroGraph->xAxis->setRange(0, 40);
    m_ui->gyroGraph->yAxis->setRange(-1, 1);

    // Magnetometer Graph
    // Set graphs
    m_ui->magGraph->addGraph(); // x
    m_ui->magGraph->graph(0)->setPen(QPen(QColor(214,39,40),2));
    m_ui->magGraph->graph(0)->setName("X");
    m_ui->magGraph->addGraph(); // y
    m_ui->magGraph->graph(1)->setPen(QPen(QColor(44,160,44),2));
    m_ui->magGraph->graph(1)->setName("Y");
    m_ui->magGraph->addGraph(); // z
    m_ui->magGraph->graph(2)->setPen(QPen(QColor(31,119,180),2));
    m_ui->magGraph->graph(2)->setName("Z");
    // Set legend, title and axis names
    m_ui->magGraph->legend->setVisible(true);
    m_ui->magGraph->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
    m_ui->magGraph->legend->setFont(legendFont);
    m_ui->magGraph->legend->setSelectedFont(legendFont);
    m_ui->magGraph->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);
    m_ui->magGraph->yAxis->setLabel("mG");
    m_ui->magGraph->xAxis->setTickLabels(false);
    m_ui->magGraph->plotLayout()->insertRow(0);
    QCPTextElement *titleMag = new QCPTextElement(m_ui->magGraph, "Magnetometer Data", QFont("sans", 8, QFont::Bold));
    m_ui->magGraph->plotLayout()->addElement(0, 0, titleMag);
    m_ui->magGraph->plotLayout()->setAutoMargins(QCP::MarginSide(0x00));
    m_ui->magGraph->plotLayout()->setRowSpacing(0);
    m_ui->magGraph->plotLayout()->setMargins(QMargins(0,0,0,0));
    m_ui->magGraph->legend->setFillOrder(QCPLegend::foColumnsFirst);
    // Set range
    m_ui->magGraph->xAxis->setRange(0, 40);
    m_ui->magGraph->yAxis->setRange(-1, 1);

    // RPY Graph
    // Set graphs
    m_ui->rpyGraph->addGraph(); // x
    m_ui->rpyGraph->graph(0)->setPen(QPen(QColor(214,39,40),2));
    m_ui->rpyGraph->graph(0)->setName("Roll");
    m_ui->rpyGraph->addGraph(); // y
    m_ui->rpyGraph->graph(1)->setPen(QPen(QColor(44,160,44),2));
    m_ui->rpyGraph->graph(1)->setName("Pitch");
    m_ui->rpyGraph->addGraph(); // z
    m_ui->rpyGraph->graph(2)->setPen(QPen(QColor(31,119,180),2));
    m_ui->rpyGraph->graph(2)->setName("Yaw");
    // Set legend, title and axis names
    m_ui->rpyGraph->legend->setVisible(true);
    m_ui->rpyGraph->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
    m_ui->rpyGraph->legend->setFont(legendFont);
    m_ui->rpyGraph->legend->setSelectedFont(legendFont);
    m_ui->rpyGraph->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);
    m_ui->rpyGraph->yAxis->setLabel("deg");
    m_ui->rpyGraph->xAxis->setTickLabels(false);
    m_ui->rpyGraph->plotLayout()->insertRow(0);
    QCPTextElement *titleRPY = new QCPTextElement(m_ui->rpyGraph, "Orientation", QFont("sans", 8, QFont::Bold));
    m_ui->rpyGraph->plotLayout()->addElement(0, 0, titleRPY);
    m_ui->rpyGraph->plotLayout()->setAutoMargins(QCP::MarginSide(0x00));
    m_ui->rpyGraph->plotLayout()->setRowSpacing(0);
    m_ui->rpyGraph->plotLayout()->setMargins(QMargins(0,0,0,0));
    m_ui->rpyGraph->legend->setFillOrder(QCPLegend::foColumnsFirst);
    // Set range
    m_ui->rpyGraph->xAxis->setRange(0, 40);
    m_ui->rpyGraph->yAxis->setRange(-200, 200);
    QSharedPointer<QCPAxisTickerFixed> fixedTicker(new QCPAxisTickerFixed);
    m_ui->rpyGraph->yAxis->setTicker(fixedTicker);
    fixedTicker->setTickStep(60);



}
// Writes incoming data to .CSV file
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
// Adds new data to graphs
void MainWindow::updateGraphs(double ax, double ay, double az,
                              double gx, double gy, double gz,
                              double mx, double my, double mz,
                              double yaw, double pitch, double roll
                              ){
    // Update Accelerometer Graph
    m_ui->accelGraph->graph(0)->addData(key,ax);
    m_ui->accelGraph->graph(1)->addData(key,ay);
    m_ui->accelGraph->graph(2)->addData(key,az);

    m_ui->accelGraph->xAxis->setRange(key, 40, Qt::AlignRight);
    m_ui->accelGraph->yAxis->rescale(true);

    m_ui->accelGraph->replot();

    // Update Gyroscope Graph
    m_ui->gyroGraph->graph(0)->addData(key,gx);
    m_ui->gyroGraph->graph(1)->addData(key,gy);
    m_ui->gyroGraph->graph(2)->addData(key,gz);

    m_ui->gyroGraph->xAxis->setRange(key, 40, Qt::AlignRight);
    m_ui->gyroGraph->yAxis->rescale(true);

    m_ui->gyroGraph->replot();

    // Update Magnetometer Graph
    m_ui->magGraph->graph(0)->addData(key,mx);
    m_ui->magGraph->graph(1)->addData(key,my);
    m_ui->magGraph->graph(2)->addData(key,mz);

    m_ui->magGraph->xAxis->setRange(key, 40, Qt::AlignRight);
    m_ui->magGraph->yAxis->rescale(true);

    m_ui->magGraph->replot();

    // Update RPY Graph
    m_ui->rpyGraph->graph(0)->addData(key,roll);
    m_ui->rpyGraph->graph(1)->addData(key,pitch);
    m_ui->rpyGraph->graph(2)->addData(key,yaw);

    m_ui->rpyGraph->xAxis->setRange(key, 40, Qt::AlignRight);

    m_ui->rpyGraph->replot();

    QString rpyVals = QString("Roll: %1\n\nPitch: %2\n\nYaw: %3");
    rpyVals = rpyVals.arg(QString::number(rint(roll)),9).arg(QString::number(rint(pitch)),9).arg(QString::number(rint(yaw)),9);


    m_ui->rpyValue->setText(rpyVals);

    // Increase x value
    key++;

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
    // Save to class variables
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
    m_ui->browseButton->setEnabled(false);
    m_ui->pathToFile->setEnabled(false);
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
    m_ui->browseButton->setEnabled(true);
    m_ui->pathToFile->setEnabled(true);
    m_ui->cbQuaternions->setEnabled(true);
    m_ui->cbRaw->setEnabled(true);
    m_ui->cbRPY->setEnabled(true);
    fileOut.close();
    readyToSave = false;

}

