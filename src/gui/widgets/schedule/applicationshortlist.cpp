#include "applicationshortlist.h"
#include "application.h"
#include "applicationlist.h"
#include "ui_applicationshortlist.h"

ApplicationShortList::ApplicationShortList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ApplicationShortList)
{
    ui->setupUi(this);
}

ApplicationShortList::~ApplicationShortList()
{
    delete ui;
}

void ApplicationShortList::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updateText();
}

void ApplicationShortList::setApplicationList(QList<sun::persistence::ApplicationList> appicationLists)
{
    for(const sun::persistence::ApplicationList& applicationList : appicationLists) {
        if(applicationList.name) {
            listNames.append(*applicationList.name);
        } else {
            const QList<sun::persistence::Application>& applications = applicationListService.getAllApplications(applicationList.id);
            for(const sun::persistence::Application& application : applications) {
                applicationNames.append(application.name);
            }
        }
    }
    updateText();
}

void ApplicationShortList::updateText()
{
    QStringList names;

    for (const QString &name : listNames) {
        names.append(name);
    }

    for (const QString &name : applicationNames) {
        names.append(name);
    }

    const int availableWidth = ui->text->contentsRect().width();
    const QFontMetrics metrics(ui->text->font());

    for (int fitted = names.size(); fitted >= 0; --fitted) {
        QString text = names.mid(0, fitted).join(", ");

        const int omitted = names.size() - fitted;

        if (omitted > 0) {
            if (!text.isEmpty()) {
                text += ", ";
            }

            text += QString("+%1").arg(omitted);
        }

        if (metrics.horizontalAdvance(text) <= availableWidth) {
            ui->text->setText(text);
            return;
        }
    }

    ui->text->clear();
}
