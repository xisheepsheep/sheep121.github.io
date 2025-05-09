#include "DepositDialog.h"
#include "ui_DepositDialog.h"
#include <QMessageBox>

DepositDialog::DepositDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::DepositDialog) {
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, [this]() {
        bool ok; double amt=ui->editAmount->text().toDouble(&ok);
        if(!ok||amt<=0) QMessageBox::warning(this,"错误","请输入有效金额");
        else accept();
    });
}

DepositDialog::~DepositDialog() { delete ui; }

double DepositDialog::amount() const { return ui->editAmount->text().toDouble(); }
