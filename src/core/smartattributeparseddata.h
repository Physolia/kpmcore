/*************************************************************************
 *  Copyright (C) 2018 by Caio Carvalho <caiojcarvalho@gmail.com>        *
 *                                                                       *
 *  This program is free software; you can redistribute it and/or        *
 *  modify it under the terms of the GNU General Public License as       *
 *  published by the Free Software Foundation; either version 3 of       *
 *  the License, or (at your option) any later version.                  *
 *                                                                       *
 *  This program is distributed in the hope that it will be useful,      *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 *  GNU General Public License for more details.                         *
 *                                                                       *
 *  You should have received a copy of the GNU General Public License    *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.*
 *************************************************************************/

#if !defined(KPMCORE_SMARTATTRIBUTEPARSEDDATA_H)
#define KPMCORE_SMARTATTRIBUTEPARSEDDATA_H

#include <QJsonObject>
#include <QString>

class SmartDiskInformation;

class SmartAttributeParsedData
{
public:
    enum SmartAttributeUnit {
        SMART_ATTRIBUTE_UNIT_UNKNOWN,
        SMART_ATTRIBUTE_UNIT_NONE,
        SMART_ATTRIBUTE_UNIT_MSECONDS,
        SMART_ATTRIBUTE_UNIT_SECTORS,
        SMART_ATTRIBUTE_UNIT_MKELVIN,
        SMART_ATTRIBUTE_UNIT_SMALL_PERCENT,
        SMART_ATTRIBUTE_UNIT_PERCENT,
        SMART_ATTRIBUTE_UNIT_MB,
        _SMART_ATTRIBUTE_UNIT_MAX
    };

    enum SmartQuirk {
        SMART_QUIRK_9_POWERONMINUTES            = 0x000001,
        SMART_QUIRK_9_POWERONSECONDS            = 0x000002,
        SMART_QUIRK_9_POWERONHALFMINUTES        = 0x000004,
        SMART_QUIRK_192_EMERGENCYRETRACTCYCLECT = 0x000008,
        SMART_QUIRK_193_LOADUNLOAD              = 0x000010,
        SMART_QUIRK_194_10XCELSIUS              = 0x000020,
        SMART_QUIRK_194_UNKNOWN                 = 0x000040,
        SMART_QUIRK_200_WRITEERRORCOUNT         = 0x000080,
        SMART_QUIRK_201_DETECTEDTACOUNT         = 0x000100,
        SMART_QUIRK_5_UNKNOWN                   = 0x000200,
        SMART_QUIRK_9_UNKNOWN                   = 0x000400,
        SMART_QUIRK_197_UNKNOWN                 = 0x000800,
        SMART_QUIRK_198_UNKNOWN                 = 0x001000,
        SMART_QUIRK_190_UNKNOWN                 = 0x002000,
        SMART_QUIRK_232_AVAILABLERESERVEDSPACE  = 0x004000,
        SMART_QUIRK_233_MEDIAWEAROUTINDICATOR   = 0x008000,
        SMART_QUIRK_225_TOTALLBASWRITTEN        = 0x010000,
        SMART_QUIRK_4_UNUSED                    = 0x020000,
        SMART_QUIRK_226_TIMEWORKLOADMEDIAWEAR   = 0x040000,
        SMART_QUIRK_227_TIMEWORKLOADHOSTREADS   = 0x080000,
        SMART_QUIRK_228_WORKLOADTIMER           = 0x100000,
        SMART_QUIRK_3_UNUSED                    = 0x200000
    };

    struct SmartQuirkDataBase {
        const char *model;
        const char *firmware;
        SmartAttributeParsedData::SmartQuirk quirk;
    };

public:
    SmartAttributeParsedData(SmartDiskInformation *disk, QJsonObject jsonAttribute);

    SmartAttributeParsedData(const SmartAttributeParsedData &other);

public:
    quint32 id() const
    {
        return m_Id;
    }

    qint32 currentValue() const
    {
        return m_CurrentValue;
    }

    qint32 worstValue() const
    {
        return m_WorstValue;
    }

    qint32 threshold() const
    {
        return m_Threshold;
    }

    bool prefailure() const
    {
        return m_Prefailure;
    }

    bool online() const
    {
        return m_Online;
    }

    quint64 raw() const
    {
        return m_Raw;
    }

    quint64 prettyValue() const
    {
        return m_PrettyValue;
    }

    SmartAttributeUnit prettyUnit() const
    {
        return m_PrettyUnit;
    }

    bool goodNowValid() const
    {
        return m_GoodNowValid;
    }

    bool goodNow() const
    {
        return m_GoodNow;
    }

    bool goodInThePastValid() const
    {
        return m_GoodInThePastValid;
    }

    bool goodInThePast() const
    {
        return m_GoodInThePast;
    }

    bool thresholdValid() const
    {
        return m_ThresholdValid;
    }

    bool currentValueValid() const
    {
        return m_CurrentValueValid;
    }

    bool worstValueValid() const
    {
        return m_WorstValueValid;
    }

    bool warn() const
    {
        return m_Warn;
    }

    SmartDiskInformation *disk() const
    {
        return m_Disk;
    }

protected:
    void validateValues();

    bool updateUnit();

    void makePretty();

    void verifyAttribute();

    void verifyTemperature();

    void verifyShortTime();

    void verifyLongTime();

    void verifySectors();

private:
    quint32 m_Id;
    qint32 m_CurrentValue;
    qint32 m_WorstValue;
    qint32 m_Threshold;
    quint64 m_Raw;
    quint64 m_PrettyValue;
    bool m_CurrentValueValid;
    bool m_WorstValueValid;
    bool m_ThresholdValid;
    bool m_Prefailure;
    bool m_Online;
    bool m_GoodNow;
    bool m_GoodNowValid;
    bool m_GoodInThePast;
    bool m_GoodInThePastValid;
    bool m_Warn;
    SmartAttributeUnit m_PrettyUnit;
    SmartDiskInformation *m_Disk;
    SmartQuirk m_Quirk;
};

#endif // SMARTATTRIBUTEPARSEDDATA_H
