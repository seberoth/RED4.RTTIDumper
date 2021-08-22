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

    // This is a simple for some reason.
    m_typeMappings.emplace("multiChannelCurve:Float", "multiChannelCurve<CFloat>");

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
    m_skippedOrdinals.emplace("animLipsyncMapping", std::unordered_set<size_t>{3});
    m_skippedOrdinals.emplace("worldNode", std::unordered_set<size_t>{0, 1});
}

void WolvenKitWriter::Write(Global& aGlobal)
{
    m_enumWriter.open(m_dir / "cp77enums.cs", std::ios::out);
    m_enumWriter << "using System;" << std::endl;
    m_enumWriter << "using WolvenKit.RED4.CR2W.Reflection;" << std::endl;
    m_enumWriter << "// ReSharper disable InconsistentNaming" << std::endl;
    m_enumWriter << std::endl;
    m_enumWriter << "namespace WolvenKit.RED4.CR2W.Types" << std::endl;
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

void WolvenKitWriter::Write(std::shared_ptr<Class> aClass)
{
    auto dir = m_dir / L"classes";
    if (!std::filesystem::exists(dir))
    {
        std::filesystem::create_directories(dir);
    }

    auto orgName = GetWolvenType(aClass->name.ToString());
    auto name = orgName;

    auto isWritten = m_isWritten.find(name);
    if (isWritten != m_isWritten.end())
    {
        return;
    }

    if (aClass->parent)
    {
        Write(aClass->parent);
    }

    auto skippedOrdinals = m_skippedOrdinals.find(name);

    auto elem = m_customClasses.find(name);
    if (elem != m_customClasses.end())
    {
        name += "_";
    }

    std::fstream file(dir / (name + ".cs"), std::ios::out);

    file << "using WolvenKit.RED4.CR2W.Reflection;" << std::endl;

    if (!aClass->props.empty())
    {
        file << "using FastMember;" << std::endl;
        file << "using static WolvenKit.RED4.CR2W.Types.Enums;" << std::endl;
    }

    file << std::endl;
    file << "namespace WolvenKit.RED4.CR2W.Types" << std::endl;
    file << "{" << std::endl;
    file << "\t[REDMeta]" << std::endl;

    file << "\tpublic partial class " << name << " : ";
    if (aClass->parent)
    {
        auto parent = GetWolvenType(aClass->parent->name.ToString());
        file << parent;
    }
    else
    {
        file << "CVariable";
    }

    file << std::endl;
    file << "\t{" << std::endl;

    auto ordinal = GetOrdinalStart(aClass);
    if (name == "worldInstancedDestructibleMeshNode")
    {
        ordinal = 1000;
    }

    RED4ext::IScriptable* inst;
    if (!aClass->props.empty())
    {
        //inst = GetDefaultInstance(aClass->raw);
        inst = aClass->raw->AllocInstance();
    }

    for (auto prop : aClass->props)
    {
        auto csType = GetCSType(prop->type);
        auto name = SanitizeGeneral(prop->name.ToString());
        name[0] = std::tolower(name[0]);

        if (CheckForDuplicate(prop->parent, prop))
        {
            name += "_" + std::to_string(prop->valueOffset);
        }

        file << "\t\tprivate " << csType << " _" << name;

        if (inst)
        {
            std::string value = GetDefaultValue(prop, inst);
            if (!value.empty())
            {
                file << " = " << value;
            }
        }

        file << ";" << std::endl;
    }

    file << std::endl;

    // We want to write them as they are in the RTTI type, not orderd by offset.
    std::unordered_set<std::string> ord_lst;
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

        Write(file, prop, &ord_lst, ordinal++);
    }

    if (elem != m_customClasses.end())
    {
        ordinal += elem->second;
    }

    m_nextOrdinals.emplace(orgName, ordinal);

    file << "\t\tpublic " << name
         << "(IRed4EngineFile cr2w, CVariable parent, string name) : base(cr2w, parent, name) { }" << std::endl;

    file << "\t\tprotected override OrdinalDict GetPropertyOrder()" << std::endl;
    file << "\t\t{" << std::endl;
    file << "\t\t\tvar dict = base.GetPropertyOrder();" << std::endl;
    if (!ord_lst.empty())
    {
        file << std::endl;
    }
    for (auto ord : ord_lst)
    {
        file << ord;
    }
    file << std::endl;
    file << "\t\t\tPatchPropertyOrder(dict);" << std::endl;
    file << std::endl;
    file << "\t\t\treturn dict;" << std::endl;
    file << "\t\t}" << std::endl;
    file << std::endl;
    file << "\t\tpartial void PatchPropertyOrder(OrdinalDict dict);" << std::endl;

    file << "\t}" << std::endl;
    file << "}" << std::endl;

    m_isWritten.emplace(orgName);
}

