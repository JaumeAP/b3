/*
 Copyright (c) 2026. Steven Song (izwb-003)
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#ifndef CINEIA_CLI_ADM_BED_MAPPING_H
#define CINEIA_CLI_ADM_BED_MAPPING_H

#include <IABDataTypes.h>

#include <array>
#include <cstdint>
#include <string>

namespace CineIA {
namespace ADM {

using namespace SMPTE::ImmersiveAudioBitstream;

// EBU ADM common-definitions audioPackFormatID for the "9.1_7.1.2_(2+7+0)"
// DirectSpeakers pack (libadm resources/common_definitions.xml). This is the
// 10-channel bed IAB Application Profile 1 (RDD57 Table 1, item B2) allows,
// alongside "7.1DS" - no other bed soundfield group is permitted.
constexpr char kSevenOneTwoBedPackFormatId[] = "AP_00010016";

struct BedChannelMapping {
    char const *admChannelFormatId; // e.g. "AC_00010001"
    char const *admChannelName;     // e.g. "FrontLeft"
    IABChannelIDType iabChannelId;
};

// One entry per <audioChannelFormatIDRef> of AP_00010016, in the order they
// appear in libadm's common_definitions.xml. AudioDataID assignment (see
// kFirstObjectAudioDataId below) follows this same order: channel index n
// (0-based) gets AudioDataID n+1.
extern std::array<BedChannelMapping, 10> const kSevenOneTwoBedChannelTable;

// True if iAdmPackFormatId identifies the bed pack this module maps
// (kSevenOneTwoBedPackFormatId).
bool IsSevenOneTwoBedPackFormat(std::string const &iAdmPackFormatId);

// Looks up an ADM audioChannelFormatID within kSevenOneTwoBedChannelTable.
// Returns false, leaving oChannelId untouched, if iAdmChannelFormatId is not
// one of the 10 known channels.
bool LookupBedChannelId(std::string const &iAdmChannelFormatId, IABChannelIDType &oChannelId);

// AudioDataID numbering: the bed's channels occupy AudioDataID 1..10, in
// kSevenOneTwoBedChannelTable order; objects are numbered sequentially from
// 11. RDD57 item O1 (SMPTE RDD57:2021, 8.3) caps ObjectDefinition MetaID at
// 118, so at most kMaxObjects are representable under Profile 1.
constexpr IABAudioDataIDType kFirstObjectAudioDataId = 11;
constexpr uint32_t kMaxObjects = 118; // RDD57 8.1.4

} // namespace ADM
} // namespace CineIA

#endif // #ifndef CINEIA_CLI_ADM_BED_MAPPING_H
