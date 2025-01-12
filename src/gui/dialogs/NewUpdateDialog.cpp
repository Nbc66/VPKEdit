#include "NewUpdateDialog.h"

#include <QDialogButtonBox>
#include <QLabel>
#include <QVBoxLayout>

#include <vpkedit/Version.h>

using namespace vpkedit;

NewUpdateDialog::NewUpdateDialog(const QString& releaseLink, const QString& version, QWidget* parent)
        : QDialog(parent) {
    this->setModal(true);
    this->setWindowTitle(tr("New Update Available"));

    auto* layout = new QVBoxLayout(this);

    auto* label = new QLabel(tr("There is a new update available.\n\n"
							    "Current version:  *v%1*\n\n"
							    "Latest version:  *%2*\n\n"
                                "[Click here to download the new version.](%3)").arg(PROJECT_VERSION.data(), version, releaseLink), this);
    label->setTextFormat(Qt::MarkdownText);
    label->setOpenExternalLinks(true);
    layout->addWidget(label);

    auto* buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, this);
    layout->addWidget(buttonBox);

    QObject::connect(buttonBox, &QDialogButtonBox::accepted, this, &NewUpdateDialog::accept);
    QObject::connect(buttonBox, &QDialogButtonBox::rejected, this, &NewUpdateDialog::reject);
}

void NewUpdateDialog::getNewUpdatePrompt(const QString& releaseLink, const QString& version, QWidget* parent) {
    auto* dialog = new NewUpdateDialog(releaseLink, version, parent);
    dialog->exec();
    dialog->deleteLater();
}
