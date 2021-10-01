#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <string>
#include <cstring>
#include <math.h>

static int binaryArray[100];
static int truthTableIndex = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::binaryPrint(int variables_count, int* truthTableArray)
{
    for (int i = 0; i < variables_count; i++) {
        QString bit = QString::number(binaryArray[i]);
        QTableWidgetItem* binary = new QTableWidgetItem(bit);
        ui->tableWidget->setItem(truthTableIndex,i,binary);
    }
    QString result = QString::number(truthTableArray[truthTableIndex]);
    QTableWidgetItem* value = new QTableWidgetItem(result);
    ui->tableWidget->setItem(truthTableIndex,variables_count,value);
    truthTableIndex++;
}

// Рекурсивная функция для генерация двоичных наборов
void MainWindow::truthTablePrint(int index, int variables_count, int* truthTableArray)
{
    if (index == variables_count) {
        binaryPrint(variables_count, truthTableArray);
        return;
    } else {
        binaryArray[index] = 0;
        truthTablePrint(index + 1, variables_count, truthTableArray);
        binaryArray[index] = 1;
        truthTablePrint(index + 1, variables_count, truthTableArray);
    }
}

void MainWindow::delete_table(){
    ui->tableWidget->horizontalHeader()->hide();
    while (ui->tableWidget->rowCount() > 0)
    {
        ui->tableWidget->removeRow(0);
    }
}

void MainWindow::create_table(char ** variables, unsigned variables_count, char* expression){
    ui->tableWidget->setColumnCount(variables_count+1);
    ui->tableWidget->setRowCount(pow(2,variables_count));
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->horizontalHeader()->setHidden(false);

    QStringList headers;
    for (unsigned i = 0;i < variables_count;i++){
        headers.append(QString(variables[i]));
    }
    headers.append(QString(expression));
    // или
    // headers.append("Value");
    ui->tableWidget->setHorizontalHeaderLabels(headers);
}

void MainWindow::result(){
    truthTableIndex = 0;
    for (int j =0;j < 100 ;j++ ) {
        binaryArray[j] = 0;
    }

    MainWindow::delete_table();

    QString str = ui->lineEdit_input->text();
    QByteArray a = str.toUtf8();
    char* input = a.data();
    removeWhiteSpace(input);
    enum check_expression check_it = Empty_string;

    bool b = check(input,&check_it);
    if (b){
        unsigned lengh = 0;
        list_t Token_list = make_token_list(input, &check_it, &lengh);
        if (check_it == All_is_good && lengh){
            list_t postfix = make_postfix(&Token_list,&lengh,&check_it);

            if (check_it == All_is_good) {
                unsigned variables_count = 0;
                char ** variables = array_of_unique_variables(postfix,lengh,&variables_count);

                // Создание пустой таблицы
                create_table(variables,variables_count,input);
                int* truthTableOutput = (int*) malloc((int) pow(2, variables_count) * sizeof (int));

                // Фунция высчитывает значения булевой функции и помещает их в массив truthTableOutput
                truthTable(&postfix,truthTableOutput,0,variables_count,lengh);

               // Заполенение таблицы
                truthTablePrint(0, variables_count, truthTableOutput);
                for (unsigned s = 0; s < variables_count ;s++ ) {
                    free(variables[s]);
                }
                free(variables);
                free(truthTableOutput);
               }

            // Очичаем лист с постфиксным выражением
            list_delete(&postfix);
        }

        // Очищаем лист токенов
        node_t *head = Token_list.head;

        for (; head; head = head->next){
            free(head);
        }
    }
    ui->label_2->setText(result_of_check(check_it));
}

QString MainWindow::result_of_check(enum check_expression check_expression){
    switch (check_expression) {
    case  All_is_good:
    {
        return QString("Correct Expression");
    }
    case  Empty_string:
    {
        return QString("Please enter expression, then click evaluate");
    }
    case  Uncorrect_expression:
    {
        return QString("Uncorrect Expression");
    }
    case   Uncorrect_operators:
    {
        return QString("Uncorrect expression, operator can't be after operator");
    }
    case Operator_without_variable:
    {
        return QString("Operator can't be withou variable after");
    }
    case Operator_not_error:
    {
        return QString("Uncorrect use of operator not");
    }
    case Uncorrect_parentheses:
    {
        return QString("Uncorrect parenthrsis, enter correct");
    }
    case Too_Long_Variable:
    {
        return QString("Variable name is too long (maximim 3)");
    }
    }
}


