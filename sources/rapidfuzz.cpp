#include "rapidfuzz.h"

#include <rapidfuzz/fuzz.hpp>

#include <QDebug>


namespace
{


template <typename Sentence1, typename Iterable, typename Sentence2 = typename Iterable::value_type>
std::optional<std::pair<int, double>>
extractOneWithSimpleQuery(const Sentence1& query, const Iterable& choices, const double scoreCutoff = 0.0)
{
    int bestMatchIndex = -1;
    double bestScore = scoreCutoff;

    auto scorer = rapidfuzz::fuzz::CachedRatio<typename Sentence1::value_type>(query);

    int i = 0;
    for (const auto& choice : choices) {
        const double score = scorer.similarity(choice, bestScore);
        if (score >= bestScore) {
            bestMatchIndex = i;
            bestScore = score;
        }
        ++i;
    }

    if (bestMatchIndex == -1) {
        return std::nullopt;
    }
    return std::make_pair(bestMatchIndex, bestScore);
}


}


namespace Moqt
{


RapidFuzz::RapidFuzz(QObject *parent)
    : QObject{parent}
{
}


QVariantList RapidFuzz::extractOne(const QStringList& query, const QStringList& choices, qreal scoreCutoff, bool caseSensitive)
{
    QList<std::wstring> choicesStd(choices.size());
    std::transform(choices.begin(), choices.end(), choicesStd.begin(), [caseSensitive] (const QString& e) {
        return (caseSensitive ? e : e.toLower()).toStdWString();
    });

    int bestIndex = -1;
    double bestScore = scoreCutoff;
    for (const auto& q : query) {
        const auto opt = extractOneWithSimpleQuery((caseSensitive ? q : q.toLower()).toStdWString(), choicesStd, scoreCutoff);
        if (opt.has_value()) {
            const auto& pair = opt.value();
            const int index = pair.first;
            const double score = pair.second;
            if (score >= bestScore) {
                bestScore = score;
                bestIndex = index;
            }
        }
    }
    const QString bestText = bestIndex != -1 ? choices[bestIndex] : QString();
    qDebug() << "RapidFuzz::bestScore:" << bestScore << bestText;
    return QVariantList() << bestScore << bestText;
}


}
