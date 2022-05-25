#include "messageboxcreator.h"
#include "./ui_messageboxcreator.h"
#include <iostream>
#include <QMessageBox>
#include <QFile>
#include <qfiledialog.h>
#include <QHBoxLayout>

using namespace std;

bool isDigitString(const QString& src) { // 判断一个 QString 是否由数字组成
    const char *s = src.toUtf8().data();
    while(*s && *s>='0' && *s<='9')s++;
    return !bool(*s);
}

void MessageboxCreator::createMenuBar() { // 创建菜单栏
    connect(ui->actionAbout, &QAction::triggered, this, &MessageboxCreator::aboutMenu); // 关于菜单
}

void MessageboxCreator::createMenu() { // 创建菜单
    QMenu *qicon_bar = new QMenu();

    /* 图标 */
    // 不显示图标
    QMenu *qicon_no_icon = new QMenu();
    QAction *no_icon = new QAction("不显示图标", qicon_bar);
    QAction *with_ok_button_0 = new QAction("并显示[确定]按钮", qicon_no_icon);
    QAction *with_ok_cancel_button_1 = new QAction("并显示[确定]、[取消]按钮", qicon_no_icon);

    // 显示警告图标
    QMenu *qicon_warning_icon = new QMenu();
    QAction *warning_icon = new QAction("显示警告图标", qicon_bar);
    QAction *with_ok_button_48 = new QAction("并显示[确认]按钮", qicon_warning_icon);
    QAction *with_ok_button_49 = new QAction("并显示[确认]、[取消]按钮", qicon_warning_icon);

    /* 向图标菜单添加动作 */
    qicon_bar->addAction(no_icon);
    qicon_bar->addAction(warning_icon);

    /* 向按钮菜单添加动作 */
    // 无图标
    qicon_no_icon->addAction(with_ok_button_0);
    qicon_no_icon->addAction(with_ok_cancel_button_1);

    // 显示警告图标
    qicon_warning_icon->addAction(with_ok_button_48);
    qicon_warning_icon->addAction(with_ok_button_49);

    /* 将子菜单绑定 */
    no_icon->setMenu(qicon_no_icon);
    warning_icon->setMenu(qicon_warning_icon);

    /* 绑定子菜单函数 */
    // 无图标
    connect(with_ok_button_0, &QAction::triggered, this, &MessageboxCreator::no_icon_with_ok_button);
    connect(with_ok_cancel_button_1, &QAction::triggered, this, &MessageboxCreator::no_icon_with_ok_cancel_button);

    // 显示警告图标
    connect(with_ok_button_48, &QAction::triggered, this, &MessageboxCreator::warning_icon_with_ok_button);
    connect(with_ok_button_49, &QAction::triggered, this, &MessageboxCreator::warning_icon_with_ok_cancel_button);

    /* 将菜单绑定到 pushButton_4 上 */
    ui->pushButton_4->setMenu(qicon_bar);
    QHBoxLayout *mainlayout = new QHBoxLayout(this);
    mainlayout->addWidget(ui->pushButton_4);
}

MessageboxCreator::MessageboxCreator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MessageboxCreator)
{
    ui->setupUi(this);
    this->createMenuBar();
    this->createMenu();
}

MessageboxCreator::~MessageboxCreator()
{
    delete ui;
}


void MessageboxCreator::on_pushButton_clicked() // 创建
{
    QString qtitle = ui->lineEdit->text(); // 弹窗的标题
    QString qtext = ui->lineEdit_2->text(); // 弹窗的正文
    QString qicon = ui->lineEdit_3->text(); // 弹窗的图标参数
    // 写入弹窗文件
    if (qicon.isEmpty()) {
        qicon = QString('0');
    } else if (!isDigitString(qicon)) {
        QMessageBox::warning(this, "MessageboxCreator", "图标参数需要输入数字");
        return;
    }
    QString msg = "msgbox " + QString('"') + qtext + QString('"') + ',' + qicon + ',' + '"' + qtitle + '"';
    qDebug() << "标题" << qtitle;
    qDebug() << "正文" << qtext;
    qDebug() << "图标参数" << qicon;
    qDebug() << "vbs脚本命令：" << msg;
    if (ui->lineEdit_4->text().isEmpty()) {
        QMessageBox::warning(this, "MessageboxCreator", "你还没有选择文件的生成文件夹");
        return;
    }
    QDir path(ui->lineEdit_4->text());
    if (!path.exists()) { // 判断文件夹是否存在，不存在则创建
        path.mkpath(ui->lineEdit_4->text());
    }
    QFile file(ui->lineEdit_4->text() + "/弹窗.vbs");
    qDebug() << "文件路径：" << ui->lineEdit_4->text() + "/弹窗.vbs";
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    file.write(msg.toLocal8Bit().data());
    file.flush();
    QMessageBox::information(this, "MessageboxCreator", "弹窗文件的创建已经完成");
    file.close();
}


void MessageboxCreator::on_pushButton_2_clicked() // 取消
{
    QApplication *app = nullptr;
    app->quit();
}


void MessageboxCreator::on_pushButton_3_clicked() // 路径选择
{
    QString path = QFileDialog::getExistingDirectory(this, "选择生成目录", "./", QFileDialog::ShowDirsOnly);
    ui->lineEdit_4->setText(path);
}

/* 菜单栏 */
void MessageboxCreator::aboutMenu() { // 关于菜单
    QMessageBox::information(this, "MessageboxCreator", "作者：Jerry\n版本：1.0\n这个程序可以帮你创建简单的弹窗文件");
}

/* 图标参数候选项 */
void MessageboxCreator::no_icon_with_ok_button() { // 不显示图标并提供[确认]按钮
    ui->lineEdit_3->setText(QString('0'));
}

void MessageboxCreator::no_icon_with_ok_cancel_button() { // 不显示图标并提供[确认]、[取消]按钮
    ui->lineEdit_3->setText(QString('1'));
}

void MessageboxCreator::warning_icon_with_ok_button() { // 显示警告图标并提供[确认]按钮
    ui->lineEdit_3->setText("48");
}

void MessageboxCreator::warning_icon_with_ok_cancel_button() { // 显示警告图标并提供[确认]、[取消]按钮
    ui->lineEdit_3->setText("49");
}
