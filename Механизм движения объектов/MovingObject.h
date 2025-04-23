#pragma once

#include "RouteActor.h"			  	 // Объявление класса-маршрута.

#include "CoreMinimal.h"		  	 // Базовые типы, функции Unreal Engine.
#include "GameFramework/Actor.h"  	         // Объявление родительского класса - AActor.
#include "MovingObject.generated.h"              // Авто-сгенерированный заголовок для системы рефлексии.

/*	--- --- --- ---  */

/*
	AMovingObject - класс движущегося (по некоторому маршруту) объекта. 
	Наследуется от AActor - базового класса для всех игровых объектов в UE.
*/
UCLASS()
class TIRED_API AMovingObject : public AActor
{
	GENERATED_BODY() // Обязательный макрос для классов UE (содержит служебный код).

public:
	/*
		Конструктор AMovingObject для инициализации компонентов:
		 -> Визуальное представление (UStaticMeshComponent).
		 -> Компоненты движения, коллизий и прочее.
	*/
	AMovingObject();

protected:
	/*
		Метод BeginPlay вызывается при появлении актера в игровом мире. Идеальное место для:
		 -> Установки начальных параметров движения.
		 -> Кэширования ссылок на компоненты.
		 -> Запуска таймеров.
	*/
	void BeginPlay() override;

public:
	/*
		Метод Tick используется для обновления состояния, вызывается каждый кадр.
		DeltaTime - время в секундах с последнего кадра.

		Здесь реализуется:
		 -> Расчёт перемещения по маршруту.
		 -> Обработка ввода игрока/ИИ.
		 -> Физическое движение.
	*/
	void Tick(float DeltaTime) override;

	// ------------------------------------- //
	// Настройки, доступные в Details Panel: //
	// ------------------------------------- //

	// Визуальное представление (модель объекта):
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visual")
	UStaticMeshComponent* objectMesh;

	// Скорость движения объекта:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float movementSpeed;

	// Маршрут движения задается актером-объектом маршрута:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	ARouteActor* route;

private:

	// Текущий индекс точки в маршруте.
	int32 currRouteIndex;
};
