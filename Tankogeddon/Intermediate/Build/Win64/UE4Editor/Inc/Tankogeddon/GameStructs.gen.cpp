// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Tankogeddon/GameStructs.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGameStructs() {}
// Cross Module References
	TANKOGEDDON_API UEnum* Z_Construct_UEnum_Tankogeddon_ECannonType();
	UPackage* Z_Construct_UPackage__Script_Tankogeddon();
// End Cross Module References
	static UEnum* ECannonType_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_Tankogeddon_ECannonType, Z_Construct_UPackage__Script_Tankogeddon(), TEXT("ECannonType"));
		}
		return Singleton;
	}
	template<> TANKOGEDDON_API UEnum* StaticEnum<ECannonType>()
	{
		return ECannonType_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ECannonType(ECannonType_StaticEnum, TEXT("/Script/Tankogeddon"), TEXT("ECannonType"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_Tankogeddon_ECannonType_Hash() { return 55434473U; }
	UEnum* Z_Construct_UEnum_Tankogeddon_ECannonType()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_Tankogeddon();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ECannonType"), 0, Get_Z_Construct_UEnum_Tankogeddon_ECannonType_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "ECannonType::FireProjectile", (int64)ECannonType::FireProjectile },
				{ "ECannonType::FireTrace", (int64)ECannonType::FireTrace },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "FireProjectile.DisplayName", "Use projectile" },
				{ "FireProjectile.Name", "ECannonType::FireProjectile" },
				{ "FireTrace.DisplayName", "Use trace" },
				{ "FireTrace.Name", "ECannonType::FireTrace" },
				{ "ModuleRelativePath", "GameStructs.h" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_Tankogeddon,
				nullptr,
				"ECannonType",
				"ECannonType",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
