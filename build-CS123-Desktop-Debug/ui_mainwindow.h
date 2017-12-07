/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Canvas2D.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionQuit;
    QAction *actionRevert;
    QAction *actionCopy3Dto2D;
    QAction *actionClear;
    QAction *actionUseOrbitingCamera;
    QWidget *centralWidget;
    QGridLayout *gridLayout_10;
    QTabWidget *tabWidget;
    QWidget *tab2D;
    QGridLayout *gridLayout_11;
    QScrollArea *scrollArea;
    Canvas2D *canvas2D;
    QWidget *tab3D;
    QGridLayout *gridLayout_12;
    QWidget *canvas3D;
    QDockWidget *shapesDock;
    QWidget *shapesDockContents;
    QVBoxLayout *verticalLayout_7;
    QCheckBox *showSceneviewInstead;
    QGroupBox *shapeType;
    QVBoxLayout *verticalLayout_8;
    QRadioButton *shapeTypeCube;
    QRadioButton *shapeTypeCone;
    QRadioButton *shapeTypeSphere;
    QRadioButton *shapeTypeCylinder;
    QRadioButton *shapeTypeTorus;
    QRadioButton *shapeTypeSpecial1;
    QRadioButton *shapeTypeSpecial2;
    QGroupBox *shapeParameters;
    QGridLayout *gridLayout_4;
    QLabel *shapeParameterLabel1;
    QLabel *shapeParameterLabel2;
    QLabel *shapeParameterLabel3;
    QSlider *shapeParameterSlider1;
    QSlider *shapeParameterSlider2;
    QSlider *shapeParameterSlider3;
    QLineEdit *shapeParameterTextbox1;
    QLineEdit *shapeParameterTextbox2;
    QLineEdit *shapeParameterTextbox3;
    QCheckBox *useLightingCheckbox;
    QCheckBox *drawWireframeCheckbox;
    QCheckBox *drawNormalsCheckbox;
    QCheckBox *deferredLightCheckbox;
    QWidget *shapesDockEmptySpace;
    QDockWidget *rayDock;
    QWidget *rayDockContents;
    QVBoxLayout *verticalLayout_4;
    QWidget *rayAllOrNone;
    QHBoxLayout *horizontalLayout;
    QPushButton *rayAllButton;
    QPushButton *rayNoneButton;
    QGroupBox *rayFeatures;
    QVBoxLayout *verticalLayout_11;
    QCheckBox *raySuperSamping;
    QWidget *raySuperSamples;
    QGridLayout *gridLayout_7;
    QLabel *raySuperSamplesLabel;
    QLineEdit *raySuperSamplesTextbox;
    QCheckBox *rayAntiAliasing;
    QCheckBox *rayShadows;
    QCheckBox *rayTextureMapping;
    QCheckBox *rayReflection;
    QCheckBox *rayRefraction;
    QCheckBox *rayMultiThreading;
    QGroupBox *rayLighting;
    QVBoxLayout *verticalLayout_9;
    QCheckBox *rayPointLights;
    QCheckBox *rayDirectionalLights;
    QCheckBox *raySpotLights;
    QPushButton *rayRenderButton;
    QPushButton *rayStopRenderingButton;
    QWidget *rayDockEmptySpace;
    QDockWidget *camtransDock;
    QWidget *camtransDockContents;
    QVBoxLayout *verticalLayout_10;
    QCheckBox *cameraOrbitCheckbox;
    QGroupBox *cameraPosition;
    QGridLayout *gridLayout;
    QLabel *cameraPositionLabelX;
    QLabel *cameraPositionLabelY;
    QLabel *cameraPositionLabelZ;
    QDial *transX;
    QDial *transY;
    QDial *transZ;
    QGroupBox *cameraRotation;
    QVBoxLayout *verticalLayout_13;
    QWidget *cameraRotation_2;
    QGridLayout *gridLayout_15;
    QDial *rotU;
    QDial *rotV;
    QDial *rotW;
    QLabel *cameraRotationLabelYaw;
    QLabel *cameraRotationLabelPitch;
    QLabel *cameraRotationLabelRoll;
    QPushButton *resetUpVector;
    QGroupBox *cameraResetAxis;
    QGridLayout *gridLayout_14;
    QPushButton *xAxisButton;
    QPushButton *yAxisButton;
    QPushButton *zAxisButton;
    QPushButton *axonometricButton;
    QWidget *cameraFrustum;
    QGridLayout *gridLayout_5;
    QLabel *cameraFovLabel;
    QLineEdit *cameraFovTextbox;
    QSlider *cameraFovSlider;
    QLabel *cameraNearLabel;
    QLineEdit *cameraNearTextbox;
    QLabel *cameraFarLabel;
    QLineEdit *cameraFarTextbox;
    QSlider *cameraNearSlider;
    QSlider *cameraFarSlider;
    QPushButton *resetSliders;
    QLabel *cameraAspectRatio;
    QLabel *label;
    QWidget *cameraDockEmptySpace;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuToolbars;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(600, 3112);
        MainWindow->setDockNestingEnabled(true);
        MainWindow->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks|QMainWindow::ForceTabbedDocks|QMainWindow::VerticalTabs);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionRevert = new QAction(MainWindow);
        actionRevert->setObjectName(QStringLiteral("actionRevert"));
        actionRevert->setEnabled(true);
        actionCopy3Dto2D = new QAction(MainWindow);
        actionCopy3Dto2D->setObjectName(QStringLiteral("actionCopy3Dto2D"));
        actionClear = new QAction(MainWindow);
        actionClear->setObjectName(QStringLiteral("actionClear"));
        actionUseOrbitingCamera = new QAction(MainWindow);
        actionUseOrbitingCamera->setObjectName(QStringLiteral("actionUseOrbitingCamera"));
        actionUseOrbitingCamera->setCheckable(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_10 = new QGridLayout(centralWidget);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        gridLayout_10->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::North);
        tab2D = new QWidget();
        tab2D->setObjectName(QStringLiteral("tab2D"));
        gridLayout_11 = new QGridLayout(tab2D);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        gridLayout_11->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(tab2D);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setFrameShadow(QFrame::Plain);
        scrollArea->setLineWidth(0);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setWidgetResizable(true);
        canvas2D = new Canvas2D();
        canvas2D->setObjectName(QStringLiteral("canvas2D"));
        canvas2D->setGeometry(QRect(0, 0, 100, 30));
        scrollArea->setWidget(canvas2D);

        gridLayout_11->addWidget(scrollArea, 0, 0, 1, 1);

        tabWidget->addTab(tab2D, QString());
        tab3D = new QWidget();
        tab3D->setObjectName(QStringLiteral("tab3D"));
        gridLayout_12 = new QGridLayout(tab3D);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        gridLayout_12->setContentsMargins(0, 0, 0, 0);
        canvas3D = new QWidget(tab3D);
        canvas3D->setObjectName(QStringLiteral("canvas3D"));

        gridLayout_12->addWidget(canvas3D, 0, 0, 1, 1);

        tabWidget->addTab(tab3D, QString());

        gridLayout_10->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        shapesDock = new QDockWidget(MainWindow);
        shapesDock->setObjectName(QStringLiteral("shapesDock"));
        shapesDockContents = new QWidget();
        shapesDockContents->setObjectName(QStringLiteral("shapesDockContents"));
        verticalLayout_7 = new QVBoxLayout(shapesDockContents);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        showSceneviewInstead = new QCheckBox(shapesDockContents);
        showSceneviewInstead->setObjectName(QStringLiteral("showSceneviewInstead"));

        verticalLayout_7->addWidget(showSceneviewInstead);

        shapeType = new QGroupBox(shapesDockContents);
        shapeType->setObjectName(QStringLiteral("shapeType"));
        verticalLayout_8 = new QVBoxLayout(shapeType);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(-1, 5, -1, 5);
        shapeTypeCube = new QRadioButton(shapeType);
        shapeTypeCube->setObjectName(QStringLiteral("shapeTypeCube"));
        shapeTypeCube->setChecked(true);

        verticalLayout_8->addWidget(shapeTypeCube);

        shapeTypeCone = new QRadioButton(shapeType);
        shapeTypeCone->setObjectName(QStringLiteral("shapeTypeCone"));

        verticalLayout_8->addWidget(shapeTypeCone);

        shapeTypeSphere = new QRadioButton(shapeType);
        shapeTypeSphere->setObjectName(QStringLiteral("shapeTypeSphere"));

        verticalLayout_8->addWidget(shapeTypeSphere);

        shapeTypeCylinder = new QRadioButton(shapeType);
        shapeTypeCylinder->setObjectName(QStringLiteral("shapeTypeCylinder"));

        verticalLayout_8->addWidget(shapeTypeCylinder);

        shapeTypeTorus = new QRadioButton(shapeType);
        shapeTypeTorus->setObjectName(QStringLiteral("shapeTypeTorus"));

        verticalLayout_8->addWidget(shapeTypeTorus);

        shapeTypeSpecial1 = new QRadioButton(shapeType);
        shapeTypeSpecial1->setObjectName(QStringLiteral("shapeTypeSpecial1"));

        verticalLayout_8->addWidget(shapeTypeSpecial1);

        shapeTypeSpecial2 = new QRadioButton(shapeType);
        shapeTypeSpecial2->setObjectName(QStringLiteral("shapeTypeSpecial2"));

        verticalLayout_8->addWidget(shapeTypeSpecial2);


        verticalLayout_7->addWidget(shapeType);

        shapeParameters = new QGroupBox(shapesDockContents);
        shapeParameters->setObjectName(QStringLiteral("shapeParameters"));
        gridLayout_4 = new QGridLayout(shapeParameters);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setVerticalSpacing(5);
        gridLayout_4->setContentsMargins(-1, 5, -1, 5);
        shapeParameterLabel1 = new QLabel(shapeParameters);
        shapeParameterLabel1->setObjectName(QStringLiteral("shapeParameterLabel1"));

        gridLayout_4->addWidget(shapeParameterLabel1, 0, 0, 1, 1);

        shapeParameterLabel2 = new QLabel(shapeParameters);
        shapeParameterLabel2->setObjectName(QStringLiteral("shapeParameterLabel2"));

        gridLayout_4->addWidget(shapeParameterLabel2, 2, 0, 1, 1);

        shapeParameterLabel3 = new QLabel(shapeParameters);
        shapeParameterLabel3->setObjectName(QStringLiteral("shapeParameterLabel3"));

        gridLayout_4->addWidget(shapeParameterLabel3, 4, 0, 1, 1);

        shapeParameterSlider1 = new QSlider(shapeParameters);
        shapeParameterSlider1->setObjectName(QStringLiteral("shapeParameterSlider1"));
        shapeParameterSlider1->setMinimumSize(QSize(100, 0));
        shapeParameterSlider1->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(shapeParameterSlider1, 0, 1, 1, 1);

        shapeParameterSlider2 = new QSlider(shapeParameters);
        shapeParameterSlider2->setObjectName(QStringLiteral("shapeParameterSlider2"));
        shapeParameterSlider2->setMinimumSize(QSize(100, 0));
        shapeParameterSlider2->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(shapeParameterSlider2, 2, 1, 1, 1);

        shapeParameterSlider3 = new QSlider(shapeParameters);
        shapeParameterSlider3->setObjectName(QStringLiteral("shapeParameterSlider3"));
        shapeParameterSlider3->setMinimumSize(QSize(100, 0));
        shapeParameterSlider3->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(shapeParameterSlider3, 4, 1, 1, 1);

        shapeParameterTextbox1 = new QLineEdit(shapeParameters);
        shapeParameterTextbox1->setObjectName(QStringLiteral("shapeParameterTextbox1"));
        shapeParameterTextbox1->setMinimumSize(QSize(40, 0));
        shapeParameterTextbox1->setMaximumSize(QSize(40, 16777215));

        gridLayout_4->addWidget(shapeParameterTextbox1, 0, 2, 1, 1);

        shapeParameterTextbox2 = new QLineEdit(shapeParameters);
        shapeParameterTextbox2->setObjectName(QStringLiteral("shapeParameterTextbox2"));
        shapeParameterTextbox2->setMinimumSize(QSize(40, 0));
        shapeParameterTextbox2->setMaximumSize(QSize(40, 16777215));

        gridLayout_4->addWidget(shapeParameterTextbox2, 2, 2, 1, 1);

        shapeParameterTextbox3 = new QLineEdit(shapeParameters);
        shapeParameterTextbox3->setObjectName(QStringLiteral("shapeParameterTextbox3"));
        shapeParameterTextbox3->setMinimumSize(QSize(40, 0));
        shapeParameterTextbox3->setMaximumSize(QSize(40, 16777215));

        gridLayout_4->addWidget(shapeParameterTextbox3, 4, 2, 1, 1);


        verticalLayout_7->addWidget(shapeParameters);

        useLightingCheckbox = new QCheckBox(shapesDockContents);
        useLightingCheckbox->setObjectName(QStringLiteral("useLightingCheckbox"));

        verticalLayout_7->addWidget(useLightingCheckbox);

        drawWireframeCheckbox = new QCheckBox(shapesDockContents);
        drawWireframeCheckbox->setObjectName(QStringLiteral("drawWireframeCheckbox"));

        verticalLayout_7->addWidget(drawWireframeCheckbox);

        drawNormalsCheckbox = new QCheckBox(shapesDockContents);
        drawNormalsCheckbox->setObjectName(QStringLiteral("drawNormalsCheckbox"));

        verticalLayout_7->addWidget(drawNormalsCheckbox);

        deferredLightCheckbox = new QCheckBox(shapesDockContents);
        deferredLightCheckbox->setObjectName(QStringLiteral("deferredLightCheckbox"));

        verticalLayout_7->addWidget(deferredLightCheckbox);

        shapesDockEmptySpace = new QWidget(shapesDockContents);
        shapesDockEmptySpace->setObjectName(QStringLiteral("shapesDockEmptySpace"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(shapesDockEmptySpace->sizePolicy().hasHeightForWidth());
        shapesDockEmptySpace->setSizePolicy(sizePolicy);

        verticalLayout_7->addWidget(shapesDockEmptySpace);

        shapesDock->setWidget(shapesDockContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), shapesDock);
        rayDock = new QDockWidget(MainWindow);
        rayDock->setObjectName(QStringLiteral("rayDock"));
        rayDockContents = new QWidget();
        rayDockContents->setObjectName(QStringLiteral("rayDockContents"));
        verticalLayout_4 = new QVBoxLayout(rayDockContents);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        rayAllOrNone = new QWidget(rayDockContents);
        rayAllOrNone->setObjectName(QStringLiteral("rayAllOrNone"));
        horizontalLayout = new QHBoxLayout(rayAllOrNone);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        rayAllButton = new QPushButton(rayAllOrNone);
        rayAllButton->setObjectName(QStringLiteral("rayAllButton"));

        horizontalLayout->addWidget(rayAllButton);

        rayNoneButton = new QPushButton(rayAllOrNone);
        rayNoneButton->setObjectName(QStringLiteral("rayNoneButton"));

        horizontalLayout->addWidget(rayNoneButton);


        verticalLayout_4->addWidget(rayAllOrNone);

        rayFeatures = new QGroupBox(rayDockContents);
        rayFeatures->setObjectName(QStringLiteral("rayFeatures"));
        verticalLayout_11 = new QVBoxLayout(rayFeatures);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(-1, 5, -1, 5);
        raySuperSamping = new QCheckBox(rayFeatures);
        raySuperSamping->setObjectName(QStringLiteral("raySuperSamping"));

        verticalLayout_11->addWidget(raySuperSamping);

        raySuperSamples = new QWidget(rayFeatures);
        raySuperSamples->setObjectName(QStringLiteral("raySuperSamples"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(raySuperSamples->sizePolicy().hasHeightForWidth());
        raySuperSamples->setSizePolicy(sizePolicy1);
        gridLayout_7 = new QGridLayout(raySuperSamples);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        gridLayout_7->setHorizontalSpacing(6);
        gridLayout_7->setContentsMargins(-1, 0, -1, 0);
        raySuperSamplesLabel = new QLabel(raySuperSamples);
        raySuperSamplesLabel->setObjectName(QStringLiteral("raySuperSamplesLabel"));
        sizePolicy1.setHeightForWidth(raySuperSamplesLabel->sizePolicy().hasHeightForWidth());
        raySuperSamplesLabel->setSizePolicy(sizePolicy1);

        gridLayout_7->addWidget(raySuperSamplesLabel, 1, 1, 1, 1);

        raySuperSamplesTextbox = new QLineEdit(raySuperSamples);
        raySuperSamplesTextbox->setObjectName(QStringLiteral("raySuperSamplesTextbox"));
        raySuperSamplesTextbox->setEnabled(false);
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(raySuperSamplesTextbox->sizePolicy().hasHeightForWidth());
        raySuperSamplesTextbox->setSizePolicy(sizePolicy2);
        raySuperSamplesTextbox->setMinimumSize(QSize(40, 0));
        raySuperSamplesTextbox->setMaximumSize(QSize(40, 16777215));

        gridLayout_7->addWidget(raySuperSamplesTextbox, 1, 0, 1, 1);


        verticalLayout_11->addWidget(raySuperSamples);

        rayAntiAliasing = new QCheckBox(rayFeatures);
        rayAntiAliasing->setObjectName(QStringLiteral("rayAntiAliasing"));

        verticalLayout_11->addWidget(rayAntiAliasing);

        rayShadows = new QCheckBox(rayFeatures);
        rayShadows->setObjectName(QStringLiteral("rayShadows"));

        verticalLayout_11->addWidget(rayShadows);

        rayTextureMapping = new QCheckBox(rayFeatures);
        rayTextureMapping->setObjectName(QStringLiteral("rayTextureMapping"));

        verticalLayout_11->addWidget(rayTextureMapping);

        rayReflection = new QCheckBox(rayFeatures);
        rayReflection->setObjectName(QStringLiteral("rayReflection"));

        verticalLayout_11->addWidget(rayReflection);

        rayRefraction = new QCheckBox(rayFeatures);
        rayRefraction->setObjectName(QStringLiteral("rayRefraction"));

        verticalLayout_11->addWidget(rayRefraction);

        rayMultiThreading = new QCheckBox(rayFeatures);
        rayMultiThreading->setObjectName(QStringLiteral("rayMultiThreading"));

        verticalLayout_11->addWidget(rayMultiThreading);


        verticalLayout_4->addWidget(rayFeatures);

        rayLighting = new QGroupBox(rayDockContents);
        rayLighting->setObjectName(QStringLiteral("rayLighting"));
        verticalLayout_9 = new QVBoxLayout(rayLighting);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(-1, 5, -1, 5);
        rayPointLights = new QCheckBox(rayLighting);
        rayPointLights->setObjectName(QStringLiteral("rayPointLights"));

        verticalLayout_9->addWidget(rayPointLights);

        rayDirectionalLights = new QCheckBox(rayLighting);
        rayDirectionalLights->setObjectName(QStringLiteral("rayDirectionalLights"));

        verticalLayout_9->addWidget(rayDirectionalLights);

        raySpotLights = new QCheckBox(rayLighting);
        raySpotLights->setObjectName(QStringLiteral("raySpotLights"));

        verticalLayout_9->addWidget(raySpotLights);


        verticalLayout_4->addWidget(rayLighting);

        rayRenderButton = new QPushButton(rayDockContents);
        rayRenderButton->setObjectName(QStringLiteral("rayRenderButton"));

        verticalLayout_4->addWidget(rayRenderButton);

        rayStopRenderingButton = new QPushButton(rayDockContents);
        rayStopRenderingButton->setObjectName(QStringLiteral("rayStopRenderingButton"));

        verticalLayout_4->addWidget(rayStopRenderingButton);

        rayDockEmptySpace = new QWidget(rayDockContents);
        rayDockEmptySpace->setObjectName(QStringLiteral("rayDockEmptySpace"));
        sizePolicy.setHeightForWidth(rayDockEmptySpace->sizePolicy().hasHeightForWidth());
        rayDockEmptySpace->setSizePolicy(sizePolicy);

        verticalLayout_4->addWidget(rayDockEmptySpace);

        rayDock->setWidget(rayDockContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), rayDock);
        camtransDock = new QDockWidget(MainWindow);
        camtransDock->setObjectName(QStringLiteral("camtransDock"));
        camtransDockContents = new QWidget();
        camtransDockContents->setObjectName(QStringLiteral("camtransDockContents"));
        verticalLayout_10 = new QVBoxLayout(camtransDockContents);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        cameraOrbitCheckbox = new QCheckBox(camtransDockContents);
        cameraOrbitCheckbox->setObjectName(QStringLiteral("cameraOrbitCheckbox"));

        verticalLayout_10->addWidget(cameraOrbitCheckbox);

        cameraPosition = new QGroupBox(camtransDockContents);
        cameraPosition->setObjectName(QStringLiteral("cameraPosition"));
        gridLayout = new QGridLayout(cameraPosition);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setVerticalSpacing(5);
        gridLayout->setContentsMargins(-1, 5, -1, 5);
        cameraPositionLabelX = new QLabel(cameraPosition);
        cameraPositionLabelX->setObjectName(QStringLiteral("cameraPositionLabelX"));
        cameraPositionLabelX->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(cameraPositionLabelX, 1, 0, 1, 1);

        cameraPositionLabelY = new QLabel(cameraPosition);
        cameraPositionLabelY->setObjectName(QStringLiteral("cameraPositionLabelY"));
        cameraPositionLabelY->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(cameraPositionLabelY, 1, 1, 1, 1);

        cameraPositionLabelZ = new QLabel(cameraPosition);
        cameraPositionLabelZ->setObjectName(QStringLiteral("cameraPositionLabelZ"));
        cameraPositionLabelZ->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(cameraPositionLabelZ, 1, 2, 1, 1);

        transX = new QDial(cameraPosition);
        transX->setObjectName(QStringLiteral("transX"));
        transX->setMinimumSize(QSize(60, 60));
        transX->setMaximumSize(QSize(60, 60));
        transX->setMinimum(-360);
        transX->setMaximum(360);
        transX->setSingleStep(10);
        transX->setPageStep(30);
        transX->setOrientation(Qt::Horizontal);
        transX->setInvertedControls(true);
        transX->setWrapping(true);

        gridLayout->addWidget(transX, 0, 0, 1, 1);

        transY = new QDial(cameraPosition);
        transY->setObjectName(QStringLiteral("transY"));
        transY->setMinimumSize(QSize(60, 60));
        transY->setMaximumSize(QSize(60, 60));
        transY->setMinimum(-360);
        transY->setMaximum(360);
        transY->setSingleStep(10);
        transY->setPageStep(30);
        transY->setOrientation(Qt::Horizontal);
        transY->setInvertedControls(true);
        transY->setWrapping(true);

        gridLayout->addWidget(transY, 0, 1, 1, 1);

        transZ = new QDial(cameraPosition);
        transZ->setObjectName(QStringLiteral("transZ"));
        transZ->setMinimumSize(QSize(60, 60));
        transZ->setMaximumSize(QSize(60, 60));
        transZ->setMinimum(-360);
        transZ->setMaximum(360);
        transZ->setSingleStep(10);
        transZ->setPageStep(30);
        transZ->setOrientation(Qt::Horizontal);
        transZ->setInvertedControls(true);
        transZ->setWrapping(true);

        gridLayout->addWidget(transZ, 0, 2, 1, 1);


        verticalLayout_10->addWidget(cameraPosition);

        cameraRotation = new QGroupBox(camtransDockContents);
        cameraRotation->setObjectName(QStringLiteral("cameraRotation"));
        cameraRotation->setEnabled(true);
        verticalLayout_13 = new QVBoxLayout(cameraRotation);
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        verticalLayout_13->setContentsMargins(-1, 5, -1, 5);
        cameraRotation_2 = new QWidget(cameraRotation);
        cameraRotation_2->setObjectName(QStringLiteral("cameraRotation_2"));
        gridLayout_15 = new QGridLayout(cameraRotation_2);
        gridLayout_15->setSpacing(6);
        gridLayout_15->setContentsMargins(11, 11, 11, 11);
        gridLayout_15->setObjectName(QStringLiteral("gridLayout_15"));
        gridLayout_15->setVerticalSpacing(18);
        gridLayout_15->setContentsMargins(0, 0, 0, 0);
        rotU = new QDial(cameraRotation_2);
        rotU->setObjectName(QStringLiteral("rotU"));
        rotU->setMinimumSize(QSize(60, 60));
        rotU->setMaximumSize(QSize(60, 60));
        rotU->setMinimum(-360);
        rotU->setMaximum(360);
        rotU->setSingleStep(10);
        rotU->setPageStep(30);
        rotU->setOrientation(Qt::Horizontal);
        rotU->setInvertedControls(true);
        rotU->setWrapping(true);

        gridLayout_15->addWidget(rotU, 0, 0, 1, 1);

        rotV = new QDial(cameraRotation_2);
        rotV->setObjectName(QStringLiteral("rotV"));
        rotV->setMinimumSize(QSize(60, 60));
        rotV->setMaximumSize(QSize(60, 60));
        rotV->setMinimum(-360);
        rotV->setMaximum(360);
        rotV->setSingleStep(10);
        rotV->setPageStep(30);
        rotV->setOrientation(Qt::Horizontal);
        rotV->setInvertedControls(true);
        rotV->setWrapping(true);

        gridLayout_15->addWidget(rotV, 0, 1, 1, 1);

        rotW = new QDial(cameraRotation_2);
        rotW->setObjectName(QStringLiteral("rotW"));
        rotW->setMinimumSize(QSize(60, 60));
        rotW->setMaximumSize(QSize(60, 60));
        rotW->setMinimum(-360);
        rotW->setMaximum(360);
        rotW->setSingleStep(10);
        rotW->setPageStep(30);
        rotW->setOrientation(Qt::Horizontal);
        rotW->setInvertedControls(true);
        rotW->setWrapping(true);

        gridLayout_15->addWidget(rotW, 0, 2, 1, 1);

        cameraRotationLabelYaw = new QLabel(cameraRotation_2);
        cameraRotationLabelYaw->setObjectName(QStringLiteral("cameraRotationLabelYaw"));
        cameraRotationLabelYaw->setAlignment(Qt::AlignCenter);

        gridLayout_15->addWidget(cameraRotationLabelYaw, 1, 0, 1, 1);

        cameraRotationLabelPitch = new QLabel(cameraRotation_2);
        cameraRotationLabelPitch->setObjectName(QStringLiteral("cameraRotationLabelPitch"));
        cameraRotationLabelPitch->setAlignment(Qt::AlignCenter);

        gridLayout_15->addWidget(cameraRotationLabelPitch, 1, 1, 1, 1);

        cameraRotationLabelRoll = new QLabel(cameraRotation_2);
        cameraRotationLabelRoll->setObjectName(QStringLiteral("cameraRotationLabelRoll"));
        cameraRotationLabelRoll->setAlignment(Qt::AlignCenter);

        gridLayout_15->addWidget(cameraRotationLabelRoll, 1, 2, 1, 1);


        verticalLayout_13->addWidget(cameraRotation_2);

        resetUpVector = new QPushButton(cameraRotation);
        resetUpVector->setObjectName(QStringLiteral("resetUpVector"));

        verticalLayout_13->addWidget(resetUpVector);


        verticalLayout_10->addWidget(cameraRotation);

        cameraResetAxis = new QGroupBox(camtransDockContents);
        cameraResetAxis->setObjectName(QStringLiteral("cameraResetAxis"));
        cameraResetAxis->setMinimumSize(QSize(0, 0));
        gridLayout_14 = new QGridLayout(cameraResetAxis);
        gridLayout_14->setSpacing(6);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName(QStringLiteral("gridLayout_14"));
        xAxisButton = new QPushButton(cameraResetAxis);
        xAxisButton->setObjectName(QStringLiteral("xAxisButton"));

        gridLayout_14->addWidget(xAxisButton, 0, 0, 1, 1);

        yAxisButton = new QPushButton(cameraResetAxis);
        yAxisButton->setObjectName(QStringLiteral("yAxisButton"));

        gridLayout_14->addWidget(yAxisButton, 1, 0, 1, 1);

        zAxisButton = new QPushButton(cameraResetAxis);
        zAxisButton->setObjectName(QStringLiteral("zAxisButton"));

        gridLayout_14->addWidget(zAxisButton, 0, 1, 1, 1);

        axonometricButton = new QPushButton(cameraResetAxis);
        axonometricButton->setObjectName(QStringLiteral("axonometricButton"));

        gridLayout_14->addWidget(axonometricButton, 1, 1, 1, 1);


        verticalLayout_10->addWidget(cameraResetAxis);

        cameraFrustum = new QWidget(camtransDockContents);
        cameraFrustum->setObjectName(QStringLiteral("cameraFrustum"));
        gridLayout_5 = new QGridLayout(cameraFrustum);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setVerticalSpacing(5);
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        cameraFovLabel = new QLabel(cameraFrustum);
        cameraFovLabel->setObjectName(QStringLiteral("cameraFovLabel"));

        gridLayout_5->addWidget(cameraFovLabel, 0, 0, 1, 1);

        cameraFovTextbox = new QLineEdit(cameraFrustum);
        cameraFovTextbox->setObjectName(QStringLiteral("cameraFovTextbox"));
        cameraFovTextbox->setMinimumSize(QSize(60, 0));
        cameraFovTextbox->setMaximumSize(QSize(60, 16777215));

        gridLayout_5->addWidget(cameraFovTextbox, 0, 3, 1, 1);

        cameraFovSlider = new QSlider(cameraFrustum);
        cameraFovSlider->setObjectName(QStringLiteral("cameraFovSlider"));
        cameraFovSlider->setMinimumSize(QSize(100, 0));
        cameraFovSlider->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(cameraFovSlider, 0, 1, 1, 1);

        cameraNearLabel = new QLabel(cameraFrustum);
        cameraNearLabel->setObjectName(QStringLiteral("cameraNearLabel"));

        gridLayout_5->addWidget(cameraNearLabel, 1, 0, 1, 1);

        cameraNearTextbox = new QLineEdit(cameraFrustum);
        cameraNearTextbox->setObjectName(QStringLiteral("cameraNearTextbox"));
        cameraNearTextbox->setMinimumSize(QSize(60, 0));
        cameraNearTextbox->setMaximumSize(QSize(60, 16777215));

        gridLayout_5->addWidget(cameraNearTextbox, 1, 3, 1, 1);

        cameraFarLabel = new QLabel(cameraFrustum);
        cameraFarLabel->setObjectName(QStringLiteral("cameraFarLabel"));

        gridLayout_5->addWidget(cameraFarLabel, 2, 0, 1, 1);

        cameraFarTextbox = new QLineEdit(cameraFrustum);
        cameraFarTextbox->setObjectName(QStringLiteral("cameraFarTextbox"));
        cameraFarTextbox->setMinimumSize(QSize(60, 0));
        cameraFarTextbox->setMaximumSize(QSize(60, 16777215));

        gridLayout_5->addWidget(cameraFarTextbox, 2, 3, 1, 1);

        cameraNearSlider = new QSlider(cameraFrustum);
        cameraNearSlider->setObjectName(QStringLiteral("cameraNearSlider"));
        cameraNearSlider->setMinimumSize(QSize(100, 0));
        cameraNearSlider->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(cameraNearSlider, 1, 1, 1, 1);

        cameraFarSlider = new QSlider(cameraFrustum);
        cameraFarSlider->setObjectName(QStringLiteral("cameraFarSlider"));
        cameraFarSlider->setMinimumSize(QSize(100, 0));
        cameraFarSlider->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(cameraFarSlider, 2, 1, 1, 1);


        verticalLayout_10->addWidget(cameraFrustum);

        resetSliders = new QPushButton(camtransDockContents);
        resetSliders->setObjectName(QStringLiteral("resetSliders"));

        verticalLayout_10->addWidget(resetSliders);

        cameraAspectRatio = new QLabel(camtransDockContents);
        cameraAspectRatio->setObjectName(QStringLiteral("cameraAspectRatio"));

        verticalLayout_10->addWidget(cameraAspectRatio);

        label = new QLabel(camtransDockContents);
        label->setObjectName(QStringLiteral("label"));
        label->setEnabled(false);
        label->setWordWrap(true);

        verticalLayout_10->addWidget(label);

        cameraDockEmptySpace = new QWidget(camtransDockContents);
        cameraDockEmptySpace->setObjectName(QStringLiteral("cameraDockEmptySpace"));
        sizePolicy.setHeightForWidth(cameraDockEmptySpace->sizePolicy().hasHeightForWidth());
        cameraDockEmptySpace->setSizePolicy(sizePolicy);

        verticalLayout_10->addWidget(cameraDockEmptySpace);

        camtransDock->setWidget(camtransDockContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), camtransDock);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 18));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuToolbars = new QMenu(menuBar);
        menuToolbars->setObjectName(QStringLiteral("menuToolbars"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuToolbars->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionRevert);
        menuFile->addAction(actionClear);
        menuFile->addAction(actionCopy3Dto2D);
        menuFile->addAction(actionUseOrbitingCamera);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);

        retranslateUi(MainWindow);
        QObject::connect(actionQuit, SIGNAL(triggered()), MainWindow, SLOT(close()));
        QObject::connect(raySuperSamping, SIGNAL(toggled(bool)), raySuperSamplesTextbox, SLOT(setEnabled(bool)));
        QObject::connect(rayAllButton, SIGNAL(clicked()), MainWindow, SLOT(checkAllRayFeatures()));
        QObject::connect(rayNoneButton, SIGNAL(clicked()), MainWindow, SLOT(uncheckAllRayFeatures()));
        QObject::connect(cameraOrbitCheckbox, SIGNAL(toggled(bool)), cameraRotation, SLOT(setDisabled(bool)));
        QObject::connect(cameraOrbitCheckbox, SIGNAL(toggled(bool)), cameraPosition, SLOT(setDisabled(bool)));
        QObject::connect(xAxisButton, SIGNAL(clicked()), MainWindow, SLOT(setCameraAxisX()));
        QObject::connect(yAxisButton, SIGNAL(clicked()), MainWindow, SLOT(setCameraAxisY()));
        QObject::connect(axonometricButton, SIGNAL(clicked()), MainWindow, SLOT(setCameraAxonometric()));
        QObject::connect(transX, SIGNAL(valueChanged(int)), MainWindow, SLOT(updateCameraTranslation()));
        QObject::connect(transY, SIGNAL(valueChanged(int)), MainWindow, SLOT(updateCameraTranslation()));
        QObject::connect(transZ, SIGNAL(valueChanged(int)), MainWindow, SLOT(updateCameraTranslation()));
        QObject::connect(rotU, SIGNAL(valueChanged(int)), MainWindow, SLOT(updateCameraRotationU()));
        QObject::connect(rotW, SIGNAL(valueChanged(int)), MainWindow, SLOT(updateCameraRotationN()));
        QObject::connect(rotV, SIGNAL(valueChanged(int)), MainWindow, SLOT(updateCameraRotationV()));
        QObject::connect(cameraNearSlider, SIGNAL(valueChanged(int)), MainWindow, SLOT(updateCameraClip()));
        QObject::connect(cameraNearTextbox, SIGNAL(textChanged(QString)), MainWindow, SLOT(updateCameraClip()));
        QObject::connect(cameraFarSlider, SIGNAL(valueChanged(int)), MainWindow, SLOT(updateCameraClip()));
        QObject::connect(cameraFarTextbox, SIGNAL(textChanged(QString)), MainWindow, SLOT(updateCameraClip()));
        QObject::connect(cameraFovSlider, SIGNAL(valueChanged(int)), MainWindow, SLOT(updateCameraHeightAngle()));
        QObject::connect(cameraFovTextbox, SIGNAL(textChanged(QString)), MainWindow, SLOT(updateCameraHeightAngle()));
        QObject::connect(actionSave, SIGNAL(triggered()), MainWindow, SLOT(fileSave()));
        QObject::connect(actionOpen, SIGNAL(triggered()), MainWindow, SLOT(fileOpen()));
        QObject::connect(rayRenderButton, SIGNAL(clicked()), MainWindow, SLOT(renderImage()));
        QObject::connect(actionNew, SIGNAL(triggered()), MainWindow, SLOT(fileNew()));
        QObject::connect(resetUpVector, SIGNAL(clicked()), MainWindow, SLOT(resetUpVector()));
        QObject::connect(cameraOrbitCheckbox, SIGNAL(toggled(bool)), cameraResetAxis, SLOT(setDisabled(bool)));
        QObject::connect(showSceneviewInstead, SIGNAL(toggled(bool)), shapeType, SLOT(setDisabled(bool)));
        QObject::connect(rayStopRenderingButton, SIGNAL(clicked()), canvas2D, SLOT(cancelRender()));
        QObject::connect(actionCopy3Dto2D, SIGNAL(triggered()), MainWindow, SLOT(fileCopy3Dto2D()));
        QObject::connect(zAxisButton, SIGNAL(clicked()), MainWindow, SLOT(setCameraAxisZ()));
        QObject::connect(actionClear, SIGNAL(triggered()), MainWindow, SLOT(clearImage()));
        QObject::connect(actionRevert, SIGNAL(triggered()), MainWindow, SLOT(revertImage()));
        QObject::connect(resetSliders, SIGNAL(clicked()), MainWindow, SLOT(resetSliders()));
        QObject::connect(actionUseOrbitingCamera, SIGNAL(toggled(bool)), cameraOrbitCheckbox, SLOT(setChecked(bool)));
        QObject::connect(cameraOrbitCheckbox, SIGNAL(toggled(bool)), actionUseOrbitingCamera, SLOT(setChecked(bool)));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "CS 123: Introduction to Computer Graphics", 0));
        actionNew->setText(QApplication::translate("MainWindow", "New", 0));
        actionNew->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open...", 0));
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        actionSave->setText(QApplication::translate("MainWindow", "Save...", 0));
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0));
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0));
        actionRevert->setText(QApplication::translate("MainWindow", "Revert Image", 0));
        actionRevert->setShortcut(QApplication::translate("MainWindow", "Ctrl+R", 0));
        actionCopy3Dto2D->setText(QApplication::translate("MainWindow", "Copy 3D tab to 2D tab", 0));
        actionClear->setText(QApplication::translate("MainWindow", "Clear Image", 0));
