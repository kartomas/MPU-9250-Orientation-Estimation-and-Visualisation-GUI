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

#include "console.h"

#include <QScrollBar>
#include <QString>
#include <QDebug>

Console::Console(QWidget *parent) :
    QPlainTextEdit(parent),
    charBuffer("")
{
    document()->setMaximumBlockCount(100);
    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::green);
    setPalette(p);
}

void Console::putData(const QByteArray &data)
{
    insertPlainText(data);
    charBuffer.append(data);
//    qDebug()<<"raw:";
//    qDebug()<<data;
//    qDebug();
    // Check both start and end to ensure full block of data was aquired successfully
    if(charBuffer.endsWith("Hz\r\n")){
//        qDebug()<<"buffer:";
//        qDebug() << charBuffer;
        // Split into array
        QStringList dataString = QString::fromUtf8(charBuffer).split(QLatin1Char(' '));
//        Every block is the same so we can access the data by hardcoding the array index
//        instead of looking it up every time by string matching (it is faster as well)
        double ax = dataString[2].toDouble();
        double ay = dataString[5].toDouble();
        double az = dataString[8].toDouble();
        double gx = dataString[11].toDouble();
        double gy = dataString[14].toDouble();
        double gz = dataString[17].toDouble();
        double mx = dataString[20].toDouble();
        double my = dataString[23].toDouble();
        double mz = dataString[26].toDouble();

        double qw = dataString[29].toDouble();
        double qx = dataString[32].toDouble();
        double qy = dataString[35].toDouble();
        double qz = dataString[38].remove("\r\nYaw,").toDouble();

        double yaw = dataString[41].remove(',').toDouble();
        double pitch = dataString[42].remove(',').toDouble();
        double roll = dataString[43].remove("\r\nrate").toDouble();
//    qDebug() << dataString;
//        qDebug() << "ypr";
//qDebug() << yaw;
//         qDebug()<< pitch;
//         qDebug()<< roll;

//        emit sendQuaternions(qw, qx, qy, qz);
        emit sendRPY(roll, pitch, yaw);
        emit sendAccelData(ax, ay, az);
        emit sendGyroData(gx, gy, gz);
        emit sendMagData(mx, my, mz);
        emit sendAllData( ax,  ay,  az,
                          gx,  gy,  gz,
                          mx,  my,  mz,
                          yaw,  pitch,  roll,
                          qw,  qx,  qy,  qz
                         );


//        qDebug()<<ax;
//        qDebug()<<ay;
//        qDebug()<<az;

//        qDebug()<<gx;
//        qDebug()<<gy;
//        qDebug()<<gz;

//        qDebug()<<mx;
//        qDebug()<<my;
//        qDebug()<<mz;
       charBuffer = "";

    }
    QScrollBar *bar = verticalScrollBar();
    bar->setValue(bar->maximum());
}

void Console::setLocalEchoEnabled(bool set)
{
    m_localEchoEnabled = set;
}

void Console::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_Backspace:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
        break;
    default:
        if (m_localEchoEnabled)
            QPlainTextEdit::keyPressEvent(e);
        emit getData(e->text().toLocal8Bit());
    }
}

void Console::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    setFocus();
}

void Console::mouseDoubleClickEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
}

void Console::contextMenuEvent(QContextMenuEvent *e)
{
    Q_UNUSED(e)
}
