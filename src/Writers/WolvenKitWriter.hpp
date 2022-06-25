#pragma once

#include "IWriter.hpp"

class WolvenKitWriter : public IWriter
{
    struct CsProperty
    {
        RED4ext::CProperty* raw;

        size_t ordinal;

        std::string redName;
        std::string csName;

        std::string fixedSize;
        std::string csType;

        std::string defaultValue;
        std::string value;
    };

    struct CsPropertyValueHolder
    {
        RED4ext::CProperty* raw;
        std::string defaultValue;
        std::string value;
    };

    struct CsClass
    {
        RED4ext::CClass* raw;

        std::string redName;
        std::string csName;
        std::string parentName;
        bool serializeDefault = false;

        bool hasEnumOrFlag = false;
        std::vector<CsProperty> properties;
        size_t nextOrdinal;

        bool isValueListSet = false;
        std::vector<std::pair<std::string, CsPropertyValueHolder>> propertiesValueList;
    };

public:
    WolvenKitWriter(const std::filesystem::path& aRootDir);
    ~WolvenKitWriter() = default;

    void Write(Global& aGlobal);
    void Write(std::shared_ptr<Class> aClass);
    void Write(std::shared_ptr<Enum> aEnum);
    void Write(std::shared_ptr<BitField> aBit);
    void Flush();

private:
    void Write(std::fstream& aFile, RED4ext::CBaseRTTIType* aType);

    void GetCClassInfo(std::shared_ptr<Class> aClass);
    CsProperty GetCPropertyInfo(RED4ext::CProperty* aProperty, size_t aOrdinal);

    void GetPropertiesDefaults(CsClass* aClass, RED4ext::IScriptable* aInstance = nullptr);

    void Write(CsClass aClass);
    void Write(std::fstream& aFile, CsProperty aProperty);

    std::string GetWolvenType(const char* aName);
    std::string GetFixedSize(RED4ext::CBaseRTTIType* aType);

    std::string GetCSType(RED4ext::CBaseRTTIType* aType);
    bool ContainsEnum(RED4ext::CBaseRTTIType* aType);
    std::string GetCSDefault(RED4ext::CBaseRTTIType* aType);

    std::vector<std::string> GetDefaultValues(RED4ext::CClass* aType, RED4ext::ScriptInstance* aInstance);
    std::string GetDefaultValue(RED4ext::CBaseRTTIType* aType, RED4ext::ScriptInstance* aInstance);

    size_t GetOrdinalStart(std::shared_ptr<Class> aClass);

    bool CheckForDuplicate(RED4ext::CClass* aClass, RED4ext::CProperty* aProperty);
    size_t CountOccurences(RED4ext::CClass* aClass, RED4ext::CProperty* aProperty);

    std::string Sanitize(const std::string& aInput);

    std::filesystem::path m_dir;

    std::unordered_map<std::string, std::string> m_typeMappings;

    std::fstream m_enumWriter;

    std::unordered_map<std::string, size_t> m_customClasses;
    std::unordered_map<std::string, std::unordered_set<size_t>> m_skippedOrdinals;
    std::unordered_map<std::string, size_t> m_nextOrdinals;
    std::unordered_set<std::string> m_isWritten;

    std::unordered_map<std::string, CsClass> m_classCollection;
};
