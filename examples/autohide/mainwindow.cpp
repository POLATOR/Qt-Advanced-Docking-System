#include "mainwindow.h"

#include "ui_mainwindow.h"

#include <QWidgetAction>
#include <QFileSystemModel>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QPlainTextEdit>
#include <QSettings>
#include <QTableWidget>
#include <QToolBar>

#include "AutoHideDockContainer.h"
#include "DockAreaWidget.h"
#include "DockAreaTitleBar.h"

using namespace ads;

CMainWindow::CMainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::CMainWindow)
{
    ui->setupUi(this);
    CDockManager::setConfigFlag(CDockManager::OpaqueSplitterResize, true);
    CDockManager::setConfigFlag(CDockManager::XmlCompressionEnabled, false);
    CDockManager::setConfigFlag(CDockManager::FocusHighlighting, true);
    CDockManager::setAutoHideConfigFlags(CDockManager::DefaultAutoHideConfig);
    DockManager = new CDockManager(this);

    // Set central widget
    QPlainTextEdit* w = new QPlainTextEdit();
    w->setPlaceholderText("This is the central editor. Enter your text here.");
    CDockWidget* CentralDockWidget = new CDockWidget("CentralWidget");
    CentralDockWidget->setWidget(w);
    auto* CentralDockArea = DockManager->setCentralWidget(CentralDockWidget);
    CentralDockArea->setAllowedAreas(DockWidgetArea::OuterDockAreas);

    // create other dock widgets
    QTableWidget* table = new QTableWidget();
    table->setColumnCount(3);
    table->setRowCount(10);
    CDockWidget* TableDockWidget = new CDockWidget("Table 1");
    TableDockWidget->setWidget(table);
    TableDockWidget->setMinimumSizeHintMode(
        CDockWidget::MinimumSizeHintFromDockWidget);
    TableDockWidget->setMinimumSize(200, 150);
    const auto autoHideContainer = DockManager->addAutoHideDockWidget(
        SideBarLocation::SideBarLeft, TableDockWidget);
    autoHideContainer->setSize(480);
    ui->menuView->addAction(TableDockWidget->toggleViewAction());

    table = new QTableWidget();
    table->setColumnCount(5);
    table->setRowCount(1020);
    TableDockWidget = new CDockWidget("Table 2");
    TableDockWidget->setWidget(table);
    TableDockWidget->setMinimumSizeHintMode(
        CDockWidget::MinimumSizeHintFromDockWidget);
    TableDockWidget->resize(250, 150);
    TableDockWidget->setMinimumSize(200, 150);
    DockManager->addAutoHideDockWidget(SideBarLocation::SideBarLeft,
                                       TableDockWidget);
    ui->menuView->addAction(TableDockWidget->toggleViewAction());

    QTableWidget* propertiesTable = new QTableWidget();
    propertiesTable->setColumnCount(3);
    propertiesTable->setRowCount(10);
    CDockWidget* PropertiesDockWidget = new CDockWidget("Properties");
    PropertiesDockWidget->setWidget(propertiesTable);
    PropertiesDockWidget->setMinimumSizeHintMode(
        CDockWidget::MinimumSizeHintFromDockWidget);
    PropertiesDockWidget->resize(250, 150);
    PropertiesDockWidget->setMinimumSize(200, 150);
    DockManager->addDockWidget(DockWidgetArea::RightDockWidgetArea,
                               PropertiesDockWidget, CentralDockArea);
    ui->menuView->addAction(PropertiesDockWidget->toggleViewAction());

    createPerspectiveUi();
}

CMainWindow::~CMainWindow()
{
    delete ui;
}

