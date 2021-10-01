#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

extern "C" {
    #include "Make_list_of_tokens.h"
    #include "Make_postfix.h"
    #include "Truth_table.h"
    #include "list.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_evaluate_clicked();

    void on_pushButton_konjuct_clicked();

    void on_pushButton_disjunction_clicked();

    void on_pushButton_not_clicked();

    void on_pushButton_xor_clicked();

    void on_pushButton_implication_clicked();

    void on_pushButton_x_clicked();

    void on_pushButton_y_clicked();

    void on_pushButton_z_clicked();

    void on_pushButton_del_clicked();

    void on_pushButton_del_all_clicked();

    void on_pushButton_add_left_clicked();

    void on_pushButton_add_right_clicked();

    void on_pushButton_equal_clicked();

    void on_pushButton_pierce_clicked();

    void on_pushButton_sheffer_clicked();

private:
    void binaryPrint(int variables_count, int* truthTableArray);

    void truthTablePrint(int index, int variables_count, int* truthTableArray);

    void create_table(char ** variables, unsigned variables_count, char* expression);

    void delete_table();

    QString result_of_check(enum check_expression check_expression);

    void result();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
