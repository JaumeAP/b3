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

#include "adm_bed_mapping.h"

namespace CineIA {
namespace ADM {

std::array<BedChannelMapping, 10> const kSevenOneTwoBedChannelTable{{
    {"AC_00010001", "FrontLeft", kIABChannelID_Left},
    {"AC_00010002", "FrontRight", kIABChannelID_Right},
    {"AC_00010003", "FrontCentre", kIABChannelID_Center},
    {"AC_00010004", "LowFrequencyEffects", kIABChannelID_LFE},
    {"AC_0001000a", "SideLeft", kIABChannelID_LeftSideSurround},
    {"AC_0001000b", "SideRight", kIABChannelID_RightSideSurround},
    {"AC_0001001c", "BackLeftMid", kIABChannelID_LeftRearSurround},
    {"AC_0001001d", "BackRightMid", kIABChannelID_RightRearSurround},
    {"AC_00010013", "TopSideLeft", kIABChannelID_LeftTopSurround},
    {"AC_00010014", "TopSideRight", kIABChannelID_RightTopSurround},
}};

bool IsSevenOneTwoBedPackFormat(std::string const &iAdmPackFormatId)
{
    return iAdmPackFormatId == kSevenOneTwoBedPackFormatId;
}

bool LookupBedChannelId(std::string const &iAdmChannelFormatId, IABChannelIDType &oChannelId)
{
    for (auto const &entry : kSevenOneTwoBedChannelTable)
    {
        if (iAdmChannelFormatId == entry.admChannelFormatId)
        {
            oChannelId = entry.iabChannelId;
            return true;
        }
    }
    return false;
}

} // namespace ADM
} // namespace CineIA
