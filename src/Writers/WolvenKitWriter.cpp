#include "stdafx.hpp"
#include "WolvenKitWriter.hpp"
#include "Utils.hpp"
#include <limits>

WolvenKitWriter::WolvenKitWriter(const std::filesystem::path& aRootDir)
    : m_dir(aRootDir / L"csharp")
{
    if (!std::filesystem::exists(m_dir))
    {
        std::filesystem::create_directories(m_dir);
    }

    // WolvenKit has custom names for some types.
    m_typeMappings.emplace("bool", "CBool");
    m_typeMappings.emplace("int", "CInt32");
    m_typeMappings.emplace("float", "CFloat");

    m_typeMappings.emplace("Uint8", "UInt8");
    m_typeMappings.emplace("Uint16", "UInt16");
    m_typeMappings.emplace("Uint32", "UInt32");
    m_typeMappings.emplace("Uint64", "UInt64");

    m_typeMappings.emplace("String", "CString");
    m_typeMappings.emplace("string", "CString");
    m_typeMappings.emplace("Color", "CColor");
    m_typeMappings.emplace("Matrix", "CMatrix");
    m_typeMappings.emplace("Variant", "CVariant");

    m_typeMappings.emplace("multiChannelCurve", "MultiChannelCurve");
    m_typeMappings.emplace("serializationDeferredDataBuffer", "SerializationDeferredDataBuffer");

    // This is a simple for some reason.
    m_typeMappings.emplace("multiChannelCurve:Float", "MultiChannelCurve<CFloat>");

    // WolvenKit has custom classes (with more functions or fields) for some RTTI classes.
    m_customClasses.emplace("CColor", 0);
    m_customClasses.emplace("C2dArray", 0);
    m_customClasses.emplace("CMatrix", 0);
    m_customClasses.emplace("CMesh", 0);

    m_customClasses.emplace("AITrafficWorkspotCompiled", 0);
    m_customClasses.emplace("STextureGroupSetup", 1);
    m_customClasses.emplace("animAnimFeatureEntry", 0);
    m_customClasses.emplace("animAnimGraph", 0);
    m_customClasses.emplace("animAnimNode_AddSnapToTerrainIkRequest", 0);
    m_customClasses.emplace("animAnimNode_Base", 10);
    m_customClasses.emplace("animAnimNode_BlendFromPose", 0);
    m_customClasses.emplace("animAnimNode_BlendMultiple", 0);
    m_customClasses.emplace("animAnimNode_ConditionalSegmentBegin", 0);
    m_customClasses.emplace("animAnimNode_ConditionalSegmentEnd", 0);
    m_customClasses.emplace("animAnimNode_Drag", 0);
    m_customClasses.emplace("animAnimNode_FloatInput", 0);
    m_customClasses.emplace("animAnimNode_FloatTrackDirectConnConstraint", 1);
    m_customClasses.emplace("animAnimNode_ForegroundSegmentBegin", 0);
    m_customClasses.emplace("animAnimNode_ForegroundSegmentEnd", 0);
    m_customClasses.emplace("animAnimNode_IntInput", 0);
    m_customClasses.emplace("animAnimNode_LookAtController", 0);
    m_customClasses.emplace("animAnimNode_MathExpressionFloat", 0);
    m_customClasses.emplace("animAnimNode_MathExpressionPose", 0);
    m_customClasses.emplace("animAnimNode_MathExpressionVector", 0);
    m_customClasses.emplace("animAnimNode_ReferencePoseTerminator", 0);
    m_customClasses.emplace("animAnimNode_Sermo", 0);
    m_customClasses.emplace("animAnimNode_SkAnim", 2);
    m_customClasses.emplace("animAnimNode_StackTracksExtender", 0);
    m_customClasses.emplace("animAnimNode_StackTracksShrinker", 0);
    m_customClasses.emplace("animAnimNode_StackTransformsExtender", 0);
    m_customClasses.emplace("animAnimNode_StackTransformsShrinker", 0);
    m_customClasses.emplace("animAnimNode_StateMachine", 0);
    m_customClasses.emplace("animAnimStateTransitionCondition_IntFeature", 0);
    m_customClasses.emplace("animAnimStateTransitionInterpolator_Blend", 0);
    m_customClasses.emplace("animAnimVariable", 1);
    m_customClasses.emplace("animCollisionRoundedShape", 0);
    m_customClasses.emplace("animDangleConstraint_Simulation", 5);
    m_customClasses.emplace("animDangleConstraint_SimulationDyng", 0);
    m_customClasses.emplace("animDyngConstraintEllipsoid", 0);
    m_customClasses.emplace("animDyngParticle", 0);
    m_customClasses.emplace("animIDyngConstraint", 1);
    m_customClasses.emplace("animLipsyncMapping", 1);
    m_customClasses.emplace("animLookAtPartInfo", 0);
    m_customClasses.emplace("animLookAtPartsDependency", 0);
    m_customClasses.emplace("animLookAtRequest", 0);
    m_customClasses.emplace("animRig", 0);
    m_customClasses.emplace("AreaShapeOutline", 0);
    m_customClasses.emplace("CMaterialInstance", 0);
    m_customClasses.emplace("CMaterialTemplate", 0);
    m_customClasses.emplace("gameCompiledCoverData", 0);
    m_customClasses.emplace("gameCompiledSmartObjectData", 0);
    m_customClasses.emplace("gameDeviceResourceData", 0);
    m_customClasses.emplace("gameJournalCodexDescription", 0);
    m_customClasses.emplace("gameJournalInternetPage", 1);
    m_customClasses.emplace("gameLocationResource", 0);
    m_customClasses.emplace("gameLootResourceData", 0);
    m_customClasses.emplace("gameSmartObjectAnimationDatabase", 0);
    m_customClasses.emplace("meshMeshParamSpeedTreeWind", 0);
    m_customClasses.emplace("MorphTargetMesh", 0);
    m_customClasses.emplace("physicsColliderMesh", 0);
    m_customClasses.emplace("physicsMaterialLibraryResource", 0);
    m_customClasses.emplace("scnAnimationRid", 0);
    m_customClasses.emplace("scnAnimName", 0);
    m_customClasses.emplace("scnAnimName", 0);
    m_customClasses.emplace("worldInstancedMeshNode", 0);
    m_customClasses.emplace("worldInstancedOccluderNode", 0);
    m_customClasses.emplace("worldTrafficLanesSpotsResource", 0);
    m_customClasses.emplace("worldNode", 0);
    m_customClasses.emplace("worldStreamingSector", 0);
    m_customClasses.emplace("worldStreamingWorld", 0);
    m_customClasses.emplace("worldTrafficCompiledNode", 0);

    // Some ordinals needs to be skipped.
    m_skippedOrdinals.emplace("CMesh", std::unordered_set<size_t>{1, 5, 22});
    m_skippedOrdinals.emplace("animAnimNode_AddSnapToTerrainIkRequest", std::unordered_set<size_t>{12});
    m_skippedOrdinals.emplace("animAnimNode_ConditionalSegmentBegin", std::unordered_set<size_t>{12});
    m_skippedOrdinals.emplace("animAnimNode_Drag", std::unordered_set<size_t>{16});
    m_skippedOrdinals.emplace("animDyngParticle", std::unordered_set<size_t>{0});
    m_skippedOrdinals.emplace("animFacialSetup", std::unordered_set<size_t>{8, 9});
    m_skippedOrdinals.emplace("animLipsyncMapping", std::unordered_set<size_t>{3});
    m_skippedOrdinals.emplace("worldNode", std::unordered_set<size_t>{0, 1});
}