#ifndef QT_NO_TOOLTIP
        actionClear->setToolTip(QApplication::translate("MainWindow", "Clear Image", 0));
#endif // QT_NO_TOOLTIP
        actionClear->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", 0));
        actionUseOrbitingCamera->setText(QApplication::translate("MainWindow", "Use Orbiting Camera", 0));
        actionUseOrbitingCamera->setShortcut(QApplication::translate("MainWindow", "Ctrl+B", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab2D), QApplication::translate("MainWindow", "2D", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab3D), QApplication::translate("MainWindow", "3D", 0));
        shapesDock->setWindowTitle(QApplication::translate("MainWindow", "Shapes/Sceneview", 0));
        showSceneviewInstead->setText(QApplication::translate("MainWindow", "Show sceneview instead", 0));
        shapeType->setTitle(QApplication::translate("MainWindow", "Shape Type", 0));
        shapeTypeCube->setText(QApplication::translate("MainWindow", "Cube", 0));
        shapeTypeCone->setText(QApplication::translate("MainWindow", "Cone", 0));
        shapeTypeSphere->setText(QApplication::translate("MainWindow", "Sphere", 0));
        shapeTypeCylinder->setText(QApplication::translate("MainWindow", "Cylinder", 0));
        shapeTypeTorus->setText(QApplication::translate("MainWindow", "Torus", 0));
        shapeTypeSpecial1->setText(QApplication::translate("MainWindow", "Special 1", 0));
        shapeTypeSpecial2->setText(QApplication::translate("MainWindow", "Special 2", 0));
        shapeParameters->setTitle(QApplication::translate("MainWindow", "Shape Parameters", 0));
        shapeParameterLabel1->setText(QApplication::translate("MainWindow", "1", 0));
        shapeParameterLabel2->setText(QApplication::translate("MainWindow", "2", 0));
        shapeParameterLabel3->setText(QApplication::translate("MainWindow", "3", 0));
        useLightingCheckbox->setText(QApplication::translate("MainWindow", "Use lighting", 0));
        drawWireframeCheckbox->setText(QApplication::translate("MainWindow", "Draw wireframe", 0));
        drawNormalsCheckbox->setText(QApplication::translate("MainWindow", "Draw normals", 0));
        deferredLightCheckbox->setText(QApplication::translate("MainWindow", "Deferred Lighting", 0));
        rayDock->setWindowTitle(QApplication::translate("MainWindow", "Ray", 0));
        rayAllButton->setText(QApplication::translate("MainWindow", "All", 0));
        rayNoneButton->setText(QApplication::translate("MainWindow", "None", 0));
        rayFeatures->setTitle(QApplication::translate("MainWindow", "Features", 0));
        raySuperSamping->setText(QApplication::translate("MainWindow", "Super sampling", 0));
        raySuperSamplesLabel->setText(QApplication::translate("MainWindow", "sqrt(samples)", 0));
        raySuperSamplesTextbox->setText(QString());
        rayAntiAliasing->setText(QApplication::translate("MainWindow", "Anti-aliasing", 0));
        rayShadows->setText(QApplication::translate("MainWindow", "Shadows", 0));
        rayTextureMapping->setText(QApplication::translate("MainWindow", "Texture Mapping", 0));
        rayReflection->setText(QApplication::translate("MainWindow", "Reflection", 0));
        rayRefraction->setText(QApplication::translate("MainWindow", "Refraction", 0));
        rayMultiThreading->setText(QApplication::translate("MainWindow", "Multithreading", 0));
        rayLighting->setTitle(QApplication::translate("MainWindow", "Lighting", 0));
        rayPointLights->setText(QApplication::translate("MainWindow", "Point lights", 0));
        rayDirectionalLights->setText(QApplication::translate("MainWindow", "Directional lights", 0));
        raySpotLights->setText(QApplication::translate("MainWindow", "Spot lights", 0));
        rayRenderButton->setText(QApplication::translate("MainWindow", "Render!", 0));
        rayStopRenderingButton->setText(QApplication::translate("MainWindow", "Stop rendering", 0));
        camtransDock->setWindowTitle(QApplication::translate("MainWindow", "Camtrans", 0));
        cameraOrbitCheckbox->setText(QApplication::translate("MainWindow", "Use orbit camera instead", 0));
        cameraPosition->setTitle(QApplication::translate("MainWindow", "Translation", 0));
        cameraPositionLabelX->setText(QApplication::translate("MainWindow", "X", 0));
        cameraPositionLabelY->setText(QApplication::translate("MainWindow", "Y", 0));
        cameraPositionLabelZ->setText(QApplication::translate("MainWindow", "Z", 0));
        cameraRotation->setTitle(QApplication::translate("MainWindow", "Rotation", 0));
        cameraRotationLabelYaw->setText(QApplication::translate("MainWindow", "U", 0));
        cameraRotationLabelPitch->setText(QApplication::translate("MainWindow", "V", 0));
        cameraRotationLabelRoll->setText(QApplication::translate("MainWindow", "W", 0));
        resetUpVector->setText(QApplication::translate("MainWindow", "Reset up vector", 0));
        cameraResetAxis->setTitle(QApplication::translate("MainWindow", "Reset", 0));
        xAxisButton->setText(QApplication::translate("MainWindow", "X axis", 0));
        yAxisButton->setText(QApplication::translate("MainWindow", "Y axis", 0));
        zAxisButton->setText(QApplication::translate("MainWindow", "Z axis", 0));
        axonometricButton->setText(QApplication::translate("MainWindow", "Axonometric", 0));
        cameraFovLabel->setText(QApplication::translate("MainWindow", "FOV", 0));
        cameraNearLabel->setText(QApplication::translate("MainWindow", "Near", 0));
        cameraFarLabel->setText(QApplication::translate("MainWindow", "Far", 0));
        resetSliders->setText(QApplication::translate("MainWindow", "Reset FOV / Near / Far", 0));
        cameraAspectRatio->setText(QApplication::translate("MainWindow", "Aspect ratio:", 0));
        label->setText(QApplication::translate("MainWindow", "Resize the window to change the aspect ratio.", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", 0));
        menuToolbars->setTitle(QApplication::translate("MainWindow", "&Toolbars", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
