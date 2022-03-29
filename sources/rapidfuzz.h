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
    // Returns [score, choice]
    QVariantList extractOne(const QStringList& query, const QStringList& choices, qreal scoreCutoff = 0.0, bool caseSensitive = false);

    // Returns [[score, choice], ...]
    QVariantList extract(const QStringList& query, const QStringList& choices, qreal scoreCutoff = 0.0, bool caseSensitive = false);

    qreal ratio(const QString& s1, const QString& s2, qreal scoreCutoff = 0.0, bool caseSensitive = false);
    qreal partialRatio(const QString& s1, const QString& s2, qreal scoreCutoff = 0.0, bool caseSensitive = false);
    qreal tokenRatio(const QString& s1, const QString& s2, qreal scoreCutoff = 0.0, bool caseSensitive = false);
    qreal tokenSortRatio(const QString& s1, const QString& s2, qreal scoreCutoff = 0.0, bool caseSensitive = false);
    qreal tokenSetRatio(const QString& s1, const QString& s2, qreal scoreCutoff = 0.0, bool caseSensitive = false);
};


}

#endif // RAPIDFUZZ_H
