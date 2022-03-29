#include "rapidfuzz.h"

#include <rapidfuzz/fuzz.hpp>

#include <QDebug>


namespace
{


template <typename Sentence1, typename Iterable, typename Sentence2 = typename Iterable::value_type>
std::optional<std::pair<int, double>>
extractOneWithSimpleQuery(const Sentence1& query, const Iterable& choices, const double scoreCutoff)
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


inline std::wstring toNormalizedStdWString(const QString& qs, bool caseSensitive)
{
    return (caseSensitive ? qs : qs.toLower()).toStdWString();
}


QList<std::wstring> toNormalizedStdWStringList(const QStringList& strings, bool caseSensitive)
{
    QList<std::wstring> normalizedStrings(strings.size());
    std::transform(strings.begin(), strings.end(), normalizedStrings.begin(), [caseSensitive] (const QString& e) {
        return toNormalizedStdWString(e, caseSensitive);
    });
    return normalizedStrings;
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
    const auto normalizedChoices = toNormalizedStdWStringList(choices, caseSensitive);

    int bestIndex = -1;
    double bestScore = scoreCutoff;
    for (const auto& q : query) {
        const auto opt = extractOneWithSimpleQuery(toNormalizedStdWString(q, caseSensitive), normalizedChoices, bestScore);
        if (opt.has_value()) {
            const auto& pair = opt.value();
            bestScore = pair.second;
            bestIndex = pair.first;
        }
    }
    const QString bestChoice = bestIndex != -1 ? choices[bestIndex] : QString();
    qDebug() << "RapidFuzz::extractOne:" << bestScore << bestChoice;
    return QVariantList() << bestScore << bestChoice;
}


QVariantList RapidFuzz::extract(const QStringList& query, const QStringList& choices, qreal scoreCutoff, bool caseSensitive)
{
    QVariantList results;
    const auto normalizedQuery = toNormalizedStdWStringList(query, caseSensitive);
    for (const auto& choice : choices) {
        const auto opt = extractOneWithSimpleQuery(toNormalizedStdWString(choice, caseSensitive), normalizedQuery, scoreCutoff);
        if (opt.has_value()) {
            const double score = opt.value().second;
            results.append(QVariant(QVariantList() << score << choice));
        }
    }
    return results;
}


qreal RapidFuzz::ratio(const QString& s1, const QString& s2, qreal scoreCutoff, bool caseSensitive)
{
    return rapidfuzz::fuzz::ratio(toNormalizedStdWString(s1, caseSensitive),
                                  toNormalizedStdWString(s2, caseSensitive),
                                  scoreCutoff);
}


qreal RapidFuzz::partialRatio(const QString& s1, const QString& s2, qreal scoreCutoff, bool caseSensitive)
{
    return rapidfuzz::fuzz::partial_ratio(toNormalizedStdWString(s1, caseSensitive),
                                          toNormalizedStdWString(s2, caseSensitive),
                                          scoreCutoff);
}


qreal RapidFuzz::tokenRatio(const QString& s1, const QString& s2, qreal scoreCutoff, bool caseSensitive)
{
    return rapidfuzz::fuzz::token_ratio(toNormalizedStdWString(s1, caseSensitive),
                                        toNormalizedStdWString(s2, caseSensitive),
                                        scoreCutoff);
}


qreal RapidFuzz::tokenSortRatio(const QString& s1, const QString& s2, qreal scoreCutoff, bool caseSensitive)
{
    return rapidfuzz::fuzz::token_sort_ratio(toNormalizedStdWString(s1, caseSensitive),
                                             toNormalizedStdWString(s2, caseSensitive),
                                             scoreCutoff);
}


qreal RapidFuzz::tokenSetRatio(const QString& s1, const QString& s2, qreal scoreCutoff, bool caseSensitive)
{
    return rapidfuzz::fuzz::token_set_ratio(toNormalizedStdWString(s1, caseSensitive),
                                            toNormalizedStdWString(s2, caseSensitive),
                                            scoreCutoff);
}


}
