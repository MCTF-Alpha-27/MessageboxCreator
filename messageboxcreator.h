#ifndef MESSAGEBOXCREATOR_H
#define MESSAGEBOXCREATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MessageboxCreator; }
QT_END_NAMESPACE

class MessageboxCreator : public QMainWindow
{
    Q_OBJECT

public:
    MessageboxCreator(QWidget *parent = nullptr);
    ~MessageboxCreator();

    void createMenuBar();
    void createMenu();

    /* 图标 */
    // 不显示图标
    void no_icon_with_ok_button();
    void no_icon_with_ok_cancel_button();

    // 显示警告图标
    void warning_icon_with_ok_button();
    void warning_icon_with_ok_cancel_button();

    // 显示信息图标
    void info_icon_with_ok_button();
    void info_icon_with_ok_cancel_button();

    /* 菜单栏 */
    void aboutMenu();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_toolButton_clicked();

private:
    Ui::MessageboxCreator *ui;
};
#endif // MESSAGEBOXCREATOR_H