void WolvenKitWriter::Write(std::shared_ptr<Enum> aEnum)
{
    std::string name = aEnum->name.ToString();

    m_enumWriter << "\t\tpublic enum " << name;

    switch (aEnum->typeSize)
    {
    case sizeof(int64_t):
    {
        m_enumWriter << " : ulong";
        break;
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

        switch (aEnum->typeSize)
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

    switch (aBit->typeSize)
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
            switch (aBit->typeSize)
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
    default:
    {
        aFile << name;
        break;
    }
    }
}

void WolvenKitWriter::Write(std::fstream& aFile, RED4ext::CProperty* aProperty, std::unordered_set<std::string>* aOrdLst, size_t aOrdinal)
{
    std::string orgName = aProperty->name.ToString();

    aFile << "\t\t[Ordinal(" << aOrdinal << ")] " << std::endl;
    aFile << "\t\t[RED(\"" << orgName << "\"" << GetFixedSize(aProperty->type) << ")] " << std::endl;

    auto csType = GetCSType(aProperty->type);

    aFile << "\t\tpublic " << csType << " ";

    auto name = SanitizeGeneral(orgName);
    name[0] = std::toupper(name[0]);
    name = Sanitize(name);

    auto privateName = SanitizeGeneral(orgName);
    privateName[0] = std::tolower(privateName[0]);
    privateName = "_" + privateName;

    auto parent = aProperty->parent;

    // Check if the variable has the same name as the class.
    if (_stricmp(name.c_str(), parent->name.ToString()) == 0)
    {
        name += "_";
    }

    if (CheckForDuplicate(parent, aProperty))
    {
        // Do not append "_" twice.
        if (name[name.size() - 1] != '_')
        {
            name += "_";
        }

        privateName += "_" + std::to_string(aProperty->valueOffset);
        name += std::to_string(aProperty->valueOffset);
    }

    aFile << name;
    aOrdLst->emplace("\t\t\tdict.Add(nameof(" + name + "), " + std::to_string(aOrdinal) + ");\n");

    aFile << std::endl;
    aFile << "\t\t{" << std::endl;
    aFile << "\t\t\tget => GetProperty(ref " << privateName << ");" << std::endl;
    aFile << "\t\t\tset => SetProperty(ref " << privateName << ", value);" << std::endl;
    aFile << "\t\t}" << std::endl;
    aFile << std::endl;
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
    default:
    {
        return "";
    }
    }
}

std::string WolvenKitWriter::GetCSType(RED4ext::CBaseRTTIType* aType)
{
    auto cname = aType->GetName();

    auto name = GetWolvenType(cname.ToString());

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
    case ERTTIType::BitField:
    {
        return "CEnum<" + name + ">";
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
        return "wCHandle<" + GetCSType(whandle->innerType) + ">";
    }
    case ERTTIType::ResourceReference:
    {
        auto rRef = static_cast<RED4ext::CRTTIResourceReferenceType*>(aType);
        return "rRef<" + GetCSType(rRef->innerType) + ">";
    }
    case ERTTIType::ResourceAsyncReference:
    {
        auto raRef = static_cast<RED4ext::CRTTIResourceAsyncReferenceType*>(aType);
        return "raRef<" + GetCSType(raRef->innerType) + ">";
    }
    case ERTTIType::LegacySingleChannelCurve:
    {
        auto curve = static_cast<RED4ext::CRTTILegacySingleChannelCurveType*>(aType);
        return "curveData<" + GetCSType(curve->curveType) + ">";
    }
    default:
    {
        return name;
    }
    }
}