void MainWindow::on_pushButton_evaluate_clicked()
{
    result();
}

void MainWindow::on_pushButton_konjuct_clicked()
{
    unsigned position = ui->lineEdit_input->cursorPosition();
    QString text = ui->lineEdit_input->text();
    text.insert(position,'&');
    ui->lineEdit_input->setText(text);
}

void MainWindow::on_pushButton_disjunction_clicked()
{
    unsigned position = ui->lineEdit_input->cursorPosition();
    QString text = ui->lineEdit_input->text();
    text.insert(position,'+');
    ui->lineEdit_input->setText(text);
}

void MainWindow::on_pushButton_not_clicked()
{
    unsigned position = ui->lineEdit_input->cursorPosition();
    QString text = ui->lineEdit_input->text();
    text.insert(position,'!');
    ui->lineEdit_input->setText(text);
}

void MainWindow::on_pushButton_xor_clicked()
{
    unsigned position = ui->lineEdit_input->cursorPosition();
    QString text = ui->lineEdit_input->text();
    text.insert(position,'^');
    ui->lineEdit_input->setText(text);
}

void MainWindow::on_pushButton_implication_clicked()
{
    unsigned position = ui->lineEdit_input->cursorPosition();
    QString text = ui->lineEdit_input->text();
    text.insert(position,"->");
    ui->lineEdit_input->setText(text);
}

void MainWindow::on_pushButton_x_clicked()
{
    unsigned position = ui->lineEdit_input->cursorPosition();
    QString text = ui->lineEdit_input->text();
    text.insert(position,'x');
    ui->lineEdit_input->setText(text);
}

void MainWindow::on_pushButton_y_clicked()
{
    unsigned position = ui->lineEdit_input->cursorPosition();
    QString text = ui->lineEdit_input->text();
    text.insert(position,'y');
    ui->lineEdit_input->setText(text);
}

void MainWindow::on_pushButton_z_clicked()
{
    unsigned position = ui->lineEdit_input->cursorPosition();
    QString text = ui->lineEdit_input->text();
    text.insert(position,'z');
    ui->lineEdit_input->setText(text);
}

void MainWindow::on_pushButton_del_clicked()
{
    QString text = ui->lineEdit_input->text();
    text.remove(text.length()-1,text.length());
    ui->lineEdit_input->setText(text);
}

void MainWindow::on_pushButton_del_all_clicked()
{
    ui->lineEdit_input->clear();
}


void MainWindow::on_pushButton_add_left_clicked()
{
    unsigned position = ui->lineEdit_input->cursorPosition();
    QString text = ui->lineEdit_input->text();
    text.insert(position,'(');
    ui->lineEdit_input->setText(text);
}

void MainWindow::on_pushButton_add_right_clicked()
{
    unsigned position = ui->lineEdit_input->cursorPosition();
    QString text = ui->lineEdit_input->text();
    text.insert(position,')');
    ui->lineEdit_input->setText(text);
}

void MainWindow::on_pushButton_equal_clicked()
{
    unsigned position = ui->lineEdit_input->cursorPosition();
    QString text = ui->lineEdit_input->text();
    text.insert(position,'=');
    ui->lineEdit_input->setText(text);
}

void MainWindow::on_pushButton_pierce_clicked()
{
    unsigned position = ui->lineEdit_input->cursorPosition();
    QString text = ui->lineEdit_input->text();
    text.insert(position,'#');
    ui->lineEdit_input->setText(text);
}

void MainWindow::on_pushButton_sheffer_clicked()
{
    unsigned position = ui->lineEdit_input->cursorPosition();
    QString text = ui->lineEdit_input->text();
    text.insert(position,'|');
    ui->lineEdit_input->setText(text);
}
