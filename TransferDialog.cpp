#include "TransferDialog.h"
#include "ui_TransferDialog.h"
#include <QMessageBox>

TransferDialog::TransferDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::TransferDialog) {
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, [this]() {
        bool ok;
        double amt = ui->editAmount->text().toDouble(&ok);
        if (ui->editRecipient->text().isEmpty()) {
            QMessageBox::warning(this, "错误", "请输入接收账号");
        } else if (!ok || amt <= 0) {
            QMessageBox::warning(this, "错误", "请输入有效金额");
        } else {
            accept();
        }
    });
}

TransferDialog::~TransferDialog() { delete ui; }

QString TransferDialog::recipient() const {
    return ui->editRecipient->text();
}

double TransferDialog::amount() const {
    return ui->editAmount->text().toDouble();
}
