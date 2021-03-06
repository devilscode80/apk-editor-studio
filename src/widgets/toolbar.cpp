#include "widgets/toolbar.h"
#include "widgets/spacer.h"
#include "base/application.h"
#include "base/utils.h"

QMap<QString, QAction *> Toolbar::pool;

Toolbar::Toolbar(QWidget *parent) : QToolBar(parent)
{
    setMovable(false);

    const QList<int> availableSizes = {16, 30, 40}; // Hardcoded icon sizes
    const int closestSize = Utils::roundToNearest(app->scale(30, 30).width(), availableSizes);
    setIconSize(QSize(closestSize, closestSize));
}

QMap<QString, QAction *> Toolbar::all()
{
    return pool;
}

void Toolbar::addToPool(const QString &identifier, QAction *action)
{
    pool.insert(identifier, action);
}

void Toolbar::reinitialize()
{
    clear();
    QStringList entries = app->settings->getToolbar();
    for (const QString &entry : entries) {
        if (entry == "separator") {
            addSeparator();
        } else if (entry == "spacer") {
            addWidget(new Spacer(this));
        } else {
            addAction(pool.value(entry, nullptr));
        }
    }
}