void WolvenKitWriter::Write(Global& aGlobal)
{
    m_enumWriter.open(m_dir / "cp77enums.cs", std::ios::out);
    m_enumWriter << "using System;" << std::endl;
    m_enumWriter << std::endl;
    m_enumWriter << "namespace WolvenKit.RED4.Types" << std::endl;
    m_enumWriter << "{" << std::endl;
    m_enumWriter << "\tpublic static partial class Enums" << std::endl;
    m_enumWriter << "\t{" << std::endl;
}

RED4ext::IScriptable* WolvenKitWriter::GetDefaultInstance(RED4ext::CClass* cls)
{
    using func_t = RED4ext::IScriptable* (*)(RED4ext::CClass*);
    RED4ext::RelocFunc<func_t> func(0x21C650); // 40 56 48 83 EC 30 48 8B 81 E0 00 00 00 48 8B F1
    return func(cls);
}

void WolvenKitWriter::GetCClassInfo(std::shared_ptr<Class> aClass)
{
    auto redName = aClass->name.ToString();
    auto csName = GetWolvenType(redName);
    auto elem = m_classCollection.find(csName);
    if (elem != m_classCollection.end())
    {
        return;
    }

    CsClass info;

    info.raw = aClass->raw;

    info.redName = redName;
    info.csName = csName;

    if (aClass->parent)
    {
        GetCClassInfo(aClass->parent);

        info.parentName = GetWolvenType(aClass->parent->name.ToString());
    }

    auto ordinal = GetOrdinalStart(aClass);
    auto skippedOrdinals = m_skippedOrdinals.find(info.redName);

    if (info.redName == "worldInstancedDestructibleMeshNode")
    {
        ordinal = 1000;
    }

    for (auto prop : aClass->props)
    {
        if (skippedOrdinals != m_skippedOrdinals.end())
        {
            const auto& set = skippedOrdinals->second;
            while (set.count(ordinal))
            {
                ordinal++;
            }
        }

        info.properties.emplace_back(GetCPropertyInfo(prop->raw, ordinal++));
    }

    auto elem2 = m_customClasses.find(info.redName);
    if (elem2 != m_customClasses.end())
    {
        ordinal += elem2->second;
    }
    info.nextOrdinal = ordinal;

    m_classCollection.emplace(info.csName, info);
}

