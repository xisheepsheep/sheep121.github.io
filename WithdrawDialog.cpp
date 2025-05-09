#include "WithdrawDialog.h"
#include "ui_WithdrawDialog.h"
#include <QMessageBox>

WithdrawDialog::WithdrawDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::WithdrawDialog) {
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, [this]() {
        bool ok; double amt=ui->editAmount->text().toDouble(&ok);
        if(!ok||amt<=0) QMessageBox::warning(this,"错误","请输入有效金额");
        else accept();
    });
}

WithdrawDialog::~WithdrawDialog() { delete ui; }

double WithdrawDialog::amount() const { return ui->editAmount->text().toDouble(); }