std::string WolvenKitWriter::GetDefaultValue(RED4ext::CProperty* aProperty, RED4ext::IScriptable* aInst)
{
    std::string result;

    switch (aProperty->type->GetType())
    {
    case RED4ext::ERTTIType::Name:
    {
        const auto value = aProperty->GetValue<RED4ext::CName>(aInst);

        if (const auto str = value.ToString())
        {
            if (str != std::string("None"))
            {
                return "new() { Value = " + std::string(str) + " }";
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
        auto name = aProperty->type->GetName().ToString();

        if (name == std::string("Bool"))
        {
            if (aProperty->GetValue<bool>(aInst))
            {
                return "new() { Value = true }";
            }
            return "";
        }

        if (name == std::string("Int8"))
        {
            const auto value = aProperty->GetValue<int8_t>(aInst);
            if (value != 0)
            {
                return "new() { Value = " + std::to_string(value) + " }";
            }
            return "";
        }

        if (name == std::string("Uint8"))
        {
            const auto value = aProperty->GetValue<uint8_t>(aInst);
            if (value != 0)
            {
                return "new() { Value = " + std::to_string(value) + " }";
            }
            return "";
        }

        if (name == std::string("Int16"))
        {
            const auto value = aProperty->GetValue<int16_t>(aInst);
            if (value != 0)
            {
                return "new() { Value = " + std::to_string(value) + " }";
            }
            return "";
        }

        if (name == std::string("Uint16"))
        {
            const auto value = aProperty->GetValue<uint16_t>(aInst);
            if (value != 0)
            {
                return "new() { Value = " + std::to_string(value) + " }";
            }
            return "";
        }

        if (name == std::string("Int32"))
        {
            const auto value = aProperty->GetValue<int32_t>(aInst);
            if (value != 0)
            {
                return "new() { Value = " + std::to_string(value) + " }";
            }
            return "";
        }

        if (name == std::string("Uint32"))
        {
            const auto value = aProperty->GetValue<uint32_t>(aInst);
            if (value != 0)
            {
                return "new() { Value = " + std::to_string(value) + " }";
            }
            return "";
        }

        if (name == std::string("Int64"))
        {
            const auto value = aProperty->GetValue<int64_t>(aInst);
            if (value != 0)
            {
                return "new() { Value = " + std::to_string(value) + " }";
            }
            return "";
        }

        if (name == std::string("Uint64"))
        {
            const auto value = aProperty->GetValue<uint64_t>(aInst);
            if (value != 0)
            {
                return "new() { Value = " + std::to_string(value) + " }";
            }
            return "";
        }

        if (name == std::string("Float"))
        {
            const auto value = aProperty->GetValue<float>(aInst);
            if (value != 0.0F)
            {
                return "new() { Value = " + std::to_string(value) + "F }";
            }
            return "";
        }

        if (name == std::string("Double"))
        {
            const auto value = aProperty->GetValue<double>(aInst);
            if (value != 0.0)
            {
                return "new() { Value = " + std::to_string(value) + " }";
            }
            return "";
        }

        auto tmp = "";
        break;
    }
    case RED4ext::ERTTIType::Class:
    {
        auto tmp = "";
        break;
    }
    case RED4ext::ERTTIType::Array:
        break;
    case RED4ext::ERTTIType::Simple:
    {
        auto name = aProperty->type->GetName().ToString();

        if (name == std::string("NodeRef"))
        {
            const auto value = aProperty->GetValue<RED4ext::NodeRef>(aInst);
            if (value.unk00 != 0)
            {
                auto tmp = "";
            }
            return "";
        }

        if (name == std::string("LocalizationString"))
        {
            const auto value = aProperty->GetValue<RED4ext::LocalizationString*>(aInst);
            return "";
        }

        if (name == std::string("TweakDBID"))
        {
            const auto value = aProperty->GetValue<RED4ext::TweakDBID>(aInst);
            if (value.value != 0)
            {
                return std::to_string(value.value);
            }
            return "";
        }

        if (name == std::string("String"))
        {
            const auto value = aProperty->GetValue<RED4ext::CString*>(aInst);
            if (value->Length() != 0)
            {
                return value->c_str();
            }
            return "";
        }

        if (name == std::string("Variant"))
        {
            const auto value = aProperty->GetValue<RED4ext::Variant>(aInst);
            return "";
        }

        if (name == std::string("CRUID"))
        {
            const auto value = aProperty->GetValue<RED4ext::CRUID>(aInst);
            if (value.unk00 != 0)
            {
                auto tmp = "";
            }
            return "";
        }

        if (name == std::string("CGUID"))
        {
            const auto value = aProperty->GetValue<RED4ext::CGUID>(aInst);
            if (value.unk00 != 0 || value.unk08 != 0)
            {
                auto tmp = "";
            }
            return "";
        }

        if (name == std::string("DataBuffer"))
        {
            const auto value = aProperty->GetValue<RED4ext::DataBuffer>(aInst);
            return "";
        }

        if (name == std::string("serializationDeferredDataBuffer"))
        {
            return "";
        }

        if (name == std::string("multiChannelCurve:Float"))
        {
            return "";
        }

        if (name == std::string("CDateTime"))
        {
            const auto value = aProperty->GetValue<RED4ext::CDateTime>(aInst);
            if (value.unk00 != 0)
            {
                auto tmp = "";
            }
            return "";
        }

        auto tmp = "";
        break;
    }
    case RED4ext::ERTTIType::Enum:
    {
        auto ce = static_cast<RED4ext::CEnum*>(aProperty->type);
        auto size = ce->GetSize();

        size_t value;
        if (size == 1)
        {
            value = aProperty->GetValue<uint8_t>(aInst);
        }
        else if (size == 2)
        {
            value = aProperty->GetValue<uint16_t>(aInst);
        }
        else if (size == 4)
        {
            value = aProperty->GetValue<uint32_t>(aInst);
        }
        else
        {
            auto tmp = "";
        }

        if (value)
        {
            for (uint32_t i = 0; i < ce->hashList.size; i++)
            {
                if (ce->valueList[i] == value)
                {
                    auto name = ce->name.ToString();
                    auto tmp = ce->hashList[i].ToString();

                    return "new() { Value = " + std::string(name) + "." + std::string(tmp) + " }";
                }
            }
        }

        break;
    }
    case RED4ext::ERTTIType::StaticArray:
    {
        // auto value = aProperty->GetValue<RED4ext::CRTTIStaticArrayType*>(aInst);
        break;


        auto carr = static_cast<RED4ext::CRTTIStaticArrayType*>(aProperty->type);
        auto inner = carr->GetInnerType();
        auto innerName = inner->GetName().ToString();

        for (uint32_t i = 0, n = carr->GetLength(aInst); i < n; ++i)
        {
            auto t = carr->GetValuePointer(aInst, i);
            auto tmp = "";
        }
        break;
    }
    case RED4ext::ERTTIType::NativeArray:
    {
        auto tmp = "";
        break;
    }
    case RED4ext::ERTTIType::Pointer:
    {
        auto tmp = "";
        break;
    }
    case RED4ext::ERTTIType::Handle:
    {
        auto tmp = "";
        break;
    }
    case RED4ext::ERTTIType::WeakHandle:
    {
        auto ptr = aProperty->GetValue<uint64_t*>(aInst);
        if (ptr)
        {
            struct HandleType : RED4ext::CBaseRTTIType
            {
                uint64_t uk;
                CBaseRTTIType* inner;
                RED4ext::CName name;
            };

            auto inner_type = ((HandleType*)aProperty->type)->inner;

            auto tmp = "";
        }

        break;
    }
    case RED4ext::ERTTIType::ResourceReference:
    {
        auto tmp = "";
        break;
    }
    case RED4ext::ERTTIType::ResourceAsyncReference:
    {
        auto value = aProperty->GetValue<uint64_t*>(aInst);

        auto tmp = "";
        break;
    }
    case RED4ext::ERTTIType::BitField:
    {
        auto bitField = static_cast<RED4ext::CBitfield*>(aProperty->type);
        auto size = bitField->GetSize();

        size_t value;
        if (size == 1)
        {
            value = aProperty->GetValue<uint8_t>(aInst);
        }
        else if (size == 2)
        {
            value = aProperty->GetValue<uint16_t>(aInst);
        }
        else if (size == 4)
        {
            value = aProperty->GetValue<uint32_t>(aInst);
        }
        else if (size == 8)
        {
            value = aProperty->GetValue<uint64_t>(aInst);
        }
        else
        {
            auto tmp = "";
        }

        if (value)
        {
            auto counter = 0;

            auto bitFieldName = aProperty->name.ToString();
            auto str = std::string("new() { Value = ");
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

                    str += std::string(bitFieldName) + "." + std::string(bitField->bitNames[counter].ToString());

                    auto tmp = "";
                }

                counter++;
            }

            str += " }";
            return str;
        }

        break;
    }
    case RED4ext::ERTTIType::LegacySingleChannelCurve:
    {
        auto realType = static_cast<RED4ext::CRTTILegacySingleChannelCurveType*>(aProperty->type);

        auto value = aProperty->GetValue<RED4ext::CRTTILegacySingleChannelCurveType*>(aInst);
        auto name = value->name.ToString();

        auto tmp = "";
        break;
    }
    case RED4ext::ERTTIType::ScriptReference:
    {
        auto realType = static_cast<RED4ext::CRTTIScriptReferenceType*>(aProperty->type);

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
        auto elem = m_nextOrdinals.find(parentName);
        if (elem != m_nextOrdinals.end())
        {
            return elem->second;
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
