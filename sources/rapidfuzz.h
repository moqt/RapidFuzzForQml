#ifndef RAPIDFUZZ_H
#define RAPIDFUZZ_H

#include <QObject>
#include <QVariantList>
#include <qqml.h>

namespace Moqt
{


class RapidFuzz : public QObject
{
    Q_OBJECT
    QML_SINGLETON
    QML_NAMED_ELEMENT(RapidFuzz)//QML_ELEMENT Does not work with Qt 5.15.2

    Q_DISABLE_COPY_MOVE(RapidFuzz)

public:
    explicit RapidFuzz(QObject *parent = nullptr);

public slots:
    // returns [score, text]
    QVariantList bestScore(const QStringList& query, const QStringList& choices, qreal scoreCutoff, bool caseSensitive = false);

signals:

};


}

#endif // RAPIDFUZZ_H
