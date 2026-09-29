// Self-check for adm_bed_mapping.{h,cpp}: exits non-zero on any failed
// assertion. Not a test framework - just the smallest thing that fails if
// the ADM channel-format-ID -> IAB ChannelID table or numbering breaks.

#include "adm_bed_mapping.h"

#include <common/IABElements.h>

#include <cassert>
#include <cstdio>
#include <set>
#include <vector>

using namespace CineIA::ADM;
using namespace SMPTE::ImmersiveAudioBitstream;

int main()
{
    // Every table entry must resolve, in order, and AudioDataID n (0-based
    // index) must equal n + 1 per the numbering convention.
    IABChannelIDType channelId;
    for (std::size_t i = 0; i < kSevenOneTwoBedChannelTable.size(); ++i)
    {
        auto const &entry = kSevenOneTwoBedChannelTable[i];
        assert(LookupBedChannelId(entry.admChannelFormatId, channelId));
        assert(channelId == entry.iabChannelId);
    }

    // An unknown ADM channel format ID must not match.
    assert(!LookupBedChannelId("AC_99999999", channelId));

    // The pack format ID must be recognised, and only that one.
    assert(IsSevenOneTwoBedPackFormat(kSevenOneTwoBedPackFormatId));
    assert(!IsSevenOneTwoBedPackFormat("AP_00010005")); // 9.1_5.1.4, a different bed

    // RDD57 Table 1, item B2: exactly the ten ChannelIDs it lists, no more,
    // no fewer, and no duplicates.
    std::set<IABChannelIDType> const expected{
        kIABChannelID_Left, kIABChannelID_Center, kIABChannelID_Right,
        kIABChannelID_LeftSideSurround, kIABChannelID_RightSideSurround,
        kIABChannelID_LeftRearSurround, kIABChannelID_RightRearSurround,
        kIABChannelID_LFE, kIABChannelID_LeftTopSurround, kIABChannelID_RightTopSurround,
    };
    std::set<IABChannelIDType> actual;
    for (auto const &entry : kSevenOneTwoBedChannelTable)
    {
        actual.insert(entry.iabChannelId);
    }
    assert(actual == expected);
    assert(kSevenOneTwoBedChannelTable.size() == expected.size());

    // Build a real IABBedDefinition from the table and confirm it round-trips
    // through the actual IABLib setter/getter API: AudioDataID 1..10 in
    // table order, default (unity, no decorrelation) channel gain per RDD57
    // items B3/B6, default bedUseCase (9.1OH) per RDD57 6.2.
    std::vector<IABChannel *> bedChannels;
    for (std::size_t i = 0; i < kSevenOneTwoBedChannelTable.size(); ++i)
    {
        IABChannel *channel = new IABChannel();
        channel->SetChannelID(kSevenOneTwoBedChannelTable[i].iabChannelId);
        channel->SetAudioDataID(static_cast<IABAudioDataIDType>(i + 1));
        bedChannels.push_back(channel);
    }
    assert(kFirstObjectAudioDataId == bedChannels.size() + 1);

    IABBedDefinition bed(kIABFrameRate_24FPS);
    assert(bed.SetBedChannels(bedChannels) == kIABNoError);

    IABChannelCountType channelCount;
    bed.GetChannelCount(channelCount);
    assert(channelCount == kSevenOneTwoBedChannelTable.size());

    IABUseCaseType useCase;
    bed.GetBedUseCase(useCase);
    assert(useCase == kIABUseCase_9_1_OH);

    std::vector<IABChannel *> readBack;
    bed.GetBedChannels(readBack);
    assert(readBack.size() == kSevenOneTwoBedChannelTable.size());
    for (std::size_t i = 0; i < readBack.size(); ++i)
    {
        IABChannelIDType readChannelId;
        IABAudioDataIDType readAudioDataId;
        readBack[i]->GetChannelID(readChannelId);
        readBack[i]->GetAudioDataID(readAudioDataId);
        assert(readChannelId == kSevenOneTwoBedChannelTable[i].iabChannelId);
        assert(readAudioDataId == i + 1);

        IABGain gain;
        readBack[i]->GetChannelGain(gain);
        assert(gain.getIABGainPrefix() == kIABGainPrefix_Unity); // RDD57 item B3

        uint1_t decorInfoExists;
        readBack[i]->GetDecorInfoExists(decorInfoExists);
        assert(decorInfoExists == 0); // RDD57 item B6
    }

    std::printf("adm_bed_mapping_selfcheck: all checks passed\n");
    return 0;
}
