#include "LevelSpawner.h"
// Completa tu aviso de copyright en la página de Descripción de la Configuración del Proyecto.

#include "BaseLevel.h"
#include "Engine.h"
#include "Components/BoxComponent.h"
#include "CoreMinimal.h"

// Establece valores predeterminados
ALevelSpawner::ALevelSpawner()
{
    // Configura este actor para llamar a Tick() cada cuadro. Puedes desactivar esto para mejorar el rendimiento si no lo necesitas.
    PrimaryActorTick.bCanEverTick = true;
}

// Llamado cuando el juego comienza o cuando se genera
void ALevelSpawner::BeginPlay()
{
    Super::BeginPlay();

    // Genera el primer nivel
    SpawnLevel(true);

    // Genera tres niveles adicionales
    SpawnLevel(false);
    SpawnLevel(false);
    SpawnLevel(false);
}

// Llamado cada cuadro
void ALevelSpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Función para generar un nivel
void ALevelSpawner::SpawnLevel(bool IsFirst)
{
    // Establece la ubicación y rotación de generación predeterminada

    SpawnLocation = FVector(0.0f, 1000.0f, 0.0f);
    SpawnRotation = FRotator(0, 90, 0);

    if (!IsFirst)
    {
        ABaseLevel* LastLevel = LevelList.Last();
        SpawnLocation = LastLevel->GetSpawnLocation()->GetComponentTransform().GetTranslation();
    }

    RandomLevel = FMath::RandRange(1, 10);
    ABaseLevel* NewLevel = nullptr;
    try
    {
        // Genera un nivel basado en el valor aleatorio

        if (RandomLevel == 1)
        {
            NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level1,
                SpawnLocation, SpawnRotation, SpawnInfo);
        }
        else if (RandomLevel == 2)
        {
            NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level2,
                SpawnLocation, SpawnRotation, SpawnInfo);
        }
        else if (RandomLevel == 3)
        {
            NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level3,
                SpawnLocation, SpawnRotation, SpawnInfo);
        }
        else if (RandomLevel == 4)
        {
            NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level4,
                SpawnLocation, SpawnRotation, SpawnInfo);
        }
        else if (RandomLevel == 5)
        {
            NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level5,
                SpawnLocation, SpawnRotation, SpawnInfo);
        }
    }
    catch (const std::exception& e)
    {
        // Maneja cualquier otra excepción
        UE_LOG(LogTemp, Error, TEXT("Ocurrió una excepción: %s"), *e.what());
    }

    // Si se generó un nuevo nivel
    if (NewLevel != nullptr)
    {
        if (NewLevel->GetTrigger())
        {
            NewLevel->GetTrigger()->OnComponentBeginOverlap.AddDynamic(this, &ALevelSpawner::OnOverlapBegin);
        }
    }
    if (NewLevel != nullptr)
    {
        // Agrega el nuevo nivel a la lista de niveles generados
        LevelList.Add(NewLevel);
    }
    

    // Si hay más de 5 niveles generados, elimina el más antiguo
    if (LevelList.Num() > 5)
    {
        LevelList.RemoveAt(0);
    }
}

// Función llamada cuando ocurre una superposición
void ALevelSpawner::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    SpawnLevel(false);
}