WolvenKitWriter::CsProperty WolvenKitWriter::GetCPropertyInfo(RED4ext::CProperty* aProperty, size_t aOrdinal)
{
    CsProperty info;

    info.raw = aProperty;

    info.ordinal = aOrdinal;
    info.redName = aProperty->name.ToString();
    info.csType = GetCSType(aProperty->type);
    info.fixedSize = GetFixedSize(aProperty->type);

    info.csName = SanitizeGeneral(info.redName);
    info.csName[0] = std::toupper(info.csName[0]);
    info.csName = Sanitize(info.csName);

    auto parent = aProperty->parent;

    // Check if the variable has the same name as the class.
    if (_stricmp(info.csName.c_str(), parent->name.ToString()) == 0)
    {
        info.csName += "_";
    }

    if (CheckForDuplicate(parent, aProperty))
    {
        // Do not append "_" twice.
        if (info.csName[info.csName.size() - 1] != '_')
        {
            info.csName += "_";
        }

        info.csName += std::to_string(aProperty->valueOffset);
    }

    return info;
}

void WolvenKitWriter::GetPropertiesDefaults(CsClass* aClass, RED4ext::ScriptInstance aInstance, std::vector<std::string>* aPropertyValueList, int level)
{
    if (!aClass->parentName.empty())
    {
        auto parentPair = m_classCollection.find(aClass->parentName);
        if (parentPair != m_classCollection.end())
        {
            GetPropertiesDefaults(&parentPair->second, aInstance, aPropertyValueList, level + 1);
        }
    }

    for (auto prop : aClass->properties)
    {
        auto addr = prop.raw->GetValue<RED4ext::ScriptInstance*>(aInstance);
        std::string value = GetDefaultValue(prop.raw->type, addr, level);
        std::string value2;

        if (level != 0)
        {
            auto inst2 = aClass->raw->AllocInstance();
            if (inst2)
            {
                auto addr2 = prop.raw->GetValue<RED4ext::ScriptInstance*>(inst2);
                value2 = GetDefaultValue(prop.raw->type, addr2, 0);

                if (value == value2)
                {
                    continue;
                }
            }
        }

        if (!value.empty())
        {
            aPropertyValueList->emplace_back(prop.csName + " = " + value + ";");
        }
        else
        {
            auto b = "";
        }
    }
}

void WolvenKitWriter::Write(CsClass aClass)
{
    auto dir = m_dir / L"classes";
    // std::filesystem::path dir = "D:\\Homebrew\\WolvenKit\\WolvenKit.RED4.Types\\Classes";
    if (!std::filesystem::exists(dir))
    {
        std::filesystem::create_directories(dir);
    }

    std::fstream file(dir / (aClass.csName + ".cs"), std::ios::out);

    // TODO: Only if Enums
    if (!aClass.properties.empty())
    {
        file << "using static WolvenKit.RED4.Types.Enums;" << std::endl;
    }

    file << std::endl;
    file << "namespace WolvenKit.RED4.Types" << std::endl;
    file << "{" << std::endl;
    if (aClass.raw->flags.hasNoDefaultObjectSerialization)
    {
        file << "\t[REDClass(SerializeDefault = true)]" << std::endl;
    }
    file << "\tpublic ";

    file << "partial class ";

    file << aClass.csName << " : ";
    if (!aClass.parentName.empty())
    {
        file << aClass.parentName;
    }
    else
    {
        file << "RedBaseClass";
    }

    file << std::endl;
    file << "\t{" << std::endl;

    RED4ext::ScriptInstance inst = nullptr;
    if (aClass.redName != "inkInputKeyIconManager")
    {
        inst = aClass.raw->AllocInstance();
    }

    if (aClass.redName == "ActionsSequencerControllerPS")
    {
        auto b = "";
    }

    std::vector<std::string> prop_lst;
    if (inst)
    {
        GetPropertiesDefaults(&aClass, inst, &prop_lst, 0);
    }

    bool first = true;
    for (auto prop : aClass.properties)
    {
        if (!first)
        {
            file << std::endl;
        }
        first = false;

        Write(file, &prop);
    }

    if (!first)
    {
        file << std::endl;
    }

    file << "\t\tpublic " << aClass.csName << "()" << std::endl;
    file << "\t\t{" << std::endl;

    if (!prop_lst.empty())
    {
        for (auto ord : prop_lst)
        {
            file << "\t\t\t" + ord << std::endl;
        }

        file << std::endl;
    }

    file << "\t\t\tPostConstruct();" << std::endl;
    file << "\t\t}" << std::endl;
    file << std::endl;
    file << "\t\tpartial void PostConstruct();" << std::endl;

    file << "\t}" << std::endl;
    file << "}" << std::endl;
}

void WolvenKitWriter::Write(std::fstream& aFile, CsProperty* aProperty)
{
    aFile << "\t\t[Ordinal(" << aProperty->ordinal << ")] " << std::endl;
    aFile << "\t\t[RED(\"" << aProperty->redName << "\"" << aProperty->fixedSize << ")] " << std::endl;
    aFile << "\t\tpublic " << aProperty->csType << " " << aProperty->csName << std::endl;
    aFile << "\t\t{" << std::endl;
    aFile << "\t\t\tget => GetPropertyValue<" << aProperty->csType << ">();" << std::endl;
    aFile << "\t\t\tset => SetPropertyValue<" << aProperty->csType << ">(value);" << std::endl;
    aFile << "\t\t}" << std::endl;
}

