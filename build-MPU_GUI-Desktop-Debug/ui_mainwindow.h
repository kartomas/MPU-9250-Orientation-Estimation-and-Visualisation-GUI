/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "console.h"
#include "qcustomplot.h"
#include "viz3D.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout;
    QAction *actionAboutQt;
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionConfigure;
    QAction *actionClear;
    QAction *actionQuit;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab_3d;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_3;
    Viz3D *openGLWidget;
    QVBoxLayout *verticalLayout_2;
    QCustomPlot *accelGraph;
    QCustomPlot *gyroGraph;
    QCustomPlot *magGraph;
    QHBoxLayout *horizontalLayout_6;
    QLabel *rpyValue;
    QCustomPlot *rpyGraph;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *cbQuaternions;
    QCheckBox *cbRPY;
    QCheckBox *cbRaw;
    QSpacerItem *horizontalSpacer;
    QPushButton *enableSavingButton;
    QPushButton *disableSavingButton;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QTextEdit *pathToFile;
    QPushButton *browseButton;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout;
    Console *m_console;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1011, 873);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionAboutQt = new QAction(MainWindow);
        actionAboutQt->setObjectName(QString::fromUtf8("actionAboutQt"));
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QString::fromUtf8("actionConnect"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/connect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConnect->setIcon(icon);
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName(QString::fromUtf8("actionDisconnect"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/disconnect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDisconnect->setIcon(icon1);
        actionConfigure = new QAction(MainWindow);
        actionConfigure->setObjectName(QString::fromUtf8("actionConfigure"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConfigure->setIcon(icon2);
        actionClear = new QAction(MainWindow);
        actionClear->setObjectName(QString::fromUtf8("actionClear"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClear->setIcon(icon3);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/application-exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuit->setIcon(icon4);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setMinimumSize(QSize(100, 100));
        centralWidget->setStyleSheet(QString::fromUtf8("border-color: rgb(100, 0, 0);"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab_3d = new QWidget();
        tab_3d->setObjectName(QString::fromUtf8("tab_3d"));
        sizePolicy.setHeightForWidth(tab_3d->sizePolicy().hasHeightForWidth());
        tab_3d->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(tab_3d);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(5, 5, 5, 5);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, -1, -1);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, -1, -1);
        openGLWidget = new Viz3D(tab_3d);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy1);
        openGLWidget->setMinimumSize(QSize(450, 450));

        verticalLayout_3->addWidget(openGLWidget);


        horizontalLayout_5->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, -1, -1);
        accelGraph = new QCustomPlot(tab_3d);
        accelGraph->setObjectName(QString::fromUtf8("accelGraph"));
        sizePolicy.setHeightForWidth(accelGraph->sizePolicy().hasHeightForWidth());
        accelGraph->setSizePolicy(sizePolicy);
        accelGraph->setMinimumSize(QSize(0, 150));

        verticalLayout_2->addWidget(accelGraph);

        gyroGraph = new QCustomPlot(tab_3d);
        gyroGraph->setObjectName(QString::fromUtf8("gyroGraph"));
        sizePolicy.setHeightForWidth(gyroGraph->sizePolicy().hasHeightForWidth());
        gyroGraph->setSizePolicy(sizePolicy);
        gyroGraph->setMinimumSize(QSize(0, 150));

        verticalLayout_2->addWidget(gyroGraph);

        magGraph = new QCustomPlot(tab_3d);
        magGraph->setObjectName(QString::fromUtf8("magGraph"));
        sizePolicy.setHeightForWidth(magGraph->sizePolicy().hasHeightForWidth());
        magGraph->setSizePolicy(sizePolicy);
        magGraph->setMinimumSize(QSize(0, 150));

        verticalLayout_2->addWidget(magGraph);


        horizontalLayout_5->addLayout(verticalLayout_2);


        verticalLayout_5->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(5);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, -1, -1);
        rpyValue = new QLabel(tab_3d);
        rpyValue->setObjectName(QString::fromUtf8("rpyValue"));
        rpyValue->setMinimumSize(QSize(80, 0));

        horizontalLayout_6->addWidget(rpyValue);

        rpyGraph = new QCustomPlot(tab_3d);
        rpyGraph->setObjectName(QString::fromUtf8("rpyGraph"));
        sizePolicy.setHeightForWidth(rpyGraph->sizePolicy().hasHeightForWidth());
        rpyGraph->setSizePolicy(sizePolicy);
        rpyGraph->setMinimumSize(QSize(0, 150));

        horizontalLayout_6->addWidget(rpyGraph);


        verticalLayout_5->addLayout(horizontalLayout_6);

        groupBox = new QGroupBox(tab_3d);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy2);
        groupBox->setMinimumSize(QSize(300, 140));
        groupBox->setMaximumSize(QSize(900, 16777215));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(5, 5, 5, 5);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(10);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(5, 5, 5, 5);
        cbQuaternions = new QCheckBox(groupBox);
        cbQuaternions->setObjectName(QString::fromUtf8("cbQuaternions"));

        horizontalLayout_4->addWidget(cbQuaternions);

        cbRPY = new QCheckBox(groupBox);
        cbRPY->setObjectName(QString::fromUtf8("cbRPY"));

        horizontalLayout_4->addWidget(cbRPY);

        cbRaw = new QCheckBox(groupBox);
        cbRaw->setObjectName(QString::fromUtf8("cbRaw"));

        horizontalLayout_4->addWidget(cbRaw);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        enableSavingButton = new QPushButton(groupBox);
        enableSavingButton->setObjectName(QString::fromUtf8("enableSavingButton"));
        enableSavingButton->setEnabled(true);
        sizePolicy1.setHeightForWidth(enableSavingButton->sizePolicy().hasHeightForWidth());
        enableSavingButton->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(enableSavingButton);

        disableSavingButton = new QPushButton(groupBox);
        disableSavingButton->setObjectName(QString::fromUtf8("disableSavingButton"));
        disableSavingButton->setEnabled(false);
        sizePolicy1.setHeightForWidth(disableSavingButton->sizePolicy().hasHeightForWidth());
        disableSavingButton->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(disableSavingButton);


        verticalLayout_4->addLayout(horizontalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 5, 5, 5);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        pathToFile = new QTextEdit(groupBox);
        pathToFile->setObjectName(QString::fromUtf8("pathToFile"));
        pathToFile->setEnabled(true);
        sizePolicy2.setHeightForWidth(pathToFile->sizePolicy().hasHeightForWidth());
        pathToFile->setSizePolicy(sizePolicy2);
        pathToFile->setMinimumSize(QSize(500, 10));
        pathToFile->setBaseSize(QSize(10, 10));

        horizontalLayout_2->addWidget(pathToFile);

        browseButton = new QPushButton(groupBox);
        browseButton->setObjectName(QString::fromUtf8("browseButton"));
        sizePolicy1.setHeightForWidth(browseButton->sizePolicy().hasHeightForWidth());
        browseButton->setSizePolicy(sizePolicy1);
        browseButton->setMinimumSize(QSize(0, 0));

        horizontalLayout_2->addWidget(browseButton);


        verticalLayout_4->addLayout(horizontalLayout_2);


        gridLayout_2->addLayout(verticalLayout_4, 0, 0, 1, 1);


        verticalLayout_5->addWidget(groupBox);


        gridLayout->addLayout(verticalLayout_5, 0, 0, 1, 1);

        tabWidget->addTab(tab_3d, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        sizePolicy.setHeightForWidth(tab_2->sizePolicy().hasHeightForWidth());
        tab_2->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(tab_2);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        m_console = new Console(tab_2);
        m_console->setObjectName(QString::fromUtf8("m_console"));
        sizePolicy.setHeightForWidth(m_console->sizePolicy().hasHeightForWidth());
        m_console->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(m_console);

        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setFloatable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        mainToolBar->addAction(actionConnect);
        mainToolBar->addAction(actionDisconnect);
        mainToolBar->addAction(actionConfigure);
        mainToolBar->addAction(actionClear);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MPU GUI", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "&About", nullptr));
#if QT_CONFIG(tooltip)
        actionAbout->setToolTip(QCoreApplication::translate("MainWindow", "About program", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionAbout->setShortcut(QCoreApplication::translate("MainWindow", "Alt+A", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAboutQt->setText(QCoreApplication::translate("MainWindow", "About Qt", nullptr));
        actionConnect->setText(QCoreApplication::translate("MainWindow", "C&onnect", nullptr));
#if QT_CONFIG(tooltip)
        actionConnect->setToolTip(QCoreApplication::translate("MainWindow", "Connect to serial port", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionConnect->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionDisconnect->setText(QCoreApplication::translate("MainWindow", "&Disconnect", nullptr));
#if QT_CONFIG(tooltip)
        actionDisconnect->setToolTip(QCoreApplication::translate("MainWindow", "Disconnect from serial port", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionDisconnect->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+D", nullptr));
#endif // QT_CONFIG(shortcut)
        actionConfigure->setText(QCoreApplication::translate("MainWindow", "&Configure", nullptr));
#if QT_CONFIG(tooltip)
        actionConfigure->setToolTip(QCoreApplication::translate("MainWindow", "Configure serial port", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionConfigure->setShortcut(QCoreApplication::translate("MainWindow", "Alt+C", nullptr));
#endif // QT_CONFIG(shortcut)
        actionClear->setText(QCoreApplication::translate("MainWindow", "C&lear", nullptr));
#if QT_CONFIG(tooltip)
        actionClear->setToolTip(QCoreApplication::translate("MainWindow", "Clear data", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionClear->setShortcut(QCoreApplication::translate("MainWindow", "Alt+L", nullptr));
#endif // QT_CONFIG(shortcut)
        actionQuit->setText(QCoreApplication::translate("MainWindow", "&Quit", nullptr));
#if QT_CONFIG(shortcut)
        actionQuit->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        rpyValue->setText(QCoreApplication::translate("MainWindow", "Roll: 0\n"
"\n"
"Pitch: 0\n"
"\n"
"Yaw: 0", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Save Data to File", nullptr));
        cbQuaternions->setText(QCoreApplication::translate("MainWindow", "Quaternions", nullptr));
        cbRPY->setText(QCoreApplication::translate("MainWindow", "RPY Angles", nullptr));
        cbRaw->setText(QCoreApplication::translate("MainWindow", "Raw Sensor Data", nullptr));
        enableSavingButton->setText(QCoreApplication::translate("MainWindow", "Enable", nullptr));
        disableSavingButton->setText(QCoreApplication::translate("MainWindow", "Disable", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Path to File:", nullptr));
        browseButton->setText(QCoreApplication::translate("MainWindow", "Browse...", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3d), QCoreApplication::translate("MainWindow", "Main Page", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Serial Monitor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