void CMainWindow::createPerspectiveUi()
{
    SavePerspectiveAction = new QAction("Create Perspective", this);
    connect(SavePerspectiveAction, SIGNAL(triggered()), SLOT(savePerspective()));
    PerspectiveListAction = new QWidgetAction(this);
    PerspectiveComboBox = new QComboBox(this);
    PerspectiveComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    PerspectiveComboBox->setSizePolicy(QSizePolicy::Preferred,
                                       QSizePolicy::Preferred);
    connect(PerspectiveComboBox, SIGNAL(currentTextChanged(const QString&)),
            DockManager, SLOT(openPerspective(const QString&)));
    PerspectiveListAction->setDefaultWidget(PerspectiveComboBox);
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(PerspectiveListAction);
    ui->toolBar->addAction(SavePerspectiveAction);
    auto* action = new QAction("Bug #1");
    action->connect(action, &QAction::triggered, [this]() {
        for (int i = 0; i < 30; ++i)
        {
            DockManager->restoreState(
                {R"(<?xml version="1.0" encoding="UTF-8"?><QtAdvancedDockingSystem Version="1" UserVersion="0" Containers="1" CentralWidget="CentralWidget"><Container Floating="0"><Splitter Orientation="|" Count="2"><Area Tabs="1" Current="Table 1"><Widget Name="Table 1" Closed="0"/></Area><Splitter Orientation="-" Count="1"><Splitter Orientation="|" Count="2"><Area Tabs="1" Current="CentralWidget" AllowedAreas="f" Flags="1"><Widget Name="CentralWidget" Closed="0"/></Area><Area Tabs="1" Current="Properties"><Widget Name="Properties" Closed="0"/></Area><Sizes>734 256 </Sizes></Splitter><Sizes>707 </Sizes></Splitter><Sizes>256 995 </Sizes></Splitter><SideBar Area="1" Tabs="1"><Widget Name="Table 2" Closed="0" Size="100"/></SideBar></Container></QtAdvancedDockingSystem>)"});
            DockManager->restoreState(
                {R"(<?xml version="1.0" encoding="UTF-8"?><QtAdvancedDockingSystem Version="1" UserVersion="0" Containers="1" CentralWidget="CentralWidget"><Container Floating="0"><Splitter Orientation="|" Count="2"><Area Tabs="1" Current="Table 2"><Widget Name="Table 2" Closed="0"/></Area><Splitter Orientation="-" Count="1"><Splitter Orientation="|" Count="2"><Area Tabs="1" Current="CentralWidget" AllowedAreas="f" Flags="1"><Widget Name="CentralWidget" Closed="0"/></Area><Area Tabs="1" Current="Properties"><Widget Name="Properties" Closed="0"/></Area><Sizes>734 256 </Sizes></Splitter><Sizes>707 </Sizes></Splitter><Sizes>256 995 </Sizes></Splitter><SideBar Area="1" Tabs="1"><Widget Name="Table 1" Closed="0" Size="272"/></SideBar></Container></QtAdvancedDockingSystem>)"});
        }
    });
    ui->toolBar->addAction(action);

    action = new QAction("Bug #2 Click me three times");
    action->connect(action, &QAction::triggered, [this]() {
        QMetaObject::invokeMethod(qApp, [this]() {
            DockManager->restoreState(
                {R"(<?xml version="1.0" encoding="UTF-8"?><QtAdvancedDockingSystem Version="1" UserVersion="0" Containers="1" CentralWidget="CentralWidget"><Container Floating="0"><Splitter Orientation="|" Count="3"><Area Tabs="1" Current="Table 2"><Widget Name="Table 2" Closed="0"/></Area><Area Tabs="1" Current="Table 1"><Widget Name="Table 1" Closed="0"/></Area><Splitter Orientation="-" Count="1"><Splitter Orientation="|" Count="2"><Area Tabs="1" Current="CentralWidget" AllowedAreas="f" Flags="1"><Widget Name="CentralWidget" Closed="0"/></Area><Area Tabs="1" Current="Properties"><Widget Name="Properties" Closed="0"/></Area><Sizes>501 256 </Sizes></Splitter><Sizes>707 </Sizes></Splitter><Sizes>256 256 762 </Sizes></Splitter></Container></QtAdvancedDockingSystem>)"});
        });
        QMetaObject::invokeMethod(qApp, [this]() {
            DockManager->restoreState(
                {R"(<?xml version="1.0" encoding="UTF-8"?><QtAdvancedDockingSystem Version="1" UserVersion="0" Containers="4" CentralWidget="CentralWidget"><Container Floating="0"><Splitter Orientation="-" Count="1"><Area Tabs="1" Current="CentralWidget" AllowedAreas="f" Flags="1"><Widget Name="CentralWidget" Closed="0"/></Area><Sizes>707 </Sizes></Splitter></Container><Container Floating="1"><Geometry>01 d9 d0 cb 00 03 00 00 00 00 01 72 00 00 01 0c 00 00 02 71 00 00 03 ce 00 00 01 72 00 00 01 2a 00 00 02 71 00 00 03 ce 00 00 00 00 00 00 00 00 08 00 00 00 01 72 00 00 01 2a 00 00 02 71 00 00 03 ce</Geometry><Splitter Orientation="-" Count="1"><Area Tabs="1" Current="Table 2"><Widget Name="Table 2" Closed="0"/></Area><Sizes>675 </Sizes></Splitter></Container><Container Floating="1"><Geometry>01 d9 d0 cb 00 03 00 00 00 00 02 ac 00 00 01 0e 00 00 03 ab 00 00 03 d0 00 00 02 ac 00 00 01 2c 00 00 03 ab 00 00 03 d0 00 00 00 00 00 00 00 00 08 00 00 00 02 ac 00 00 01 2c 00 00 03 ab 00 00 03 d0</Geometry><Splitter Orientation="-" Count="1"><Area Tabs="1" Current="Table 1"><Widget Name="Table 1" Closed="0"/></Area><Sizes>675 </Sizes></Splitter></Container><Container Floating="1"><Geometry>01 d9 d0 cb 00 03 00 00 00 00 04 35 00 00 01 15 00 00 05 34 00 00 03 d7 00 00 04 35 00 00 01 33 00 00 05 34 00 00 03 d7 00 00 00 00 00 00 00 00 08 00 00 00 04 35 00 00 01 33 00 00 05 34 00 00 03 d7</Geometry><Splitter Orientation="-" Count="1"><Area Tabs="1" Current="Properties"><Widget Name="Properties" Closed="0"/></Area><Sizes>675 </Sizes></Splitter></Container></QtAdvancedDockingSystem>)"});
        });
    });
    ui->toolBar->addAction(action);
}

void CMainWindow::savePerspective()
{
	QString PerspectiveName = QInputDialog::getText(this, "Save Perspective", "Enter unique name:");
	if (PerspectiveName.isEmpty())
	{
		return;
	}

	DockManager->addPerspective(PerspectiveName);
	QSignalBlocker Blocker(PerspectiveComboBox);
	PerspectiveComboBox->clear();
	PerspectiveComboBox->addItems(DockManager->perspectiveNames());
	PerspectiveComboBox->setCurrentText(PerspectiveName);
}


//============================================================================
void CMainWindow::closeEvent(QCloseEvent* event)
{
    // Delete dock manager here to delete all floating widgets. This ensures
    // that all top level windows of the dock manager are properly closed
    DockManager->deleteLater();
	QMainWindow::closeEvent(event);
}