void WolvenKitWriter::Write(std::shared_ptr<Class> aClass)
{
    GetCClassInfo(aClass);
}

void WolvenKitWriter::Write(std::shared_ptr<Enum> aEnum)
{
    std::string name = aEnum->name.ToString();

    m_enumWriter << "\t\tpublic enum " << name;

    if (name == "questVehicleCameraPerspective")
    {
        auto a = "";
    }
    
    switch (aEnum->actualSize)
    {
    case sizeof(int8_t):
    {
        m_enumWriter << " : byte";
        break;
    }
    case sizeof(int16_t):
    {
        m_enumWriter << " : ushort";
        break;
    }
    case sizeof(int32_t):
    {
        break;
    }
    case sizeof(int64_t):
    {
        m_enumWriter << " : ulong";
        break;
    }
    default:
    {
        auto a = "";
    }
    }

    m_enumWriter << std::endl;

    m_enumWriter << "\t\t{" << std::endl;

    std::unordered_set<std::string> m_valNames;

    for (size_t i = 0; i < aEnum->enumerators.size(); i++)
    {
        const auto& enumerator = aEnum->enumerators[i];
        auto orgName = enumerator.name.ToString();
        auto valName = SanitizeGeneral(orgName);
        valName = Sanitize(valName);
        if (std::isdigit(valName[0]))
        {
            valName = "_" + valName;
        }

        m_enumWriter << "\t\t\t";

        auto elem = m_valNames.find(valName);
        if (elem != m_valNames.end())
        {
            m_enumWriter << "// ";
        }
        else
        {
            m_valNames.emplace(valName);
        }

        if (valName != orgName)
        {
            m_enumWriter << "[RED(\"" << orgName << "\")] ";
        }

        if (name == "ETextureCompression" || name == "ETextureRawFormat")
        {
            m_enumWriter << valName << ", // = ";
        }
        else
        {
            m_enumWriter << valName << " = ";
        }

        switch (aEnum->actualSize)
        {
        case sizeof(int8_t):
        case sizeof(int16_t):
        {
            m_enumWriter << static_cast<int16_t>(enumerator.value);
            break;
        }
        case sizeof(int32_t):
        {
            m_enumWriter << static_cast<int32_t>(enumerator.value);
            break;
        }
        case sizeof(int64_t):
        {
            m_enumWriter << static_cast<int64_t>(enumerator.value);
            break;
        }
        default:
        {
            m_enumWriter << enumerator.value;
            break;
        }
        }

        if (i < aEnum->enumerators.size() - 1)
        {
            m_enumWriter << ",";
        }

        m_enumWriter << std::endl;
    }

    m_enumWriter << "\t\t}" << std::endl;
    m_enumWriter << std::endl;
}

void WolvenKitWriter::Write(std::shared_ptr<BitField> aBit)
{
    std::string name = aBit->name.ToString();

    m_enumWriter << "\t\t[Flags]" << std::endl;
    m_enumWriter << "\t\tpublic enum " << name;

    switch (aBit->actualSize)
    {
    case sizeof(int64_t):
    {
        m_enumWriter << " : ulong";
        break;
    }
    }

    m_enumWriter << std::endl;

    m_enumWriter << "\t\t{" << std::endl;

    auto validBits = aBit->validBits;
    auto counter = 0;
    while (validBits != 0)
    {
        auto bit = validBits & 1;
        validBits >>= 1;

        if (bit == 1)
        {
            m_enumWriter << "\t\t\t" << aBit->bitNames[counter].ToString() << " = 1";
            switch (aBit->actualSize)
            {
            case sizeof(int64_t):
            {
                m_enumWriter << "UL";
                break;
            }
            }

            m_enumWriter << " << " << counter;

            if (validBits != 0)
            {
                m_enumWriter << ",";
            }

            m_enumWriter << std::endl;
        }

        counter++;
    }

    m_enumWriter << "\t\t}" << std::endl;
    m_enumWriter << std::endl;
}

void WolvenKitWriter::Flush()
{
    m_enumWriter << "\t}" << std::endl;
    m_enumWriter << "}" << std::endl;

    for (auto pair : m_classCollection)
    {
        Write(pair.second);
    }
}

