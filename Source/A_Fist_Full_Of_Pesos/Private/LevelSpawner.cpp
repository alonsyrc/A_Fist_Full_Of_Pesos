#include "LevelSpawner.h"
// Completa tu aviso de copyright en la p�gina de Descripci�n de la Configuraci�n del Proyecto.

#include "BaseLevel.h"
#include "Engine.h"
#include "Components/BoxComponent.h"

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

// Funci�n para generar un nivel
void ALevelSpawner::SpawnLevel(bool IsFirst)
{
    // Establece la ubicaci�n y rotaci�n de generaci�n predeterminada
    SpawnLocation = FVector(0.0f, 1000.0f, 0.0f);
    SpawnRotation = FRotator(0, 90, 0);

    // Si no es el primer nivel, establece la ubicaci�n de generaci�n en base al �ltimo nivel generado
    if (!IsFirst)
    {
        ABaseLevel* LastLevel = LevelList.Last();
        SpawnLocation = LastLevel->GetSpawnLocation()->GetComponentTransform().GetTranslation();
        SpawnRotation = FRotator(0, 90, 0);
    }

    // Selecciona un nivel aleatorio para generar
    RandomLevel = FMath::RandRange(1, 10);
    ABaseLevel* NewLevel = nullptr;

    // Genera un nivel basado en el valor aleatorio
    if (RandomLevel == 1)
    {
        NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level1, SpawnLocation, SpawnRotation, SpawnInfo);
    }
    else if (RandomLevel == 2)
    {
        NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level2, SpawnLocation, SpawnRotation, SpawnInfo);
    }
    else if (RandomLevel == 3)
    {
        NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level3, SpawnLocation, SpawnRotation, SpawnInfo);
    }
    else if (RandomLevel == 4)
    {
        NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level4, SpawnLocation, SpawnRotation, SpawnInfo);
    }
    else if (RandomLevel == 5)
    {
        NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level5, SpawnLocation, SpawnRotation, SpawnInfo);
    }

    // Si se gener� un nuevo nivel
    if (NewLevel)
    {
        // Si el nuevo nivel tiene un componente de disparador, agrega una funci�n de superposici�n
        if (NewLevel->GetTrigger())
        {
            NewLevel->GetTrigger()->OnComponentBeginOverlap.AddDynamic(this, &ALevelSpawner::OnOverlapBegin);
        }
    }

    // Agrega el nuevo nivel a la lista de niveles generados
    LevelList.Add(NewLevel);

    // Si hay m�s de 5 niveles generados, elimina el m�s antiguo
    if (LevelList.Num() > 5)
    {
        LevelList.RemoveAt(0);
    }
}

// Funci�n llamada cuando ocurre una superposici�n
void ALevelSpawner::OnOverlapBegin(UPrimitiveComponent* OverlappepedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepREsult)
{
    // Genera un nuevo nivel
    SpawnLevel(false);
}
