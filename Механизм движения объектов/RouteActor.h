#pragma once

#include "CoreMinimal.h"		  	 // Базовые типы, функции Unreal Engine.
#include "GameFramework/Actor.h"  	 // Объявление родительского класса - AActor.
#include "RouteActor.generated.h"    // Авто-сгенерированный заголовок для системы рефлексии.

/*  --- --- --- ---  */

/*
	ARouteActor — актёр, хранящий информацию о маршруте для других объектов.
	Наследуется от AActor, соответственно может быть размещён в игровом мире.
*/
UCLASS()
class TIRED_API ARouteActor : public AActor
{
	GENERATED_BODY()

public:

	// ------------------------------------- //
	// Настройки, доступные в Details Panel: //
	// ------------------------------------- //

	// Массив маршрутных точек (координат):
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Route")
	TArray<FVector> routePoints;

	/*
		routePoints — последовательность ключевых точек,
		по которым могут двигаться объекты (например, AMovingObject).
		Можно задавать и изменять прямо в редакторе.
	*/
};