void WolvenKitWriter::Write(std::fstream& aFile, RED4ext::CBaseRTTIType* aType)
{
    auto cname = aType->GetName();
    auto name = GetWolvenType(cname.ToString());

    using ERTTIType = RED4ext::ERTTIType;
    switch (aType->GetType())
    {
    case ERTTIType::Fundamental:
    {
        aFile << "C" << name;
        break;
    }
    case ERTTIType::Array:
    {
        aFile << "CArray<";

        auto arr = static_cast<RED4ext::CRTTIArrayType*>(aType);
        Write(aFile, arr->innerType);

        aFile << ">";

        break;
    }
    case ERTTIType::Enum:
    case ERTTIType::BitField:
    {
        aFile << "CEnum<" << name << ">";
        break;
    }
    case ERTTIType::StaticArray:
    {
        aFile << "CStatic<";

        auto arr = static_cast<RED4ext::CRTTIStaticArrayType*>(aType);
        Write(aFile, arr->innerType);

        aFile << ">";

        break;
    }
    case ERTTIType::NativeArray:
    {
        aFile << "CArrayFixedSize<";

        auto arr = static_cast<RED4ext::CRTTINativeArrayType*>(aType);
        Write(aFile, arr->innerType);

        aFile << ">";

        break;
    }
    case ERTTIType::Handle:
    {
        aFile << "CHandle<";

        auto handle = static_cast<RED4ext::CRTTIHandleType*>(aType);
        Write(aFile, handle->innerType);

        aFile << ">";
        break;
    }
    case ERTTIType::WeakHandle:
    {
        aFile << "wCHandle<";

        auto whandle = static_cast<RED4ext::CRTTIWeakHandleType*>(aType);
        Write(aFile, whandle->innerType);

        aFile << ">";
        break;
    }
    case ERTTIType::ResourceReference:
    {
        aFile << "rRef<";

        auto rRef = static_cast<RED4ext::CRTTIResourceReferenceType*>(aType);
        Write(aFile, rRef->innerType);

        aFile << ">";

        break;
    }
    case ERTTIType::ResourceAsyncReference:
    {
        aFile << "raRef<";

        auto raRef = static_cast<RED4ext::CRTTIResourceAsyncReferenceType*>(aType);
        Write(aFile, raRef->innerType);

        aFile << ">";

        break;
    }
    case ERTTIType::LegacySingleChannelCurve:
    {
        aFile << "curveData<";

        auto curve = static_cast<RED4ext::CRTTILegacySingleChannelCurveType*>(aType);
        Write(aFile, curve->curveType);

        aFile << ">";

        break;
    }
    }
}

std::string WolvenKitWriter::GetWolvenType(const char* aName)
{
    auto elem = m_typeMappings.find(aName);
    if (elem != m_typeMappings.end())
    {
        return elem->second;
    }

    return aName;
}

std::string WolvenKitWriter::GetFixedSize(RED4ext::CBaseRTTIType* aType)
{
    using ERTTIType = RED4ext::ERTTIType;
    switch (aType->GetType())
    {
    case ERTTIType::StaticArray:
    {
        auto arr = static_cast<RED4ext::CRTTIStaticArrayType*>(aType);
        return ", " + std::to_string(arr->size) + GetFixedSize(arr->innerType);
    }
    case ERTTIType::NativeArray:
    {
        auto arr = static_cast<RED4ext::CRTTINativeArrayType*>(aType);
        return ", " + std::to_string(arr->size) + GetFixedSize(arr->innerType);
    }
    case ERTTIType::FixedArray:
    {
        auto arr = static_cast<RED4ext::CRTTIStaticArrayType*>(aType);
        return ", " + std::to_string(arr->size) + GetFixedSize(arr->innerType);
    }
    default:
    {
        auto b = aType->GetType();
        return "";
    }
    }
}

std::string WolvenKitWriter::GetCSType(RED4ext::CBaseRTTIType* aType)
{
    auto cname = aType->GetName();

    auto name = GetWolvenType(cname.ToString());

    if (name.find("Color") != std::string::npos)
    {
        auto tmp = "";
    }

    using ERTTIType = RED4ext::ERTTIType;
    switch (aType->GetType())
    {
    case ERTTIType::Fundamental:
    {
        return "C" + name;
    }
    case ERTTIType::Array:
    {
        auto arr = static_cast<RED4ext::CRTTIArrayType*>(aType);
        return "CArray<" + GetCSType(arr->innerType) + ">";
    }
    case ERTTIType::Enum:
    {
        return "CEnum<" + name + ">";
    }
    case ERTTIType::BitField:
    {
        return "CBitField<" + name + ">";
    }
    case ERTTIType::StaticArray:
    {
        auto arr = static_cast<RED4ext::CRTTIStaticArrayType*>(aType);
        return "CStatic<" + GetCSType(arr->innerType) + ">";
    }
    case ERTTIType::NativeArray:
    {
        auto arr = static_cast<RED4ext::CRTTINativeArrayType*>(aType);
        return "CArrayFixedSize<" + GetCSType(arr->innerType) + ">";
    }
    case ERTTIType::Handle:
    {
        auto handle = static_cast<RED4ext::CRTTIHandleType*>(aType);
        return "CHandle<" + GetCSType(handle->innerType) + ">";
    }
    case ERTTIType::WeakHandle:
    {
        auto whandle = static_cast<RED4ext::CRTTIWeakHandleType*>(aType);
        return "CWeakHandle<" + GetCSType(whandle->innerType) + ">";
    }
    case ERTTIType::ResourceReference:
    {
        auto rRef = static_cast<RED4ext::CRTTIResourceReferenceType*>(aType);
        return "CResourceReference<" + GetCSType(rRef->innerType) + ">";
    }
    case ERTTIType::ResourceAsyncReference:
    {
        auto raRef = static_cast<RED4ext::CRTTIResourceAsyncReferenceType*>(aType);
        return "CResourceAsyncReference<" + GetCSType(raRef->innerType) + ">";
    }
    case ERTTIType::LegacySingleChannelCurve:
    {
        auto curve = static_cast<RED4ext::CRTTILegacySingleChannelCurveType*>(aType);
        return "CLegacySingleChannelCurve<" + GetCSType(curve->curveType) + ">";
    }
    case RED4ext::ERTTIType::Simple:
    {
        if (name == std::string("CGUID"))
        {
            return "CGuid";
        }
        return name;
    }
    default:
    {
        auto b = aType->GetType();
        return name;
    }
    }
}

