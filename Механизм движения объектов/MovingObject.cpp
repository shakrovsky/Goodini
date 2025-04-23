#include "MovingObject.h"


AMovingObject::AMovingObject()
{
    // Устанавливаю компонент визуального облика.
    objectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("objectMesh"));

    // Делаю вышеупомянутый компонент корневым.
    RootComponent = objectMesh;

    // Включаю Tick для объектов данного класса.
    PrimaryActorTick.bCanEverTick = true;
}


void AMovingObject::BeginPlay() {
    Super::BeginPlay();
}


void AMovingObject::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    /* 1.   Если объект не привязан ни к какому маршруту, или же 
            количество точек в маршруте менее 2 -> объект никуда не двигается.   */
    if (!route || route->routePoints.Num() < 2) { return; }


    // 2.1  Вычисляю координаты (x, y, z) точки, в сторону которой направляюсь в текущий момент.
    FVector currTarget = route->routePoints[currRouteIndex];

    // 2.2  Вычисляю координаты (x, y, z) точки, в которой нахожусь в текущий момент времени.
    FVector currLocation = GetActorLocation();

    /* 2.3  Вычисляю разность-вектор, который указывает направление и расстояние от одной точки до другой.
            Метод GetSafeNormal позволяет нормализовать вектор, чтобы использовать только его направление без учета длины.  */
    FVector direction = (currTarget - currLocation).GetSafeNormal();


    // 3.1  Вычисляю координаты (x, y, z) временной точки, в которой я должен оказаться после текущего тика.
    FVector newLocation = currLocation + direction * movementSpeed * DeltaTime;

    // 3.2  Устанавливаю новое положение в пространстве для текущего объекта.
    SetActorLocation(newLocation);


    // 4.   Вычисляю евклидово (прямое) расстояние между текущим положением объекта и целевой точкой.
    float distance = FVector::Dist(newLocation, currTarget);


    // 5.   Если объект находится очень близко к текущей целевой точке маршрута - он переключается на следующую точку.
    if (distance <= 30.f) // 30.f - радиус достижения точки (магическое число).
    {
        currRouteIndex++;

        /* 5.1  Если текущая целевая точка была последней - направляю объект в самое начало маршрута.
                Простыми словами - зацикливаю движение объекта.  */
        if (currRouteIndex >= route->routePoints.Num()) {
            currRouteIndex = 0;
        }
    }

    // 6.1  Получаю поворот, который должен иметь объект, чтобы смотреть в нужном направлении.
    FRotator targetRotation = direction.Rotation();

    // 6.2  Плавно поворачиваю объект в направлении targetRotation с помощью интерполяции.
    SetActorRotation(FMath::RInterpTo(GetActorRotation(), targetRotation, DeltaTime, 3.f));
}