// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef TANKOGEDDON_TankPlayerController_generated_h
#error "TankPlayerController.generated.h already included, missing '#pragma once' in TankPlayerController.h"
#endif
#define TANKOGEDDON_TankPlayerController_generated_h

#define Tankogeddon_Source_Tankogeddon_TankPlayerController_h_17_SPARSE_DATA
#define Tankogeddon_Source_Tankogeddon_TankPlayerController_h_17_RPC_WRAPPERS
#define Tankogeddon_Source_Tankogeddon_TankPlayerController_h_17_RPC_WRAPPERS_NO_PURE_DECLS
#define Tankogeddon_Source_Tankogeddon_TankPlayerController_h_17_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesATankPlayerController(); \
	friend struct Z_Construct_UClass_ATankPlayerController_Statics; \
public: \
	DECLARE_CLASS(ATankPlayerController, APlayerController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Tankogeddon"), NO_API) \
	DECLARE_SERIALIZER(ATankPlayerController)


#define Tankogeddon_Source_Tankogeddon_TankPlayerController_h_17_INCLASS \
private: \
	static void StaticRegisterNativesATankPlayerController(); \
	friend struct Z_Construct_UClass_ATankPlayerController_Statics; \
public: \
	DECLARE_CLASS(ATankPlayerController, APlayerController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Tankogeddon"), NO_API) \
	DECLARE_SERIALIZER(ATankPlayerController)


#define Tankogeddon_Source_Tankogeddon_TankPlayerController_h_17_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ATankPlayerController(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ATankPlayerController) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATankPlayerController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATankPlayerController); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ATankPlayerController(ATankPlayerController&&); \
	NO_API ATankPlayerController(const ATankPlayerController&); \
public:


#define Tankogeddon_Source_Tankogeddon_TankPlayerController_h_17_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ATankPlayerController(ATankPlayerController&&); \
	NO_API ATankPlayerController(const ATankPlayerController&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATankPlayerController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATankPlayerController); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ATankPlayerController)


#define Tankogeddon_Source_Tankogeddon_TankPlayerController_h_17_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__TankPawn() { return STRUCT_OFFSET(ATankPlayerController, TankPawn); } \
	FORCEINLINE static uint32 __PPO__MousePos() { return STRUCT_OFFSET(ATankPlayerController, MousePos); }


#define Tankogeddon_Source_Tankogeddon_TankPlayerController_h_14_PROLOG
#define Tankogeddon_Source_Tankogeddon_TankPlayerController_h_17_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Tankogeddon_Source_Tankogeddon_TankPlayerController_h_17_PRIVATE_PROPERTY_OFFSET \
	Tankogeddon_Source_Tankogeddon_TankPlayerController_h_17_SPARSE_DATA \
	Tankogeddon_Source_Tankogeddon_TankPlayerController_h_17_RPC_WRAPPERS \
	Tankogeddon_Source_Tankogeddon_TankPlayerController_h_17_INCLASS \
	Tankogeddon_Source_Tankogeddon_TankPlayerController_h_17_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Tankogeddon_Source_Tankogeddon_TankPlayerController_h_17_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Tankogeddon_Source_Tankogeddon_TankPlayerController_h_17_PRIVATE_PROPERTY_OFFSET \
	Tankogeddon_Source_Tankogeddon_TankPlayerController_h_17_SPARSE_DATA \
	Tankogeddon_Source_Tankogeddon_TankPlayerController_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	Tankogeddon_Source_Tankogeddon_TankPlayerController_h_17_INCLASS_NO_PURE_DECLS \
	Tankogeddon_Source_Tankogeddon_TankPlayerController_h_17_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> TANKOGEDDON_API UClass* StaticClass<class ATankPlayerController>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Tankogeddon_Source_Tankogeddon_TankPlayerController_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