std::string WolvenKitWriter::GetDefaultValues(RED4ext::CClass* aType, RED4ext::ScriptInstance* aInstance)
{
    if (aType->props.size == 0)
    {
        return "";
    }

    for (auto prop : aType->props)
    {
        if (prop->flags.b3)
            continue;

        auto propInst = prop->GetValue<RED4ext::ScriptInstance*>(aInstance);
        auto tResult = GetDefaultValue(prop->type, propInst);
    }

    return "";
}

std::string WolvenKitWriter::GetDefaultValue(RED4ext::CBaseRTTIType* aType, RED4ext::ScriptInstance* aInstance, int level)
{
    std::string result;

    auto type = aType->GetType();

    switch (aType->GetType())
    {
    case RED4ext::ERTTIType::Name:
    {
        const auto value = *(RED4ext::CName*)aInstance;

        if (const auto str = value.ToString())
        {
            if (level != 0 || str != std::string("None"))
            {
                return "@\"" + std::string(str) + "\"";
            }
        }
        else
        {
            result = std::to_string(value.hash);
        }

        break;
    }
    case RED4ext::ERTTIType::Fundamental:
    {
        auto name = aType->GetName().ToString();

        if (name == std::string("Bool"))
        {
            auto val = (bool)(*(uint8_t*)aInstance);
            if (level != 0)
            {
                return val ? "true" : "false";
            }

            if (val)
            {
                return "true";
            }
        }
        else if (name == std::string("Int8"))
        {
            const auto value = *(int8_t*)aInstance;
            if (level != 0 || value != 0)
            {
                return std::to_string(value);
            }
        }
        else if (name == std::string("Uint8"))
        {
            const auto value = *(uint8_t*)aInstance;
            if (level != 0 || value != 0)
            {
                return std::to_string(value);
            }
        }
        else if (name == std::string("Int16"))
        {
            const auto value = *(int16_t*)aInstance;
            if (level != 0 || value != 0)
            {
                return std::to_string(value);
            }
        }
        else if (name == std::string("Uint16"))
        {
            const auto value = *(uint16_t*)aInstance;
            if (level != 0 || value != 0)
            {
                // why this no work?!?
                //if (value == std::numeric_limits<uint16_t>::max())
                return std::to_string(value);
            }
        }
        else if (name == std::string("Int32"))
        {
            const auto value = *(int32_t*)aInstance;
            if (level != 0 || value != 0)
            {
                return std::to_string(value);
            }
        }
        else if (name == std::string("Uint32"))
        {
            const auto value = *(uint32_t*)aInstance;
            if (level != 0 || value != 0)
            {
                return std::to_string(value);
            }
        }
        else if (name == std::string("Int64"))
        {
            const auto value = *(int64_t*)aInstance;
            if (level != 0 || value != 0)
            {
                return std::to_string(value);
            }
        }
        else if (name == std::string("Uint64"))
        {
            const auto value = *(uint64_t*)aInstance;
            if (level != 0 || value != 0)
            {
                return std::to_string(value);
            }
        }
        else if (name == std::string("Float"))
        {
            const auto value = *(float*)aInstance;
            if (level != 0 || value != 0.0F)
            {
                if (isinf(value))
                {
                    return "float.PositiveInfinity";
                }
                else
                {
                    return std::to_string(value) + "F";
                }
            }
        }
        else if (name == std::string("Double"))
        {
            const auto value = *(double*)aInstance;
            if (level != 0 || value != 0.0)
            {
                return std::to_string(value) + "D";
            }
        }
        
        break;
    }
    case RED4ext::ERTTIType::Class:
    {
        auto tResult = GetDefaultValues((RED4ext::CClass*)aType, aInstance);

        // TODO: Do we need to check this?
        // auto tResult = GetDefaultValues((RED4ext::CClass*)aType, aInstance);
        /*if (level == 0)
        {
            return "new()";
        }
        else
        {
            auto tmp = "";
        }*/

        break;
    }
    case RED4ext::ERTTIType::Array:
    {
        auto carr = static_cast<RED4ext::CRTTIArrayType*>(aType);
        auto inner = carr->GetInnerType();
        auto innerName = inner->GetName().ToString();

        for (uint32_t i = 0, n = carr->GetLength(aInstance); i < n; ++i)
        {
            RED4ext::ScriptInstance* t1 = (RED4ext::ScriptInstance*)carr->GetValuePointer(aInstance, i);
            auto innerValue = GetDefaultValue(inner, t1, level + 1);
            auto tmp = "";
        }
        break;
    }
    case RED4ext::ERTTIType::Simple:
    {
        auto name = aType->GetName().ToString();

        if (name == std::string("NodeRef"))
        {
            // TODO:
            const auto value = *(RED4ext::NodeRef*)aInstance;
            if (value.unk00 != 0)
            {
                auto tmp = "";
            }
        }
        else if (name == std::string("LocalizationString"))
        {
            const auto value = (RED4ext::LocalizationString*)aInstance;
            auto str = value->unk08.c_str();
            if (level != 0 || str != std::string(""))
            {
                return "new() { Unk1 = " + std::to_string(value->unk00) + ", Value = \"" + std::string(str) + "\" }";
            }
        }
        else if (name == std::string("TweakDBID"))
        {
            const auto var = *(RED4ext::TweakDBID*)aInstance;
            if (var.value != 0)
            {
                return "new() { Value = " + std::to_string(var.value) + " }";
            }
        }
        else if (name == std::string("String"))
        {
            const auto var = ((RED4ext::CString*)aInstance)->c_str();
            if (level != 0 || var != std::string(""))
            {
                return "@\"" + std::string(var) + "\"";
            }
        }
        else if (name == std::string("Variant"))
        {
            // TODO
            auto var = (RED4ext::Variant*)aInstance;
        }
        else if (name == std::string("CRUID"))
        {
            const auto var = *(RED4ext::CRUID*)aInstance;
            if (level != 0 || var.unk00 != 0)
            {
                return "new() { Value = " + std::to_string(var.unk00) + " }";
            }
        }
        else if (name == std::string("CGUID"))
        {
            // TODO: 16 bytes
            const auto value = *(RED4ext::CGUID*)aInstance;
            if (value.unk00 != 0 || value.unk08 != 0)
            {
                auto tmp = "";
            }
        }
        else if (name == std::string("DataBuffer"))
        {
            // TODO
            const auto value = *(RED4ext::DataBuffer*)aInstance;
            return "";
        }
        else if (name == std::string("serializationDeferredDataBuffer"))
        {
            // TODO
            return "";
        }
        else if (name == std::string("multiChannelCurve:Float"))
        {
            // TODO
            const auto var = (RED4ext::CRTTIMultiChannelCurveType*)aInstance;
            return "";
        }
        else if (name == std::string("CDateTime"))
        {
            const auto var = *(RED4ext::CDateTime*)aInstance;
            if (level != 0 || var.unk00 != 0)
            {
                return "new() { Value = " + std::to_string(var.unk00) + " }";
            }
        }

        break;
    }
    case RED4ext::ERTTIType::Enum:
    {
        auto ce = static_cast<RED4ext::CEnum*>(aType);
        auto size = ce->GetSize();

        size_t value;
        if (size == 1)
        {
            value = *(uint8_t*)aInstance;
        }
        else if (size == 2)
        {
            value = *(uint16_t*)aInstance;
        }
        else if (size == 4)
        {
            value = *(uint32_t*)aInstance;
        }
        else if (size == 8)
        {
            value = *(uint64_t*)aInstance;
        }

        if (value)
        {
            for (uint32_t i = 0; i < ce->hashList.size; i++)
            {
                size_t enumValue;
                if (size == 1)
                {
                    enumValue = (uint8_t)ce->valueList[i];
                }
                else if (size == 2)
                {
                    enumValue = (uint16_t)ce->valueList[i];
                }
                else if (size == 4)
                {
                    enumValue = (uint32_t)ce->valueList[i];
                }
                else if (size == 8)
                {
                    enumValue = (uint64_t)ce->valueList[i];
                }
                if (enumValue == value)
                {
                    auto name = ce->name.ToString();
                    auto orgName = std::string(ce->hashList[i].ToString());

                    auto valName = SanitizeGeneral(orgName);
                    valName = Sanitize(valName);
                    if (std::isdigit(valName[0]))
                    {
                        valName = "_" + valName;
                    }

                    return "Enums." + std::string(name) + "." + valName;
                }
            }
        }

        break;
    }
    case RED4ext::ERTTIType::StaticArray:
    {
        auto carr = static_cast<RED4ext::CRTTIStaticArrayType*>(aType);
        auto inner = carr->GetInnerType();
        auto innerName = inner->GetName().ToString();

        return "new(" + std::to_string(carr->GetLength(aInstance)) + ");";

        auto csType = GetCSType(inner);
        std::string tResult = "new() {";

        for (uint32_t i = 0, n = carr->GetLength(aInstance); i < n; ++i)
        {
            RED4ext::ScriptInstance* t1 = (RED4ext::ScriptInstance*)carr->GetValuePointer(aInstance, i);
            auto innerValue = GetDefaultValue(inner, t1, level + 1);
            tResult += " " + innerValue + ",";
        }

        if (tResult[tResult.size() - 1] == ',')
        {
            tResult.pop_back();
        }

        tResult += " }";
        break;
    }
    case RED4ext::ERTTIType::NativeArray:
    {
        auto carr = static_cast<RED4ext::CRTTINativeArrayType*>(aType);
        auto inner = carr->GetInnerType();
        auto innerName = inner->GetName().ToString();

        return "new(" + std::to_string(carr->GetLength(aInstance)) + ");";

        for (uint32_t i = 0, n = carr->GetLength(aInstance); i < n; ++i)
        {
            RED4ext::ScriptInstance* t1 = (RED4ext::ScriptInstance*)carr->GetValuePointer(aInstance, i);
            auto innerValue = GetDefaultValue(inner, t1, level + 1);
            auto tmp = "";
        }
        break;
    }
    case RED4ext::ERTTIType::Pointer:
    case RED4ext::ERTTIType::Handle:
    case RED4ext::ERTTIType::WeakHandle:
    {
        auto ptr = *(uint64_t*)aInstance;
        if (ptr)
        {
            struct HandleType : RED4ext::CBaseRTTIType
            {
                CBaseRTTIType* innerType;
            };

            auto inner_type = ((HandleType*)aType)->innerType;
            if (inner_type->GetType() == RED4ext::ERTTIType::Class)
            {
                auto innerValue = GetDefaultValue(inner_type, (RED4ext::ScriptInstance*)ptr, level + 1);
                auto tmp = "";
            }
        }

        auto tmp = "";
        break;
    }
    case RED4ext::ERTTIType::ResourceReference:
    {
        auto tmp = "";
        break;
    }
    case RED4ext::ERTTIType::ResourceAsyncReference:
    {
        auto value = *(uint64_t*)aInstance;

        auto tmp = "";
        break;
    }
    case RED4ext::ERTTIType::BitField:
    {
        auto bitField = static_cast<RED4ext::CBitfield*>(aType);
        auto size = bitField->GetSize();

        size_t value;
        if (size == 1)
        {
            value = *(uint8_t*)aInstance;
        }
        else if (size == 2)
        {
            value = *(uint16_t*)aInstance;
        }
        else if (size == 4)
        {
            value = *(uint32_t*)aInstance;
        }
        else if (size == 8)
        {
            value = *(uint64_t*)aInstance;
        }

        if (value)
        {
            auto counter = 0;

            //auto bitFieldName = aProperty->name.ToString();
            auto bitFieldName = bitField->name.ToString();
            auto str = std::string("");
            auto isFirst = true;

            while (value != 0)
            {
                auto bit = value & 1;
                value >>= 1;

                if (bit == 1)
                {
                    if (isFirst)
                    {
                        isFirst = false;
                    }
                    else
                    {
                        str += " | ";
                    }

                    auto orgName = std::string(bitField->bitNames[counter].ToString());

                    auto valName = SanitizeGeneral(orgName);
                    valName = Sanitize(valName);
                    if (std::isdigit(valName[0]))
                    {
                        valName = "_" + valName;
                    }

                    str += "Enums." + std::string(bitFieldName) + "." + valName;
                }

                counter++;
            }

            return str;
        }

        break;
    }
    case RED4ext::ERTTIType::LegacySingleChannelCurve:
    {
        auto realType = static_cast<RED4ext::CRTTILegacySingleChannelCurveType*>(aType);

        //auto value = *(RED4ext::CRTTILegacySingleChannelCurveType*)aInstance;
        //auto name = value.name.ToString();

        auto tmp = "";
        break;
    }
    case RED4ext::ERTTIType::ScriptReference:
    {
        auto realType = static_cast<RED4ext::CRTTIScriptReferenceType*>(aType);

        auto tmp = "";
        break;
    }
    default:;
    }

    return "";
}

