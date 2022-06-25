#include "stdafx.hpp"
#include "WolvenKitWriter.hpp"
#include "Utils.hpp"

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

    if (aClass->raw->flags.hasNoDefaultObjectSerialization)
    {
        info.serializeDefault = true;
    }

    if (aClass->parent)
    {
        GetCClassInfo(aClass->parent);

        info.parentName = GetWolvenType(aClass->parent->name.ToString());
    }

    for (auto prop : aClass->props)
    {
        if (prop->isClass)
        {
            GetCClassInfo(prop->cls);
        }
    }

    auto ordinal = GetOrdinalStart(aClass);
    auto skippedOrdinals = m_skippedOrdinals.find(info.redName);

    if (info.redName == "worldInstancedDestructibleMeshNode")
    {
        ordinal = 1000;
    }

    for (auto prop : aClass->props)
    {
        if (ContainsEnum(prop->raw->type))
        {
            info.hasEnumOrFlag = true;
        }

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

    GetPropertiesDefaults(&info);

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

void WolvenKitWriter::GetPropertiesDefaults(CsClass* aClass, RED4ext::IScriptable* aInstance)
{
    bool hasParent = false;
    CsClass parent;
    if (!aClass->parentName.empty())
    {
        auto parentPair = m_classCollection.find(aClass->parentName);
        if (parentPair != m_classCollection.end())
        {
            hasParent = true;
            parent = parentPair->second;
            GetPropertiesDefaults(&parentPair->second, aInstance);
        }
    }

    if (!aClass->isValueListSet)
    {
        RED4ext::ScriptInstance instance = nullptr;
        if (aClass->redName != "inkInputKeyIconManager")
        {
            instance = aClass->raw->AllocInstance();
        }

        if (hasParent)
        {
            for (auto pair : parent.propertiesValueList)
            {
                auto propertyHolder = pair.second;

                CsPropertyValueHolder valueHolder;

                valueHolder.raw = propertyHolder.raw;
                valueHolder.defaultValue = propertyHolder.defaultValue;

                valueHolder.value = propertyHolder.value;
                if (instance)
                {
                    auto addr = propertyHolder.raw->GetValue<RED4ext::ScriptInstance*>(instance);
                    std::string instanceValue = GetDefaultValue(propertyHolder.raw->type, addr);

                    if (propertyHolder.value.empty())
                    {
                        if (propertyHolder.defaultValue != instanceValue)
                        {
                            valueHolder.value = instanceValue;
                        }
                    }
                    else
                    {
                        valueHolder.defaultValue = valueHolder.value;
                        if (valueHolder.defaultValue != instanceValue)
                        {
                            valueHolder.value = instanceValue;
                        }
                        else
                        {
                            valueHolder.value = "";
                        }
                    }
                }
                aClass->propertiesValueList.emplace_back(std::pair{pair.first, valueHolder});
            }
        }

        for (auto prop : aClass->properties)
        {
            CsPropertyValueHolder valueHolder;

            valueHolder.raw = prop.raw;
            auto b = GetCSDefault(prop.raw->type);
            valueHolder.defaultValue = GetCSDefault(prop.raw->type);

            if (prop.redName == "socketId")
            {
                aClass->propertiesValueList.emplace_back(std::pair{prop.csName, valueHolder});
                continue;
            }

            if (instance != nullptr)
            {
                auto addr = prop.raw->GetValue<RED4ext::ScriptInstance*>(instance);
                std::string instanceValue = GetDefaultValue(prop.raw->type, addr);
                if (prop.csName == "BatchPositionsPath" || prop.csName == "OutputPath")
                {
                    instanceValue = "new()";
                }

                if (valueHolder.defaultValue != instanceValue)
                {
                    valueHolder.value = instanceValue;
                }
            }

            aClass->propertiesValueList.emplace_back(std::pair{prop.csName, valueHolder});
        }

        aClass->isValueListSet = true;
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
    // file << std::endl;
    if (aClass.serializeDefault)
    {
        file << "\t[REDClass(SerializeDefault = true)]" << std::endl;
    }
    if (aClass.redName != aClass.csName)
    {
        file << "\t[RED(\"" << aClass.redName << "\")]" << std::endl;
    }
    file << "\tpublic partial class ";

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
    file << "\t{";

    if (!aClass.properties.empty())
    {
        // for (auto prop : aClass.properties)
        //{
        //     file << "\tprivate " << prop.csType << " " << prop.privateCsName << ";" << std::endl;
        // }

        for (auto prop : aClass.properties)
        {
            file << std::endl;
            Write(file, prop);
        }
    }

    file << std::endl;
    file << "\t\tpublic " << aClass.csName << "()" << std::endl;
    file << "\t\t{";

    if (!aClass.propertiesValueList.empty())
    {
        std::vector<std::string> prop_lst;
        for (auto pair : aClass.propertiesValueList)
        {
            if (!pair.second.value.empty())
            {
                prop_lst.emplace_back(pair.first + " = " + pair.second.value + ";");
            }
        }

        if (!prop_lst.empty())
        {
            for (auto line : prop_lst)
            {
                file << std::endl;
                file << "\t\t\t" << line;
            }
            file << std::endl;
        }
    }

    file << std::endl;
    file << "\t\t\tPostConstruct();" << std::endl;
    file << "\t\t}" << std::endl;
    file << std::endl;
    file << "\t\tpartial void PostConstruct();" << std::endl;
    file << "\t}" << std::endl;

    file << "}" << std::endl;
}

void WolvenKitWriter::Write(std::fstream& aFile, CsProperty aProperty)
{
    aFile << "\t\t[Ordinal(" << aProperty.ordinal << ")] " << std::endl;
    aFile << "\t\t[RED(\"" << aProperty.redName << "\"" << aProperty.fixedSize << ")] " << std::endl;
    aFile << "\t\tpublic " << aProperty.csType << " " << aProperty.csName << std::endl;
    aFile << "\t\t{" << std::endl;
    aFile << "\t\t\tget => GetPropertyValue<" << aProperty.csType << ">();" << std::endl;
    aFile << "\t\t\tset => SetPropertyValue<" << aProperty.csType << ">(value);" << std::endl;
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

    auto b = aEnum->actualSize;
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
    case RED4ext::ERTTIType::FixedArray:
    {
        aFile << "CFixedArray<";

        auto arr = static_cast<RED4ext::CRTTIStaticArrayType*>(aType);
        Write(aFile, arr->innerType);

        aFile << ">";
        break;
    }
    default:
    {
        auto b = aType->GetType();
        aFile << name;
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
    case ERTTIType::FixedArray:
    {
        auto arr = static_cast<RED4ext::CRTTIStaticArrayType*>(aType);
        return "CArrayFixedSize<" + GetCSType(arr->innerType) + ">";
    }
    default:
    {
        auto b = aType->GetType();
        return name;
    }
    }
}

bool WolvenKitWriter::ContainsEnum(RED4ext::CBaseRTTIType* aType)
{
    using ERTTIType = RED4ext::ERTTIType;
    switch (aType->GetType())
    {
    case ERTTIType::Enum:
    case ERTTIType::BitField:
    {
        return true;
    }
    case ERTTIType::Array:
    {
        auto arr = static_cast<RED4ext::CRTTIArrayType*>(aType);
        return ContainsEnum(arr->innerType);
    }
    case ERTTIType::StaticArray:
    {
        auto arr = static_cast<RED4ext::CRTTIStaticArrayType*>(aType);
        return ContainsEnum(arr->innerType);
    }
    case ERTTIType::NativeArray:
    {
        auto arr = static_cast<RED4ext::CRTTINativeArrayType*>(aType);
        return ContainsEnum(arr->innerType);
    }
    case ERTTIType::Handle:
    {
        auto handle = static_cast<RED4ext::CRTTIHandleType*>(aType);
        return ContainsEnum(handle->innerType);
    }
    case ERTTIType::WeakHandle:
    {
        auto wHandle = static_cast<RED4ext::CRTTIWeakHandleType*>(aType);
        return ContainsEnum(wHandle->innerType);
    }
    case ERTTIType::ResourceReference:
    {
        auto rRef = static_cast<RED4ext::CRTTIResourceReferenceType*>(aType);
        return ContainsEnum(rRef->innerType);
    }
    case ERTTIType::ResourceAsyncReference:
    {
        auto raRef = static_cast<RED4ext::CRTTIResourceAsyncReferenceType*>(aType);
        return ContainsEnum(raRef->innerType);
    }
    case ERTTIType::LegacySingleChannelCurve:
    {
        auto curve = static_cast<RED4ext::CRTTILegacySingleChannelCurveType*>(aType);
        return ContainsEnum(curve->curveType);
    }
    case RED4ext::ERTTIType::FixedArray:
    {
        auto arr = static_cast<RED4ext::CRTTIStaticArrayType*>(aType);
        return ContainsEnum(arr->innerType);
    }
    default:
    {
        return false;
    }
    }
}

std::string WolvenKitWriter::GetCSDefault(RED4ext::CBaseRTTIType* aType)
{
    using ERTTIType = RED4ext::ERTTIType;
    auto b = aType->GetType();
    switch (aType->GetType())
    {
    case ERTTIType::Name:
        return "\"None\"";
    case ERTTIType::Fundamental:
    {
        auto name = aType->GetName().ToString();

        if (name == std::string("Bool"))
        {
            return "false";
        }

        if (name == std::string("Float"))
        {
            return "0.000000F";
        }

        return "0";
    }
    case ERTTIType::Class:
        return "null";
    case ERTTIType::Array:
        return "null";
    case ERTTIType::Simple:
    {
        auto name = aType->GetName().ToString();

        if (name == std::string("NodeRef"))
        {
            return "\"\"";
        }
        if (name == std::string("LocalizationString"))
        {
            return "null";
        }
        if (name == std::string("TweakDBID"))
        {
            return "null";
        }
        if (name == std::string("String"))
        {
            return "\"\"";
        }
        if (name == std::string("Variant"))
        {
            return "null";
        }
        if (name == std::string("CRUID"))
        {
            return "0";
        }
        if (name == std::string("CGUID"))
        {
            return "null";
        }
        if (name == std::string("DataBuffer"))
        {
            return "null";
        }
        if (name == std::string("serializationDeferredDataBuffer"))
        {
            return "null";
        }
        if (name == std::string("multiChannelCurve:Float"))
        {
            return "null";
        }
        if (name == std::string("CDateTime"))
        {
            return "0";
        }
        return "null";
    }
    case ERTTIType::Enum:
    {
        auto ce = static_cast<RED4ext::CEnum*>(aType);
        for (uint32_t i = 0; i < ce->hashList.size; i++)
        {
            if (ce->valueList[i] == (uint64_t)0)
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
    case ERTTIType::StaticArray:
        return "null";
    case ERTTIType::NativeArray:
        return "null";
    case ERTTIType::Pointer:
        return "null";
    case ERTTIType::Handle:
        return "null";
    case ERTTIType::WeakHandle:
        return "null";
    case ERTTIType::ResourceReference:
        return "null";
    case ERTTIType::ResourceAsyncReference:
        return "null";
    case ERTTIType::BitField:
        return "0";
    case ERTTIType::LegacySingleChannelCurve:
        return "null";
    case ERTTIType::ScriptReference:
        return "null";
    case ERTTIType::FixedArray:
        return "null";
    default:
        return "";
    }
}

std::vector<std::string> WolvenKitWriter::GetDefaultValues(RED4ext::CClass* aType, RED4ext::ScriptInstance* aInstance)
{
    std::vector<std::string> valueList;

    if (aType->props.size == 0)
    {
        return valueList;
    }

    auto redName = aType->name.ToString();
    auto element = m_classCollection.find(redName);
    if (element == m_classCollection.end())
    {
        return valueList;
    }

    CsClass defCls = element->second;

    for (auto prop : defCls.properties)
    {
        std::string defaultValue;
        for (auto pair : defCls.propertiesValueList)
        {
            if (pair.first == prop.csName)
            {
                defaultValue = pair.second.defaultValue;
            }
        }

        auto propInst = prop.raw->GetValue<RED4ext::ScriptInstance*>(aInstance);
        auto value = GetDefaultValue(prop.raw->type, propInst);

        if (defaultValue != value)
        {
            valueList.emplace_back(prop.csName + " = " + value);
        }
    }

    return valueList;
}

inline void ReplaceAll(std::string& str, const std::string& from, const std::string& to)
{
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

std::string WolvenKitWriter::GetDefaultValue(RED4ext::CBaseRTTIType* aType, RED4ext::ScriptInstance* aInstance)
{
    auto type = aType->GetType();

    switch (aType->GetType())
    {
    case RED4ext::ERTTIType::Name:
    {
        const auto value = *(RED4ext::CName*)aInstance;

        if (const auto str = value.ToString())
        {
            return "\"" + std::string(str) + "\"";
        }
        else
        {
            return std::to_string(value.hash);
        }
    }
    case RED4ext::ERTTIType::Fundamental:
    {
        auto name = aType->GetName().ToString();

        if (name == std::string("Bool"))
        {
            auto val = (bool)(*(uint8_t*)aInstance);
            return val ? "true" : "false";
        }
        else if (name == std::string("Int8"))
        {
            const auto value = *(int8_t*)aInstance;
            return std::to_string(value);
        }
        else if (name == std::string("Uint8"))
        {
            const auto value = *(uint8_t*)aInstance;
            return std::to_string(value);
        }
        else if (name == std::string("Int16"))
        {
            const auto value = *(int16_t*)aInstance;
            return std::to_string(value);
        }
        else if (name == std::string("Uint16"))
        {
            const auto value = *(uint16_t*)aInstance;
            return std::to_string(value);
        }
        else if (name == std::string("Int32"))
        {
            const auto value = *(int32_t*)aInstance;
            return std::to_string(value);
        }
        else if (name == std::string("Uint32"))
        {
            const auto value = *(uint32_t*)aInstance;
            return std::to_string(value);
        }
        else if (name == std::string("Int64"))
        {
            const auto value = *(int64_t*)aInstance;
            return std::to_string(value);
        }
        else if (name == std::string("Uint64"))
        {
            const auto value = *(uint64_t*)aInstance;
            return std::to_string(value);
        }
        else if (name == std::string("Float"))
        {
            const auto value = *(float*)aInstance;
            if (isinf(value))
            {
                return "float.PositiveInfinity";
            }
            return std::to_string(value) + "F";
        }
        else if (name == std::string("Double"))
        {
            const auto value = *(double*)aInstance;
            return std::to_string(value);
        }

        break;
    }
    case RED4ext::ERTTIType::Class:
    {
        auto valLst = GetDefaultValues((RED4ext::CClass*)aType, aInstance);

        std::string result = "new()";

        if (!valLst.empty())
        {
            result += " {";
        }

        for (auto val : valLst)
        {
            result += " " + val + ",";
        }

        if (!valLst.empty())
        {
            result = result.substr(0, result.size() - 1);
            result += " }";
        }

        return result;
    }
    case RED4ext::ERTTIType::Array:
    {
        auto carr = static_cast<RED4ext::CRTTIArrayType*>(aType);
        auto inner = carr->GetInnerType();
        auto innerName = inner->GetName().ToString();
        auto length = carr->GetLength(aInstance);
        if (length == 0)
        {
            return "new()";
        }

        std::string tResult = "new()";

        std::vector<std::string> valLst;
        for (uint32_t i = 0, n = carr->GetLength(aInstance); i < n; ++i)
        {
            RED4ext::ScriptInstance* t1 = (RED4ext::ScriptInstance*)carr->GetValuePointer(aInstance, i);
            auto innerValue = GetDefaultValue(inner, t1);
            if (!innerValue.empty())
            {
                valLst.emplace_back(innerValue);
            }
        }

        if (!valLst.empty())
        {
            tResult += " {";
        }

        for (auto val : valLst)
        {
            tResult += " " + val + ",";
        }

        if (!valLst.empty())
        {
            tResult = tResult.substr(0, tResult.size() - 1);
            tResult += " }";
        }

        return tResult;
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
            return GetCSDefault(aType);
        }
        else if (name == std::string("LocalizationString"))
        {
            const auto value = (RED4ext::LocalizationString*)aInstance;
            auto str = value->unk08.c_str();
            return "new() { Unk1 = " + std::to_string(value->unk00) + ", Value = \"" + std::string(str) + "\" }";
        }
        else if (name == std::string("TweakDBID"))
        {
            const auto var = *(RED4ext::TweakDBID*)aInstance;
            if (var.value != 0)
            {
                return std::to_string(var.value);
            }
            return GetCSDefault(aType);
        }
        else if (name == std::string("String"))
        {
            std::string var = ((RED4ext::CString*)aInstance)->c_str();
            if (!var.empty())
            {
                ReplaceAll(var, std::string("\\"), std::string("\\\\"));

                return "\"" + var + "\"";
            }
            return GetCSDefault(aType);
        }
        else if (name == std::string("Variant"))
        {
            // TODO
            auto var = (RED4ext::Variant*)aInstance;
            return GetCSDefault(aType);
        }
        else if (name == std::string("CRUID"))
        {
            const auto var = *(RED4ext::CRUID*)aInstance;
            return std::to_string(var.unk00);
        }
        else if (name == std::string("CGUID"))
        {
            // TODO: 16 bytes
            const auto value = *(RED4ext::CGUID*)aInstance;
            return GetCSDefault(aType);
        }
        else if (name == std::string("DataBuffer"))
        {
            // TODO
            const auto value = *(RED4ext::DataBuffer*)aInstance;
            return GetCSDefault(aType);
        }
        else if (name == std::string("serializationDeferredDataBuffer"))
        {
            // TODO
            return GetCSDefault(aType);
        }
        else if (name == std::string("multiChannelCurve:Float"))
        {
            // TODO
            const auto var = (RED4ext::CRTTIMultiChannelCurveType*)aInstance;
            return GetCSDefault(aType);
        }
        else if (name == std::string("CDateTime"))
        {
            const auto var = *(RED4ext::CDateTime*)aInstance;
            return std::to_string(var.unk00);
        }

        return GetCSDefault(aType);
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

        break;
    }
    case RED4ext::ERTTIType::StaticArray:
    {
        auto carr = static_cast<RED4ext::CRTTIStaticArrayType*>(aType);
        auto inner = carr->GetInnerType();
        auto innerName = inner->GetName().ToString();

        return "new(" + std::to_string(carr->GetLength(aInstance)) + ")";

        auto csType = GetCSType(inner);
        std::string tResult = "new() {";

        for (uint32_t i = 0, n = carr->GetLength(aInstance); i < n; ++i)
        {
            RED4ext::ScriptInstance* t1 = (RED4ext::ScriptInstance*)carr->GetValuePointer(aInstance, i);
            auto innerValue = GetDefaultValue(inner, t1);
            tResult += " " + innerValue + ",";
        }

        if (tResult[tResult.size() - 1] == ',')
        {
            tResult.pop_back();
        }

        tResult += " }";
        break;
    }
    case RED4ext::ERTTIType::FixedArray:
    {
        auto carr = static_cast<RED4ext::CRTTIStaticArrayType*>(aType);
        auto inner = carr->GetInnerType();
        auto innerName = inner->GetName().ToString();

        return "new(" + std::to_string(carr->GetLength(aInstance)) + ")";

        auto csType = GetCSType(inner);
        std::string tResult = "new() {";

        for (uint32_t i = 0, n = carr->GetLength(aInstance); i < n; ++i)
        {
            RED4ext::ScriptInstance* t1 = (RED4ext::ScriptInstance*)carr->GetValuePointer(aInstance, i);
            auto innerValue = GetDefaultValue(inner, t1);
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

        return "new(" + std::to_string(carr->GetLength(aInstance)) + ")";

        for (uint32_t i = 0, n = carr->GetLength(aInstance); i < n; ++i)
        {
            RED4ext::ScriptInstance* t1 = (RED4ext::ScriptInstance*)carr->GetValuePointer(aInstance, i);
            auto innerValue = GetDefaultValue(inner, t1);
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
                auto innerValue = GetDefaultValue(inner_type, (RED4ext::ScriptInstance*)ptr);
                auto tmp = "";
            }
        }

        return GetCSDefault(aType);
    }
    case RED4ext::ERTTIType::ResourceReference:
    {
        return GetCSDefault(aType);
    }
    case RED4ext::ERTTIType::ResourceAsyncReference:
    {
        auto value = *(uint64_t*)aInstance;

        return GetCSDefault(aType);
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

        return GetCSDefault(aType);
    }
    case RED4ext::ERTTIType::ScriptReference:
    {
        auto realType = static_cast<RED4ext::CRTTIScriptReferenceType*>(aType);

        return GetCSDefault(aType);
    }
    }

    return GetCSDefault(aType);
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