size_t WolvenKitWriter::GetOrdinalStart(std::shared_ptr<Class> aClass)
{
    if (aClass->parent)
    {
        auto parentName = GetWolvenType(aClass->parent->name.ToString());
        auto parentPair = m_classCollection.find(parentName);
        if (parentPair != m_classCollection.end())
        {
            CsClass parent = (CsClass)parentPair->second;
            return parent.nextOrdinal;
        }

        throw std::runtime_error("unknown parent");
    }

    return 0;
}

bool WolvenKitWriter::CheckForDuplicate(RED4ext::CClass* aClass, RED4ext::CProperty* aProperty)
{
    // Exclude self.
    return CountOccurences(aClass, aProperty) > 1;
}

size_t WolvenKitWriter::CountOccurences(RED4ext::CClass* aClass, RED4ext::CProperty* aProperty)
{
    size_t occurences = 0;
    if (aClass->parent)
    {
        occurences += CountOccurences(aClass->parent, aProperty);
    }

    for (auto prop : aClass->props)
    {
        // Properties can have almost the same name, only the first letter is lowercase or uppercase.
        if (_stricmp(prop->name.ToString(), aProperty->name.ToString()) == 0)
        {
            occurences++;
        }
    }

    return occurences;
}

std::string WolvenKitWriter::Sanitize(const std::string& aInput)
{
    static std::regex reservedKeywords(R"(\bEquals\b|\bPropertyChanged\b|\bRead\b|\bSetValue\b|\btrue\b|\bfalse\b)");
    return std::regex_replace(aInput, reservedKeywords, "$&_");
}
